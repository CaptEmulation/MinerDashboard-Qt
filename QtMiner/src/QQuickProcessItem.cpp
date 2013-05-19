#include "QQuickProcessItem.h"
#include <QQuickItem>
#include <QDir>
#include <QDebug>

class QQuickProcessItemPrivate {
public:
    QString command;
    QString errorFile;
    QString inputFile;
    QString outputFile;
    QQuickProcessItem* outputProcess;
};

QQuickProcessItem::QQuickProcessItem(QQuickItem *parent) :
    QProcess(parent),
    p(new QQuickProcessItemPrivate)
{
    this->connect(this, SIGNAL(error(QProcess::ProcessError)), this, SIGNAL(errorChanged()));
    this->connect(this, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(onFinished(int,QProcess::ExitStatus)));
    this->connect(this, SIGNAL(finished(int,QProcess::ExitStatus)), this, SIGNAL(exitCodeChanged()));
    this->connect(this, SIGNAL(finished(int,QProcess::ExitStatus)), this, SIGNAL(exitStatusChanged()));
    this->connect(this, SIGNAL(stateChanged(QProcess::ProcessState)), this, SLOT(onStateChanged(QProcess::ProcessState)));
    this->connect(this, SIGNAL(stateChanged(QProcess::ProcessState)), this, SIGNAL(pidChanged()));
}

QQuickProcessItem::~QQuickProcessItem()
{
}

QString QQuickProcessItem::command() const {
    return p->command;
}

void QQuickProcessItem::setCommand(const QString &command) {
    if (command != p->command) {
        p->command = command;
        emit commandChanged();
    }
}

void QQuickProcessItem::closeReadChannel(QQuickProcessEnums::ProcessChannel channel) {
    QProcess::closeReadChannel(QProcess::ProcessChannel(channel));
}

void QQuickProcessItem::closeWriteChannel() {
    QProcess::closeWriteChannel();
}

QString QQuickProcessItem::readAllStandardError() {
    return QString(QProcess::readAllStandardError());
}

QString QQuickProcessItem::readAllStandardOutput() {
    //p->outputText.append(QString(QProcess::readAllStandardOutput()));
    return QString(QProcess::readAllStandardOutput());
}

void QQuickProcessItem::start() {
    qDebug() << "Starting" << this->command() << "in currentDir:" << QDir::currentPath() << "with workingDir" << QProcess::workingDirectory();
    QStringList list;
    //list <<  "--default-config" << "../Resources/cgminer.conf";
    QProcess::start(this->command(), list);
    QProcess::waitForStarted(1000);
}

QString QQuickProcessItem::standardErrorFile() const {
    return p->errorFile;
}

void QQuickProcessItem::setStandardErrorFile(const QString &fileName) {
    p->errorFile = fileName;
    QProcess::setStandardErrorFile(fileName);
}

QString QQuickProcessItem::standardInputFile() const {
    return p->inputFile;
}

void QQuickProcessItem::setStandardInputFile(const QString &fileName) {
    p->inputFile = fileName;
    QProcess::setStandardInputFile(fileName);
}

QString QQuickProcessItem::standardOutputFile() const {
    return p->outputFile;
}

void QQuickProcessItem::setStandardOutputFile(const QString &fileName) {
    p->outputFile = fileName;
    QProcess::setStandardOutputFile(fileName);
}

QQuickProcessItem *QQuickProcessItem::standardOutputProcess() const {
    return p->outputProcess;
}

void QQuickProcessItem::setStandardOutputProcess(QQuickProcessItem *destination) {
    p->outputProcess = destination;
    QProcess::setStandardOutputProcess(destination);
}

QVariantMap QQuickProcessItem::processEnvironment() {
    QVariantMap envMap;

    foreach (QString value, QProcess::processEnvironment().toStringList()) {
        envMap.insert(value.section('=', 0, 0), value.section('=', 1, 1));
    }

    return envMap;
}

void QQuickProcessItem::setProcessEnvironment(const QVariantMap &envMap) {
    QProcessEnvironment env;

    foreach(QString key, envMap.keys()) {
        env.insert(key, envMap.value(key).toString());
    }

    QProcess::setProcessEnvironment(env);
    emit processEnvironmentChanged();
}

void QQuickProcessItem::setWorkingDirectory(const QString &dir) {
    if (dir != QDir::currentPath()) {
        QDir::setCurrent(dir);
        QProcess::setWorkingDirectory(dir);
        emit workingDirectoryChanged();
    }
}

void QQuickProcessItem::setProcessChannelMode(QQuickProcessEnums::ProcessChannelMode mode) {
    QProcess::setProcessChannelMode(QProcess::ProcessChannelMode(mode));
}

void QQuickProcessItem::setReadChannel(QQuickProcessEnums::ProcessChannel channel) {
    QProcess::setReadChannel(QProcess::ProcessChannel(channel));
}

QQuickProcessEnums::ProcessError QQuickProcessItem::error() const {
    return QQuickProcessEnums::ProcessError(QProcess::error());
}

QQuickProcessEnums::ProcessChannel QQuickProcessItem::readChannel() const {
    return QQuickProcessEnums::ProcessChannel(QProcess::readChannel());
}

QQuickProcessEnums::ProcessChannelMode QQuickProcessItem::processChannelMode() const {
    return QQuickProcessEnums::ProcessChannelMode(QProcess::processChannelMode());
}

QQuickProcessEnums::ExitStatus QQuickProcessItem::exitStatus() const {
    return QQuickProcessEnums::ExitStatus(QProcess::exitStatus());
}

QQuickProcessEnums::ProcessState QQuickProcessItem::state() const {
    return QQuickProcessEnums::ProcessState(QProcess::state());
}

void QQuickProcessItem::onStateChanged(QProcess::ProcessState state) {
    emit stateChanged(QQuickProcessEnums::ProcessState(state));
}

void QQuickProcessItem::onFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    emit finished(exitCode, QQuickProcessEnums::ExitStatus(exitStatus));
}

void QQuickProcessItem::kill()
{
    QProcess::close();
}
