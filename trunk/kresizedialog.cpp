#include "kresizedialog.h"
#include "kimage.h"
#include "ui_kresizedialog.h"

KResizeDialog::KResizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KResizeDialog)
{
    main = (MainWindow*) parent;
    ui->setupUi(this);

    int width, height;
    width = main->getCurrentImage()->width;
    height = main->getCurrentImage()->height;

    ratio = (float) 1;
    ui->spinBox->setValue(width);
    ui->spinBox_2->setValue(height);
    ratio = (float) height / width;
}

KResizeDialog::~KResizeDialog()
{
    delete ui;
}

void KResizeDialog::changeHeightValue()
{
    if(ui->checkBox->isChecked() && ui->spinBox->hasFocus())
        ui->spinBox_2->setValue(ui->spinBox->value() * ratio);
}

void KResizeDialog::changeWidthValue()
{
    if(ui->checkBox->isChecked() && ui->spinBox_2->hasFocus())
        ui->spinBox->setValue(ui->spinBox_2->value() / ratio);
}
void KResizeDialog::validateResize()
{
    main->resize(ui->spinBox->value(), ui->spinBox_2->value(), ui->checkBox_2->isChecked(), this);
    if(!ui->checkBox_2->isChecked()) ui->progressBar->setValue(100);
}

void KResizeDialog::setProgressBar(int value)
{
    ui->progressBar->setValue(value);
    ui->progressBar->repaint();
}
