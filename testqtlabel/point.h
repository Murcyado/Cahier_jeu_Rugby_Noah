#ifndef POINT_H
#define POINT_H
#include <QMainWindow>
#include <QTimer>
#include <QWidget>
#include <QMouseEvent>
#include <QCursor>
#include <QPainter>
#include <QtMath>
#include <QPainterPath>
#include <QAbstractAnimation>
#include <QPropertyAnimation>
#include <QSettings>
#include <QObject>
#include <QColor>

struct ligne
{
  QPoint  pta;
  QPoint ptb;
  QList<QPoint> ptint;

};

struct ballon
{
  QPoint  pta;
  QPoint ptb;
  QList<QPoint> ptint;

};

struct joueur_2
{
  QPoint  pta;
  QPoint ptb;
  QList<QPoint> ptint;

};

class Point
{
public:
    Point();

private:
    QColor color;
};




#endif // POINT_H
