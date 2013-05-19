#ifndef QQUICKPROCESSPLUGIN_H
#define QQUICKPROCESSPLUGIN_H

#include <QQmlExtensionPlugin>

class QQuickProcessPlugin: public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.soapbubble.qtminer")
public:
    QQuickProcessPlugin();

public:
   void registerTypes(const char *uri);
};

#endif // QQUICKPROCESSPLUGIN_H
