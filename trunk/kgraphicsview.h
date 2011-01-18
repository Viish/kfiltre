#ifndef KGRAPHICSVIEW_H
#define KGRAPHICSVIEW_H

#include <QGraphicsView>
#include "mainwindow.h"

class KGraphicsView : public QGraphicsView
{
private :
    MainWindow *main;
    int getOffsetX();
    int getOffsetY();
    int oldX, oldY;
    bool keepRatio;
    SIDE resizeSide;

public:
    explicit KGraphicsView(MainWindow *main, QWidget *parent = 0);
    explicit KGraphicsView(MainWindow *main, QGraphicsScene *scene, QWidget *parent = 0);

    void mouseReleaseEvent(QMouseEvent *mouseEvent);
    void mouseMoveEvent(QMouseEvent *mouseEvent);
    void mousePressEvent(QMouseEvent *mouseEvent);
    void keyPressEvent(QKeyEvent * ev);
    void keyReleaseEvent(QKeyEvent * ev);
};

#endif // KGRAPHICSVIEW_H
