#include "clipboard.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngineQuick/qtwebenginequickglobal.h>
#include <QQmlComponent>
#include <QQmlContext>

QObject *toplevel;
void addDictBtn(QString name, QString prefixUrl){
    QMetaObject::invokeMethod(toplevel, "addDictBtn",Q_ARG(QString, "nice"),Q_ARG(QString, "ok"));
}

int main(int argc, char *argv[]) {
    // WebEngine
    QtWebEngineQuick::initialize();

    // Qt
    QGuiApplication app(argc, argv);

    // QML
    QQmlApplicationEngine engine;
    QQmlComponent component(&engine, QUrl(u"qrc:/qml_web/main.qml"_qs));
    toplevel = component.create();
    auto *wordField = toplevel->findChild<QObject *>("aWordField");
    wordField->setProperty("placeholderText", "Enter your word here...");

    // Clipboard monitor
    auto *clip = new clipboard();

    QObject::connect(clip, &clipboard::clipChanged, [=]() {
        wordField->setProperty("text", clip->getWord());
        QMetaObject::invokeMethod(toplevel, "triggerSearch");
    });

    return QGuiApplication::exec();
}
