#ifndef QQUICKNETPLUGIN_H
#define QQUICKNETPLUGIN_H

#include <QQmlExtensionPlugin>

class QQuickNetPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT

public:
    QQuickNetPlugin();

public:
   void registerTypes(const char *uri);
};

#endif // QQUICKNETPLUGIN_H
