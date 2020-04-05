#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "common.h"
#include "netdealer.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPalette>
#include <QFileDialog>
#include <QEventLoop>
#include <QLayout>
#include <windows.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private:
    Ui::MainWindow *ui;


    QString status[3] = {"Log: ", "Warning: ", "Error: "};
    netDealer *netfixer;

    QPushButton *puAutoFix;
    QTextBrowser *tbLog;
    QGroupBox *grLog;

    QWidget *mainWid;
    QVBoxLayout *vbFix;
    QVBoxLayout *vbContainer;

    void getMoniterSize(int &x, int &y);
    QString getFileWay();

private slots:
    void recvMessage(const logStatus, const QString&);
    void popUpDialog(dialogKinds question, const QString &text, QMessageBox::StandardButton &reply);
};

#endif // MAINWINDOW_H
