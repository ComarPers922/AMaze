#include "mycanvas.h"
#include <QPainter>
#include <QBrush>
#include <QColor>
#include <QRect>
#include <QtGlobal>
#include <ctime>
#include <QThread>
#include <QLinkedList>
#include <QMessageBox>

#define CUBE_HEIGHT 5
#define WALL_COLOR 51,153,255
#define ROAD_COLOR 255,255,255
#define PATH_COLOR 255,200,94
#define PLAYER_COLOR 0,0,0
#define WALL_DESTROYER_COLOR 255,0,0

int direction[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
MyCanvas::MyCanvas(QWidget *parent) : QWidget(parent)
{
    qsrand(time(NULL));
    Regenerate();
    player.x = myMaze.entranceX;
    player.y = myMaze.entranceY;
}
void MyCanvas::Generate()
{
    myMaze.reset();
    RandomQueue<Position> queue;
    Position first(myMaze.entranceX + 1,
                   myMaze.entranceY);
    queue.add(first);
    myMaze.visited[first.x][first.y] = true;
    while(!queue.isEmpty())
    {
        auto currentPosition = queue.remove();
        for(int i = 0; i < 4; i ++)
        {
            int newX = currentPosition.x + direction[i][0]*2;
            int newY = currentPosition.y + direction[i][1]*2;

            if(myMaze.inArea(newX, newY)
                    && !myMaze.visited[newX][newY]
                    && myMaze.maze[newX][newY] == ROAD)
            {
                queue.add(Position(newX, newY));
                myMaze.visited[newX][newY] = true;
                myMaze.maze[currentPosition.x + direction[i][0]][currentPosition.y + direction[i][1]] = ROAD;
            }
        }
    }
        int numberOfDestroyedWall = MazeData::height * 5;
        for(int i = 0 ; i < numberOfDestroyedWall; i ++)
        {
            int x = qrand() % MazeData::height - 2;
            int y = qrand() % MazeData::height - 2;
            if(myMaze.inArea(x,y) && x > 1 && y > 1)
            {
                myMaze.maze[x][y] = ROAD;
            }
        }
        this->update();
}
void MyCanvas::Regenerate()
{
    for(int i = 0;i < MazeData::height; i ++)
    {
        for(int j = 0;j < MazeData::height; j ++)
        {
            visited [i][j] = false;
            isPath [i][j] = false;
        }
    }
    Generate();
    player.x = myMaze.entranceX;
    player.y = myMaze.entranceY;

    wallDestroyer.x = myMaze.entranceX + 1;
    wallDestroyer.y = myMaze.entranceY;
    this->update();
}
void MyCanvas::Solve()
{
    for(int i = 0;i < MazeData::height; i ++)
    {
        for(int j = 0;j < MazeData::height; j ++)
        {
            visited [i][j] = false;
            isPath [i][j] = false;
        }
    }
    bool isSolved = false;
     QLinkedList<Position*> queue;
     Position* entrance = new Position(myMaze.entranceX, myMaze.entranceY);
     queue.push_back(entrance);
     visited[entrance->x][entrance->y] = true;

     while(!queue.isEmpty()){
         Position* currentPosition = queue.front();
         queue.pop_front();

         if(currentPosition->x == myMaze.exitX && currentPosition->y == myMaze.exitY)
         {
             findPath(currentPosition);
             isSolved = true;
             break;
         }

         for(int i = 0 ; i < 4  ; i ++){
             int newX = currentPosition->x + direction[i][0];
             int newY = currentPosition->y + direction[i][1];

             if(myMaze.inArea(newX, newY)
                     && !visited[newX][newY]
                     && myMaze.maze[newX][newY]== ROAD)
             {
                 Position* nextPos = new Position(newX, newY);
                 nextPos->from = currentPosition;
                 queue.push_back(nextPos);
                 visited[newX][newY] = true;
             }
         }
     }
    if(!isSolved)
    {
        QMessageBox::information(this,"Failed to solve","Can not solve this maze!!!");
    }
    this->update();
}
void MyCanvas::findPath(Position* destination)
{

    Position* currentPosition = destination;
    while(currentPosition != nullptr)
    {
        isPath[currentPosition->x][currentPosition->y] = true;
        currentPosition = currentPosition->from;
    }
}

void MyCanvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QBrush wallBrush(QColor(WALL_COLOR));
    QBrush roadBrush(QColor(ROAD_COLOR));
    QBrush pathBrush(QColor(PATH_COLOR));
    QBrush playerBrush(QColor(PLAYER_COLOR));
    QBrush wallDestroyerBrush(QColor(WALL_DESTROYER_COLOR));
    for(int i = 0; i < MazeData::height; i ++ )
    {
        for(int j = 0; j < MazeData::height; j ++)
        {
            if(myMaze.maze[i][j] == ROAD)
            {
                painter.fillRect(QRect(i * CUBE_HEIGHT,
                                       j * CUBE_HEIGHT,
                                       CUBE_HEIGHT,CUBE_HEIGHT),
                                         roadBrush);
            }
            if(isPath[i][j])
            {
                painter.fillRect(QRect(i * CUBE_HEIGHT,
                                       j * CUBE_HEIGHT,
                                       CUBE_HEIGHT,CUBE_HEIGHT),
                                       pathBrush);
            }
            if(myMaze.maze[i][j] == WALL)
            {
                painter.fillRect(QRect(i * CUBE_HEIGHT,
                                       j * CUBE_HEIGHT,
                                       CUBE_HEIGHT,CUBE_HEIGHT),
                                       wallBrush);
            }
        }
    }
    painter.fillRect(QRect(player.x * CUBE_HEIGHT,
                           player.y * CUBE_HEIGHT,
                           CUBE_HEIGHT,CUBE_HEIGHT),
                           playerBrush);
    painter.fillRect(QRect(wallDestroyer.x * CUBE_HEIGHT,
                           wallDestroyer.y * CUBE_HEIGHT,
                           CUBE_HEIGHT,CUBE_HEIGHT),
                           wallDestroyerBrush);
}

void MyCanvas::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
        if(myMaze.inArea(player.x, player.y - 1) &&
                myMaze.maze[player.x][player.y - 1] == ROAD)
        {
            player.y -= 1;
        }
        break;
    case Qt::Key_Down:
        if(myMaze.inArea(player.x, player.y + 1) &&
                myMaze.maze[player.x][player.y + 1] == ROAD)
        {
            player.y += 1;
        }
        break;
    case Qt::Key_Left:
        if(myMaze.inArea(player.x - 1, player.y) &&
                myMaze.maze[player.x - 1][player.y] == ROAD)
        {
            player.x -= 1;
        }
        break;
    case Qt::Key_Right:
        if(myMaze.inArea(player.x + 1, player.y) &&
                myMaze.maze[player.x + 1][player.y] == ROAD)
        {
            player.x += 1;
        }
        break;
    default:
        break;
    }

    switch (event->key())
    {
    case Qt::Key_W:
        if(myMaze.inArea(wallDestroyer.x, wallDestroyer.y - 1))
        {
            wallDestroyer.y -= 1;
        }
        break;
    case Qt::Key_S:
        if(myMaze.inArea(wallDestroyer.x, wallDestroyer.y + 1))
        {
            wallDestroyer.y += 1;
        }
        break;
    case Qt::Key_A:
        if(myMaze.inArea(wallDestroyer.x - 1, wallDestroyer.y))
        {
            wallDestroyer.x -= 1;
        }
        break;
    case Qt::Key_D:
        if(myMaze.inArea(wallDestroyer.x + 1, wallDestroyer.y) )
        {
            wallDestroyer.x += 1;
        }
        break;
    case Qt::Key_Space:
        if(myMaze.maze[wallDestroyer.x][wallDestroyer.y] == WALL)
        {
            myMaze.maze[wallDestroyer.x][wallDestroyer.y] = ROAD;
        }
        break;
    case Qt::Key_M:
        if(myMaze.maze[wallDestroyer.x][wallDestroyer.y] == ROAD)
        {
            myMaze.maze[wallDestroyer.x][wallDestroyer.y] = WALL;
        }
        break;
    default:
        break;
    }
    this->update();
}
