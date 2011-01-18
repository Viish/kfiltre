#ifndef KRESIZEDIALOG_H
#define KRESIZEDIALOG_H

#include <QDialog>
#include "mainwindow.h"

typedef class MainWindow MainWindow;

namespace Ui {
    class KResizeDialog;
}

class KResizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KResizeDialog(QWidget *parent = 0);
    ~KResizeDialog();
    void setProgressBar(int);

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
