#ifndef MAZEDATA_H
#define MAZEDATA_H
#include <QObject>

#define ROAD 'r'
#define WALL 'w'

class MazeData : QObject
{
    Q_OBJECT
public:
    MazeData();

    char maze[131][131];
    bool visited[131][131];
    bool inArea(int x, int y);
    void reset();

    static const int height = 131;

    const int entranceX = 0;
    const int entranceY = 1;
    const int exitX = 130;
    const int exitY = 129;
};

#endif // MAZEDATA_H
