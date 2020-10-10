#include "initwindow.h"

initWindow::initWindow()
{
    engine = new QQmlApplicationEngine();
}

initWindow::~initWindow()
{
    delete engine;
}

initWindow* initWindow::getInstance()
{
    static initWindow *self;
    if (self == nullptr)
        self = new initWindow();
    return self;
}

//------------------------------function------------------------------//
void initWindow::getMoniterSize(int &x, int &y)
{
    x = GetSystemMetrics(SM_CXSCREEN);
    y = GetSystemMetrics(SM_CYSCREEN);
#ifdef __DEBUG__
    qDebug() << "Moniter Size: " << x << "x" << y << endl;
#endif
}

void initWindow::init()
{
    int x, y;
    getMoniterSize(x, y);

    engine -> load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject *root = engine -> rootObjects()[0];
    root -> setProperty("width", x/2);
    root -> setProperty("height", y/2);
}
