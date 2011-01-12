/********************************************************************************
** Form generated from reading UI file 'kfusion.ui'
**
** Created: Wed Jan 12 16:14:55 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KFUSION_H
#define UI_KFUSION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_KFusion
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;
    QSlider *horizontalSlider;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QPushButton *parcourir;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *KFusion)
    {
        if (KFusion->objectName().isEmpty())
            KFusion->setObjectName(QString::fromUtf8("KFusion"));
        KFusion->resize(682, 395);
        gridLayout = new QGridLayout(KFusion);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        graphicsView = new QGraphicsView(KFusion);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        verticalLayout->addWidget(graphicsView);

        horizontalSlider = new QSlider(KFusion);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setEnabled(false);
        horizontalSlider->setMaximum(100);
        horizontalSlider->setValue(50);
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider);

        label = new QLabel(KFusion);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        parcourir = new QPushButton(KFusion);
        parcourir->setObjectName(QString::fromUtf8("parcourir"));

        horizontalLayout->addWidget(parcourir);

        buttonBox = new QDialogButtonBox(KFusion);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setEnabled(true);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);

        horizontalLayout->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(KFusion);
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), label, SLOT(setNum(int)));
        QObject::connect(buttonBox, SIGNAL(accepted()), KFusion, SLOT(validate()));
        QObject::connect(buttonBox, SIGNAL(rejected()), KFusion, SLOT(close()));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), KFusion, SLOT(factorChanged(int)));
        QObject::connect(parcourir, SIGNAL(clicked()), KFusion, SLOT(browse()));

        QMetaObject::connectSlotsByName(KFusion);
    } // setupUi

    void retranslateUi(QDialog *KFusion)
    {
        KFusion->setWindowTitle(QApplication::translate("KFusion", "Fusion", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("KFusion", "50", 0, QApplication::UnicodeUTF8));
        parcourir->setText(QApplication::translate("KFusion", "Parcourir...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class KFusion: public Ui_KFusion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KFUSION_H
