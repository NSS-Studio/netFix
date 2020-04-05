#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int x, y;
    getMoniterSize(x, y);
    this -> setFixedSize(x/4, y/2);
    this -> setWindowTitle(tr("NetWork Fixer"));
    this -> setWindowIcon(QIcon(":/icon/titleIcon"));

    mainWid = new QWidget(this);
    this -> setCentralWidget(mainWid);

    vbFix = new QVBoxLayout();
    mainWid -> setLayout(vbFix);

    netfixer = new netDealer(vbFix);
    QObject::connect(netfixer, &netDealer::sendMessage, this, &recvMessage);

    puAutoFix = new QPushButton(tr("一键修复"), mainWid);
    puAutoFix -> setFixedHeight(this->height()/2 - 40);
    vbFix -> addWidget(puAutoFix);

    vbContainer = new QVBoxLayout();
    grLog = new QGroupBox(tr("Log"), mainWid);
    grLog -> setLayout(vbContainer);

    tbLog = new QTextBrowser(mainWid);
    tbLog -> setTextBackgroundColor("black");
    QPalette pl = tbLog -> palette();
    pl.setBrush(QPalette::Base,QBrush(QColor("black")));
    tbLog ->setPalette(pl);
    vbContainer -> addWidget(tbLog);

    vbFix -> addWidget(grLog);

    QObject::connect(puAutoFix, &QPushButton::clicked, this, [=](){
        QMessageBox::StandardButton reply;
        popUpDialog(dialogKinds::question, tr("在修复之前是否备份现在的状态？\n"
                                                "若是，请选择一个保存位置；若否，则直接开始修复。"), reply);
        if (reply == QMessageBox::Yes){
            QString path = getFileWay();
            if (!path.isEmpty())
                netfixer -> backUp(path);
        }
        puAutoFix -> setEnabled(false);
        netfixer -> dealNetwork();
    });

    QObject::connect(netfixer, &netDealer::workFinish, [=](){
        if (!this->puAutoFix->isEnabled())
            this -> puAutoFix -> setEnabled(true);
    });
    recvMessage(logStatus::log, "Powered by NSS\nVerson: "+QString::number(VERSION));
}

MainWindow::~MainWindow()
{
    delete ui;
}


//------------------------------function------------------------------//
void MainWindow::getMoniterSize(int &x, int &y)
{
    x = GetSystemMetrics(SM_CXSCREEN);
    y = GetSystemMetrics(SM_CYSCREEN);
    qDebug("Moniter Size: %d x %d", x, y);

}

void MainWindow::recvMessage(const logStatus color, const QString &message)
{
    switch (color){
    case logStatus::log:
        tbLog -> setTextColor("white");
        break;
    case logStatus::warning:
        tbLog -> setTextColor("yellow");
        break;
    case logStatus::error:
        tbLog -> setTextColor("red");
        break;
    }
    tbLog -> append(status[static_cast<int>(color)] + message);
}

QString MainWindow::getFileWay()
{
    //it will lead an error:
    /*onecoreuap\shell\ext\thumbnailcache\lib\thumbcacheapi.cpp(285)\thumbcache.dll!6225FEDF:
      (caller: 6224EF31) ReturnHr(1) tid(31b4) 80004005 未指定的错误*/
    //it doesn't matter, seems windows api change but qt's not
    QString path = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                     "Desktop",
                                                     QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);
    if (path.isEmpty())
        recvMessage(logStatus::warning, pathEmpty);
    qDebug() << "reg file save path: " << path;
    return path;
}

void MainWindow::popUpDialog(dialogKinds question, const QString &text, QMessageBox::StandardButton &reply)
{
    switch (question){
    case dialogKinds::stander:
        QMessageBox::information(this, tr("Information"), text);
        break;

    case dialogKinds::question:
        reply = QMessageBox::question(this, tr("Question"),
                                            text,
                                            QMessageBox::Yes | QMessageBox::No);
        break;

    case dialogKinds::warning:
        QMessageBox::warning(this, tr("Warning"), text);
        break;

    case dialogKinds::error:
        reply = QMessageBox::critical(this, tr("Error"),
                                            text,
                                            QMessageBox::Abort | QMessageBox::Retry | QMessageBox::Ignore);
        break;
    }
}
