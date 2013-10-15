#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonStart_clicked()
{

}

void MainWindow::on_pushButtonPause_clicked()
{

}

void MainWindow::on_pushButtonReset_clicked()
{

}

