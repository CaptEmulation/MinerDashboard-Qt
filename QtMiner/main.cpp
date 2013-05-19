#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include "QQuickProcessPlugin.h"
#include "QQuickNetPlugin.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickProcessPlugin processPlugin;
    processPlugin.registerTypes("Process");

    QQuickNetPlugin netPlugin;
    netPlugin.registerTypes("TcpSocket");

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/QtMiner/Main.qml"));
    viewer.showExpanded();

    return app.exec();
}
