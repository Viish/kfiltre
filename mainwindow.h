#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QRect>

#include "histogram.h"
#include "kimage.h"
#include "kfusion.h"

typedef class Tab tab;

enum SIDE {
    TOP, BOTTOM, LEFT, RIGHT
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
    void setSelectionBottomRightCorner(int, int, bool = false, bool = false);
    TOOL getTool();
    void setNullTool();
    void moveSelection(int, int);
    void moveSelection();
    void resizeSelection();
    void resize(int, int, bool smart = false, KResizeDialog* = NULL);
    void resizeSelection(int, SIDE);
    void smartResize(int, int, KResizeDialog* = NULL);
    void refresh(KImage*);
    void validateFusion(KImage*, int);
    Tab* getCurrentTab();
    void applyCustomMatrix(int**, int, int);
    QRect getSelection();
    TOOL getSelectionShape();

    void addToTempPath(int, int);
    void addToPath(int, int);
    void finishPath(int, int);
    void deletePath();

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
        void setEllipseTool();
        void setPathTool();
        void selectAll();
        void cancelSelection();
        void applyBlur();
        void applyEdgeEnhancement();
        void applyPaintEffect();
        void showCustomDialog();
        void applyEdgeDetection();
        void showResizeDialog();
        void fusion();
        void normalizeHistogram();
        void equalizeHistogram();
        void smartResizeH();
        void smartResizeV();
        void smooth();
        void negative();
        void rotateClockwise();
        void rotateCounterClockwise();
        void verticalMirror();
        void horizontalMirror();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    KImage *image;
    Histogram *histogram;
    KImage *damier;
    TOOL tool;
    Tab *emptyTab;

    void newGraphicsViewTab(QString);
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
    void enableCloseTab();
    void disableCloseTab();
    QString getCroppedFilename();

private slots:
    void on_tabWidget_currentChanged(QWidget* );
    void on_tabWidget_tabCloseRequested(int index);
};

#endif // MAINWINDOW_H
