#ifndef MYCANVAS_H
#define MYCANVAS_H

#include <QWidget>
#include <QPaintEvent>
#include "mazedata.h"
#include "randomqueue.h"

class MyCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit MyCanvas(QWidget *parent = 0);
    void Regenerate();

signals:

public slots:
protected:
    virtual void paintEvent(QPaintEvent *);
private:
    MazeData myMaze;
    void Generate();
};

#endif // MYCANVAS_H
