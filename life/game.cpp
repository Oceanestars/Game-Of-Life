/**
Abby Nay & Oceane Andreis
Homework 4
Date: November 3 2019

This is our game.cpp.
We are including QGraphicsScene, QTimer, QGraphicsItem, QGraphicsView, QtWidget,and QDebug so we can
access elements of its library.
We have implemented our class Cell and our class bar.

*/

#include "game.h"
#include "mainwindow.h"
#include <mainwindow.cpp>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtWidgets>
#include <QTimer>

/**
Cell::Cell constructor. Takes 4 parameters to set the location and size of the cells we will put on our grid.
Randomly assigns a color to the cell, with 50% probability it will be assigned pink (alive) and the other 50%
it is assigned white (dead).
@param x
@param y
@param width
@param height
@return nothing
*/
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

/**
 * Draws the outline for the cells so that we can contain our cells within a square.
 * @param nothing
 * @return the rectangle we drew
 */
QRectF Cell::boundingRect() const
{
    return QRectF(x_, y_, width_, width_);
}

/**
 * we draw the shape of the cell that we can add to the grid
 * @return the shape of the cell
 */
QPainterPath Cell::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, width_);
    return path;
}

/**
 * Takes in graphics parameters to paint the cell the color we have assigned it in the constructor.
 * This also repaints our cells when they die/repopulate.
 * @param painter
 * @param option
 * @param widget
 * @return nothing
 */
void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget) //should not have a semi colon


    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_));

    painter->drawRect(QRect(this->x_, this->y_, this->width_, this->width_));
    painter->setBrush(b);
}

/**
 * set the bar, constructor that returns nothing. Makes the bar filled in white.
 * @param x
 * @param y
 * @param h
 * @return nothing
 */
Bar::Bar(const int x, const int y, int h) {

    x_ = x;
    y_ = y;
    height_ = -h; //without a negative I couldn't see the rectangle
    color_ = "white";

}

/**
 * Sets the outline of the rectangle for the bar graph.
 * @return rectangle outline
 */
QRectF Bar::boundingRect() const
{
    return QRectF(x_, y_, width_, height_);
}

/**
 * sets the shape of the bar/rectangle using the painter so we can see it on the graphics item
 * @return the shape of the bar
 */
QPainterPath Bar::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, height_);
    return path;
}

/**
 * fill in the bar graph with the color we set in the constructor (white) so we can see it on the graphics scene
 * @param painter
 * @param option
 * @param widget
 */
void Bar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    Q_UNUSED(widget);

    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_.dark(option->state & QStyle::State_Sunken ? 120 : 100)));

    painter->drawRect(this->x_, this->y_, this->width_, this->height_);
    painter->setBrush(b);
}
/**
 * For shift click we emit a signal telling the mainwindow to tell the user how many neighbors that cell has.
 * For right click if the cell is alive we emit a signal to decrease the population and we set the cell to the dead color.
 * For left click if the cell is dead we emit a signal to increase the population and we set the cell to the alive color.
 * @param event
 */
void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //shift
    if(event->modifiers() == Qt::ShiftModifier)
    {
        int x = this->get_x()/30;
        int y = this->get_y()/30;
        emit neighbors(x,y);
        return;

    }


    if(event->button() == Qt::RightButton){
        if(this->get_color() == QColor(242, 19, 131)){

            qDebug() << "Kill cell";
            this->set_color(QColor(255,255,255));
            emit decrease();
            //emit CellSelected(this);
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
