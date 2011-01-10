#include <QPen>
#include <QBrush>
#include "tab.h"
#include <iostream>

Tab::Tab(MainWindow *main, QString filename) : lastItem(NULL)
{
    this->image = new KImage(filename);
    this->firstRegistered = image;
    this->scene = new QGraphicsScene(this);
    scene->addPixmap(QPixmap::fromImage(image->toQImage()));

    this->graphicsView = new KGraphicsView(main, scene, this);
    this->graphicsView->setScene(scene);
    this->graphicsView->show();

    this->gridLayout = new QGridLayout(this);
    this->gridLayout->setSpacing(6);
    this->gridLayout->setContentsMargins(0, 0, 0, 0);
    this->gridLayout->addWidget(graphicsView, 0 ,0, 1, 1);
}

void Tab::refresh(KImage *newImage)
{
    //if (this->image != NULL) {
       this->image->setNext(newImage);
    //}
    this->setImage(newImage);
}

KImage* Tab::getImage()
{
    return this->image;
}

void Tab::setImage(KImage *newImage)
{
    this->image = newImage;
    delete this->scene;
    this->scene = new QGraphicsScene(this);
    scene->addPixmap(QPixmap::fromImage(newImage->toQImage()));
    this->graphicsView->setScene(scene);
    this->graphicsView->show();
}

void Tab::drawRect(int x1, int y1, int x2, int y2)
{
    if (this->lastItem != NULL) { this->scene->removeItem(this->lastItem); }

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
    std::cerr << "void Tab::undo()" << std::endl;
    if (this->image->getPrevious() == NULL) std::cerr << "void Tab::undo() : vaut null" << std::endl;
    this->setImage(this->image->getPrevious());
}

void Tab::redo()
{
    std::cerr << "void Tab::redo()" << std::endl;
    if (this->image->getNext() == NULL) std::cerr << "void Tab::redo() : vaut null" << std::endl;
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
