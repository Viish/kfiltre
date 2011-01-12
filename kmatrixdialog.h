#ifndef KMATRIXDIALOG_H
#define KMATRIXDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
    class KmatrixDialog;
}

class KmatrixDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KmatrixDialog(QWidget *parent = 0);
    ~KmatrixDialog();
    int** getValues();

public slots :
    void setMatrixSize(int);
    void validateCustomMatrix();
    void checkInput(int, int);

private:
    Ui::KmatrixDialog *ui;
    MainWindow *main;
};

#endif // KMATRIXDIALOG_H
