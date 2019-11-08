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

    ui->label_5->setText(QString("Speed: ")+QString::number(speed_, 'f', 4));



    srand(time(0));
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 20; j++) {
            Cell * item = new Cell(j, i, cell_width_/20, cell_height_/10);
            cells[i][j] = item;
            BuildGrid_->addItem(item);
            if(item->get_color()== QColor(255, 255, 255))
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
    bar_height_=graph_view->frameSize().height();

    Bar* first_bar = new Bar(0, bar_height_, int(0.5 * bar_height_ ));
    //without the int we would have some rounding error(I believe)
    bars_.push_back(first_bar);
    BuildGraph_->addItem(first_bar);

    timer=new QTimer();

    connect(timer, &QTimer::timeout, this, &MainWindow::tick_slot);

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
    QColor color(255, 0, 0);
    Cell *current_cell=new Cell(21, 21, cell_width_/20, cell_height_/10);
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 20; j++) {
            current_cell = cells[i][j];
            if(NeighborsCount(i,j)<2)
            {

               // color.setRgb(255, 255, 255);
                current_cell->set_next_status(false);

            }
            else if(NeighborsCount(i,j)>3)
            {

               // color.setRgb(255, 255, 255);
                current_cell->set_next_status(false);

            }
            else
            {

               // color.setRgb(242, 19, 131);
                current_cell->set_next_status(true);
            }
        }
    }
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 20; j++) {
             Cell *current_cell=new Cell(j, i, cell_width_/20, cell_height_/10);
            if(current_cell->get_next_status()==true)
            {

                cells[i][j]->set_color(242, 19, 131);
                //color.setRgb(242, 19, 131);
                current_cell->set_current_status(true);
                if(pop_> 0)
                {
                    //PopCounter(1);
                }

            }

            if(current_cell->get_next_status()==false)
            {
                cells[i][j]->set_color(255, 255, 255);
                //color.setRgb(255, 255, 255);
                current_cell->set_current_status(false);
                if(pop_> 0)
                {
                    //PopCounter(-1);
                }
            }

        }
     }
    TurnCounter();
    BuildGrid_->update();

}
void MainWindow::PopCounter(int pop) {
    pop_ += pop;
    ui->label_2->setText(QString("Population: ")+QString::number(pop_)+QString(" (")+QString::number((pop_*100)/200)+QString("%)"));

}
void MainWindow::on_resetButton_clicked()
{
    BuildGrid_->clear();
    turn_=0;
    srand(time(0));
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 20; j++) {
            Cell * item = new Cell(j, i, cell_width_/20, cell_height_/10);
            cells[i][j] = item;
            BuildGrid_->addItem(item);
        }
    bars_.clear();
    }
}

void MainWindow::on_startButton_clicked()
{
    //this should only have the timer
    timer->start(1000);
}

void MainWindow::on_pauseButton_clicked()
{
    timer->stop();
}
void MainWindow::tick_slot()
{
    DeadOrAlive();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    speed_=value;
    ui->label_5->setText(QString("Speed: ")+QString::number(speed_, 'f', 4));

}

void MainWindow::on_stepButton_clicked()
{
    DeadOrAlive();
}
