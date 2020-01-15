// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "controller.h"
#include "mainwindow.h"
#include "tray.h"

#include <QApplication>
#include <QSettings>
#include <QTranslator>
#include <memory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSettings settings(QString("%1/settings.ini").arg(QCoreApplication::applicationDirPath()), QSettings::IniFormat, &a);

    auto controller = std::make_shared<Controller>(&settings);
    auto trayMenu = std::make_unique<Tray>(controller);
    auto mainWindow = std::make_unique<MainWindow>(controller);

    return a.exec();
}
