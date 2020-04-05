#ifndef INITWINDOW_H
#define INITWINDOW_H

#include "common.h"
#include <QQmlApplicationEngine>
#include <windows.h>

class initWindow
{
public:
    static initWindow* getInstance();
    void init();

private:
    QQmlApplicationEngine *engine;

    initWindow();
    ~initWindow();

};

#endif // INITWINDOW_H
