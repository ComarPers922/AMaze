#ifndef MAZEDATA_H
#define MAZEDATA_H
#include <QObject>

#define ROAD 'r'
#define WALL 'w'
#define HEIGHT 141
class MazeData : QObject
{
    Q_OBJECT
public:
    MazeData();

    char maze[HEIGHT][HEIGHT];
    bool visited[HEIGHT][HEIGHT];
    bool inArea(int x, int y);
    void reset();

    static const int height = HEIGHT;

    const int entranceX = 0;
    const int entranceY = 1;
    const int exitX = HEIGHT - 1;
    const int exitY = HEIGHT - 2;
};

#endif // MAZEDATA_H
