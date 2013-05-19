#ifndef QQUICKAPISOCKET_H
#define QQUICKAPISOCKET_H

#include <QQuickItem>
#include <QScopedPointer>

class QQuickAPISocketPrivate;
class QQuickAPISocketInstance;

class QQuickAPISocket : public QObject
{
    friend class QQuickAPISocketInstance;
    Q_OBJECT
    Q_PROPERTY(QString hostname READ hostname WRITE setHostname NOTIFY hostnameChanged);
    Q_PROPERTY(quint32 port READ port WRITE setPort NOTIFY portChanged);
    Q_PROPERTY(QString request READ request WRITE setRequest NOTIFY requestChanged);

public:
    explicit QQuickAPISocket(QQuickItem *parent = 0);
    ~QQuickAPISocket();
    
    QString hostname();
    void setHostname(QString hostname);
    quint32 port();
    void setPort(quint32 port);
    QString request();
    void setRequest(QString request);
    Q_INVOKABLE QString response();

signals:
    void hostnameChanged();
    void portChanged();
    void requestChanged();
    void readyToReadResponse();

public slots:
    void connect();

protected:
    void setResponse(QString response);

private:
    QScopedPointer<QQuickAPISocketPrivate> p;
};

class QQuickAPISocketInstacePrivate;
class QTcpSocket;

class QQuickAPISocketInstance: public QObject
{
    Q_OBJECT
public:
    QQuickAPISocketInstance(QTcpSocket *socket, QQuickAPISocket *parent = 0);
    ~QQuickAPISocketInstance();

private slots:
    void onConnected();
    void bytesAvailable();
private:
    QScopedPointer<QQuickAPISocketInstacePrivate> p;
};

#endif // QQUICKAPISOCKET_H
