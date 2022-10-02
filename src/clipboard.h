#pragma once

#include <QClipboard>
#include <QGuiApplication>
#include <QObject>
#include <QString>
#include <QTimer>

class clipboard : public QObject {
    Q_OBJECT
public:
    explicit clipboard(QObject * parent = nullptr);

    QString curClipboardContent;
    [[nodiscard]] QString getWord() const;

    void stop();
    void observe();

private:
    QClipboard * sysClipboard;
    QTimer m_clipboardMonitorTimer;
    QString m_currentContent;
    void updateCurClipboard();

signals:
    void clipChanged();
};