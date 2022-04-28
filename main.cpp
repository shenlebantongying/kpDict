#include "mainwindow.h"

#include <QApplication>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string_view>
MainWindow * win;

void createDefaultUserConfig(const std::filesystem::path& path){
    std::ofstream configStream(path);

    configStream <<
                 R"(Google https://www.google.com/search?q=
Merriam-Webster https://www.merriam-webster.com/dictionary/
Wiktionary https://en.wiktionary.org/wiki/
Oxford https://www.lexico.com/definition/
Longman https://www.ldoceonline.com/dictionary/
Cambridge https://dictionary.cambridge.org/dictionary/english/
Youdao https://www.youdao.com/result?lang=en&word=)";

    configStream.close();
}

void loadUserConfig(){
    auto configFile = std::filesystem::path(getenv("HOME")) / ".kopperdict";

    if (!std::filesystem::exists(configFile)){
        createDefaultUserConfig(configFile);
    }

    std::ifstream configStream(configFile);
    std::string name;
    std::string prefixUrl;
    while(configStream >> name >> prefixUrl){
        std::cout<<"nice";
        win->addDict(QString::fromStdString(name),
                   QString::fromStdString(prefixUrl));}
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    win = new MainWindow();
    loadUserConfig();
    win->show();
    return QApplication::exec();
}
