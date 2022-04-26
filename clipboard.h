#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <QObject>
#include <QClipboard>
#include <QGuiApplication>
#include <QString>

class clipboard : public QObject {
Q_OBJECT
public:
    explicit clipboard(QObject *parent = nullptr);

    QClipboard *sysClipboard;

    QString getWord() const;

signals:

    void clipChanged();
};

#endif // CLIPBOARD_H
