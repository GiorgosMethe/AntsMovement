#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QtGui>
#include <QtCore>
#include "map.h"

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

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *rectangle;
    QGraphicsEllipseItem *ellipse;

};

#endif // MAINWINDOW_H
