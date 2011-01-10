/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon Jan 10 16:25:56 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionClose;
    QAction *actionCrop;
    QAction *actionGrayscale;
    QAction *actionFusion;
    QAction *actionResize;
    QAction *actionEdge;
    QAction *actionSelect;
    QAction *actionColor_picker;
    QAction *actionRGB;
    QAction *actionEqualize;
    QAction *actionNormalize;
    QAction *actionCustom;
    QAction *actionAbout_us;
    QAction *actionSave_as;
    QAction *actionYUV;
    QAction *actionPrevious;
    QAction *actionSelect_all;
    QAction *actionNone;
    QAction *actionRectangle;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionBlur;
    QAction *actionEdge_Enhancement;
    QAction *actionPaint;
    QAction *actionEdge_Detection;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuImage;
    QMenu *menuTools;
    QMenu *menuSelection;
    QMenu *menuHistogram;
    QMenu *menuFilters;
    QMenu *menu;
    QMenu *menuEdit;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setDockNestingEnabled(false);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionCrop = new QAction(MainWindow);
        actionCrop->setObjectName(QString::fromUtf8("actionCrop"));
        actionGrayscale = new QAction(MainWindow);
        actionGrayscale->setObjectName(QString::fromUtf8("actionGrayscale"));
        actionGrayscale->setChecked(false);
        actionFusion = new QAction(MainWindow);
        actionFusion->setObjectName(QString::fromUtf8("actionFusion"));
        actionResize = new QAction(MainWindow);
        actionResize->setObjectName(QString::fromUtf8("actionResize"));
        actionEdge = new QAction(MainWindow);
        actionEdge->setObjectName(QString::fromUtf8("actionEdge"));
        actionSelect = new QAction(MainWindow);
        actionSelect->setObjectName(QString::fromUtf8("actionSelect"));
        actionColor_picker = new QAction(MainWindow);
        actionColor_picker->setObjectName(QString::fromUtf8("actionColor_picker"));
        actionRGB = new QAction(MainWindow);
        actionRGB->setObjectName(QString::fromUtf8("actionRGB"));
        actionEqualize = new QAction(MainWindow);
        actionEqualize->setObjectName(QString::fromUtf8("actionEqualize"));
        actionNormalize = new QAction(MainWindow);
        actionNormalize->setObjectName(QString::fromUtf8("actionNormalize"));
        actionCustom = new QAction(MainWindow);
        actionCustom->setObjectName(QString::fromUtf8("actionCustom"));
        actionAbout_us = new QAction(MainWindow);
        actionAbout_us->setObjectName(QString::fromUtf8("actionAbout_us"));
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        actionYUV = new QAction(MainWindow);
        actionYUV->setObjectName(QString::fromUtf8("actionYUV"));
        actionPrevious = new QAction(MainWindow);
        actionPrevious->setObjectName(QString::fromUtf8("actionPrevious"));
        actionSelect_all = new QAction(MainWindow);
        actionSelect_all->setObjectName(QString::fromUtf8("actionSelect_all"));
        actionNone = new QAction(MainWindow);
        actionNone->setObjectName(QString::fromUtf8("actionNone"));
        actionRectangle = new QAction(MainWindow);
        actionRectangle->setObjectName(QString::fromUtf8("actionRectangle"));
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        actionBlur = new QAction(MainWindow);
        actionBlur->setObjectName(QString::fromUtf8("actionBlur"));
        actionEdge_Enhancement = new QAction(MainWindow);
        actionEdge_Enhancement->setObjectName(QString::fromUtf8("actionEdge_Enhancement"));
        actionPaint = new QAction(MainWindow);
        actionPaint->setObjectName(QString::fromUtf8("actionPaint"));
        actionEdge_Detection = new QAction(MainWindow);
        actionEdge_Detection->setObjectName(QString::fromUtf8("actionEdge_Detection"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(3, 3, 3, 3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMaximumSize);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setTabsClosable(true);
        tabWidget->setMovable(true);

        verticalLayout_2->addWidget(tabWidget);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 25));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuImage = new QMenu(menuBar);
        menuImage->setObjectName(QString::fromUtf8("menuImage"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuSelection = new QMenu(menuTools);
        menuSelection->setObjectName(QString::fromUtf8("menuSelection"));
        menuHistogram = new QMenu(menuBar);
        menuHistogram->setObjectName(QString::fromUtf8("menuHistogram"));
        menuFilters = new QMenu(menuBar);
        menuFilters->setObjectName(QString::fromUtf8("menuFilters"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setAllowedAreas(Qt::AllToolBarAreas);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuImage->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHistogram->menuAction());
        menuBar->addAction(menuFilters->menuAction());
        menuBar->addAction(menu->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_as);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        menuImage->addAction(actionCrop);
        menuImage->addAction(actionGrayscale);
        menuImage->addAction(actionFusion);
        menuImage->addAction(actionResize);
        menuTools->addAction(menuSelection->menuAction());
        menuSelection->addAction(actionSelect_all);
        menuSelection->addAction(actionNone);
        menuSelection->addSeparator();
        menuSelection->addAction(actionRectangle);
        menuHistogram->addAction(actionRGB);
        menuHistogram->addAction(actionYUV);
        menuHistogram->addAction(actionEqualize);
        menuHistogram->addAction(actionNormalize);
        menuFilters->addAction(actionBlur);
        menuFilters->addAction(actionPaint);
        menuFilters->addSeparator();
        menuFilters->addAction(actionEdge_Detection);
        menuFilters->addAction(actionEdge_Enhancement);
        menuFilters->addSeparator();
        menuFilters->addAction(actionCustom);
        menu->addAction(actionAbout_us);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);

        retranslateUi(MainWindow);
        QObject::connect(actionClose, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(actionOpen, SIGNAL(triggered()), MainWindow, SLOT(open()));
        QObject::connect(actionSave, SIGNAL(triggered()), MainWindow, SLOT(save()));
        QObject::connect(actionSave_as, SIGNAL(triggered()), MainWindow, SLOT(saveAs()));
        QObject::connect(actionGrayscale, SIGNAL(triggered()), MainWindow, SLOT(toGray()));
        QObject::connect(actionRGB, SIGNAL(triggered()), MainWindow, SLOT(showHistogram()));
        QObject::connect(actionYUV, SIGNAL(triggered()), MainWindow, SLOT(showYUVHistogram()));
        QObject::connect(actionCrop, SIGNAL(triggered()), MainWindow, SLOT(crop()));
        QObject::connect(actionRectangle, SIGNAL(triggered()), MainWindow, SLOT(setRectTool()));
        QObject::connect(actionSelect_all, SIGNAL(triggered()), MainWindow, SLOT(selectAll()));
        QObject::connect(actionNone, SIGNAL(triggered()), MainWindow, SLOT(cancelSelection()));
        QObject::connect(actionUndo, SIGNAL(triggered()), MainWindow, SLOT(undo()));
        QObject::connect(actionRedo, SIGNAL(triggered()), MainWindow, SLOT(redo()));
        QObject::connect(actionBlur, SIGNAL(triggered()), MainWindow, SLOT(applyBlur()));
        QObject::connect(actionEdge_Enhancement, SIGNAL(triggered()), MainWindow, SLOT(applyEdgeEnhancement()));
        QObject::connect(actionPaint, SIGNAL(triggered()), MainWindow, SLOT(applyPaintEffect()));
        QObject::connect(actionEdge_Detection, SIGNAL(triggered()), MainWindow, SLOT(applyEdgeDetection()));
        QObject::connect(actionResize, SIGNAL(triggered()), MainWindow, SLOT(resize()));
        QObject::connect(actionFusion, SIGNAL(triggered()), MainWindow, SLOT(fusion()));

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "Open...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionClose->setToolTip(QApplication::translate("MainWindow", "Close", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionClose->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionCrop->setText(QApplication::translate("MainWindow", "Crop", 0, QApplication::UnicodeUTF8));
        actionCrop->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", 0, QApplication::UnicodeUTF8));
        actionGrayscale->setText(QApplication::translate("MainWindow", "Grayscale", 0, QApplication::UnicodeUTF8));
        actionFusion->setText(QApplication::translate("MainWindow", "Fusion...", 0, QApplication::UnicodeUTF8));
        actionResize->setText(QApplication::translate("MainWindow", "Resize...", 0, QApplication::UnicodeUTF8));
        actionEdge->setText(QApplication::translate("MainWindow", "Edge", 0, QApplication::UnicodeUTF8));
        actionSelect->setText(QApplication::translate("MainWindow", "Select", 0, QApplication::UnicodeUTF8));
        actionColor_picker->setText(QApplication::translate("MainWindow", "Color picker", 0, QApplication::UnicodeUTF8));
        actionRGB->setText(QApplication::translate("MainWindow", "RGB", 0, QApplication::UnicodeUTF8));
        actionRGB->setShortcut(QApplication::translate("MainWindow", "Ctrl+H", 0, QApplication::UnicodeUTF8));
        actionEqualize->setText(QApplication::translate("MainWindow", "Equalize", 0, QApplication::UnicodeUTF8));
        actionNormalize->setText(QApplication::translate("MainWindow", "Normalize", 0, QApplication::UnicodeUTF8));
        actionCustom->setText(QApplication::translate("MainWindow", "Custom...", 0, QApplication::UnicodeUTF8));
        actionAbout_us->setText(QApplication::translate("MainWindow", "About us", 0, QApplication::UnicodeUTF8));
        actionSave_as->setText(QApplication::translate("MainWindow", "Save as...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSave_as->setToolTip(QApplication::translate("MainWindow", "Save as", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSave_as->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", 0, QApplication::UnicodeUTF8));
        actionYUV->setText(QApplication::translate("MainWindow", "YUV", 0, QApplication::UnicodeUTF8));
        actionYUV->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+H", 0, QApplication::UnicodeUTF8));
        actionPrevious->setText(QApplication::translate("MainWindow", "Previous", 0, QApplication::UnicodeUTF8));
        actionPrevious->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", 0, QApplication::UnicodeUTF8));
        actionSelect_all->setText(QApplication::translate("MainWindow", "All", 0, QApplication::UnicodeUTF8));
        actionSelect_all->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", 0, QApplication::UnicodeUTF8));
        actionNone->setText(QApplication::translate("MainWindow", "None", 0, QApplication::UnicodeUTF8));
        actionNone->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+A", 0, QApplication::UnicodeUTF8));
        actionRectangle->setText(QApplication::translate("MainWindow", "Rectangle", 0, QApplication::UnicodeUTF8));
        actionRectangle->setShortcut(QApplication::translate("MainWindow", "R", 0, QApplication::UnicodeUTF8));
        actionUndo->setText(QApplication::translate("MainWindow", "Undo", 0, QApplication::UnicodeUTF8));
        actionUndo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", 0, QApplication::UnicodeUTF8));
        actionRedo->setText(QApplication::translate("MainWindow", "Redo", 0, QApplication::UnicodeUTF8));
        actionRedo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+Z", 0, QApplication::UnicodeUTF8));
        actionBlur->setText(QApplication::translate("MainWindow", "Blur", 0, QApplication::UnicodeUTF8));
        actionEdge_Enhancement->setText(QApplication::translate("MainWindow", "Edge Enhancement", 0, QApplication::UnicodeUTF8));
        actionPaint->setText(QApplication::translate("MainWindow", "Paint", 0, QApplication::UnicodeUTF8));
        actionEdge_Detection->setText(QApplication::translate("MainWindow", "Edge Detection", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuImage->setTitle(QApplication::translate("MainWindow", "Image", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0, QApplication::UnicodeUTF8));
        menuSelection->setTitle(QApplication::translate("MainWindow", "Select", 0, QApplication::UnicodeUTF8));
        menuHistogram->setTitle(QApplication::translate("MainWindow", "Histogram", 0, QApplication::UnicodeUTF8));
        menuFilters->setTitle(QApplication::translate("MainWindow", "Filters", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("MainWindow", "?", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
