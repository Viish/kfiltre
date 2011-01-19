#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tab.h"
#include "kfiltre.h"
#include "ui_fusion.h"
#include "kresizedialog.h"
#include "kmatrixdialog.h"

Path::Path(int x, int y, Path *next) : point(x,y), next(next)
{
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(NULL),
    damier(NULL),
    tool(NONE)
{
    this->ui = new Ui::MainWindow();
    this->ui->setupUi(this);
    this->damier = new KImage("./icons/damier.png");
    this->disableActions();
    emptyTab = new Tab(this, NULL);
    this->ui->tabWidget->insertTab(1, emptyTab, "KFiltre");
    this->ui->tabWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete damier;
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::open()
{
    QStringList filenames = QFileDialog::getOpenFileNames(this, "Open a file", QString(), "Images (*.png *.gif *.jpg *.jpeg *.pnm *.ico *.bmp *.tiff)");

    for(int i = 0; i < filenames.size(); ++i)
    {
        this->newGraphicsViewTab(filenames[i]);
        //this->getCurrentImage()->calculateEnergy();
    }

    this->enableActions();

    if (ui->tabWidget->count() == 2 and ui->tabWidget->widget(1) == emptyTab)
    {
        ui->tabWidget->removeTab(1);
        enableCloseTab();
    }
}

void MainWindow::save()
{
    QImage image = getCurrentImage()->toQImage();
    image.save(getCurrentImage()->getFilename());
    this->getCurrentTab()->getFirstImage()->setNextUnsaved();
    this->getCurrentImage()->setSaved(true);
    disableSave();
}

void MainWindow::saveAs()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save a file", QString(), "Images (*.png *.gif *.jpg *.jpeg *.pnm)");
    QString format = filename.split(".")[filename.split(".").length() - 1];
    QImage image = getCurrentImage()->toQImage();
    image.save(filename, format.toStdString().c_str());

    getCurrentImage()->setFilename(filename);
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), getCroppedFilename());

    this->getCurrentImage()->setSaved(true);
    disableSave();
}

void MainWindow::toGray()
{
    QRect selection = this->getCurrentTab()->getSelection();
    int x1, x2, y1, y2;
    x1 = selection.x();
    x2 = selection.width();
    y1 = selection.y();
    y2 = selection.height();

    if (this->getCurrentTab()->getSelectionPath() != NULL)
        this->refresh(this->getCurrentImage()->toGrayScale(this->getCurrentTab()->getSelectionPath()));
    else if (x1 != x2 && y1 != y2)
        this->refresh(this->getCurrentImage()->toGrayScale(x1, y1, x2, y2, this->getCurrentTab()->getSelectionShape()));
    else
        this->refresh(this->getCurrentImage()->toGrayScale());
}

void MainWindow::smooth()
{
    QRect selection = this->getCurrentTab()->getSelection();
    int x1, x2, y1, y2;
    x1 = selection.x();
    x2 = selection.width();
    y1 = selection.y();
    y2 = selection.height();

    if (this->getCurrentTab()->getSelectionPath() != NULL)
        this->refresh(this->getCurrentImage()->applyMedianSmoothing(this->getCurrentTab()->getSelectionPath()));
   else if (x1 != x2 && y1 != y2)
        this->refresh(this->getCurrentImage()->applyMedianSmoothing(x1, y1, x2, y2, this->getCurrentTab()->getSelectionShape()));
    else
        this->refresh(this->getCurrentImage()->applyMedianSmoothing());
}

void MainWindow::negative()
{
    QRect selection = this->getCurrentTab()->getSelection();
    int x1, x2, y1, y2;
    x1 = selection.x();
    x2 = selection.width();
    y1 = selection.y();
    y2 = selection.height();

    if (this->getCurrentTab()->getSelectionPath() != NULL)
        this->refresh(this->getCurrentImage()->applyNegative(this->getCurrentTab()->getSelectionPath()));
    else if (x1 != x2 && y1 != y2)
        this->refresh(this->getCurrentImage()->applyNegative(x1, y1, x2, y2, this->getCurrentTab()->getSelectionShape()));
    else
        this->refresh(this->getCurrentImage()->applyNegative());
}

void MainWindow::resize(int width, int height, bool smart, KResizeDialog *dialog)
{
    if (smart)
        this->smartResize(width, height, dialog);
    else
        this->refresh(this->getCurrentImage()->resize(width, height));
}

void MainWindow::smartResize(int width, int height, KResizeDialog *dialog)
{
    this->refresh(this->getCurrentImage()->copy()->seamCarving(width, height, dialog));
}

void MainWindow::smartResizeH()
{
    this->getCurrentTab()->setImage(this->getCurrentImage()->seamCarving(getCurrentImage()->width, getCurrentImage()->height - 1));
}

void MainWindow::smartResizeV()
{
    this->getCurrentTab()->setImage(this->getCurrentImage()->seamCarving(getCurrentImage()->width - 1, getCurrentImage()->height));
}

void MainWindow::rotateClockwise()
{
    this->refresh(this->getCurrentImage()->rotateClockwise());
}

void MainWindow::rotateCounterClockwise()
{
    this->refresh(this->getCurrentImage()->rotateCounterClockwise());
}

void MainWindow::horizontalMirror()
{
    this->refresh(this->getCurrentImage()->horizontalMirror());
}

void MainWindow::verticalMirror()
{
    this->refresh(this->getCurrentImage()->verticalMirror());
}

void MainWindow::showResizeDialog()
{
    KResizeDialog *resizeDialog = new KResizeDialog(this);
    resizeDialog->show();
}

void MainWindow::fusion()
{
    KFusion *fusionDialog = new KFusion(this);
    fusionDialog->show();
}

void MainWindow::validateFusion(KImage *fusionImage, int factor)
{
    this->refresh(getCurrentTab()->getImage()->fusion(fusionImage, factor));
    delete fusionImage;
}

void MainWindow::applyBlur()
{
    KFiltre filterBlur(BLUR);

    QRect selection = this->getCurrentTab()->getSelection();
    int x1, x2, y1, y2;
    x1 = selection.x();
    x2 = selection.width();
    y1 = selection.y();
    y2 = selection.height();

    if (this->getCurrentTab()->getSelectionPath() != NULL)
        this->refresh(this->getCurrentImage()->applyFilter(filterBlur, this->getCurrentTab()->getSelectionPath()));
    else if (x1 != x2 && y1 != y2)
        this->refresh(this->getCurrentImage()->applyFilter(filterBlur, x1, y1, x2, y2, this->getCurrentTab()->getSelectionShape()));
    else
        this->refresh(this->getCurrentImage()->applyFilter(filterBlur));
}

void MainWindow::applyEdgeEnhancement()
{
    KImage *temp;
    KFiltre filterEdgeH(EDGE_H);
    KFiltre filterEdgeV(EDGE_V);

    QRect selection = this->getCurrentTab()->getSelection();
    int x1, x2, y1, y2;
    x1 = selection.x();
    x2 = selection.width();
    y1 = selection.y();
    y2 = selection.height();

    if (this->getCurrentTab()->getSelectionPath() != NULL)
    {
        temp = this->getCurrentImage()->applyFilter(filterEdgeH, this->getCurrentTab()->getSelectionPath());
        this->refresh(temp->applyFilter(filterEdgeV, this->getCurrentTab()->getSelectionPath()));
    }
    else if (x1 != x2 && y1 != y2)
    {
        temp = this->getCurrentImage()->applyFilter(filterEdgeH, x1, y1, x2, y2, this->getCurrentTab()->getSelectionShape());
        this->refresh(temp->applyFilter(filterEdgeV, x1, y1, x2, y2, this->getCurrentTab()->getSelectionShape()));
    }
    else
    {
        temp = this->getCurrentImage()->applyFilter(filterEdgeH);
        this->refresh(temp->applyFilter(filterEdgeV));
    }

    delete temp;
}

void MainWindow::applyEdgeDetection()
{
    KFiltre filterEdge(EDGE);

    QRect selection = this->getCurrentTab()->getSelection();
    int x1, x2, y1, y2;
    x1 = selection.x();
    x2 = selection.width();
    y1 = selection.y();
    y2 = selection.height();

    if (this->getCurrentTab()->getSelectionPath() != NULL)
        this->refresh(this->getCurrentImage()->applyFilter(filterEdge, this->getCurrentTab()->getSelectionPath()));
    else if (x1 != x2 && y1 != y2)
        this->refresh(this->getCurrentImage()->applyFilter(filterEdge, x1, y1, x2, y2, this->getCurrentTab()->getSelectionShape()));
    else
        this->refresh(this->getCurrentImage()->applyFilter(filterEdge));
}

void MainWindow::applyPaintEffect()
{
    KFiltre filterPaint(PAINT);
    QRect selection = this->getCurrentTab()->getSelection();
    int x1, x2, y1, y2;
    x1 = selection.x();
    x2 = selection.width();
    y1 = selection.y();
    y2 = selection.height();

    if (this->getCurrentTab()->getSelectionPath() != NULL)
        this->refresh(this->getCurrentImage()->applyFilter(filterPaint, this->getCurrentTab()->getSelectionPath()));
    else if (x1 != x2 && y1 != y2)
        this->refresh(this->getCurrentImage()->applyFilter(filterPaint, x1, y1, x2, y2, this->getCurrentTab()->getSelectionShape()));
    else
        this->refresh(this->getCurrentImage()->applyFilter(filterPaint));
}

void MainWindow::showCustomDialog()
{
    KmatrixDialog *matrixDialog = new KmatrixDialog(this);
    matrixDialog->setFixedSize(158, 240);
    matrixDialog->show();
}

void MainWindow::applyCustomMatrix(int** matrix, int size, int div)
{
    KFiltre customFilter(matrix, size, div);

    QRect selection = this->getCurrentTab()->getSelection();
    int x1, x2, y1, y2;
    x1 = selection.x();
    x2 = selection.width();
    y1 = selection.y();
    y2 = selection.height();

    if (this->getCurrentTab()->getSelectionPath() != NULL)
        this->refresh(this->getCurrentImage()->applyFilter(customFilter, this->getCurrentTab()->getSelectionPath()));
    else if (x1 != x2 && y1 != y2)
        this->refresh(this->getCurrentImage()->applyFilter(customFilter, x1, y1, x2, y2, this->getCurrentTab()->getSelectionShape()));
    else
        this->refresh(this->getCurrentImage()->applyFilter(customFilter));
}

void MainWindow::undo()
{
    this->getCurrentTab()->undo();
    this->enableRedo();
    if(this->getCurrentImage()->isSaved()) disableSave();
    else this->enableSave();
}

void MainWindow::redo()
{
    this->getCurrentTab()->redo();
    this->enableUndo();
    if(this->getCurrentImage()->isSaved()) disableSave();
    else this->enableSave();
}

void MainWindow::normalizeHistogram()
{
    this->histogram = new Histogram(this->getCurrentImage(), false);
    this->refresh(histogram->normalize());
}

void MainWindow::equalizeHistogram()
{
    this->histogram = new Histogram(this->getCurrentImage(), false);
    this->refresh(histogram->equalize());
}

void MainWindow::showHistogram()
{
    this->histogram = new Histogram(this->getCurrentImage(), false);
    this->histogram->show();
}

void MainWindow::showYUVHistogram()
{
    this->histogram = new Histogram(this->getCurrentImage(), true);
    this->histogram->show();
}

void MainWindow::refresh(KImage* image)
{
    this->enableUndo();
    this->getCurrentTab()->refresh(image);
    enableSave();
}

Tab* MainWindow::getCurrentTab()
{
    return ((Tab*)(ui->tabWidget->currentWidget()));
}

KImage* MainWindow::getCurrentImage()
{
    return this->getCurrentTab()->getImage();
}

void MainWindow::newGraphicsViewTab(QString filename)
{
    Tab *tab = new Tab(this, filename);
    if (filename.contains("/"))
    {
        filename = filename.split("/")[filename.split("/").length()-1];
    }
    ui->tabWidget->insertTab(0, tab, filename);
    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::displayPixelColor(int x, int y)
{
    if (x < getCurrentImage()->width && y < getCurrentImage()->height)
    {
        Pixel rgb = this->getCurrentImage()->getPixel(x,y);
        int red = rgb.red;
        int green = rgb.green;
        int blue = rgb.blue;

        Pixel yuv = this->getCurrentImage()->getYUVPixel(x,y);
        int y = yuv.red;
        int u = yuv.green;
        int v = yuv.blue;

        QString s;
        ui->statusBar->showMessage(s.sprintf("RGB : %d, %d, %d   YUV : %d, %d, %d", red, green, blue, y, u, v));
    }
}

void MainWindow::setSelectionTopLeftCorner(int x, int y)
{
    this->getCurrentTab()->setSelectionTopLeftCorner(x, y);
}

void MainWindow::setSelectionBottomRightCorner(int x, int y, bool finished, bool keepRatio)
{
    this->getCurrentTab()->setSelectionBottomRightCorner(x, y, finished, keepRatio);

    enableCrop();
}

void MainWindow::drawSelection()
{
    this->getCurrentTab()->drawSelection();
}

void MainWindow::crop()
{
    int startingX, startingY, finishingX, finishingY;
    int x1, x2, y1, y2;

    if(this->getCurrentTab()->selectionShape == PATH)
    {
        Path *path = this->getCurrentTab()->getSelectionPath();
        Point firstPoint, point;
        firstPoint = path->point;
        x1 = x2 = firstPoint.x;
        y1 = y2 = firstPoint.y;
        path = path->next;
        point = path->point;
        while((point.x != firstPoint.x) && (point.y != firstPoint.y))
        {
            if(point.x < x1) x1 = point.x;
            if(point.x > x2) x2 = point.x;
            if(point.y < y1) y1 = point.y;
            if(point.y > y2) y2 = point.y;

            path = path->next;
            point = path->point;
        }
    }
    else
    {
        QRect selection = this->getCurrentTab()->getSelection();
        x1 = selection.x();
        x2 = selection.width();
        y1 = selection.y();
        y2 = selection.height();
    }

    if (x1 > x2) { startingX = x2; finishingX = x1; }
    else  { startingX = x1; finishingX = x2; }
    if (y1 > y2) { startingY = y2; finishingY = y1; }
    else  { startingY = y1; finishingY = y2; }

    int width, height;
    width = finishingX - startingX;
    height = finishingY - startingY;

    KImage *croppedImage = new KImage(width, height, this->getCurrentImage()->getFilename());
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (this->getCurrentTab()->getSelectionShape() == RECTANGLE || (this->getCurrentTab()->getSelectionShape() == ELLIPSE && getCurrentImage()->isInsideEllipse(i + startingX, j + startingY, x1, y1, x2, y2)) || (this->getCurrentTab()->getSelectionShape() == PATH && getCurrentImage()->isInsidePath(i + startingX, j + startingY, this->getCurrentTab()->getSelectionPath())))
                croppedImage->matrix[i][j] = getCurrentImage()->getPixel(i + startingX, j + startingY);
        }
    }

    this->refresh(croppedImage);
    disableCrop();
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if (ui->tabWidget->count() == 1)
    {
        ui->tabWidget->insertTab(1, emptyTab, "KFiltre");
        ui->tabWidget->setCurrentIndex(0);
        this->disableActions();
        disableCloseTab();
    }

    ui->tabWidget->removeTab(index);
}

void MainWindow::addToTempPath(int x, int y)
{
    this->getCurrentTab()->addToTempPath(x, y);
}

void MainWindow::addToPath(int x, int y)
{
    this->getCurrentTab()->addToPath(x, y);
}

void MainWindow::finishPath(int x, int y)
{
    this->getCurrentTab()->finishPath(x, y);
    this->enableCrop();
}

void MainWindow::deletePath()
{
    this->getCurrentTab()->deletePath();
}

void MainWindow::selectAll()
{
    this->getCurrentTab()->selectAll();
    enableCrop();
}

QRect MainWindow::getSelection()
{
    return this->getCurrentTab()->getSelection();
}

void MainWindow::cancelSelection()
{
    this->getCurrentTab()->cancelSelection();
    disableCrop();
}

void MainWindow::moveSelection()
{
    this->tool = MOVE;
}

void MainWindow::resizeSelection()
{
    this->tool = RESIZE;
}

void MainWindow::moveSelection(int x, int y)
{
    this->getCurrentTab()->moveSelection(x, y);
}

void MainWindow::resizeSelection(int i, SIDE cote)
{
    this->getCurrentTab()->resizeSelection(i, cote);
}

TOOL MainWindow::getTool()
{
    return this->tool;
}

void MainWindow::setPathTool()
{
    this->getCurrentTab()->deletePath();
    this->tool = PATH;
    this->getCurrentTab()->selectionShape = PATH;
}

void MainWindow::setRectTool()
{
    this->getCurrentTab()->deletePath();
    this->tool = RECTANGLE;
    this->getCurrentTab()->selectionShape = RECTANGLE;
}

void MainWindow::setEllipseTool()
{
    this->getCurrentTab()->deletePath();
    this->tool = ELLIPSE;
    this->getCurrentTab()->selectionShape = ELLIPSE;
}

void MainWindow::setNullTool()
{
    this->tool = NONE;
}

void MainWindow::disableActions()
{
    ui->actionGrayscale->setEnabled(false);
    ui->actionRGB->setEnabled(false);
    ui->actionSave_as->setEnabled(false);
    ui->actionYUV->setEnabled(false);
    ui->actionBlur->setEnabled(false);
    ui->actionPaint->setEnabled(false);
    ui->actionEdge_Enhancement->setEnabled(false);
    ui->actionEdge_Detection->setEnabled(false);
    ui->actionSelect_all->setEnabled(false);
    ui->actionNone->setEnabled(false);
    ui->actionFusion->setEnabled(false);
    ui->actionResize->setEnabled(false);
    ui->actionRectangle->setEnabled(false);
    ui->actionNegative->setEnabled(false);
    ui->actionSmooth->setEnabled(false);
    ui->actionNormalize->setEnabled(false);
    ui->actionCustom->setEnabled(false);
    ui->actionVertical_Resize->setEnabled(false);
    ui->actionHorizontal_Resize->setEnabled(false);
    ui->actionRotate_90->setEnabled(false);
    ui->actionRotate_270->setEnabled(false);
    ui->actionVertical_Mirror->setEnabled(false);
    ui->actionHorizontal_Mirror->setEnabled(false);
    ui->actionEqualize->setEnabled(false);
    ui->actionEllipse->setEnabled(false);
    ui->actionPath->setEnabled(false);
    disableCrop();
    disableUndo();
    disableRedo();
    disableSave();
}

void MainWindow::enableActions()
{
    ui->actionGrayscale->setEnabled(true);
    ui->actionRGB->setEnabled(true);
    ui->actionSave_as->setEnabled(true);
    ui->actionYUV->setEnabled(true);
    ui->actionBlur->setEnabled(true);
    ui->actionPaint->setEnabled(true);
    ui->actionEdge_Enhancement->setEnabled(true);
    ui->actionEdge_Detection->setEnabled(true);
    ui->actionSelect_all->setEnabled(true);
    ui->actionNone->setEnabled(true);
    ui->actionFusion->setEnabled(true);
    ui->actionResize->setEnabled(true);
    ui->actionRectangle->setEnabled(true);
    ui->actionNegative->setEnabled(true);
    ui->actionSmooth->setEnabled(true);
    ui->actionNormalize->setEnabled(true);
    ui->actionCustom->setEnabled(true);
    ui->actionVertical_Resize->setEnabled(true);
    ui->actionHorizontal_Resize->setEnabled(true);
    ui->actionRotate_90->setEnabled(true);
    ui->actionRotate_270->setEnabled(true);
    ui->actionVertical_Mirror->setEnabled(true);
    ui->actionHorizontal_Mirror->setEnabled(true);
    ui->actionEqualize->setEnabled(true);
    ui->actionEllipse->setEnabled(true);
    ui->actionPath->setEnabled(true);
}

void MainWindow::enableUndo()
{
    this->cancelSelection();
    ui->actionUndo->setEnabled(true);
    if (this->getCurrentTab()->isLast()) disableRedo();
}

void MainWindow::disableUndo()
{
    ui->actionUndo->setEnabled(false);
}

void MainWindow::enableRedo()
{
    this->cancelSelection();
    ui->actionRedo->setEnabled(true);
    if (this->getCurrentTab()->isFirst()) this->disableUndo();
}

void MainWindow::disableRedo()
{
    ui->actionRedo->setEnabled(false);
}

void MainWindow::enableCrop()
{
    ui->actionCrop->setEnabled(true);
}

void MainWindow::disableCrop()
{
    ui->actionCrop->setEnabled(false);
}

void MainWindow::enableCloseTab()
{
    ui->tabWidget->setTabsClosable(true);
}

void MainWindow::disableCloseTab()
{
    ui->tabWidget->setTabsClosable(false);
}

QString MainWindow::getCroppedFilename()
{
    QString filename = getCurrentImage()->getFilename();
    if (filename.contains("/"))
    {
        filename = filename.split("/")[filename.split("/").length()-1];
    }
    return filename;
}

void MainWindow::enableSave()
{
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), getCroppedFilename() + "*");
    ui->actionSave->setEnabled(true);
}

void MainWindow::disableSave()
{
    if (ui->tabWidget->count() > 0) ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), getCroppedFilename());
    ui->actionSave->setEnabled(false);
}

void MainWindow::on_tabWidget_currentChanged(QWidget* tab)
{
    this->getCurrentTab()->isLast() ? this->disableRedo() : this->enableRedo();
    this->getCurrentTab()->isFirst() ? this->disableUndo() : this->enableUndo();
}
