#ifndef INPUTWINDOW_H
#define INPUTWINDOW_H
#include "timer.h"

#include <QDialog>
#include <QListWidget>
#include <QMessageBox>
#include <QQueue>

namespace Ui {
class InputWindow;
}

class InputWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InputWindow(QHash<int, Timer>& newTimersRef,
                         QQueue<int>& newIdGarbageRef,
                         int& newCurrentIdRef,
                         QListWidget* newListWidget,
                         QWidget *parent = nullptr);
    ~InputWindow();

private slots:
    void on_addButton_clicked();

private:
    QString isCorrectInput();

    Ui::InputWindow *ui;
    QHash<int, Timer>& timersRef;
    QListWidget*  listWidget;
    QQueue<int>& idGarbageRef;
    int& currentIdRef;
};

#endif // INPUTWINDOW_H
