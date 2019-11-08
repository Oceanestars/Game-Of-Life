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
        set_current_status(true);
        qDebug("count");
    }
    else{
        color.setRgb(255, 255, 255);
        set_current_status(false);
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
    painter->setBrush(QBrush(color_));

    painter->drawRect(QRect(this->x_, this->y_, this->width_, this->width_));
    painter->setBrush(b);
}

Bar::Bar(int x, int y, int h) {

    x_ = x;
    y_ = y;
    height_ = -h; //without a negative I couldn't see the rectangle
    color_ = "white";

}

QRectF Bar::boundingRect() const
{
    return QRectF(x_, y_, width_, height_);
}

QPainterPath Bar::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, height_);
    return path;
}

//bar paint using QBrush
void Bar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    Q_UNUSED(widget)

    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_.dark(option->state & QStyle::State_Sunken ? 120 : 100)));

    painter->drawRect(this->x_, this->y_, this->width_, this->height_);
    painter->setBrush(b);
}

void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton){
        emit CellSelected(this);
        if(this->get_color() == QColor(242, 19, 131)){
            qDebug() << "Kill cell";
            this->set_color(QColor(255,255,255));
            emit decrease();
        }
    }
    else if(event->button() == Qt::LeftButton){
        if(this->get_color() == QColor(255, 255, 255)){
            qDebug() << "Ressurect Cell";
            this->set_color(QColor(242,19,131));
            emit increase();
        }
    }
    update();
}
