#include "clipboard.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngineQuick/qtwebenginequickglobal.h>
#include <QQmlComponent>
#include <QQmlContext>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string_view>

QObject *toplevel;

void addDictBtn(QString name, QString prefixUrl){
    QMetaObject::invokeMethod(toplevel, "addDictBtn",Q_ARG(QString, name),Q_ARG(QString, prefixUrl));
}

void createDefaultUserConfig(const std::filesystem::path& path){
    std::ofstream configStream(path);

    configStream <<
R"(Google https://www.google.com/search?q=
Merriam-Webster https://www.merriam-webster.com/dictionary/
Wiktionary https://en.wiktionary.org/wiki/
Oxford https://www.lexico.com/definition/
Longman https://www.ldoceonline.com/dictionary/
Cambridge https://dictionary.cambridge.org/dictionary/english/)";

    configStream.close();
}


void loadUserConfig(){
    auto configFile = std::filesystem::path(getenv("HOME")) / ".kopperdict";

    if (std::filesystem::exists(configFile)){
        std::ifstream configStream(configFile);
        std::string name;
        std::string prefixUrl;
        while(configStream >> name >> prefixUrl){
            std::cout<<"nice";
            addDictBtn(QString::fromStdString(name),
                       QString::fromStdString(prefixUrl));}

    } else {
        createDefaultUserConfig(configFile);
    }
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

    // Clipboard monitor
    auto *clip = new clipboard();

    loadUserConfig();

    QObject::connect(clip, &clipboard::clipChanged, [=]() {
        wordField->setProperty("text", clip->getWord());
        QMetaObject::invokeMethod(toplevel, "triggerSearch");
    });

    return QGuiApplication::exec();
}
