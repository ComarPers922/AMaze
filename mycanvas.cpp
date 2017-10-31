#include "mycanvas.h"
#include <QPainter>
#include <QBrush>
#include <QColor>
#include <QRect>
#include <QtGlobal>
#include <ctime>
#include <QThread>

#define CUBE_HEIGHT 5
#define WALL_COLOR 51,153,255
#define ROAD_COLOR 255,255,255
#define PATH_COLOR 255,200,94
#define PLAYER_COLOR 0,0,0

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
                this->update();
            }
        }
    }
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
    this->update();
}
void MyCanvas::Solve()
{
    _Solve(myMaze.entranceX, myMaze.entranceY, myMaze.exitX, myMaze.exitY);
    this->update();
}

bool MyCanvas::_Solve(int startX, int startY, int endX, int endY)
{
    visited[startX][startY] = true;
    isPath[startX][startY] = true;
    if(startX == endX &&
       startY == endY)
    {
        return true;
    }
    for(int i = 0; i < 4; i ++)
    {
        int newX = startX + direction[i][0];
        int newY = startY + direction[i][1];

        if(myMaze.inArea(newX, newY)
                && !visited[newX][newY]
                && myMaze.maze[newX][newY] == ROAD)
        {
           if(_Solve(newX, newY, endX, endY))
           {
               return true;
           }
        }
    }
    isPath[startX][startY] = false;
    return false;
}

void MyCanvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QBrush wallBrush(QColor(WALL_COLOR));
    QBrush roadBrush(QColor(ROAD_COLOR));
    QBrush pathBrush(QColor(PATH_COLOR));
    QBrush playerBrush(QColor(PLAYER_COLOR));
    for(int i = 0; i < MazeData::height; i ++ )
    {
        for(int j = 0; j < MazeData::height; j ++)
        {
            painter.fillRect(QRect(i * CUBE_HEIGHT,
                                   j * CUBE_HEIGHT,
                                   CUBE_HEIGHT,CUBE_HEIGHT),
                                   myMaze.maze[i][j] == ROAD ? roadBrush : wallBrush);
            if(isPath[i][j])
            {
                painter.fillRect(QRect(i * CUBE_HEIGHT,
                                       j * CUBE_HEIGHT,
                                       CUBE_HEIGHT,CUBE_HEIGHT),
                                       pathBrush);
            }
        }
    }
    painter.fillRect(QRect(player.x * CUBE_HEIGHT,
                           player.y * CUBE_HEIGHT,
                           CUBE_HEIGHT,CUBE_HEIGHT),
                           playerBrush);
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
    this->update();
}
