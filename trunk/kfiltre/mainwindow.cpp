#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tab.h"
#include "kfiltre.h"
#include "ui_fusion.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setNullTool();
    this->disableActions();
}

MainWindow::~MainWindow()
{
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
    QStringList filenames = QFileDialog::getOpenFileNames(this, "Open a file", QString(), "Images (*.png *.gif *.jpg *.jpeg *.pnm)");
    for(int i = 0; i < filenames.size(); ++i) {
        this->newGraphicsViewTab(filenames[i]);
    }
    if (ui->tabWidget->count() > 0)
    {
        this->enableActions();
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
    this->refresh(this->getCurrentImage()->toGrayScale());
    this->enableUndo();
}

void MainWindow::resize()
{
    this->refresh(this->getCurrentImage()->resize(350, 450));
    this->enableUndo();
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
    KFiltre *filterBlur = new KFiltre(BLUR);
    this->refresh(this->getCurrentImage()->applyFilter(filterBlur));
    this->enableUndo();
}

void MainWindow::applyEdgeEnhancement()
{
    KFiltre *filterEdge = new KFiltre(EDGE_H);
    KImage *temp = this->getCurrentImage()->applyFilter(filterEdge);

    filterEdge = new KFiltre(EDGE_V);
    this->refresh(temp->applyFilter(filterEdge));
    delete temp;

    this->enableUndo();
}

void MainWindow::applyEdgeDetection()
{
    KFiltre *filterEdge = new KFiltre(LAPLACIEN);
    this->getCurrentTab()->refresh(this->getCurrentImage()->applyFilter(filterEdge));
    this->enableUndo();
}

void MainWindow::applyPaintEffect()
{
    KFiltre *filterEdge = new KFiltre(PAINT);
    this->getCurrentTab()->refresh(this->getCurrentImage()->applyFilter(filterEdge));
    this->enableUndo();
}

void MainWindow::undo()
{
    std::cerr << "void MainWindow::undo()" << std::endl;
    this->getCurrentTab()->undo();
    std::cerr << "void MainWindow::undo() enableRedo" << std::endl;
    this->enableRedo();
    std::cerr << "void MainWindow::undo() enableSave" << std::endl;
    if(this->getCurrentImage()->isSaved()) disableSave();
    else this->enableSave();
    std::cerr << "void MainWindow::undo() END" << std::endl;
}

void MainWindow::redo()
{
    std::cerr << "void MainWindow::redo()" << std::endl;
    this->getCurrentTab()->redo();
    this->enableUndo();
    if(this->getCurrentImage()->isSaved()) disableSave();
    else this->enableSave();
}

void MainWindow::showHistogram()
{
    this->histogram = new Histogram(this->getCurrentImage(), false);
}

void MainWindow::showYUVHistogram()
{
    this->histogram = new Histogram(this->getCurrentImage(), true);
}

void MainWindow::refresh(KImage* image)
{
    std::cerr << "void MainWindow::refresh(KImage* image)" << std::endl;
    this->getCurrentTab()->refresh(image);
    this->enableUndo();
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
        KRGB rgb = this->getCurrentImage()->matrix[x][y];
        int red = rgb.red;
        int green = rgb.green;
        int blue = rgb.blue;

        KRGB *yuv = this->getCurrentImage()->matrix[x][y].copyToYUV();
        int y = yuv->red;
        int u = yuv->green;
        int v = yuv->blue;

        char buffer[50];
        sprintf(buffer, "RGB : %d, %d, %d   YUV : %d, %d, %d", red, green, blue, y, u, v);
        ui->statusBar->showMessage(buffer);
    }
}

void MainWindow::setSelectionTopLeftCorner(int x, int y)
{
    this->x1 = x;
    this->y1 = y;
}

void MainWindow::setSelectionBottomRightCorner(int x, int y)
{
    this->x2 = x;
    this->y2 = y;

    enableCrop();
    drawSelection();
}

void MainWindow::drawSelection()
{
    this->getCurrentTab()->drawRect(x1, y1, x2, y2);
}

QRect MainWindow::getSelection()
{
    return QRect(x1, y1, x2, y2);
}

void MainWindow::crop()
{
    std::cerr << "void MainWindow::crop()" << std::endl;
    int startingX, startingY, finishingX, finishingY;

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
            croppedImage->matrix[i][j] = getCurrentImage()->matrix[i + startingX][j + startingY].copy();
        }
    }

    this->refresh(croppedImage);
    disableCrop();
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    std::cerr << "void MainWindow::on_tabWidget_tabCloseRequested(int index)" << std::endl;
    ui->tabWidget->removeTab(index);

    std::cerr << "void MainWindow::on_tabWidget_tabCloseRequested(int index) ui->tabWidget->count()" << std::endl;
    if (ui->tabWidget->count() <= 0)
    {
        std::cerr << "void MainWindow::on_tabWidget_tabCloseRequested(int index) this->disableActions();" << std::endl;
        this->disableActions();
    }

    std::cerr << "void MainWindow::on_tabWidget_tabCloseRequested(int index)" << std::endl;
}

void MainWindow::selectAll()
{
    this->x1 = 0;
    this->y1 = 0;
    this->x2 = getCurrentImage()->width;
    this->y2 = getCurrentImage()->height;

    enableCrop();
    drawSelection();
}

void MainWindow::cancelSelection()
{
    this->x1 = this->x2 = this->y1 = this->y2 = 0;

    disableCrop();
    drawSelection();
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
    if(x1+x >= 0 && x1+x <getCurrentImage()->width && x2+x >= 0 && x2+x <getCurrentImage()->width)
    {
        this->x1 += x;
        this->x2 += x;
    }
    if(y1+y >= 0 && y1+y <getCurrentImage()->height && y2+y >= 0 && y2+y <getCurrentImage()->height)
    {
        this->y1 += y;
        this->y2 += y;
    }

    drawSelection();
}

void MainWindow::resizeSelection(int i, SIDE cote)
{
    if(cote == LEFT)
    {
        if(x1 < x2)
        {
            if (x1 + i >= x2)
                i = x2 - x1 - 1;
            else if (x1 + i < 0)
                i = -x1;

            this->x1 += i;
        }
        else if(x2 < x1)
        {
            if (x2 + i >= x1)
                i = x1 - x2 - 1;
            else if (x2 + i < 0)
                i = -x2;

            this->x2 += i;
        }
    }
    else if(cote == RIGHT)
    {
        if(x1 > x2)
        {
            if(x1 + i <= x2)
                i = x2 - x1 + 1;
            else if (x1 + i > getCurrentImage()->width)
                i = getCurrentImage()->width - x1;

            this->x1 += i;
        }
        else if(x2 > x1)
        {
            if (x2 + i <= x1)
                i = x1 - x2 + 1;
            else if (x2 + i > getCurrentImage()->width)
                i = getCurrentImage()->width - x2;

            this->x2 += i;
        }
    }
    else if(cote == TOP)
    {
        if(y1 < y2)
        {
            if (y1 + i >= y2)
                i = y2 - y1 - 1;
            else if(y1 + i < 0)
                i = -y1;

            this->y1 += i;
        }
        else if (y2 < y1)
        {
            if (y2 + i >= y1)
                i = y1 - y2 - 1;
            else if(y2 + i < 0)
                i = -y2;

            this->y2 += i;
        }
    }
    else if(cote == BOTTOM)
    {
        if(y1 > y2)
        {
            if(y1 + i <= y2)
                i = y2 - y1 + 1;
            else if (y1 + i > getCurrentImage()->height)
                i = getCurrentImage()->height - y1;

            this->y1 += i;
        }
        else if (y2 > y1)
        {
            if(y2 + i <= y1)
                i = y1 - y2 + 1;
            else if (y2 + i > getCurrentImage()->height)
                i = getCurrentImage()->height - y2;

            this->y2 += i;
        }
    }
    drawSelection();
}

TOOL MainWindow::getTool()
{
    return this->tool;
}

void MainWindow::setRectTool()
{
    this->tool = RECTANGLE;
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
}

void MainWindow::enableUndo()
{
    ui->actionUndo->setEnabled(true);
    if (this->getCurrentTab()->isLast()) disableRedo();
}

void MainWindow::disableUndo()
{
    ui->actionUndo->setEnabled(false);
}

void MainWindow::enableRedo()
{
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
