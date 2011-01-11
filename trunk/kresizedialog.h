#ifndef KRESIZEDIALOG_H
#define KRESIZEDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
    class KResizeDialog;
}

class KResizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KResizeDialog(QWidget *parent = 0);
    ~KResizeDialog();

public slots :
    void changeWidthValue();
    void changeHeightValue();
    void validateResize();

private:
    Ui::KResizeDialog *ui;
    float ratio;
    MainWindow *main;
};

#endif // KRESIZE_H
