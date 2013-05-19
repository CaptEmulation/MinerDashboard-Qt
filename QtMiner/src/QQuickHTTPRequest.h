#ifndef QQUICKHTTPREQUEST_H
#define QQUICKHTTPREQUEST_H

#include <QQuickItem>
#include <QScopedPointer>
#include <QUrl>
#include <QNetworkReply>

class QQuickHTTPRequestPrivate;

class QQuickHTTPRequest : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged);
    Q_PROPERTY(QString request READ request WRITE setRequest NOTIFY requestChanged);
public:
    explicit QQuickHTTPRequest(QQuickItem *parent = 0);
    ~QQuickHTTPRequest();
    
    QUrl url();
    void setUrl(QUrl url);
    QString request();
    void setRequest(QString string);

signals:
    void urlChanged();
    void requestChanged();
    void responseReceived();

public slots:
    void get();


protected slots:
    void replyFinished(QNetworkReply *reply);

private:
    QScopedPointer<QQuickHTTPRequestPrivate> p;
};

#endif // QQUICKHTTPREQUEST_H
