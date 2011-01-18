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
    QGraphicsItem *lastItem, *tempLine;
protected:
    QGridLayout *gridLayout;
    QGraphicsScene *scene;
    QImage *bg;
    KGraphicsView *graphicsView;
    KImage *image;
    KImage *firstRegistered;
public:
    int x1, y1, x2, y2;
    Path *firstPoint, *lastPoint, *previousPoint, *tempPoint;
    TOOL selectionShape;

    Tab(MainWindow *main, QString);
    ~Tab();
    KImage* getImage();
    void setImage(KImage*);
    void refresh(KImage*);
    void hideSelection();
    void drawRect(int, int, int, int);
    void drawEllipse(int, int, int, int);
    void drawPath(bool = false);
    void drawTempPath();
    void undo();
    void redo();
    bool isFirst();
    bool isLast();
    KImage* getFirstImage();
    bool isInsidePath2(int, int);

    void addToTempPath(int, int);
    void addToPath(int, int);
    void finishPath(int, int);
    void deletePath();
    QRect getSelection();
    Path* getSelectionPath();
    TOOL getSelectionShape();
    void drawSelection();
    void setSelectionTopLeftCorner(int, int);
    void setSelectionBottomRightCorner(int, int, bool = false, bool = false);
    void moveSelection(int, int);
    void resize(int, int, bool smart = false);
    void resizeSelection(int, SIDE);
    void selectAll();
    void cancelSelection();
};

#endif // TAB_H
