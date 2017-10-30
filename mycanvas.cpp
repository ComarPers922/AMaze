#include "mycanvas.h"
#include <QPainter>
#include <QBrush>
#include <QColor>
#include <QRect>
#include <QtGlobal>
#include <ctime>
#include <QThread>

#include "randomqueue.h"
#include "position.h"

#define CUBE_HEIGHT 5
#define WALL_COLOR 51,153,255
#define PATH_COLOR 255,255,255
int direction[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
MyCanvas::MyCanvas(QWidget *parent) : QWidget(parent)
{
    qsrand(time(NULL));
    Regenerate();
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
    Generate();
    this->update();
}
void MyCanvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QBrush blackBrush(QColor(WALL_COLOR));
    QBrush whiteBrush(QColor(PATH_COLOR));
    for(int i = 0; i < MazeData::height; i ++ )
    {
        for(int j = 0; j < MazeData::height; j ++)
        {
            painter.fillRect(QRect(i * CUBE_HEIGHT,
                                   j * CUBE_HEIGHT,
                                   CUBE_HEIGHT,CUBE_HEIGHT),
                                   myMaze.maze[i][j] == ROAD ? whiteBrush : blackBrush);
        }
    }
}
