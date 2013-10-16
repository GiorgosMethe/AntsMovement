#include "mainwindow.h"
#include "omp.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //initialization phase
    this->speed = 0;
    this->sim.setSampleNum(200);
    this->sim.setFoodPos(QPoint(200, 200));
    this->sim.setNestPos(QPoint(0, 0));
    this->sim.setWorldDim(300,250);
    this->renderAnts = true;
    this->renderValues = false;
    //end

    //initialize gui
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setFixedSize(600,500);
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);
    ui->graphicsView->setScene(scene);

    //
    QImage image(245, 195, QImage::Format_RGB16);
    image.fill(Qt::black);
    QGraphicsScene *scene = new QGraphicsScene (this);
    QPixmap pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);
    ui->graphicsView_2->setScene(scene);
    ui->graphicsView_3->setScene(scene);
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
    this->sim.init();
    this->addItemToScene(this->sim.world.sampleSet);
    this->sim.stepCount = 0;
}

void MainWindow::addItemToScene(std::vector<sample> samples)
{


    QGraphicsRectItem* nest = new QGraphicsRectItem(this->sim.nest.x(), this->sim.nest.y(), 20, 20);
    nest->setBrush(QBrush(Qt::black));
    ui->graphicsView->scene()->addItem(nest);
    QGraphicsRectItem* food = new QGraphicsRectItem(this->sim.food.x(), this->sim.food.y(), 20, 20);
    food->setBrush(QBrush(Qt::cyan));
    ui->graphicsView->scene()->addItem(food);
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
#pragma omp parallel private(8)
    {
#pragma omp for schedule(static) nowait
        for(unsigned int i = 0; i < samples.size(); ++i)
        {
            sample tmp = samples.at(i);
            int dx = tmp.position.x() - ui->graphicsView->scene()->items().at(tmp.id)->pos().x();
            int dy = tmp.position.y() - ui->graphicsView->scene()->items().at(tmp.id)->pos().y();
            ui->graphicsView->scene()->items().at(tmp.id)->moveBy(dx, dy);
        }
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
    if(this->sim.world.isInitialized)
    {
        std::cout << "simulation step: " << this->sim.stepCount << std::endl;
        this->sim.step();
        if(this->renderAnts)
            this->moveItemToScene(this->sim.world.sampleSet);
    }
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
