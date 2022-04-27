#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <QObject>
#include <QClipboard>
#include <QGuiApplication>
#include <QString>
#include <QTimer>

class clipboard : public QObject {
Q_OBJECT
public:
    explicit clipboard(QObject *parent = nullptr);

    QString curClipboardContent;
    [[nodiscard]] QString getWord() const;

private:
    QClipboard *sysClipboard;
    QTimer m_clipboardMonitorTimer;
    QString m_currentContent;
    void updateCurClipboard();

signals:
    void clipChanged();
};

#endif // CLIPBOARD_H
