#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mycanvas.h"
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnRegenerate_clicked();

    void on_btnSolve_clicked();

    void getFocus();

private:
    Ui::MainWindow *ui;
    bool solved = false;
    QTimer* timer;
};

#endif // MAINWINDOW_H
