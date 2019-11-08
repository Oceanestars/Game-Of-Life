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

    //Grid
    BuildGrid_ = new QGraphicsScene;
    QGraphicsView * grid_view = ui->MainPlot;
    grid_view->setScene(BuildGrid_);
    grid_view->setSceneRect(0,0,grid_view->frameSize().width(),grid_view->frameSize().height());

    cell_height_ = grid_view->frameSize().height();
    cell_width_ = grid_view->frameSize().width(); //no matter the number there is still a weird edge

    ui->label_5->setText(QString("Speed: ")+QString::number(speed_, 'f', 4));
    ui->label->setText(QString("Turn: 0"));
    ui->label_2->setText(QString("Population: 100 (50%)"));

    srand(time(0));
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 20; j++) {
            Cell * item = new Cell(j, i, cell_width_/20, cell_height_/10);
            cells[i][j] = item;
            BuildGrid_->addItem(item);
        }
    }
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

    //QTimer *timer2 =
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


int MainWindow::NeighborsCount(){

    int count_neighbors=0;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 20; j++) {
            if(j < 19){
                //neighbor to the right
                if(cells[i][j+1]->get_color()== QColor(242, 19, 131)){
                    //alive
                    count_neighbors++;
                 }
            }
            else if(j == 19){
                if(cells[i][0]->get_color() == QColor(242, 19, 131)){
                    //alive
                    count_neighbors++;
                }
            }
            if(j > 0){
                //neighbor to the left
                if(cells[i][j-1]->get_color()== QColor(242, 19, 131)){
                    count_neighbors++;
                 }
            }
            else if(j == 0){
                if(cells[i][19]->get_color()== QColor(242, 19, 131)){
                    count_neighbors++;
                }
            }
            if(i < 9){
                //neighbor underneath
                if(cells[i+1][j]->get_color()== QColor(242, 19, 131)){
                    count_neighbors++;
                }
            }
            else if(i == 9){
                if(cells[0][j]->get_color()== QColor(242, 19, 131)){
                    count_neighbors++;
                }
            }

            if(i > 0){
                //neighbor Above
                if(cells[i-1][j]->get_color()== QColor(242, 19, 131)){
                    count_neighbors++;
                }
            }
            else if(i == 0){
                if(cells[9][j]->get_color()== QColor(242, 19, 131)){
                    count_neighbors++;
                }
            }
            if(i > 0 && j < 19){
                //upper right neighbor
                if(cells[i-1][j+1]->get_color()== QColor(242, 19, 131)){
                    count_neighbors++;
                }
            }
            else if(i == 0){
                if(j < 19){
                    if(cells[9][j+1]->get_color()== QColor(242, 19, 131)){
                        count_neighbors++;
                    }
                }
                else{
                    if(cells[9][0]->get_color()== QColor(242, 19, 131)){
                        count_neighbors++;
                    }
                }
            }
            else if(j == 19 && i > 0){
                if(cells[i-1][0]->get_color()== QColor(242, 19, 131)){
                    count_neighbors++;
                }
            }
            if(i < 9 && j <19){
                //lower right neighbor
                if(cells[i+1][j+1]->get_color()== QColor(242, 19, 131)){
                    count_neighbors++;
                }
            }
            else if(i == 9){
                if(j < 19){
                    if(cells[0][j+1]->get_color()== QColor(242, 19, 131)){
                        count_neighbors++;
                    }
                }
                else{
                    if(cells[0][0]->get_color()== QColor(242, 19, 131)){
                        count_neighbors++;
                    }
                }
            }
            else if(i < 9 && j == 19){
                if(cells[i+1][0]->get_color()== QColor(242, 19, 131)){
                    count_neighbors++;
                }
            }
            if(i > 0 && j > 0){
                //upper left neighbor
                if(cells[i-1][j-1]->get_color()== QColor(242, 19, 131)){
                    count_neighbors++;
                }
            }
            else if(j == 0){
                if(i > 0){
                    if(cells[i-1][19]->get_color()== QColor(242, 19, 131)){
                        count_neighbors++;
                    }
                }
                else{
                    if(cells[9][19]->get_color()== QColor(242, 19, 131)){
                        count_neighbors++;
                    }
                }
            }
            else if(j > 0){
                if(cells[9][j-1]->get_color()== QColor(242, 19, 131)){
                    count_neighbors++;
                }
            }
            if(i < 9 && j > 0){
                //lower left neighbor
                if(cells[i+1][j-1]->get_color()== QColor(242, 19, 131)){
                    count_neighbors++;
                }
            }
            else if (j == 0){
                if (i < 9){
                    if(cells[i+1][19]->get_color()== QColor(242, 19, 131)){
                        count_neighbors++;
                    }
                }
                else{
                    if(cells[0][19]->get_color()== QColor(242, 19, 131)){
                        count_neighbors++;
                    }
                }
            }
            else if (i == 9) {
                if(cells[0][j-1]->get_color()== QColor(242, 19, 131)){
                    count_neighbors++;
                }
            }
            qDebug() << count_neighbors;
        }
     }
    return count_neighbors;
}

void MainWindow::DeadOrAlive(){
//This will call countneighbors ,this is the function where we apply
//the four rules and where we determine if the cell is dead or alive
     QColor color(255, 0, 0);
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 20; j++) {
            Cell *current_cell=new Cell(j, i, cell_width_/20, cell_height_/10);

            if(NeighborsCount()<2)
            {

               // color.setRgb(255, 255, 255);
                current_cell->set_next_status(false);
            }
            if(NeighborsCount()>3)
            {

               // color.setRgb(255, 255, 255);
                current_cell->set_next_status(false);
            }
            if(NeighborsCount()==2 || NeighborsCount()==3)
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
                color.setRgb(242, 19, 131);
                current_cell->set_current_status(true);
            }

            if(current_cell->get_next_status()==false)
            {
                color.setRgb(255, 255, 255);
                current_cell->set_current_status(false);
            }

        }
     }
    BuildGrid_->update();

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
