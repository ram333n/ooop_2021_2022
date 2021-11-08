/********************************************************************************
** Form generated from reading UI file 'timersignal.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMERSIGNAL_H
#define UI_TIMERSIGNAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_TimerSignal
{
public:
    QLabel *timerSignalMessage;
    QPushButton *pushButton;

    void setupUi(QDialog *TimerSignal)
    {
        if (TimerSignal->objectName().isEmpty())
            TimerSignal->setObjectName(QString::fromUtf8("TimerSignal"));
        TimerSignal->resize(500, 300);
        TimerSignal->setMinimumSize(QSize(500, 300));
        TimerSignal->setMaximumSize(QSize(500, 300));
        timerSignalMessage = new QLabel(TimerSignal);
        timerSignalMessage->setObjectName(QString::fromUtf8("timerSignalMessage"));
        timerSignalMessage->setGeometry(QRect(10, 0, 481, 191));
        timerSignalMessage->setAlignment(Qt::AlignCenter);
        pushButton = new QPushButton(TimerSignal);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(150, 200, 201, 61));
        pushButton->setStyleSheet(QString::fromUtf8("font: 14pt \"MS Shell Dlg 2\";"));

        retranslateUi(TimerSignal);

        QMetaObject::connectSlotsByName(TimerSignal);
    } // setupUi

    void retranslateUi(QDialog *TimerSignal)
    {
        TimerSignal->setWindowTitle(QCoreApplication::translate("TimerSignal", "Signal", nullptr));
        timerSignalMessage->setText(QCoreApplication::translate("TimerSignal", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt;\">Time has been </span></p><p align=\"center\"><span style=\" font-size:24pt;\">expired</span></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("TimerSignal", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TimerSignal: public Ui_TimerSignal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMERSIGNAL_H
