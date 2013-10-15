#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QtCore>
#include <QtGui>
#include <QTimer>
#include <sample.h>
#include "grid.h"
#include "simulation.h"
#include "ui_mainwindow.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QTimer>
#include <QPoint>
#include <iostream>
#include <vector>

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

    void on_pushButtonStart_clicked();

    void on_pushButtonPause_clicked();

    void on_pushButtonReset_clicked();

    void update();

    void on_horizontalSlider_valueChanged(int value);

    void on_spinBox_valueChanged(int arg1);

    void on_checkBox_clicked(bool checked);

    void on_checkBox_2_clicked(bool checked);

private:
    void moveItemToScene(std::vector<sample> samples);
    void addItemToScene(std::vector<sample> samples);
    simulation sim;
    bool renderAnts;
    bool renderValues;
    QTimer *timer;
    int speed;
    unsigned int antNum;
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *rectangle;
    QGraphicsEllipseItem *ellipse;

};

#endif // MAINWINDOW_H
