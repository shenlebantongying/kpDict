#include "clipboard.h"

clipboard::clipboard(QObject *parent)
        : QObject{parent} {
    this->sysClipboard = QGuiApplication::clipboard();

    connect(&m_clipboardMonitorTimer, &QTimer::timeout, this, [this](){ updateCurClipboard(); });
}

QString clipboard::getWord() const {
    return m_currentContent;
}

void clipboard::updateCurClipboard(){
    const QString content = this->sysClipboard->text();


    if (content == m_currentContent ||
        content.length() == 0 // TODO: Hack due to wayland, remove when KF6 released.
    ){
        return;
    } else {
        m_currentContent = content;
        emit clipChanged();
    }

}

void clipboard::stop() {
    m_clipboardMonitorTimer.stop();
}

void clipboard::observe() {
    m_clipboardMonitorTimer.start(1000);
}
