#include "mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //initialization phase
    this->speed = 0;
    this->sim.setSampleNum(200);
    this->sim.stepCount = 0;
    this->sim.setFoodPos(QPoint(foodX, foodY));
    this->sim.setNestPos(QPoint(nestX, nestY));
    this->sim.setWorldDim(sizeX / 2, sizeY / 2);
    this->renderAnts = true;
    this->renderExploration = false;
    //end

    //initialize gui
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setFixedSize(sizeX, sizeY);
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);
    ui->graphicsView->setScene(scene);


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
    QGraphicsRectItem* nest = new QGraphicsRectItem(nestX, nestY, nestSize, nestSize);
    nest->setBrush(QBrush(Qt::black));
    ui->graphicsView->scene()->addItem(nest);
    QGraphicsRectItem* food = new QGraphicsRectItem(foodX, foodY, foodSize, foodSize);
    food->setBrush(QBrush(Qt::cyan));
    ui->graphicsView->scene()->addItem(food);
    for(unsigned int i = 0; i < samples.size(); ++i)
    {
        QGraphicsRectItem* item1 = new QGraphicsRectItem(samples.at(i).position.x(), samples.at(i).position.y(), sampleSize, sampleSize);
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

    if(this->sim.world.isInitialized)
    {
        std::cout << "simulation step: " << this->sim.stepCount << std::endl;
        this->sim.step();
        if(this->renderAnts)
            this->moveItemToScene(this->sim.world.sampleSet);
    }

    if(this->renderExploration && this->sim.world.isInitialized)
    {
        QImage imageFood(235, 175, QImage::Format_RGB16);
        int dx = 2;
        int dy = 2;
        imageFood.fill(Qt::black);
        for(int x = 0; x < sizeX; x+=dx)
        {
            for(int y = 0; y < sizeY; y+=dy)
            {
                if(this->sim.world.explored[x][y])
                {
                    double i = 0, j = 0;
                    i = 235.00 * ((x + 1.00) / sizeX);
                    int ii = round(i);
                    j = 175.00 * ((y + 1.00) / sizeY);
                    int jj = round(j);
                    imageFood.setPixel(ii,jj,qRgb(255,0,0));
                }

            }
        }
        scene = new QGraphicsScene (this);
        QPixmap pixmap = QPixmap::fromImage(imageFood);
        scene->addPixmap(pixmap);
        ui->graphicsView_4->setScene(scene);
    }

    if(this->renderFoodPheromone && this->sim.world.isInitialized)
    {
        QImage imageFood(245, 195, QImage::Format_RGB16);
        int dx = 2;
        int dy = 2;
        imageFood.fill(Qt::black);
        for(int x = 0; x < sizeX; x+=dx)
        {
            for(int y = 0; y < sizeY; y+=dy)
            {
                double i = 0, j = 0;
                i = 244.00 * ((x + 1.00) / sizeX);
                int ii = round(i);
                j = 194.00 * ((y + 1.00) / sizeY);
                int jj = round(j);
                double red = 255.0 * (this->sim.world.food_pheromone[x][y] / this->sim.max_food_pheromone);
                int red_i = round(red);
                imageFood.setPixel(ii,jj,qRgb(red_i,0,0));
            }
        }
        scene = new QGraphicsScene (this);
        QPixmap pixmap = QPixmap::fromImage(imageFood);
        scene->addPixmap(pixmap);
        ui->graphicsView_2->setScene(scene);
    }

    if(this->renderHomePheromone && this->sim.world.isInitialized)
    {
        QImage imageHome(245, 195, QImage::Format_RGB16);
        int dx = 2;
        int dy = 2;
        imageHome.fill(Qt::black);
        for(int x = 0; x < sizeX; x+=dx)
        {
            for(int y = 0; y < sizeY; y+=dy)
            {
                double i = 0, j = 0;
                i = 244.00 * ((x + 1.00) / sizeX);
                int ii = round(i);
                j = 194.00 * ((y + 1.00) / sizeY);
                int jj = ceil(j);
                double blue = 255.0 * (this->sim.world.food_pheromone[x][y] / this->sim.max_food_pheromone);
                int blue_i = round(blue);
                imageHome.setPixel(ii,jj,qRgb(0,0,blue_i));
            }
        }
        scene = new QGraphicsScene (this);
        QPixmap pixmap = QPixmap::fromImage(imageHome);
        scene->addPixmap(pixmap);
        ui->graphicsView_3->setScene(scene);
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

// render exploration
void MainWindow::on_checkBox_2_clicked(bool checked)
{
    this->renderExploration = checked;
}

//render food pheromone
void MainWindow::on_checkBox_3_clicked(bool checked)
{
    this->renderFoodPheromone = checked;
}

//render home pheromone
void MainWindow::on_checkBox_4_clicked(bool checked)
{
    this->renderHomePheromone = checked;
}
