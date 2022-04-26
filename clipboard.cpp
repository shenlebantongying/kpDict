#include "clipboard.h"

clipboard::clipboard(QObject *parent)
        : QObject{parent} {
    this->sysClipboard = QGuiApplication::clipboard();

    connect(sysClipboard, &QClipboard::dataChanged, this, [=]() { emit clipChanged(); });
}

QString clipboard::getWord() const {
    return sysClipboard->text();
}
