#include "kfusion.h"
#include "ui_kfusion.h"
#include "mainwindow.h"

KFusion::KFusion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KFusion),
    factor(50),
    imageB(NULL)
{
    ui->setupUi(this);
    main = (MainWindow*) parent;
    imageA = main->getCurrentImage()->resize(350, 200, false);
    this->preview = imageA;
    this->scene = new QGraphicsScene(this);
    scene->addPixmap(QPixmap::fromImage(preview->toQImage()));
    ui->graphicsView->setScene(scene);
}

KFusion::~KFusion()
{
    delete ui;
    delete imageA;
    delete imageB;
    delete preview;
}

void KFusion::validate()
{
    main->validateFusion(imageA->fusion(imageB, factor), factor);
    this->close();
}

void KFusion::factorChanged(int value)
{
    factor = value;
    preview = imageA->fusion(imageB, factor);
    refresh(preview);
}

void KFusion::browse()
{
    if (this->imageB != NULL) delete this->imageB;
    QString filename = QFileDialog::getOpenFileName(this, "Open a file", QString(), "Images (*.png *.gif *.jpg *.jpeg *.pnm)");
    if(filename != NULL)
    {
        this->imageB = new KImage(filename);
        preview = imageA->fusion(imageB, factor);
        refresh(preview);
        ui->horizontalSlider->setEnabled(true);
    }
}

void KFusion::refresh(KImage *newImage)
{
    this->preview = newImage;
    delete this->scene;
    this->scene = new QGraphicsScene(this);
    scene->addPixmap(QPixmap::fromImage(preview->toQImage()));
    ui->graphicsView->setScene(scene);
//    this->graphicsView->show();
}
