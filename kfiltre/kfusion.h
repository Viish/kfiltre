#ifndef KFUSION_H
#define KFUSION_H

#include <QDialog>
#include "mainwindow.h"

typedef class MainWindow MainWindow;

namespace Ui {
    class KFusion;
}

class KFusion : public QDialog
{
    Q_OBJECT

public:
    explicit KFusion(QWidget *parent = 0);
    ~KFusion();

public slots :
    void validate();
    void factorChanged(int value);
    void browse();

private:
    void refresh(KImage*);
    Ui::KFusion *ui;
    MainWindow *main;
    int factor;
    KImage *imageA, *imageB, *preview;
    QGraphicsScene *scene;
};

#endif // KFUSION_H
