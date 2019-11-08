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
    int get_current_status() { return current_status; }
    int get_next_status() { return next_turn_status; }
    int get_height() { return height_; }
    QColor get_color() { return color_; }

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    void set_current_status(bool current_status_){current_status=current_status_;}
    void set_next_status(bool next_turn_status_){next_turn_status=next_turn_status_;}
    void set_color(QColor color){
        color_=color;
    }

private:
  int x_;
  int y_;
  int width_;
  int height_;
  bool current_status;
  bool next_turn_status;

  QColor color_;

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

};

class Bar : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    Bar(int x, int y, int h);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    static int get_w() { return width_; }  // inline member function
     int get_x() { return x_; }  // inline member function

    void set_x(int offset) { x_ = x_ + offset; } //inline setter
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

private:
    int x_;
    int y_;

    QColor color_;

    static const int width_ = 30; //600/20
    int height_;

};


#endif // GAME_H
