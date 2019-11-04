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

class Cell : public QGraphicsItem, public QMainWindow {
    Q_OBJECT

public:
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    Cell(int x, int y, int width, int height);

private:
  int x_;
  int y_;
  int width_;
  int height_;

  QColor color_;

};
#endif // GAME_H
