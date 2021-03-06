/********************************************************************************
** Form generated from reading UI file 'kresizedialog.ui'
**
** Created: Tue Jan 25 11:18:11 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KRESIZEDIALOG_H
#define UI_KRESIZEDIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_KResizeDialog
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QLabel *label;
    QLabel *label_2;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QGridLayout *gridLayout_3;
    QDialogButtonBox *buttonBox;
    QDialogButtonBox *buttonBox_2;
    QProgressBar *progressBar;

    void setupUi(QDialog *KResizeDialog)
    {
        if (KResizeDialog->objectName().isEmpty())
            KResizeDialog->setObjectName(QString::fromUtf8("KResizeDialog"));
        KResizeDialog->resize(225, 172);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(KResizeDialog->sizePolicy().hasHeightForWidth());
        KResizeDialog->setSizePolicy(sizePolicy);
        KResizeDialog->setContextMenuPolicy(Qt::DefaultContextMenu);
        KResizeDialog->setSizeGripEnabled(false);
        KResizeDialog->setModal(false);
        gridLayout = new QGridLayout(KResizeDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(6, 6, 6, 6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        spinBox = new QSpinBox(KResizeDialog);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        spinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        spinBox->setMinimum(1);
        spinBox->setMaximum(6000);

        gridLayout_2->addWidget(spinBox, 0, 1, 1, 1);

        spinBox_2 = new QSpinBox(KResizeDialog);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_2->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        spinBox_2->setMinimum(1);
        spinBox_2->setMaximum(6000);

        gridLayout_2->addWidget(spinBox_2, 1, 1, 1, 1);

        label = new QLabel(KResizeDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(KResizeDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        checkBox = new QCheckBox(KResizeDialog);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setChecked(true);

        gridLayout_2->addWidget(checkBox, 2, 1, 1, 1);

        checkBox_2 = new QCheckBox(KResizeDialog);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        gridLayout_2->addWidget(checkBox_2, 2, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        buttonBox = new QDialogButtonBox(KResizeDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        buttonBox->setStandardButtons(QDialogButtonBox::Apply);

        gridLayout_3->addWidget(buttonBox, 0, 0, 1, 1);

        buttonBox_2 = new QDialogButtonBox(KResizeDialog);
        buttonBox_2->setObjectName(QString::fromUtf8("buttonBox_2"));
        buttonBox_2->setLayoutDirection(Qt::RightToLeft);
        buttonBox_2->setStandardButtons(QDialogButtonBox::Close);

        gridLayout_3->addWidget(buttonBox_2, 0, 1, 1, 1);


        gridLayout->addLayout(gridLayout_3, 2, 0, 1, 1);

        progressBar = new QProgressBar(KResizeDialog);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 1, 0, 1, 1);


        retranslateUi(KResizeDialog);
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), KResizeDialog, SLOT(changeHeightValue()));
        QObject::connect(spinBox_2, SIGNAL(valueChanged(int)), KResizeDialog, SLOT(changeWidthValue()));
        QObject::connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), KResizeDialog, SLOT(validateResize()));
        QObject::connect(buttonBox_2, SIGNAL(clicked(QAbstractButton*)), KResizeDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(KResizeDialog);
    } // setupUi

    void retranslateUi(QDialog *KResizeDialog)
    {
        KResizeDialog->setWindowTitle(QApplication::translate("KResizeDialog", "Resize", 0, QApplication::UnicodeUTF8));
        spinBox->setSuffix(QApplication::translate("KResizeDialog", " px", 0, QApplication::UnicodeUTF8));
        spinBox->setPrefix(QString());
        spinBox_2->setSuffix(QApplication::translate("KResizeDialog", " px", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("KResizeDialog", "Width :", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("KResizeDialog", "Height", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        checkBox->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        checkBox->setText(QApplication::translate("KResizeDialog", "Keep ratio", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        checkBox_2->setToolTip(QApplication::translate("KResizeDialog", "Resize the image with seamCarving algorithm", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        checkBox_2->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        checkBox_2->setText(QApplication::translate("KResizeDialog", "Smart Resize", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class KResizeDialog: public Ui_KResizeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KRESIZEDIALOG_H
