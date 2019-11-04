#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    turn_=0;

    BuildGrid_ = new QGraphicsScene;
    QGraphicsView * grid_view = ui->MainPlot;
    grid_view->setScene(BuildGrid_);
    grid_view->setSceneRect(0,0,grid_view->frameSize().width(),grid_view->frameSize().height());

    BuildGraph_ = new QGraphicsScene;
    QGraphicsView * graph_view = ui->MainPlot_2;
    graph_view->setScene(BuildGraph_);
    graph_view->setSceneRect(0,0,graph_view->frameSize().width(),graph_view->frameSize().height());

    cell_height_ = grid_view->frameSize().height();
    cell_width_ = grid_view->frameSize().width()+100 ; //no matter the number there is still a weird edge
    //20x10
    for(int i = 0; i < grid_view->frameSize().width(); i = i + cell_width_/20) {
        BuildGrid_->addLine(i, 0, i, cell_height_);
    }
    for(int i = 0; i < grid_view->frameSize().height(); i = i + cell_height_/10) {
        BuildGrid_->addLine(0, i, cell_width_, i);
    }
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
}
MainWindow::~MainWindow()
{
    delete ui;
}

