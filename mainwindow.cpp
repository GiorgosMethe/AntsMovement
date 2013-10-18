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
    this->sim.setWorldDim(sizeX, sizeY);
    this->renderAnts = true;
    this->renderExploration = true;
    this->renderFoodPheromone = true;
    this->renderHomePheromone = true;
    //end

    //initialize gui
    ui->setupUi(this);
    QImage rendering(sizeX, sizeY, QImage::Format_RGB16);
    rendering.fill(Qt::black);
    scene = new QGraphicsScene (this);
    QPixmap pixmap = QPixmap::fromImage(rendering);
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);

    QImage imageExplore(235, 175, QImage::Format_RGB16);
    imageExplore.fill(Qt::black);
    scene = new QGraphicsScene (this);
    scene1 = new QGraphicsScene (this);
    scene2 = new QGraphicsScene (this);
    scene3 = new QGraphicsScene (this);
    pixmap = QPixmap::fromImage(imageExplore);
    scene->addPixmap(pixmap);
    ui->graphicsView_4->setScene(scene);

    QImage imageHome(245, 195, QImage::Format_RGB16);
    imageHome.fill(Qt::black);
    scene = new QGraphicsScene (this);
    pixmap = QPixmap::fromImage(imageHome);
    scene->addPixmap(pixmap);
    ui->graphicsView_2->setScene(scene);

    QImage imageFood(245, 195, QImage::Format_RGB16);
    imageFood.fill(Qt::black);
    scene = new QGraphicsScene (this);
    pixmap = QPixmap::fromImage(imageFood);
    scene->addPixmap(pixmap);
    ui->graphicsView_3->setScene(scene);

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
    if(this->sim.world.isInitialized)
        timer->start(this->speed);
    else
    {
        timer->start(this->speed);
        this->sim.init();
        this->addItemToScene();
        this->sim.stepCount = 0;
    }
}

void MainWindow::addItemToScene()
{
    nest = new QGraphicsRectItem(nestX, nestY, nestSize, nestSize);
    nest->setBrush(QBrush(Qt::white));
    ui->graphicsView->scene()->addItem(nest);
    food = new QGraphicsRectItem(foodX, foodY , foodSize, foodSize);
    food->setBrush(QBrush(Qt::cyan));
    ui->graphicsView->scene()->addItem(food);
    for(unsigned int i = 0; i < this->sim.world.sampleSet.size(); ++i)
    {
        ant = new QGraphicsRectItem(this->sim.world.sampleSet.at(i).position.x(), this->sim.world.sampleSet.at(i).position.y(), sampleSize, sampleSize);
        ant->setBrush(QBrush(Qt::red));
        ui->graphicsView->scene()->addItem(ant);
    }
    return;
}

void MainWindow::moveItemToScene()
{
    for(int i = 0; i < ui->graphicsView->scene()->items().size(); ++i)
    {
        ui->graphicsView->scene()->items().pop_back();
    }
    this->rendering = QImage(sizeX, sizeY, QImage::Format_RGB16);
    this->rendering.fill(Qt::black);
    scene->clear();
    pixmap = QPixmap::fromImage(this->rendering);
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
    nest = new QGraphicsRectItem(nestX, nestY, nestSize, nestSize);
    nest->setBrush(QBrush(Qt::white));
    ui->graphicsView->scene()->addItem(nest);
    food = new QGraphicsRectItem(foodX, foodY , foodSize, foodSize);
    food->setBrush(QBrush(Qt::cyan));
    ui->graphicsView->scene()->addItem(food);
    for(unsigned int i = 0; i < this->sim.world.sampleSet.size(); ++i)
    {
        ant = new QGraphicsRectItem(this->sim.world.sampleSet.at(i).position.x(), this->sim.world.sampleSet.at(i).position.y(), sampleSize, sampleSize);
        ant->setBrush(QBrush(Qt::red));
        ui->graphicsView->scene()->addItem(ant);
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
    this->sim.world.destroyMap();
    timer->stop();
    this->rendering = QImage(sizeX, sizeY, QImage::Format_RGB16);
    this->rendering.fill(Qt::black);
    scene->clear();
    pixmap = QPixmap::fromImage(this->rendering);
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
    QGraphicsRectItem* nest = new QGraphicsRectItem(nestX, nestY, nestSize, nestSize);
    nest->setBrush(QBrush(Qt::white));
    ui->graphicsView->scene()->addItem(nest);
    QGraphicsRectItem* food = new QGraphicsRectItem(foodX, foodY , foodSize, foodSize);
    food->setBrush(QBrush(Qt::cyan));
    ui->graphicsView->scene()->addItem(food);

}

void MainWindow::update()
{
    if(this->sim.world.isInitialized)
    {
        std::cout << "simulation step: " << this->sim.stepCount << std::endl;
        this->sim.step();
        if(this->renderAnts)
            this->moveItemToScene();
    }
    if(this->renderExploration && this->sim.world.isInitialized)
    {
        this->imageExplore = QImage(235, 175, QImage::Format_RGB16);
        int dx = 2;
        int dy = 2;
        this->imageExplore.fill(Qt::black);
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
                    this->imageExplore.setPixel(ii,jj,qRgb(255,0,0));
                }

            }
        }
        pixmap = QPixmap::fromImage(this->imageExplore);
        scene3->clear();
        scene3->addPixmap(pixmap);
        ui->graphicsView_4->setScene(scene3);
    }

    if(this->renderFoodPheromone && this->sim.world.isInitialized)
    {
        this->imageFood = QImage(245, 195, QImage::Format_RGB16);
        int dx = 2;
        int dy = 2;
        this->imageFood.fill(Qt::black);
        for(int x = 0; x < sizeX; x+=dx)
        {
            for(int y = 0; y < sizeY; y+=dy)
            {
                if(this->sim.world.food_pheromone[x][y] > 0.00)
                {
                    double i = 0, j = 0;
                    i = 244.00 * ((x + 1.00) / sizeX);
                    int ii = round(i);
                    j = 194.00 * ((y + 1.00) / sizeY);
                    int jj = round(j);
                    double red = 255.0 * (this->sim.world.food_pheromone[x][y] / this->sim.max_food_pheromone);
                    int red_i = round(red);
                    if(red_i < 50) red_i = 50;
                    this->imageFood.setPixel(ii,jj,qRgb(red_i,red_i,red_i));
                }
            }
        }
        pixmap = QPixmap::fromImage(this->imageFood);
        scene1->clear();
        scene1->addPixmap(pixmap);
        ui->graphicsView_2->setScene(scene1);
    }

    if(this->renderHomePheromone && this->sim.world.isInitialized)
    {
        this->imageHome = QImage(245, 195, QImage::Format_RGB16);
        int dx = 2;
        int dy = 2;
        this->imageHome.fill(Qt::black);
        for(int x = 0; x < sizeX; x+=dx)
        {
            for(int y = 0; y < sizeY; y+=dy)
            {
                if(this->sim.world.home_pheromone[x][y] > 0.00)
                {
                    double i = 0, j = 0;
                    i = 244.00 * ((x + 1.00) / sizeX);
                    int ii = round(i);
                    j = 194.00 * ((y + 1.00) / sizeY);
                    int jj = ceil(j);
                    double blue = 255.0 * (this->sim.world.home_pheromone[x][y] / this->sim.max_home_pheromone);
                    int blue_i = round(blue);
                    if(blue_i < 10) blue_i = 10;
                    this->imageHome.setPixel(ii,jj,qRgb(blue_i,blue_i,blue_i));
                }
            }
        }
        pixmap = QPixmap::fromImage(this->imageHome);
        scene2->clear();
        scene2->addPixmap(pixmap);
        ui->graphicsView_3->setScene(scene2);
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
