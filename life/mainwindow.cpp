/**
Abby Nay & Oceane Andreis
Homework 4
Date: November 3 2019

This is our mainwindow.cpp.
We are including QGraphicsScene, QGraphicsView, and QDebug so we can
access elements of its library.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    turn_=0;
    QColor color(255, 0, 0);
    //Grid
    BuildGrid_ = new QGraphicsScene;
    QGraphicsView * grid_view = ui->MainPlot;
    grid_view->setScene(BuildGrid_);
    grid_view->setSceneRect(0,0,grid_view->frameSize().width(),grid_view->frameSize().height());

    cell_height_ = grid_view->frameSize().height();
    cell_width_ = grid_view->frameSize().width(); //no matter the number there is still a weird edge

    ui->label_5->setText(QString("Speed: ")+QString::number(speed_, 'f', 6));

    srand(time(0));
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 20; j++) {
            Cell * item = new Cell(j, i, cell_width_/20, cell_height_/10);
            cells[i][j] = item;
            BuildGrid_->addItem(item);
            if(item->get_color()== QColor(242, 19, 131))
            {
                PopCounter(1);
            }
        }
    }
    ui->label->setText(QString("Turn: ")+QString::number(turn_));
    ui->label_2->setText(QString("Population: ")+QString::number(pop_)+ QString(" (") + QString::number(( pop_*100 )/200 ) + QString("%)" ));
    //Graph

    BuildGraph_ = new QGraphicsScene;
    QGraphicsView * graph_view = ui->MainPlot_2;
    graph_view->setScene(BuildGraph_);
    graph_view->setSceneRect(0,0,graph_view->frameSize().width(),graph_view->frameSize().height());
    double pop_percent = (double(pop_) /200.0);
    y_bar=graph_view->frameSize().height()-2;
    h_bar = graph_view->frameSize().height() ;
    Bar* first_bar = new Bar(0, y_bar, int(pop_percent * h_bar));
    //without the int we would have some rounding error(I believe)
    bars_.push_back(first_bar);
    BuildGraph_->addItem(first_bar);

    timer=new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(on_startButton_clicked()));

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TurnCounter()
{
    turn_++;
    ui->label->setText(QString("Turn: ")+QString::number(turn_));
}

//Check if a cell is alive or not, if alive return true, if not return false
bool MainWindow::Alive(int i, int j){
    if(cells[i][j]->get_color()== QColor(242, 19, 131)){
        return true;
    }
    return false;
}

//checks the neighbors by counting the cells around
//call the Alive function for count, since a return of true is 1, then if we simply add the ones and zeros of the boolean
//function, then we will end up with a count of how many alive neighbors each cell has.
int MainWindow::NeighborsCount(int i, int j){

    int count_neighbors=0;
    //upper left
    if(i==0 && j==0){
        count_neighbors += Alive(0,1)+Alive(1,0)+Alive(1,1)+Alive(0,19)+Alive(1,19)+Alive(9,0)+Alive(9,1)+Alive(9,19);
    }
    //upper right
    else if(i==0 && j==19){
        count_neighbors += Alive(0,18)+Alive(1,18)+Alive(1,19)+Alive(0,0)+Alive(1,0)+Alive(9,18)+Alive(9,19)+Alive(9,0);
    }
    //lower left
    else if(i==9 && j==0){
        count_neighbors += Alive(8,19)+Alive(8,0)+Alive(8,1)+Alive(9,19)+Alive(9,1)+Alive(0,19)+Alive(0,0)+Alive(0,1);
    }
    //lower right
    else if(i==9 && j==19){
        count_neighbors += Alive(8,18)+Alive(8,19)+Alive(8,0)+Alive(9,18)+Alive(9,0)+Alive(0,18)+Alive(0,19)+Alive(0,0);
    }
    //first row
    else if(i == 0){
        count_neighbors += Alive(9,j-1)+Alive(9,j)+Alive(9,j+1)+Alive(i,j-1)+Alive(i,j+1)+Alive(i+1,j-1)+Alive(i+1,j)+Alive(i+1,j+1);
    }
    //last row
    else if(i == 9){
        count_neighbors += Alive(0,j-1)+Alive(0,j)+Alive(0,j+1)+Alive(i,j-1)+Alive(i,j+1)+Alive(i-1,j-1)+Alive(i-1,j)+Alive(i-1,j+1);
    }
    //first column
    else if(j == 0){
        count_neighbors += Alive(i-1,19)+Alive(i,19)+Alive(i+1,19)+Alive(i-1,j)+Alive(i+1,j)+Alive(i-1,j+1)+Alive(i,j+1)+Alive(i+1,j+1);
    }
    //last column
    else if(j == 19){
        count_neighbors += Alive(i-1,0)+Alive(i,0)+Alive(i+1,0)+Alive(i-1,j)+Alive(i+1,j)+Alive(i-1,j-1)+Alive(i,j-1)+Alive(i+1,j-1);
    }
    else{
        count_neighbors += Alive(i-1,j-1)+Alive(i-1,j)+Alive(i-1,j+1)+Alive(i,j-1)+Alive(i,j+1)+Alive(i+1,j-1)+Alive(i+1,j)+Alive(i+1,j+1);
    }
    return count_neighbors;
}

void MainWindow::DeadOrAlive(){
    //This will call countneighbors ,this is the function where we apply
    //the four rules and where we determine if the cell is dead or alive
    QColor colors[10][20];
    int count_neighbors = 0;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 20; j++) {

            count_neighbors = NeighborsCount(i,j);
            //if the cell is dead we test to see if there are enough neighbors to reproduce
            if(cells[i][j]->get_color() == QColor(255, 255, 255)){
                if(count_neighbors == 3) {
                    colors[i][j] = QColor(242, 19, 131);
                    pop_++;
                }
                else {
                    colors[i][j] = QColor(255, 255, 255);
                }
            }
            //if the cell is alive we test to see if there are too many neighbors or too little to reproduce
            else{
                if(count_neighbors < 2) {
                    colors[i][j] = QColor(255, 255, 255);
                    pop_--;
                }
                else if(count_neighbors >= 2 && count_neighbors < 4) {
                    colors[i][j] = QColor(242, 19, 131);
                }
                else {
                    colors[i][j] = QColor(255, 255, 255);
                    pop_--;
                }
            }
        }
    }
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 20; j++) {
            cells[i][j]->set_color(colors[i][j]);
        }
    }
    BuildGrid_->update();
    if (pop_ < 0){
        pop_ = 0;
    }
    PopCounter(0);
      double pop_percent = (double(pop_) /200.0);
    //bar
    //so we can move everything to the left
    if (bars_.size() > 20) {  // 600/30 = 20
        int prev = 0;
       //for ( for_range_declaration : expression ) statement;
        for (Bar* bar : bars_) {
            bar->set_x(-1 * bar->get_w()); // set each bar back -1 bar
            prev = bar->get_x();
        }
        Bar* bar = new Bar(prev+30 , y_bar, int(pop_percent * h_bar));
        bars_.push_back(bar);
        BuildGraph_->addItem(bar);

    }
    //add the bars to the right
    else {
       Bar* bar = new Bar((turn_*30)+30, y_bar, int(pop_percent * h_bar));
       bars_.push_back(bar);
       BuildGraph_->addItem(bar);
    }

    BuildGraph_->update();
    TurnCounter();

}
void MainWindow::PopCounter(int pop) {
    pop_ += pop;
    ui->label_2->setText(QString("Population: ")+QString::number(pop_)+QString(" (")+QString::number((pop_*100)/200)+QString("%)"));

}
void MainWindow::on_resetButton_clicked()
{
    BuildGrid_->clear();
    BuildGraph_->clear();
    BuildGraph_->update();
    turn_=0;
    pop_=0;
    srand(time(0));
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 20; j++) {
            Cell * item = new Cell(j, i, cell_width_/20, cell_height_/10);
            cells[i][j] = item;
            BuildGrid_->addItem(item);
            if(item->get_color()== QColor(242, 19, 131))
            {
                PopCounter(1);
            }
        }
    }
    bars_.clear();
    double pop_percent = (double(pop_) /200.0);
    Bar* first_bar = new Bar(0, 98, int(pop_percent * 100));
    //without the int we would have some rounding error(I believe)
    bars_.push_back(first_bar);
    BuildGraph_->addItem(first_bar);

}

void MainWindow::on_startButton_clicked()
{
    DeadOrAlive();
    timer->start(speed_*1000.0);
}

void MainWindow::on_pauseButton_clicked()
{
    timer->stop();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    speed_=1-(value/100.0);
    ui->label_5->setText(QString("Speed: ")+QString::number(speed_, 'f', 6));

}

void MainWindow::on_stepButton_clicked()
{
    DeadOrAlive();
}
