#include <cmath>
#include <QPen>
#include <QBrush>

#include "tab.h"

#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)

Tab::Tab(MainWindow *main, QString filename) :
        bg(NULL),
        lastItem(NULL),
        x1(0), y1(0), x2(0), y2(0),
        firstPoint(NULL),
        lastPoint(NULL),
        previousPoint(NULL)
{
    this->bg = new QImage("./icons/back.png");

    this->image = new KImage(filename);
    this->firstRegistered = image;

    this->scene = new QGraphicsScene(this);

    //QImage damier("./icons/damier.png");
    this->scene->addPixmap(QPixmap::fromImage(image->toQImage()));
    this->scene->setBackgroundBrush(QBrush(QPixmap::fromImage(*bg)));

    this->graphicsView = new KGraphicsView(main, scene, this);
    //this->graphicsView->setBackgroundBrush(Qt::NoBrush);
    //this->graphicsView->viewport()->setAutoFillBackground(false);
    this->graphicsView->setScene(scene);
    this->graphicsView->show();

//    QPalette palette;
//    palette.setBrush(this->graphicsView->backgroundRole(), QBrush(QPixmap::fromImage(damier)));
//    this->scene->setPalette(palette);

    this->gridLayout = new QGridLayout(this);
    this->gridLayout->setSpacing(6);
    this->gridLayout->setContentsMargins(0, 0, 0, 0);
    this->gridLayout->addWidget(graphicsView, 0 ,0, 1, 1);

    //this->scene->addPixmap(QPixmap::fromImage(damier));
}

Tab::~Tab()
{
    this->image->removePrevious();
    this->image->removeNext();
    delete this->image;
    delete this->bg;
}

void Tab::refresh(KImage *newImage)
{
    this->image->setNext(newImage);
    this->setImage(newImage);
}

KImage* Tab::getImage()
{
    return this->image;
}

void Tab::setImage(KImage *newImage)
{
    if (this->image->width != newImage->width or this->image->height != newImage->height)
    {
        delete this->scene;
        this->scene = new QGraphicsScene(this->graphicsView);
        this->scene->setBackgroundBrush(QBrush(QPixmap::fromImage(*bg)));
        this->graphicsView->setScene(this->scene);
    }
    else
    {
        this->scene->clear();
    }
    this->image = newImage;
    this->scene->addPixmap(QPixmap::fromImage(newImage->toQImage()));
    this->graphicsView->show();
}

void Tab::hideSelection()
{
    if (this->lastItem != NULL && this->scene != NULL && this->scene->items().contains(this->lastItem))
    {
        this->scene->removeItem(this->lastItem);
    }
    else
    {
        this->scene->clear();
        this->scene->addPixmap(QPixmap::fromImage(image->toQImage()));
    }
    this->lastItem = NULL;
}

void Tab::drawPath(bool pathFinished)
{
    this->scene->addLine(this->previousPoint->point.x, this->previousPoint->point.y, this->lastPoint->point.x, this->lastPoint->point.y, QPen(Qt::yellow));
    if (pathFinished)
        this->scene->addLine(this->lastPoint->point.x, this->lastPoint->point.y, this->firstPoint->point.x, this->firstPoint->point.y, QPen(Qt::yellow));
}

void Tab::drawTempPath()
{
    if (this->tempLine != NULL && this->scene != NULL && this->scene->items().contains(this->tempLine))
        this->scene->removeItem(this->tempLine);
    this->tempLine = this->scene->addLine(this->lastPoint->point.x, this->lastPoint->point.y, this->tempPoint->point.x, this->tempPoint->point.y, QPen(Qt::yellow));
}

void Tab::drawEllipse(int x1, int y1, int x2, int y2)
{
    hideSelection();

    if (x1 > x2 && y1 > y2)
    {
        this->lastItem = this->scene->addEllipse((qreal)(x2), (qreal)(y2), (qreal)(x1-x2), (qreal)(y1-y2), QPen(Qt::yellow));
    }
    else if (x1 > x2)
    {
        this->lastItem = this->scene->addEllipse((qreal)(x2), (qreal)(y1), (qreal)(x1-x2), (qreal)(y2-y1), QPen(Qt::yellow));
    }
    else if (y1 > y2)
    {
        this->lastItem = this->scene->addEllipse((qreal)(x1), (qreal)(y2), (qreal)(x2-x1), (qreal)(y1-y2), QPen(Qt::yellow));
    }
    else
    {
        this->lastItem = this->scene->addEllipse((qreal)(x1), (qreal)(y1), (qreal)(x2-x1), (qreal)(y2-y1), QPen(Qt::yellow));
    }
}

void Tab::drawRect(int x1, int y1, int x2, int y2)
{
    hideSelection();

    if (x1 > x2 && y1 > y2)
    {
        this->lastItem = this->scene->addRect((qreal)(x2), (qreal)(y2), (qreal)(x1-x2), (qreal)(y1-y2), QPen(Qt::yellow));
    }
    else if (x1 > x2)
    {
        this->lastItem = this->scene->addRect((qreal)(x2), (qreal)(y1), (qreal)(x1-x2), (qreal)(y2-y1), QPen(Qt::yellow));
    }
    else if (y1 > y2)
    {
        this->lastItem = this->scene->addRect((qreal)(x1), (qreal)(y2), (qreal)(x2-x1), (qreal)(y1-y2), QPen(Qt::yellow));
    }
    else
    {
        this->lastItem = this->scene->addRect((qreal)(x1), (qreal)(y1), (qreal)(x2-x1), (qreal)(y2-y1), QPen(Qt::yellow));
    }
}

void Tab::undo()
{
    this->setImage(this->image->getPrevious());
}

void Tab::redo()
{
    this->setImage(this->image->getNext());
}

bool Tab::isFirst()
{
    return this->image->getPrevious() == NULL;
}

bool Tab::isLast()
{
    return this->image->getNext() == NULL;
}

KImage* Tab::getFirstImage()
{
    return this->firstRegistered;
}

void Tab::addToTempPath(int x, int y)
{
    //if (this->tempPoint != NULL) delete tempPoint;

    if (this->firstPoint != NULL)
    {
        this->tempPoint = new Path(x, y);
        drawTempPath();
    }
}

void Tab::addToPath(int x, int y)
{
    if (this->firstPoint == NULL)
    {
        this->previousPoint = NULL;
        this->firstPoint = new Path(x, y);
        this->lastPoint = this->firstPoint;
    }
    else
    {
        this->previousPoint = this->lastPoint;
        this->previousPoint->next = new Path(x, y);
        this->lastPoint = this->previousPoint->next;

        drawPath(false);
    }
}

void Tab::finishPath(int x, int y)
{
    this->previousPoint = this->lastPoint;
    this->previousPoint->next = new Path(x, y, this->firstPoint);
    this->lastPoint = this->previousPoint->next;

    drawPath(true);
}

void Tab::deletePath()
{
    hideSelection();
    this->firstPoint = NULL;

    //    Path *p = this->firstPoint;
    //    Path *q = NULL;

    //    while(p != NULL)
    //    {
    //        q = p;
    //        p = p->next;
    //        delete q;
    //    }
}

QRect Tab::getSelection()
{
    return QRect(x1, y1, x2, y2);
}

Path* Tab::getSelectionPath()
{
    return this->firstPoint;
}

TOOL Tab::getSelectionShape()
{
    return this->selectionShape;
}
void Tab::setSelectionTopLeftCorner(int x, int y)
{
    this->x1 = x;
    this->y1 = y;
}

void Tab::setSelectionBottomRightCorner(int x, int y, bool finished, bool scale)
{
    this->x2 = x;
    this->y2 = y;

    if (scale)
    {
        if (abs(this->x2 - this->x1) > abs(this->y2 - this->y1))
        {
            this->x2 =  this->x2 > this->x1 ? abs(this->y2 - this->y1) + x1 : x1 - abs(this->y2 - this->y1);
        }
        else
        {
            this->y2 =  this->y2 > this->y1 ? abs(this->x2 - this->x1) + y1 : y1 - abs(this->x2 - this->x1);
        }
    }

    if (finished)
    {
        if (x2 < x1)
        {
           x2 = x1;
           x1 = x;
        }
        if (y2 < y1)
        {
            y2 = y1;
            y1 = y;
        }
    }

    drawSelection();
}

void Tab::drawSelection()
{
    if (this->selectionShape == RECTANGLE) drawRect(x1, y1, x2, y2);
    else if (this->selectionShape == ELLIPSE) drawEllipse(x1, y1, x2, y2);
    else drawPath(false);
}

void Tab::selectAll()
{
    this->x1 = 0;
    this->y1 = 0;
    this->x2 = this->image->width;
    this->y2 = this->image->height;
    this->selectionShape = RECTANGLE;

    drawSelection();
}

void Tab::cancelSelection()
{
    this->x1 = this->x2 = this->y1 = this->y2 = 0;
    hideSelection();
}

void Tab::moveSelection(int x, int y)
{
    if(x1+x >= 0 && x1+x < this->image->width && x2+x >= 0 && x2+x < this->image->width)
    {
        this->x1 += x;
        this->x2 += x;
    }
    if(y1+y >= 0 && y1+y < this->image->height && y2+y >= 0 && y2+y < this->image->height)
    {
        this->y1 += y;
        this->y2 += y;
    }

    drawSelection();
}

void Tab::resizeSelection(int i, SIDE cote)
{
    if(cote == LEFT)
    {
        if(x1 < x2)
        {
            if (x1 + i >= x2)
                i = x2 - x1 - 1;
            else if (x1 + i < 0)
                i = -x1;

            this->x1 += i;
        }
        else if(x2 < x1)
        {
            if (x2 + i >= x1)
                i = x1 - x2 - 1;
            else if (x2 + i < 0)
                i = -x2;

            this->x2 += i;
        }
    }
    else if(cote == RIGHT)
    {
        if(x1 > x2)
        {
            if(x1 + i <= x2)
                i = x2 - x1 + 1;
            else if (x1 + i > this->image->width)
                i = this->image->width - x1;

            this->x1 += i;
        }
        else if(x2 > x1)
        {
            if (x2 + i <= x1)
                i = x1 - x2 + 1;
            else if (x2 + i > this->image->width)
                i = this->image->width - x2;

            this->x2 += i;
        }
    }
    else if(cote == TOP)
    {
        if(y1 < y2)
        {
            if (y1 + i >= y2)
                i = y2 - y1 - 1;
            else if(y1 + i < 0)
                i = -y1;

            this->y1 += i;
        }
        else if (y2 < y1)
        {
            if (y2 + i >= y1)
                i = y1 - y2 - 1;
            else if(y2 + i < 0)
                i = -y2;

            this->y2 += i;
        }
    }
    else if(cote == BOTTOM)
    {
        if(y1 > y2)
        {
            if(y1 + i <= y2)
                i = y2 - y1 + 1;
            else if (y1 + i > this->image->height)
                i = this->image->height - y1;

            this->y1 += i;
        }
        else if (y2 > y1)
        {
            if(y2 + i <= y1)
                i = y1 - y2 + 1;
            else if (y2 + i > this->image->height)
                i = this->image->height - y2;

            this->y2 += i;
        }
    }

    drawSelection();
}

bool Tab::isInsidePath2(int x, int y)
{
    int count = 0;
    Path *p1, *p2;
    p1 = this->firstPoint;
    p2 = NULL;

    while (p2 != this->firstPoint)
    {
        if (x == p1->point.x && y == p1->point.y) // p sur le chemin
            return true;

        p2 = p1->next;
        if (y < MIN(p1->point.y, p2->point.y) && y > MAX(p1->point.y, p2->point.y))
        {
            p1 = p2;
            continue;
        }

        if (y > MIN(p1->point.y, p2->point.y) && y < MAX(p1->point.y, p2->point.y))
        {
            if (x <= MAX(p1->point.x, p2->point.x))
            {
                if (p1->point.y == p2->point.y && x >= MIN(p1->point.x, p2->point.x))
                    return true;

                if (p1->point.x == p2->point.x)
                {
                    if (p1->point.x == x)
                        return true;
                    else
                        count++;
                }
                else
                {
                    double xinters = (y - p1->point.y) * (p2->point.x - p1->point.x) / (p2->point.y - p1->point.y) + p1->point.x;

                    if(abs(x - xinters) < __DBL_EPSILON__)
                        return true;

                    if(x < xinters)
                        count++;
                }
            }
        }
        else
        {
            if(y == p2->point.y && x <= p2->point.x)
            {
                Path *p3 = p2->next;

                if(y >= MIN(p1->point.y, p3->point.y) && y <= MAX(p1->point.y, p3->point.y))
                    count++;
                else
                    count += 2;
            }
        }

        p1 = p2;
    }

    if (count % 2 == 0)
        return false;
    else
        return true;
}
