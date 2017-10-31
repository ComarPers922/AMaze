#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    timer = new QTimer();
    ui->setupUi(this);
    timer->setInterval(30);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()),this,SLOT(getFocus()));
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnRegenerate_clicked()
{
    ui->myCanvas->Regenerate();
    ui->myCanvas->setFocus();
    solved = false;
}

void MainWindow::on_btnSolve_clicked()
{
    ui->myCanvas->setFocus();
    if(!solved)
    {
        ui->myCanvas->Solve();
        solved = true;
    }
}

void MainWindow::getFocus()
{
    ui->myCanvas->setFocus();
}
