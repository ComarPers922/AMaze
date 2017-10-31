#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnRegenerate_clicked()
{
    ui->myCanvas->Regenerate();
    solved = false;
}

void MainWindow::on_btnSolve_clicked()
{
    if(!solved)
    {
        ui->myCanvas->Solve();
        solved = true;
    }
}
