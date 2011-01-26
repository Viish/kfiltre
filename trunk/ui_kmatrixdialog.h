/********************************************************************************
** Form generated from reading UI file 'kmatrixdialog.ui'
**
** Created: Tue Jan 25 11:18:11 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KMATRIXDIALOG_H
#define UI_KMATRIXDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_KmatrixDialog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QGridLayout *gridLayout_3;
    QSpinBox *spinBox;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBox_2;
    QGridLayout *gridLayout_4;
    QDialogButtonBox *buttonBox;
    QDialogButtonBox *buttonBox_2;

    void setupUi(QDialog *KmatrixDialog)
    {
        if (KmatrixDialog->objectName().isEmpty())
            KmatrixDialog->setObjectName(QString::fromUtf8("KmatrixDialog"));
        KmatrixDialog->resize(170, 242);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(KmatrixDialog->sizePolicy().hasHeightForWidth());
        KmatrixDialog->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(KmatrixDialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableWidget = new QTableWidget(KmatrixDialog);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        if (tableWidget->rowCount() < 3)
            tableWidget->setRowCount(3);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        tableWidget->setDragEnabled(false);
        tableWidget->setDragDropOverwriteMode(false);
        tableWidget->setDragDropMode(QAbstractItemView::NoDragDrop);
        tableWidget->setDefaultDropAction(Qt::CopyAction);
        tableWidget->setAlternatingRowColors(true);
        tableWidget->setRowCount(3);
        tableWidget->setColumnCount(3);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(40);
        tableWidget->horizontalHeader()->setMinimumSectionSize(40);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setCascadingSectionResizes(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(40);
        tableWidget->verticalHeader()->setMinimumSectionSize(40);

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        spinBox = new QSpinBox(KmatrixDialog);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox->setMinimum(3);
        spinBox->setMaximum(15);
        spinBox->setSingleStep(2);

        gridLayout_3->addWidget(spinBox, 0, 1, 1, 1);

        label = new QLabel(KmatrixDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(KmatrixDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        spinBox_2 = new QSpinBox(KmatrixDialog);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_2->setMaximum(1000000);
        spinBox_2->setValue(1);

        gridLayout_3->addWidget(spinBox_2, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout_3, 1, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        buttonBox = new QDialogButtonBox(KmatrixDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Apply);

        gridLayout_4->addWidget(buttonBox, 0, 0, 1, 1);

        buttonBox_2 = new QDialogButtonBox(KmatrixDialog);
        buttonBox_2->setObjectName(QString::fromUtf8("buttonBox_2"));
        buttonBox_2->setLayoutDirection(Qt::RightToLeft);
        buttonBox_2->setStandardButtons(QDialogButtonBox::Close);

        gridLayout_4->addWidget(buttonBox_2, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout_4, 2, 0, 1, 1);


        retranslateUi(KmatrixDialog);
        QObject::connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), KmatrixDialog, SLOT(validateCustomMatrix()));
        QObject::connect(buttonBox_2, SIGNAL(clicked(QAbstractButton*)), KmatrixDialog, SLOT(close()));
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), KmatrixDialog, SLOT(setMatrixSize(int)));
        QObject::connect(tableWidget, SIGNAL(cellChanged(int,int)), KmatrixDialog, SLOT(checkInput(int,int)));

        QMetaObject::connectSlotsByName(KmatrixDialog);
    } // setupUi

    void retranslateUi(QDialog *KmatrixDialog)
    {
        KmatrixDialog->setWindowTitle(QApplication::translate("KmatrixDialog", "Custom filter", 0, QApplication::UnicodeUTF8));
        spinBox->setSuffix(QString());
        label->setText(QApplication::translate("KmatrixDialog", "Taille : ", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("KmatrixDialog", "Diviseur : ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class KmatrixDialog: public Ui_KmatrixDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KMATRIXDIALOG_H
