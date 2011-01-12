#include "kmatrixdialog.h"
#include "ui_kmatrixdialog.h"
#include <iostream>

KmatrixDialog::KmatrixDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KmatrixDialog)
{
    main = (MainWindow*) parent;
    ui->setupUi(this);
}

KmatrixDialog::~KmatrixDialog()
{
    delete ui;
}

int** KmatrixDialog::getValues()
{
    int columns = ui->tableWidget->columnCount();
    int rows = ui->tableWidget->rowCount();
    int neg;

    int **values = new int*[columns];

    for (int i = 0; i < columns; i++)
    {
        values[i] = new int[rows];
    }

    for(int i = 0; i < columns; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            neg = 1;
            QString value = ui->tableWidget->item(i, j)->text();
            if(value.contains('-'))
            {
                std::cerr << "neg" << std::endl;
                value = value.remove('-');
                neg = -1;
            }
            values[i][j] = neg * value.toInt();
        }
    }
    return values;
}

void KmatrixDialog::setMatrixSize(int size)
{
    size = size + size%2 -1;
    ui->spinBox->setValue(size);
    ui->tableWidget->setRowCount(size);
    ui->tableWidget->setColumnCount(size);
    this->setFixedSize(38 + size*40, 120 + size*40);
}

void KmatrixDialog::validateCustomMatrix()
{
    main->applyCustomMatrix(this->getValues(), ui->tableWidget->rowCount(), ui->spinBox_2->value());
}

void KmatrixDialog::checkInput(int c, int r)
{
    QString input = ui->tableWidget->item(c, r)->text().remove('-');
    if(input.toInt() == 0)
    {
        ui->tableWidget->item(c, r)->setText("0");
    }
}
