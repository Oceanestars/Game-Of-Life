#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "game.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *BuildGrid_;
    QGraphicsScene *BuildGraph_;
    int cell_height_;
    int cell_width_;
    int turn_ = 0;
    double speed_ = 1.0;
    Cell * cells[10][20];

};
#endif // MAINWINDOW_H
