#ifndef POSITION_H
#define POSITION_H


class Position
{
public:
    Position(int X = 0, int Y = 0);
    int x, y;
    Position* from = nullptr;
    ~Position();
};

#endif // POSITION_H
