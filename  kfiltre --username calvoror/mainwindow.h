#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QRect>

#include "histogram.h"
#include "kimage.h"

typedef class Tab tab;

enum SIDE {
    TOP, BOTTOM, LEFT, RIGHT
};

enum TOOL {
    NONE, RESIZE, RECTANGLE, MOVE
};

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    KImage* getCurrentImage();
    void displayPixelColor(int, int);
    void setSelectionTopLeftCorner(int, int);
    void setSelectionBottomRightCorner(int, int);
    TOOL getTool();
    void setNullTool();
    void moveSelection(int, int);
    QRect getSelection();
    void moveSelection();
    void resizeSelection();
    void resizeSelection(int, SIDE);
    void refresh(KImage*);
    Tab* getCurrentTab();

public slots:
        void open();
        void save();
        void saveAs();
        void toGray();
        void crop();
        void undo();
        void redo();
        void showHistogram();
        void showYUVHistogram();
        void setRectTool();
        void selectAll();
        void cancelSelection();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    KImage *image;
    Histogram *histogram;
    int x1, y1, x2, y2;
    void newGraphicsViewTab(QString);
    TOOL tool;

    void disableActions();
    void enableActions();
    void enableUndo();
    void disableUndo();
    void enableRedo();
    void disableRedo();
    void drawSelection();
    void disableCrop();
    void enableCrop();
    void enableSave();
    void disableSave();

private slots:
    void on_tabWidget_currentChanged(QWidget* );
    void on_tabWidget_tabCloseRequested(int index);
};

#endif // MAINWINDOW_H
