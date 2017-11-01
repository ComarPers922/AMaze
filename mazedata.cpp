#include "mazedata.h"
#include <QtGlobal>
#include <ctime>
#include <QUuid>

MazeData::MazeData()
{
    auto id = QUuid::createUuid();
    qsrand(time(NULL) + id.toByteArray()[1] * id.toByteArray()[2] * + id.toByteArray()[3]);
    for(int i = 0 ; i < MazeData::height ; i ++)
    {
        for(int j = 0 ; j < MazeData::height ; j ++)
        {
            if(i%2 == 1 && j%2 == 1)
            {
                maze[i][j] = ROAD;
            }
            else
            {
                maze[i][j] = WALL;
            }
            visited[i][j] = false;
        }
    }
    maze[entranceX][entranceY] = ROAD;
    maze[exitX][exitY] = ROAD;
}

bool MazeData::inArea(int x, int y)
{
    return x >= 0 && x < height && y >= 0 && y < height;
}

void MazeData::reset()
{
    for(int i = 0 ; i < MazeData::height ; i ++)
    {
        for(int j = 0 ; j < MazeData::height ; j ++)
        {
            if(i%2 == 1 && j%2 == 1)
            {
                maze[i][j] = ROAD;
            }
            else
            {
                maze[i][j] = WALL;
            }
            visited[i][j] = false;
        }
    }
    maze[entranceX][entranceY] = ROAD;
    maze[exitX][exitY] = ROAD;
}
