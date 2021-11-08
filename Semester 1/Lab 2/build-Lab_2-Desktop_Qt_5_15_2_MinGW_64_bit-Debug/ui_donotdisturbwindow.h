/********************************************************************************
** Form generated from reading UI file 'donotdisturbwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DONOTDISTURBWINDOW_H
#define UI_DONOTDISTURBWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTimeEdit>

QT_BEGIN_NAMESPACE

class Ui_DoNotDisturbWindow
{
public:
    QLabel *label;
    QTimeEdit *disturbModeStart;
    QTimeEdit *disturbModeEnd;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton;

    void setupUi(QDialog *DoNotDisturbWindow)
    {
        if (DoNotDisturbWindow->objectName().isEmpty())
            DoNotDisturbWindow->setObjectName(QString::fromUtf8("DoNotDisturbWindow"));
        DoNotDisturbWindow->resize(400, 300);
        DoNotDisturbWindow->setMinimumSize(QSize(400, 300));
        DoNotDisturbWindow->setMaximumSize(QSize(400, 300));
        label = new QLabel(DoNotDisturbWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 10, 245, 29));
        disturbModeStart = new QTimeEdit(DoNotDisturbWindow);
        disturbModeStart->setObjectName(QString::fromUtf8("disturbModeStart"));
        disturbModeStart->setGeometry(QRect(20, 110, 151, 61));
        disturbModeStart->setStyleSheet(QString::fromUtf8("font: 14pt \"MS Shell Dlg 2\";"));
        disturbModeStart->setDateTime(QDateTime(QDate(2000, 1, 1), QTime(0, 0, 0)));
        disturbModeEnd = new QTimeEdit(DoNotDisturbWindow);
        disturbModeEnd->setObjectName(QString::fromUtf8("disturbModeEnd"));
        disturbModeEnd->setGeometry(QRect(230, 110, 151, 61));
        disturbModeEnd->setStyleSheet(QString::fromUtf8("font: 14pt \"MS Shell Dlg 2\";"));
        label_2 = new QLabel(DoNotDisturbWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(70, 80, 91, 31));
        label_3 = new QLabel(DoNotDisturbWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(290, 80, 91, 31));
        pushButton = new QPushButton(DoNotDisturbWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(110, 210, 171, 51));
        pushButton->setStyleSheet(QString::fromUtf8("font: 14pt \"MS Shell Dlg 2\";"));

        retranslateUi(DoNotDisturbWindow);

        QMetaObject::connectSlotsByName(DoNotDisturbWindow);
    } // setupUi

    void retranslateUi(QDialog *DoNotDisturbWindow)
    {
        DoNotDisturbWindow->setWindowTitle(QCoreApplication::translate("DoNotDisturbWindow", "Do not disturb mode", nullptr));
        label->setText(QCoreApplication::translate("DoNotDisturbWindow", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600;\">Do not disturb mode</span></p></body></html>", nullptr));
        disturbModeStart->setDisplayFormat(QCoreApplication::translate("DoNotDisturbWindow", "H:mm:ss", nullptr));
        disturbModeEnd->setDisplayFormat(QCoreApplication::translate("DoNotDisturbWindow", "H:mm:ss", nullptr));
        label_2->setText(QCoreApplication::translate("DoNotDisturbWindow", "<html><head/><body><p><span style=\" font-size:16pt;\">Start</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("DoNotDisturbWindow", "<html><head/><body><p><span style=\" font-size:16pt;\">End</span></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("DoNotDisturbWindow", "Set", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DoNotDisturbWindow: public Ui_DoNotDisturbWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DONOTDISTURBWINDOW_H
