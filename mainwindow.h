#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QtCore>
#include <QtGui>
#include <math.h>
#include <QTimer>
#include "sample.h"
#include "grid.h"
#include "simulation.h"
#include "ui_mainwindow.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QTimer>
#include <QPoint>
#include <iostream>
#include <vector>
#include "simulationVariables.h"

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

    void on_checkBox_3_clicked(bool checked);

    void on_checkBox_4_clicked(bool checked);

#if _WIN32
    int round(double value)
    {
        return floor(value+0.5);
    }
#endif

    void on_checkBox_5_clicked(bool checked);

    void on_checkBox_6_clicked(bool checked);

private:
    QImage imageExplore;
    QImage rendering;
    QImage imageFood;
    QImage imageHome;
    QPixmap pixmap;
    QGraphicsRectItem* ant;
    QGraphicsRectItem* nest;
    QGraphicsRectItem* food;
    void moveItemToScene();
    void addItemToScene();
    void updateRendering();
    simulation sim;
    bool renderAnts;
    bool renderExploration;
    bool renderHomePheromone;
    bool renderFoodPheromone;
    bool _evaporation;
    bool _diffusion;
    QTimer *timer;
    int speed;
    unsigned int antNum;
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsScene *scene1;
    QGraphicsScene *scene2;
    QGraphicsScene *scene3;
    QGraphicsPixmapItem *image;
    QGraphicsRectItem *rectangle;
    QGraphicsEllipseItem *ellipse;

};

#endif // MAINWINDOW_H
