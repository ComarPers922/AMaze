#include "mazedata.h"
#include <QtGlobal>
#include <ctime>

MazeData::MazeData()
{
    qsrand(time(NULL));
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
