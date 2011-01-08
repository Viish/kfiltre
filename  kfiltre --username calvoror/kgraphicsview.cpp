#include "kgraphicsview.h"
#include <iostream>
#include <QMouseEvent>
#include <QScrollBar>
#include <string>
#include <QCursor>

#define MARGIN_RESIZE 5

KGraphicsView::KGraphicsView(MainWindow *main, QWidget *parent) :
    QGraphicsView(parent), main(main)
{
    setMouseTracking(true);
}

KGraphicsView::KGraphicsView(MainWindow *main, QGraphicsScene *scene, QWidget *parent) :
    QGraphicsView(scene, parent), main(main)
{
    setMouseTracking(true);
}

void KGraphicsView::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    int offsetX, offsetY;
    offsetX = getOffsetX();
    offsetY = getOffsetY();

    QPoint pos = mouseEvent->pos();
    int x, y;
    x = offsetX + pos.x();
    y = offsetY + pos.y();
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x > main->getCurrentImage()->width) x = main->getCurrentImage()->width;
    if (y > main->getCurrentImage()->height) y = main->getCurrentImage()->height;

    if (mouseEvent->buttons() != Qt::NoButton)
    {
        if (main->getTool() == RECTANGLE) { main->setSelectionBottomRightCorner(x, y); }
        else if (main->getTool() == MOVE) { main->moveSelection(x-oldX, y-oldY); oldX = x; oldY = y; }
        else if (main->getTool() == RESIZE)
        {
            if (cursor().shape() == Qt::SizeHorCursor)
            {
                main->resizeSelection(x - oldX, resizeSide);
            }
            else if (cursor().shape() == Qt::SizeVerCursor)
            {
                main->resizeSelection(y - oldY, resizeSide);
            }
            oldX = x; oldY = y;
        }
    }
    else
    {
        main->displayPixelColor(x, y);
        this->setCursor(QCursor(Qt::ArrowCursor));

        QRect selection = main->getSelection();
        if (y > selection.y() && y < selection.height())
        {
            if ((x >= selection.x() - MARGIN_RESIZE && x<= selection.x() + MARGIN_RESIZE) ||
                (x >= selection.width() - MARGIN_RESIZE && x <= selection.width() + MARGIN_RESIZE))
            {
                this->setCursor(QCursor(Qt::SizeHorCursor));
            }
        }
        else if (x > selection.x() && x < selection.width())
        {
            if ((y >= selection.y() - MARGIN_RESIZE && y <= selection.y() + MARGIN_RESIZE) ||
                (y >= selection.height() - MARGIN_RESIZE && y <= selection.height() + MARGIN_RESIZE))
            {
                this->setCursor(QCursor(Qt::SizeVerCursor));
            }
        }
    }

    QGraphicsView::mouseMoveEvent(mouseEvent);
}

void KGraphicsView::mousePressEvent(QMouseEvent *mouseEvent)
{
    int offsetX, offsetY;
    offsetX = getOffsetX();
    offsetY = getOffsetY();

    QPoint pos = mouseEvent->pos();
    int x, y;
    x = offsetX + pos.x();
    y = offsetY + pos.y();
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x > main->getCurrentImage()->width) x = main->getCurrentImage()->width;
    if (y > main->getCurrentImage()->height) y = main->getCurrentImage()->height;

    if (main->getTool() == RECTANGLE) { main->setSelectionTopLeftCorner(x, y); this->setCursor(QCursor(Qt::CrossCursor)); }
    else
    {
        oldX = x;
        oldY = y;
        QRect selection = main->getSelection();

        if (y > selection.y() && y < selection.height())
        {
            if (x >= selection.x() - MARGIN_RESIZE && x<= selection.x() + MARGIN_RESIZE)
            {
                resizeSide = LEFT;
                main->resizeSelection();
            }
            else if (x >= selection.width() - MARGIN_RESIZE && x <= selection.width() + MARGIN_RESIZE)
            {
                resizeSide= RIGHT;
                main->resizeSelection();
            }
            else if (x > selection.x() && x < selection.width())
            {
                main->moveSelection();
                this->setCursor(QCursor(Qt::SizeAllCursor));
            }
        }
        else if (x > selection.x() && x < selection.width())
        {
            if (y >= selection.y() - MARGIN_RESIZE && y <= selection.y() + MARGIN_RESIZE)
            {
               resizeSide = TOP;
               main->resizeSelection();
            }
            else if (y >= selection.height() - MARGIN_RESIZE && y <= selection.height() + MARGIN_RESIZE)
            {
                resizeSide = BOTTOM;
                main->resizeSelection();
            }
            else if (y > selection.y() && y < selection.height())
            {
                main->moveSelection();
                this->setCursor(QCursor(Qt::SizeAllCursor));
            }
        }
    }
    QGraphicsView::mousePressEvent(mouseEvent);
}

void KGraphicsView::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
    int offsetX, offsetY;
    offsetX = getOffsetX();
    offsetY = getOffsetY();

    QPoint pos = mouseEvent->pos();
    int x, y;
    x = offsetX + pos.x();
    y = offsetY + pos.y();
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x > main->getCurrentImage()->width) x = main->getCurrentImage()->width;
    if (y > main->getCurrentImage()->height) y = main->getCurrentImage()->height;

    if (main->getTool() == RECTANGLE) { main->setSelectionBottomRightCorner(x, y); }
    main->setNullTool();
    this->setCursor(QCursor(Qt::ArrowCursor));

    QGraphicsView::mouseReleaseEvent(mouseEvent);
}

int KGraphicsView::getOffsetX()
{
    int offsetX = 0;
    int scrollbar_offset = 3;

    if(this->verticalScrollBar()->isVisible())
    {
        scrollbar_offset = this->verticalScrollBar()->size().width() - 2;
    }

    if (main->getCurrentImage()->width < this->width())
    {
        offsetX = main->getCurrentImage()->width / 2 - this->width() / 2 + scrollbar_offset;
    }
    else
    {
        offsetX = this->horizontalScrollBar()->value();
    }

    return offsetX;
}

int KGraphicsView::getOffsetY()
{
    int offsetY = 0;
    int scrollbar_offset = 3;

    if(this->horizontalScrollBar()->isVisible())
    {
        scrollbar_offset = this->horizontalScrollBar()->size().height() - 2;
    }

    if (main->getCurrentImage()->height < this->height())
    {
        offsetY = main->getCurrentImage()->height / 2 - this->height() / 2 + scrollbar_offset;
    }
    else
    {
        offsetY = this->verticalScrollBar()->value();
    }

    return offsetY;
}

