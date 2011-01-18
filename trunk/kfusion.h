#ifndef KFUSION_H
#define KFUSION_H

#include <QDialog>

class QGraphicsScene;
class MainWindow;
class KImage;

namespace Ui {
    class KFusion;
}

class KFusion : public QDialog
{
    Q_OBJECT

private:
    Ui::KFusion *ui;
    QGraphicsScene *scene;
    MainWindow *main;
    KImage *source, *target, *targetResized, *preview;
    int factor;

    void refresh();

public:
    explicit KFusion(QWidget *parent = 0);
    ~KFusion();

public slots :
    void validate();
    void factorChanged(int value);
    void browse();
};

#endif // KFUSION_H
