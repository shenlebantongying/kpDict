#include "clipboard.h"

clipboard::clipboard(QObject *parent)
        : QObject{parent} {
    this->sysClipboard = QGuiApplication::clipboard();

    connect(&m_clipboardMonitorTimer, &QTimer::timeout, this, [this](){ updateCurClipboard(); });
    m_clipboardMonitorTimer.start(1000);
}

QString clipboard::getWord() const {
    return m_currentContent;
}

void clipboard::updateCurClipboard(){
    const QString content = this->sysClipboard->text();

    if (content == m_currentContent){
        return;
    } else {
        m_currentContent = content;
        emit clipChanged();
    }

}
