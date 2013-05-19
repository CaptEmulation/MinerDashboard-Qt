#include "QQuickHTTPRequest.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>

class QQuickHTTPRequestPrivate
{
public:
    QUrl url;
    QString request;
    QNetworkAccessManager *mgr;
};

QQuickHTTPRequest::QQuickHTTPRequest(QQuickItem *parent) :
    QObject(parent),
    p(new QQuickHTTPRequestPrivate)
{
    p->mgr = new QNetworkAccessManager(this);
    QObject::connect(p->mgr, &QNetworkAccessManager::finished, this, &QQuickHTTPRequest::replyFinished);
}

QQuickHTTPRequest::~QQuickHTTPRequest()
{
}

QUrl QQuickHTTPRequest::url()
{
    return p->url;
}

void QQuickHTTPRequest::setUrl(QUrl url)
{
    if(url != p->url) {
        p->url = url;
        emit urlChanged();
    }
}

QString QQuickHTTPRequest::request()
{
    return p->request;
}

void QQuickHTTPRequest::setRequest(QString string)
{
    if (string != p->request) {
        p->request = string;
        emit requestChanged();
    }
}


void QQuickHTTPRequest::get()
{
}

void QQuickHTTPRequest::replyFinished(QNetworkReply *reply)
{
    emit responseReceived();
}
