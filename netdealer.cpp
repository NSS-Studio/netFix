#include "netdealer.h"
#include <winerror.h>

netDealer::netDealer(QObject *parent) : QObject(parent)
{}

netDealer::~netDealer()
{}

void netDealer::backUpRegedit(HKEY proxyRoot, const QString &keyWay, const QString &saveWay)
{
    // apply for permission
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        if (LookupPrivilegeValue(NULL, SE_BACKUP_NAME, &tkp.Privileges[0].Luid)) {
            tkp.PrivilegeCount = 1;
            tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
            AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
            if (GetLastError() != ERROR_SUCCESS) {
                CloseHandle(hToken);
                emit sendMessage(logStatus::error, "Application permission failed");
            }
        }
        CloseHandle(hToken);
    }

    //start backUp
    LPTSTR szSaveFileName;
    szSaveFileName = (LPTSTR)saveWay.unicode();

    HKEY key;
    long reply = RegOpenKeyEx(proxyRoot, (LPCWSTR)keyWay.unicode(), 0, KEY_READ | KEY_WOW64_64KEY, &key);
    if (reply != NO_ERROR)
        qDebug() << "RegOpen Code: " << reply << endl;

    reply = RegSaveKey(key, szSaveFileName, NULL);
    if (reply != NO_ERROR){
        emit sendMessage(logStatus::error, "Regedit file save failed! CODE: "+QString::number(reply, 10));
        qDebug() << "RegSave Code: " << reply << endl;
    } else
        emit sendMessage(logStatus::log, "Regedit file save complete! Path: "+saveWay);

    RegCloseKey(key);
}

void netDealer::cmd(const QString &program, const QStringList &arg)
{
    QProcess runner;
    runner.start(program, arg);
    runner.waitForStarted();
    runner.waitForFinished();

    QString re = QString::fromLocal8Bit(runner.readAllStandardOutput());
    emit sendMessage(logStatus::log, re);
}

void netDealer::backUp(const QString &path)
{
    if (!path.isEmpty()){
        QString temp = path + "/winsock.reg";
        backUpRegedit(HKEY_LOCAL_MACHINE, WinsockPATH, temp);
        temp = path + "/winsock2.reg";
        backUpRegedit(HKEY_LOCAL_MACHINE, Winsock2PATH, temp);
    }
}

void netDealer::dealNetwork()
{
    emit sendMessage(logStatus::log, "Working...Please wait a moment...");
    cmd("cmd", QStringList() << "/c" << "netsh winsock reset");
    cmd("cmd", QStringList() << "/c" << "netsh winhttp reset proxy");
    cmd("cmd", QStringList() << "/c" << "ipconfig /flushdns");
    emit sendMessage(logStatus::log, "Work complete, please reboot you computer");
    emit workFinish();
}
