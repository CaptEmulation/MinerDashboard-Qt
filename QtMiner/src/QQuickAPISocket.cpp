#include "QQuickAPISocket.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>

class QQuickAPISocketPrivate
{
public:
    QString hostname;
    quint32 port;
    QString request;
    QString response;
};

QQuickAPISocket::QQuickAPISocket(QQuickItem *parent) :
    QObject(parent),
    p(new QQuickAPISocketPrivate)
{
}

QQuickAPISocket::~QQuickAPISocket()
{
}

QString QQuickAPISocket::hostname()
{
    return p->hostname;
}

void QQuickAPISocket::setHostname(QString hostname)
{
    if (hostname != p->hostname) {
        p->hostname = hostname;
        emit hostnameChanged();
    }
}

quint32 QQuickAPISocket::port()
{
    return p->port;
}

void QQuickAPISocket::setPort(quint32 port)
{
    if (p->port != port) {
        p->port = port;
        emit portChanged();
    }
}

QString QQuickAPISocket::request()
{
    return p->request;
}

void QQuickAPISocket::setRequest(QString request)
{
    if (request != QQuickAPISocket::request()) {
        p->request = request;
        emit requestChanged();
    }
}

QString QQuickAPISocket::response()
{
    QString response = p->response;
    p->response = QString();
    return response;
}


void QQuickAPISocket::connect()
{
    QTcpSocket *socket = new QTcpSocket(this);
    new QQuickAPISocketInstance(socket, this);
    if (p->hostname.length() > 0) {
        socket->connectToHost(p->hostname, p->port);
    } else {
        socket->connectToHost(QHostAddress::LocalHost, p->port);
    }

}

void QQuickAPISocket::setResponse(QString response)
{
    p->response = response;
    emit readyToReadResponse();
}



class QQuickAPISocketInstacePrivate
{
public:
    QString request;
    QTcpSocket *socket;
    QQuickAPISocket *root;
};

QQuickAPISocketInstance::QQuickAPISocketInstance(QTcpSocket *socket, QQuickAPISocket *parent) :
    QObject(parent),
    p(new QQuickAPISocketInstacePrivate)
{
    p->socket = socket;
    p->socket->setParent(this);
    p->request = parent->request();
    p->root = parent;
    QObject::connect(p->socket, &QTcpSocket::connected, this, &QQuickAPISocketInstance::onConnected);
    QObject::connect(p->socket, &QTcpSocket::readyRead, this, &QQuickAPISocketInstance::bytesAvailable);
}

QQuickAPISocketInstance::~QQuickAPISocketInstance()
{
}

void QQuickAPISocketInstance::onConnected()
{
    p->socket->write(p->request.toUtf8());
}

void QQuickAPISocketInstance::bytesAvailable()
{
    QString newText(p->socket->readAll());
    //qDebug() << newText;
    p->root->setResponse(newText);
    deleteLater();
}
