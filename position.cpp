#include "position.h"

Position::Position(int X, int Y):x(X), y(Y)
{

}
Position::~Position()
{
    delete from;
}
