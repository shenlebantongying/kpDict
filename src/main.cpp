
#include <QApplication>
#include <QDir>
#include <QFile>
#include <iostream>

#include "common.h"
#include "kpDict.h"

kpDict * kpdict;

void loadUserConfig() {
    auto p = QDir::home();
    p.mkpath(kp::CONFIG_PATH);
    p.cd(kp::CONFIG_PATH);

    auto configFile = QFile(p.absoluteFilePath("urls"));


    // ensure default config file
    if (!configFile.exists()) {
        configFile.open(QIODevice::WriteOnly);
        QTextStream out(&configFile);
        out <<
                R"(Google https://www.google.com/search?q=
Merriam-Webster https://www.merriam-webster.com/dictionary/
Wiktionary https://en.wiktionary.org/wiki/
Oxford https://www.dictionary.com/browse/
Longman https://www.ldoceonline.com/dictionary/
Cambridge https://dictionary.cambridge.org/dictionary/english/
Youdao https://www.youdao.com/result?lang=en&word=)";
        configFile.close();
    }

    // load config
    configFile.open(QIODevice::ReadOnly);
    QTextStream in(&configFile);

    bool initSetted = false;

    while (!in.atEnd()) {
        QString line = in.readLine();
        auto urlSeg = line.trimmed().simplified().split(" ");
        if (urlSeg.first().length() == 0) {
            continue;
        }
        kpdict->addDict(urlSeg.first(), urlSeg.last());
        if (not initSetted) {
            kpdict->currentSearchSource = urlSeg.last();
            initSetted = true;
        }
    }

    configFile.close();
}

int main(int argc, char * argv[]) {
    QApplication a(argc, argv);
    kpdict = new kpDict();
    loadUserConfig();
    kpdict->show();
    return QApplication::exec();
}
