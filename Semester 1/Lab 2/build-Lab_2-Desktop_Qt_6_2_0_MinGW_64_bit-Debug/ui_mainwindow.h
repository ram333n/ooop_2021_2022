/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionAddTimer;
    QAction *actionDoNotDisturb;
    QAction *actionPauseTimer;
    QAction *actionRemoveTimer;
    QAction *actionPauseAllTimers;
    QAction *actionEnableTimer;
    QAction *actionEnableAllTimers;
    QWidget *centralwidget;
    QListWidget *listTimersWidget;
    QLabel *label;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(650, 450);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(650, 450));
        MainWindow->setMaximumSize(QSize(650, 450));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionAddTimer = new QAction(MainWindow);
        actionAddTimer->setObjectName(QString::fromUtf8("actionAddTimer"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddTimer->setIcon(icon);
        actionDoNotDisturb = new QAction(MainWindow);
        actionDoNotDisturb->setObjectName(QString::fromUtf8("actionDoNotDisturb"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/do_not_disturb.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDoNotDisturb->setIcon(icon1);
        actionPauseTimer = new QAction(MainWindow);
        actionPauseTimer->setObjectName(QString::fromUtf8("actionPauseTimer"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icons/pause.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionPauseTimer->setIcon(icon2);
        actionRemoveTimer = new QAction(MainWindow);
        actionRemoveTimer->setObjectName(QString::fromUtf8("actionRemoveTimer"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/icons/remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRemoveTimer->setIcon(icon3);
        actionPauseAllTimers = new QAction(MainWindow);
        actionPauseAllTimers->setObjectName(QString::fromUtf8("actionPauseAllTimers"));
        actionEnableTimer = new QAction(MainWindow);
        actionEnableTimer->setObjectName(QString::fromUtf8("actionEnableTimer"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/icons/enable.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEnableTimer->setIcon(icon4);
        actionEnableAllTimers = new QAction(MainWindow);
        actionEnableAllTimers->setObjectName(QString::fromUtf8("actionEnableAllTimers"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        listTimersWidget = new QListWidget(centralwidget);
        listTimersWidget->setObjectName(QString::fromUtf8("listTimersWidget"));
        listTimersWidget->setGeometry(QRect(40, 20, 571, 321));
        listTimersWidget->setStyleSheet(QString::fromUtf8("font: 14pt \"MS Shell Dlg 2\";"));
        listTimersWidget->setResizeMode(QListView::Fixed);
        listTimersWidget->setBatchSize(200);
        listTimersWidget->setWordWrap(true);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 0, 281, 20));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 650, 20));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addSeparator();
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        toolBar->addAction(actionAddTimer);
        toolBar->addAction(actionPauseTimer);
        toolBar->addAction(actionEnableTimer);
        toolBar->addAction(actionRemoveTimer);
        toolBar->addAction(actionDoNotDisturb);
        toolBar->addSeparator();
        toolBar->addAction(actionPauseAllTimers);
        toolBar->addSeparator();
        toolBar->addAction(actionEnableAllTimers);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        actionAddTimer->setText(QCoreApplication::translate("MainWindow", "Add timer", nullptr));
#if QT_CONFIG(tooltip)
        actionAddTimer->setToolTip(QCoreApplication::translate("MainWindow", "Add timer", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDoNotDisturb->setText(QCoreApplication::translate("MainWindow", "Do not disturb mode", nullptr));
#if QT_CONFIG(tooltip)
        actionDoNotDisturb->setToolTip(QCoreApplication::translate("MainWindow", "Do not disturb", nullptr));
#endif // QT_CONFIG(tooltip)
        actionPauseTimer->setText(QCoreApplication::translate("MainWindow", "Pause timer", nullptr));
#if QT_CONFIG(tooltip)
        actionPauseTimer->setToolTip(QCoreApplication::translate("MainWindow", "Pause timer", nullptr));
#endif // QT_CONFIG(tooltip)
        actionRemoveTimer->setText(QCoreApplication::translate("MainWindow", "Remove timer", nullptr));
        actionPauseAllTimers->setText(QCoreApplication::translate("MainWindow", "Pause all timers", nullptr));
        actionEnableTimer->setText(QCoreApplication::translate("MainWindow", "Enable", nullptr));
#if QT_CONFIG(tooltip)
        actionEnableTimer->setToolTip(QCoreApplication::translate("MainWindow", "Enable timer", nullptr));
#endif // QT_CONFIG(tooltip)
        actionEnableAllTimers->setText(QCoreApplication::translate("MainWindow", "Enable all timers", nullptr));
#if QT_CONFIG(tooltip)
        actionEnableAllTimers->setToolTip(QCoreApplication::translate("MainWindow", "Enable all timers", nullptr));
#endif // QT_CONFIG(tooltip)
        label->setText(QCoreApplication::translate("MainWindow", "  Id     Type         Time              Name", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
