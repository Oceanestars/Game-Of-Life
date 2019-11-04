#include "game.h"
#include "mainwindow.h"
#include <mainwindow.cpp>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtWidgets>
#include <QTimer>

Cell::Cell(int x, int y, int width, int height){
    QColor color(255, 0, 0);
    //randomly assign pink (alive) with 50% probability and white (dead) with 50% probability
    if(rand() % 100 < 50) {
        color.setRgb(242, 19, 131);
    }
    else{
        color.setRgb(255, 255, 255);
    }
    color_ = color;
    x_ = x * width; //since we are creating squares we need x and y to be more than simply a point
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

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget) //should not have a semi colon


    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_.dark(option->state & QStyle::State_Sunken ? 120 : 100)));

    painter->drawRect(QRect(this->x_, this->y_, this->width_, this->width_));
    painter->setBrush(b);
}

