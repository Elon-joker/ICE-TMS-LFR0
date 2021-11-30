/********************************************************************************
** Form generated from reading UI file 'serialsetting.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALSETTING_H
#define UI_SERIALSETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_serialSetting
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_5;
    QVBoxLayout *verticalLayout_2;
    QComboBox *PortBox;
    QComboBox *BaudBox;
    QComboBox *BitBox;
    QComboBox *ParityBox;
    QComboBox *StopBox;
    QPushButton *ok;
    QPushButton *cancel;
    QWidget *title;

    void setupUi(QDialog *serialSetting)
    {
        if (serialSetting->objectName().isEmpty())
            serialSetting->setObjectName(QString::fromUtf8("serialSetting"));
        serialSetting->resize(600, 600);
        serialSetting->setMinimumSize(QSize(600, 600));
        serialSetting->setMaximumSize(QSize(600, 600));
        serialSetting->setStyleSheet(QString::fromUtf8("background-color: rgb(210, 210, 210);"));
        layoutWidget = new QWidget(serialSetting);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 60, 263, 313));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 25));
        label->setMaximumSize(QSize(16777215, 25));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 25));
        label_2->setMaximumSize(QSize(16777215, 25));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(label_2);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(0, 25));
        label_4->setMaximumSize(QSize(16777215, 25));
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(label_4);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(0, 25));
        label_3->setMaximumSize(QSize(16777215, 25));
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(label_3);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMaximumSize(QSize(16777215, 25));
        label_5->setFont(font);
        label_5->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(label_5);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        PortBox = new QComboBox(layoutWidget);
        PortBox->addItem(QString());
        PortBox->setObjectName(QString::fromUtf8("PortBox"));
        PortBox->setFont(font);
        PortBox->setStyleSheet(QString::fromUtf8("background-color: rgb(213, 250, 255);/*\350\203\214\346\231\257\350\211\262*/"));

        verticalLayout_2->addWidget(PortBox);

        BaudBox = new QComboBox(layoutWidget);
        BaudBox->addItem(QString());
        BaudBox->addItem(QString());
        BaudBox->addItem(QString());
        BaudBox->setObjectName(QString::fromUtf8("BaudBox"));
        BaudBox->setFont(font);
        BaudBox->setStyleSheet(QString::fromUtf8("background-color: rgb(213, 250, 255);/*\350\203\214\346\231\257\350\211\262*/"));

        verticalLayout_2->addWidget(BaudBox);

        BitBox = new QComboBox(layoutWidget);
        BitBox->addItem(QString());
        BitBox->setObjectName(QString::fromUtf8("BitBox"));
        BitBox->setFont(font);
        BitBox->setStyleSheet(QString::fromUtf8("background-color: rgb(213, 250, 255);/*\350\203\214\346\231\257\350\211\262*/"));

        verticalLayout_2->addWidget(BitBox);

        ParityBox = new QComboBox(layoutWidget);
        ParityBox->addItem(QString());
        ParityBox->setObjectName(QString::fromUtf8("ParityBox"));
        ParityBox->setFont(font);
        ParityBox->setStyleSheet(QString::fromUtf8("background-color: rgb(213, 250, 255);/*\350\203\214\346\231\257\350\211\262*/"));

        verticalLayout_2->addWidget(ParityBox);

        StopBox = new QComboBox(layoutWidget);
        StopBox->addItem(QString());
        StopBox->addItem(QString());
        StopBox->setObjectName(QString::fromUtf8("StopBox"));
        StopBox->setFont(font);
        StopBox->setStyleSheet(QString::fromUtf8("background-color: rgb(213, 250, 255);/*\350\203\214\346\231\257\350\211\262*/"));

        verticalLayout_2->addWidget(StopBox);


        horizontalLayout->addLayout(verticalLayout_2);

        ok = new QPushButton(serialSetting);
        ok->setObjectName(QString::fromUtf8("ok"));
        ok->setGeometry(QRect(90, 510, 93, 28));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        font1.setPointSize(12);
        ok->setFont(font1);
        ok->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"    border-radius: 4px;\n"
"    background-color: rgb(213, 250, 255);/*\350\203\214\346\231\257\350\211\262*/\n"
"}"));
        cancel = new QPushButton(serialSetting);
        cancel->setObjectName(QString::fromUtf8("cancel"));
        cancel->setGeometry(QRect(400, 510, 93, 28));
        cancel->setFont(font1);
        cancel->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"    border-radius: 4px;\n"
"    background-color: rgb(213, 250, 255);/*\350\203\214\346\231\257\350\211\262*/\n"
"}"));
        title = new QWidget(serialSetting);
        title->setObjectName(QString::fromUtf8("title"));
        title->setGeometry(QRect(0, 0, 600, 60));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(title->sizePolicy().hasHeightForWidth());
        title->setSizePolicy(sizePolicy);
        title->setStyleSheet(QString::fromUtf8(" background-color: rgb(48, 48, 85);"));

        retranslateUi(serialSetting);

        QMetaObject::connectSlotsByName(serialSetting);
    } // setupUi

    void retranslateUi(QDialog *serialSetting)
    {
        serialSetting->setWindowTitle(QCoreApplication::translate("serialSetting", "\344\270\262\345\217\243\350\256\276\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("serialSetting", "\344\270\262\345\217\243", nullptr));
        label_2->setText(QCoreApplication::translate("serialSetting", "\346\263\242\347\211\271\347\216\207", nullptr));
        label_4->setText(QCoreApplication::translate("serialSetting", "\346\225\260\346\215\256\344\275\215", nullptr));
        label_3->setText(QCoreApplication::translate("serialSetting", "\345\245\207\345\201\266\346\243\200\351\252\214", nullptr));
        label_5->setText(QCoreApplication::translate("serialSetting", "\345\201\234\346\255\242\344\275\215", nullptr));
        PortBox->setItemText(0, QCoreApplication::translate("serialSetting", "NO", nullptr));

        BaudBox->setItemText(0, QCoreApplication::translate("serialSetting", "9600", nullptr));
        BaudBox->setItemText(1, QCoreApplication::translate("serialSetting", "38400", nullptr));
        BaudBox->setItemText(2, QCoreApplication::translate("serialSetting", "115200", nullptr));

        BitBox->setItemText(0, QCoreApplication::translate("serialSetting", "8", nullptr));

        ParityBox->setItemText(0, QCoreApplication::translate("serialSetting", "NO", nullptr));

        StopBox->setItemText(0, QCoreApplication::translate("serialSetting", "1", nullptr));
        StopBox->setItemText(1, QCoreApplication::translate("serialSetting", "2", nullptr));

        ok->setText(QCoreApplication::translate("serialSetting", "OK", nullptr));
        cancel->setText(QCoreApplication::translate("serialSetting", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class serialSetting: public Ui_serialSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALSETTING_H
