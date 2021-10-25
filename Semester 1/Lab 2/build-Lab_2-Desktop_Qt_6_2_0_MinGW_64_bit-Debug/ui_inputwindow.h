/********************************************************************************
** Form generated from reading UI file 'inputwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTWINDOW_H
#define UI_INPUTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InputWindow
{
public:
    QLabel *label_2;
    QLabel *label_3;
    QTimeEdit *inputTimer;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QPushButton *addButton;
    QWidget *widget;
    QGridLayout *gridLayout;
    QRadioButton *radioButtonAlarmClock;
    QRadioButton *radioButtonTimer;

    void setupUi(QDialog *InputWindow)
    {
        if (InputWindow->objectName().isEmpty())
            InputWindow->setObjectName(QString::fromUtf8("InputWindow"));
        InputWindow->resize(700, 500);
        InputWindow->setMinimumSize(QSize(700, 500));
        InputWindow->setMaximumSize(QSize(700, 500));
        label_2 = new QLabel(InputWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 60, 131, 31));
        label_3 = new QLabel(InputWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 150, 131, 31));
        inputTimer = new QTimeEdit(InputWindow);
        inputTimer->setObjectName(QString::fromUtf8("inputTimer"));
        inputTimer->setGeometry(QRect(210, 150, 311, 71));
        inputTimer->setStyleSheet(QString::fromUtf8("font: 14pt \"MS Shell Dlg 2\";"));
        inputTimer->setDateTime(QDateTime(QDate(2000, 1, 1), QTime(0, 0, 0)));
        label_4 = new QLabel(InputWindow);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(40, 280, 131, 61));
        lineEdit = new QLineEdit(InputWindow);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(210, 290, 311, 41));
        lineEdit->setStyleSheet(QString::fromUtf8("font: 14pt \"MS Shell Dlg 2\";"));
        addButton = new QPushButton(InputWindow);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setGeometry(QRect(250, 400, 201, 41));
        addButton->setStyleSheet(QString::fromUtf8("font: 8pt \"MS Shell Dlg 2\";\n"
"font: 12pt \"MS Shell Dlg 2\";"));
        widget = new QWidget(InputWindow);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(210, 70, 311, 51));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        radioButtonAlarmClock = new QRadioButton(widget);
        radioButtonAlarmClock->setObjectName(QString::fromUtf8("radioButtonAlarmClock"));

        gridLayout->addWidget(radioButtonAlarmClock, 1, 1, 1, 1);

        radioButtonTimer = new QRadioButton(widget);
        radioButtonTimer->setObjectName(QString::fromUtf8("radioButtonTimer"));

        gridLayout->addWidget(radioButtonTimer, 0, 1, 1, 1);


        retranslateUi(InputWindow);

        QMetaObject::connectSlotsByName(InputWindow);
    } // setupUi

    void retranslateUi(QDialog *InputWindow)
    {
        InputWindow->setWindowTitle(QCoreApplication::translate("InputWindow", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("InputWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">1)Select type</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("InputWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">2)Select time</span></p></body></html>", nullptr));
        inputTimer->setDisplayFormat(QCoreApplication::translate("InputWindow", "H:mm:ss", nullptr));
        label_4->setText(QCoreApplication::translate("InputWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">3)Type name</span></p><p><span style=\" font-size:14pt;\">of timer</span></p></body></html>", nullptr));
        lineEdit->setText(QCoreApplication::translate("InputWindow", "Timer name", nullptr));
        addButton->setText(QCoreApplication::translate("InputWindow", "Add", nullptr));
        radioButtonAlarmClock->setText(QCoreApplication::translate("InputWindow", "Alarm clock", nullptr));
        radioButtonTimer->setText(QCoreApplication::translate("InputWindow", "Timer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputWindow: public Ui_InputWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTWINDOW_H
