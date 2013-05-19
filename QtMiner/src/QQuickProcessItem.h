#ifndef QPROCESSITEM_H
#define QPROCESSITEM_H

#include <QQuickItem>
#include <QProcess>
#include <QScopedPointer>

class QQuickProcessItemPrivate;

class QQuickProcessEnums : public QObject
{
    Q_OBJECT

    Q_ENUMS(ExitStatus)
    Q_ENUMS(ProcessChannel)
    Q_ENUMS(ProcessChannelMode)
    Q_ENUMS(ProcessError)
    Q_ENUMS(ProcessState)

public:
    enum ExitStatus {
        NormalExit = QProcess::NormalExit,
        CrashExit = QProcess::CrashExit
    };

    enum ProcessChannel {
        StandardOutput = QProcess::StandardOutput,
        StandardError = QProcess::StandardError
    };

    enum ProcessChannelMode {
        SeparateChannels = QProcess::SeparateChannels,
        MergedChannels = QProcess::MergedChannels,
        ForwardedChannels = QProcess::ForwardedChannels
    };

    enum ProcessError {
        FailedToStart = QProcess::FailedToStart,
        Crashed = QProcess::Crashed,
        Timedout = QProcess::Timedout,
        WriteError = QProcess::WriteError,
        ReadError = QProcess::ReadError,
        UnknownError = QProcess::UnknownError
    };

    enum ProcessState {
        NotRunning = QProcess::NotRunning,
        Starting = QProcess::Starting,
        Running = QProcess::Running
    };
};

class QQuickProcessItem : public QProcess
{
    Q_OBJECT

     Q_PROPERTY(QString command
                READ command
                WRITE setCommand
                NOTIFY commandChanged)
     Q_PROPERTY(QString workingDirectory
                READ workingDirectory
                WRITE setWorkingDirectory
                NOTIFY workingDirectoryChanged)
     Q_PROPERTY(Q_PID pid
                READ pid
                NOTIFY pidChanged)
     Q_PROPERTY(QQuickProcessEnums::ProcessError error
                READ error
                NOTIFY errorChanged)
     Q_PROPERTY(QQuickProcessEnums::ProcessState state
                READ state
                NOTIFY stateChanged)
     Q_PROPERTY(int exitCode
                READ exitCode
                NOTIFY exitCodeChanged)
     Q_PROPERTY(QQuickProcessEnums::ExitStatus exitStatus
                READ exitStatus
                NOTIFY exitStatusChanged)
     Q_PROPERTY(QQuickProcessEnums::ProcessChannelMode processChannelMode
                READ processChannelMode
                WRITE setProcessChannelMode)
     Q_PROPERTY(QVariantMap processEnvironment
                READ processEnvironment
                WRITE setProcessEnvironment
                NOTIFY processEnvironmentChanged)
     Q_PROPERTY(QQuickProcessEnums::ProcessChannel readChannel
                READ readChannel
                WRITE setReadChannel)
     Q_PROPERTY(QString standardErrorFile
                READ standardErrorFile
                WRITE setStandardErrorFile)
     Q_PROPERTY(QString standardInputFile
                READ standardInputFile
                WRITE setStandardInputFile)
     Q_PROPERTY(QString standardOutputFile
                READ standardOutputFile
                WRITE setStandardOutputFile)
     Q_PROPERTY(QQuickProcessItem* standardOutputProcess
                READ standardOutputProcess
                WRITE setStandardOutputProcess)

 public:
     explicit QQuickProcessItem(QQuickItem *parent = 0);
    ~QQuickProcessItem();
     Q_INVOKABLE void closeReadChannel(QQuickProcessEnums::ProcessChannel channel);
     Q_INVOKABLE void closeWriteChannel();
     Q_INVOKABLE QString readAllStandardError();
     Q_INVOKABLE QString readAllStandardOutput();
     Q_INVOKABLE void start();
     Q_INVOKABLE void kill();

     QString command() const;
     void setCommand(const QString &command);
     QString standardErrorFile() const;
     void setStandardErrorFile(const QString &fileName);
     QString standardInputFile() const;
     void setStandardInputFile(const QString &fileName);
     QString standardOutputFile() const;
     void setStandardOutputFile(const QString &fileName);
     QQuickProcessItem* standardOutputProcess() const;
     void setStandardOutputProcess(QQuickProcessItem *destination);
     QVariantMap processEnvironment();
     void setProcessEnvironment(const QVariantMap &envMap);
     void setWorkingDirectory(const QString &dir);
     void setProcessChannelMode(QQuickProcessEnums::ProcessChannelMode mode);
     void setReadChannel(QQuickProcessEnums::ProcessChannel channel);
     QQuickProcessEnums::ProcessError error() const;
     QQuickProcessEnums::ProcessChannel readChannel() const;
     QQuickProcessEnums::ProcessChannelMode processChannelMode() const;
     QQuickProcessEnums::ExitStatus exitStatus() const;
     QQuickProcessEnums::ProcessState state() const;

 private slots:
     void onStateChanged(QProcess::ProcessState state);
     void onFinished(int exitCode, QProcess::ExitStatus exitStatus);

 signals:
     void pidChanged();
     void errorChanged();
     void stateChanged(QQuickProcessEnums::ProcessState state);
     void exitCodeChanged();
     void exitStatusChanged();
     void finished(int exitCode, QQuickProcessEnums::ExitStatus exitStatus);
     void processFinished();
     void readyReadStandardError();
     void readyReadStandardOutput();
     void started();
     void commandChanged();
     void processEnvironmentChanged();
     void workingDirectoryChanged();

private:
     QScopedPointer<QQuickProcessItemPrivate> p;
};

#endif // QPROCESSITEM_H
