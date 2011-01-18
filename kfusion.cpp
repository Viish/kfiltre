#include <iostream>

#include "kfusion.h"
#include "ui_kfusion.h"
#include "mainwindow.h"

KFusion::KFusion(QWidget *parent) :
        QDialog(parent),
        ui(NULL),
        scene(NULL),
        main((MainWindow*)parent),
        source(NULL),
        target(NULL),
        targetResized(NULL),
        preview(NULL),
        factor(50)
{
    this->ui = new Ui::KFusion;
    this->ui->setupUi(this);

    this->source = main->getCurrentImage()->resize(this->width(), this->height(), true);
    //this->targetResized = new KImage(imageA->width, imageA->height);
    this->preview = this->source->copy();

    this->scene = new QGraphicsScene(this);
    this->scene->addPixmap(QPixmap::fromImage(preview->toQImage()));

    this->ui->graphicsView->setScene(scene);

    std::cerr << "Size :: " << this->width() << "  " << this->height() << std::endl;
}

KFusion::~KFusion()
{
    delete this->preview;
    delete this->targetResized;
    delete this->target;
    delete this->source;
    delete this->ui;
}

void KFusion::validate()
{
    this->main->validateFusion(this->target, factor);
    this->close();
}

void KFusion::factorChanged(int value)
{
    this->factor = value;
    this->refresh();
}

void KFusion::browse()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open a file", QString(), "Images (*.png *.gif *.jpg *.jpeg *.pnm)");
    if(filename != NULL)
    {
        delete this->target;
        delete this->targetResized;

        //this->target->setFilename(filename);
        //this->target->reload();
        this->target = new KImage(filename);
        this->targetResized = this->target->resize(source->width, source->height);
        this->refresh();
        this->ui->horizontalSlider->setEnabled(true);
    }
}

void KFusion::refresh()
{
    this->source->fusion(*this->targetResized, *this->preview, this->factor);
    this->scene->clear();
    this->scene->addPixmap(QPixmap::fromImage(preview->toQImage()));
}
