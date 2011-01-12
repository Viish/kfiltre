#ifndef TAB_H
#define TAB_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QGraphicsRectItem>
#include <kgraphicsview.h>

#include "kimage.h"

class Tab : public QWidget
{
private :
    QGraphicsRectItem *lastItem;
protected:
    QGridLayout *gridLayout;
    QGraphicsScene *scene;
    KGraphicsView *graphicsView;
    KImage *image;
    KImage *firstRegistered;
public:
    Tab(MainWindow *main, QString);
    KImage* getImage();
    void setImage(KImage*);
    void refresh(KImage*);
    void hideSelection();
    void drawRect(int, int, int, int);
    void undo();
    void redo();
    bool isFirst();
    bool isLast();
    KImage* getFirstImage();
};

#endif // TAB_H
