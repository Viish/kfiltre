/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Jan 11 17:06:45 2011
**      by: Qt User Interface Compiler version 4.6.2
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
    QAction *actionRGB;
    QAction *actionEqualize;
    QAction *actionNormalize;
    QAction *actionCustom;
    QAction *actionAbout_us;
    QAction *actionSave_as;
    QAction *actionYUV;
    QAction *actionSelect_all;
    QAction *actionNone;
    QAction *actionRectangle;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionBlur;
    QAction *actionEdge_Enhancement;
    QAction *actionPaint;
    QAction *actionEdge_Detection;
    QAction *actionVertical_Resize;
    QAction *actionHorizontal_Resize;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuImage;
    QMenu *menuHistogram;
    QMenu *menuFilters;
    QMenu *menu;
    QMenu *menuEdit;
    QMenu *menuSelect;
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
        actionOpen->setCheckable(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8("icons/actions/document-open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionOpen->setVisible(true);
        actionOpen->setMenuRole(QAction::TextHeuristicRole);
        actionOpen->setIconVisibleInMenu(true);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("icons/devices/media-floppy.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon1);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionCrop = new QAction(MainWindow);
        actionCrop->setObjectName(QString::fromUtf8("actionCrop"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("icons/actions/edit-cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCrop->setIcon(icon2);
        actionGrayscale = new QAction(MainWindow);
        actionGrayscale->setObjectName(QString::fromUtf8("actionGrayscale"));
        actionGrayscale->setChecked(false);
        actionFusion = new QAction(MainWindow);
        actionFusion->setObjectName(QString::fromUtf8("actionFusion"));
        actionResize = new QAction(MainWindow);
        actionResize->setObjectName(QString::fromUtf8("actionResize"));
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
        actionAbout_us->setMenuRole(QAction::AboutRole);
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        actionYUV = new QAction(MainWindow);
        actionYUV->setObjectName(QString::fromUtf8("actionYUV"));
        actionSelect_all = new QAction(MainWindow);
        actionSelect_all->setObjectName(QString::fromUtf8("actionSelect_all"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("icons/actions/view-fullscreen.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelect_all->setIcon(icon3);
        actionNone = new QAction(MainWindow);
        actionNone->setObjectName(QString::fromUtf8("actionNone"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("icons/actions/process-stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNone->setIcon(icon4);
        actionRectangle = new QAction(MainWindow);
        actionRectangle->setObjectName(QString::fromUtf8("actionRectangle"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("icons/actions/media-playback-stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRectangle->setIcon(icon5);
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("icons/actions/edit-undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUndo->setIcon(icon6);
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("icons/actions/edit-redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRedo->setIcon(icon7);
        actionBlur = new QAction(MainWindow);
        actionBlur->setObjectName(QString::fromUtf8("actionBlur"));
        actionEdge_Enhancement = new QAction(MainWindow);
        actionEdge_Enhancement->setObjectName(QString::fromUtf8("actionEdge_Enhancement"));
        actionPaint = new QAction(MainWindow);
        actionPaint->setObjectName(QString::fromUtf8("actionPaint"));
        actionEdge_Detection = new QAction(MainWindow);
        actionEdge_Detection->setObjectName(QString::fromUtf8("actionEdge_Detection"));
        actionVertical_Resize = new QAction(MainWindow);
        actionVertical_Resize->setObjectName(QString::fromUtf8("actionVertical_Resize"));
        actionHorizontal_Resize = new QAction(MainWindow);
        actionHorizontal_Resize->setObjectName(QString::fromUtf8("actionHorizontal_Resize"));
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
        menuBar->setGeometry(QRect(0, 0, 800, 27));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuImage = new QMenu(menuBar);
        menuImage->setObjectName(QString::fromUtf8("menuImage"));
        menuHistogram = new QMenu(menuBar);
        menuHistogram->setObjectName(QString::fromUtf8("menuHistogram"));
        menuFilters = new QMenu(menuBar);
        menuFilters->setObjectName(QString::fromUtf8("menuFilters"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuSelect = new QMenu(menuEdit);
        menuSelect->setObjectName(QString::fromUtf8("menuSelect"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(toolBar->sizePolicy().hasHeightForWidth());
        toolBar->setSizePolicy(sizePolicy1);
        toolBar->setCursor(QCursor(Qt::ArrowCursor));
        toolBar->setAllowedAreas(Qt::AllToolBarAreas);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuImage->menuAction());
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
        menuImage->addAction(actionVertical_Resize);
        menuImage->addAction(actionHorizontal_Resize);
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
        menuEdit->addAction(menuSelect->menuAction());
        menuSelect->addAction(actionSelect_all);
        menuSelect->addAction(actionNone);
        menuSelect->addAction(actionRectangle);
        toolBar->addAction(actionOpen);
        toolBar->addAction(actionSave);
        toolBar->addSeparator();
        toolBar->addAction(actionUndo);
        toolBar->addAction(actionRedo);
        toolBar->addSeparator();
        toolBar->addAction(actionSelect_all);
        toolBar->addAction(actionNone);
        toolBar->addAction(actionRectangle);
        toolBar->addAction(actionCrop);

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
        QObject::connect(actionFusion, SIGNAL(triggered()), MainWindow, SLOT(fusion()));
        QObject::connect(actionResize, SIGNAL(triggered()), MainWindow, SLOT(showResizeDialog()));
        QObject::connect(actionNormalize, SIGNAL(triggered()), MainWindow, SLOT(normalizeHistogram()));
        QObject::connect(actionVertical_Resize, SIGNAL(triggered()), MainWindow, SLOT(smartResizeV()));
        QObject::connect(actionHorizontal_Resize, SIGNAL(triggered()), MainWindow, SLOT(smartResizeH()));

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "Open...", 0, QApplication::UnicodeUTF8));
        actionOpen->setIconText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
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
        actionVertical_Resize->setText(QApplication::translate("MainWindow", "Vertical Resize", 0, QApplication::UnicodeUTF8));
        actionVertical_Resize->setShortcut(QApplication::translate("MainWindow", "V", 0, QApplication::UnicodeUTF8));
        actionHorizontal_Resize->setText(QApplication::translate("MainWindow", "Horizontal Resize", 0, QApplication::UnicodeUTF8));
        actionHorizontal_Resize->setShortcut(QApplication::translate("MainWindow", "H", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuImage->setTitle(QApplication::translate("MainWindow", "Image", 0, QApplication::UnicodeUTF8));
        menuHistogram->setTitle(QApplication::translate("MainWindow", "Histogram", 0, QApplication::UnicodeUTF8));
        menuFilters->setTitle(QApplication::translate("MainWindow", "Filters", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("MainWindow", "?", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0, QApplication::UnicodeUTF8));
        menuSelect->setTitle(QApplication::translate("MainWindow", "Select", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H