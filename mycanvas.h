#ifndef MYCANVAS_H
#define MYCANVAS_H

#include <QWidget>
#include <QPaintEvent>
#include "mazedata.h"
#include "randomqueue.h"
#include "position.h"

class MyCanvas : public QWidget
{
    Q_OBJECT
private:
    bool visited[MazeData::height][MazeData::height];
    bool isPath[MazeData::height][MazeData::height];
public:
    explicit MyCanvas(QWidget *parent = 0);
    void Regenerate();
    void Solve();

signals:

public slots:
protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void keyPressEvent(QKeyEvent * event);
private:
    MazeData myMaze;
    Position player;
    bool _Solve(int startX, int startY, int endX, int endY);
    void Generate();
};

#endif // MYCANVAS_H
