#ifndef GAME_H
#define GAME_H

#include <QColor>
#include <QWidget>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QtWidgets>
#include <QObject>

class Cell : public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    Cell(int x, int y, int width, int height); //constructor

    int get_x() const { return x_; }  // inline member function
    int get_y() const { return y_; }  // inline member function
    int get_width() { return width_; }
    int get_height() { return height_; }
    QColor get_color() { return color_; }

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void set_color(QColor color){
        color_=color;
    }

private:
  int x_;
  int y_;
  int width_;
  int height_;

  QColor color_;

};
#endif // GAME_H
