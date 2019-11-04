#include "game.h"
#include "mainwindow.h"
#include <mainwindow.cpp>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>

Cell::Cell(int x, int y, int width, int height){
    QColor color(255, 0, 0);
    if(rand() % 100 < 50) {
        color.setRgb(242, 19, 131);
    }
    else{
        color.setRgb(255, 255, 255);
    }
    color_ = color;
    x_ = x * width;
    y_ = y * height;
    width_ = width;
    height_ = height;
}

QRectF Cell::boundingRect() const
{
    return QRectF(x_, y_, width_, width_);
}

QPainterPath Cell::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, width_);
    return path;
}

