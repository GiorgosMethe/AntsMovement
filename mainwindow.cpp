#include "mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //initialization phase
    this->speed = 20;
    this->antNum = 200;
    this->renderAnts = true;
    this->renderValues = false;
    //end

    //initialize gui
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    //end

    //set up timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(this->speed);
    //end


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonStart_clicked()
{
    timer->start(this->speed);
    this->sim.init(this->antNum, ui->graphicsView->width(), ui->graphicsView->height(), QPoint(0, 0));
    this->addItemToScene(this->sim.world.sampleSet);
}

void MainWindow::addItemToScene(std::vector<sample> samples)
{
    for(unsigned int i = 0; i < samples.size(); ++i)
    {
        QGraphicsRectItem* item1 = new QGraphicsRectItem(samples.at(i).position.x(), samples.at(i).position.y(), 3, 3);
        item1->setBrush(QBrush(Qt::red));
        ui->graphicsView->scene()->addItem(item1);
    }
    return;
}

void MainWindow::moveItemToScene(std::vector<sample> samples)
{
    for(unsigned int i = 0; i < samples.size(); ++i)
    {
        sample tmp = samples.at(i);
        int dx = tmp.position.x() - ui->graphicsView->scene()->items().at(tmp.id)->pos().x();
        int dy = tmp.position.y() - ui->graphicsView->scene()->items().at(tmp.id)->pos().y();
        ui->graphicsView->scene()->items().at(tmp.id)->moveBy(dx, dy);
    }
    return;
}

void MainWindow::on_pushButtonPause_clicked()
{
    timer->stop();
}

void MainWindow::on_pushButtonReset_clicked()
{
    //end simulation
    this->sim.~simulation();
}

void MainWindow::update()
{
    this->sim.step();
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    timer->stop();
    timer->start(20-value);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    this->antNum = arg1;
}

// render ants
void MainWindow::on_checkBox_clicked(bool checked)
{
    this->renderAnts = checked;

}

// render values
void MainWindow::on_checkBox_2_clicked(bool checked)
{
    this->renderValues = checked;
}
