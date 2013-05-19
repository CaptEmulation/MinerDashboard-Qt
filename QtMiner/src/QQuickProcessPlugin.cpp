#include "QQuickProcessPlugin.h"
#include "QQuickProcessItem.h"

QQuickProcessPlugin::QQuickProcessPlugin()
{
}


void QQuickProcessPlugin::registerTypes(const char *uri)
{
    // @uri Processes
    qmlRegisterUncreatableType<QQuickProcessEnums>(uri, 1, 0, "Processes", "");
    // @uri Process
    qmlRegisterType<QQuickProcessItem>(uri, 1, 0, "Process");
}
