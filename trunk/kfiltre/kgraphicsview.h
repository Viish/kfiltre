#ifndef KGRAPHICSVIEW_H
#define KGRAPHICSVIEW_H

#include <QGraphicsView>
#include "mainwindow.h"

class KGraphicsView : public QGraphicsView
{
public:
    explicit KGraphicsView(MainWindow *main, QWidget *parent = 0);
    explicit KGraphicsView(MainWindow *main, QGraphicsScene *scene, QWidget *parent = 0);

    void mouseReleaseEvent(QMouseEvent *mouseEvent);
    void mouseMoveEvent(QMouseEvent *mouseEvent);
    void mousePressEvent(QMouseEvent *mouseEvent);
signals:

public slots:

private :
    MainWindow *main;
    int getOffsetX();
    int getOffsetY();
    int oldX, oldY;
    SIDE resizeSide;
};

#endif // KGRAPHICSVIEW_H
