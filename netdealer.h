#ifndef NETDEALER_H
#define NETDEALER_H

#include "common.h"
#include <QString>
#include <QStringList>
#include <QProcess>
#include <QObject>
#include <windows.h>
#include <winreg.h>
#include <tchar.h>

#define WinsockPATH "System\\CurrentControlSet\\Services\\Winsock"
#define Winsock2PATH "System\\CurrentControlSet\\Services\\Winsock2"

class netDealer : public QObject
{
    Q_OBJECT

public:
    netDealer(QObject *parent = nullptr);
    ~netDealer();

    void dealNetwork();
    void backUp(const QString &path);
    void cmd(const QString &program, const QStringList &arg);

signals:
    void sendMessage(logStatus, const QString&);
    void workFinish();

private:
    QString getFileWay();
    void backUpRegedit(HKEY proxyRoot, const QString &keyWay, const QString &saveWay);

};

#endif // NETDEALER_H
