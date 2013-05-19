#include "QQuickNetPlugin.h"
#include "QQuickAPISocket.h"

QQuickNetPlugin::QQuickNetPlugin()
{
}


void QQuickNetPlugin::registerTypes(const char *uri)
{
    // @uri TcpSocket
    qmlRegisterType<QQuickAPISocket>(uri, 1, 0, "TcpSocket");
}
