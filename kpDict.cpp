#include "kpDict.h"
#include "common.h"

kpDict::kpDict(QWidget *parent)
        : QMainWindow(parent) {

    historyPanel = new QListWidget();

    // Construct GUI

    auto mainSplitter = new QSplitter(this);

    // Left side init
    auto leftContainer = new QWidget(this);
    auto leftLayout = new QVBoxLayout(this);

    autoCheckBtn = new QCheckBox(this);
    autoCheckBtn->setStyleSheet("QCheckBox::indicator { width:23px; height: 23px; }");
    autoCheckBtn->setToolTip("Auto update from clipboard");

    wordInputField = new QLineEdit(this);
    wordInputField->setContentsMargins(0, 0, 0, 0);

    auto searchBar = new QHBoxLayout(this);

    dictRow = new QHBoxLayout(this);
    dictRow->setContentsMargins(0, 0, 0, 0);

    browser = new QWebEngineView(this);

    // Left side combing

    searchBar->addWidget(autoCheckBtn);
    searchBar->addWidget(wordInputField);

    leftLayout->addLayout(searchBar);
    leftLayout->addLayout(dictRow);
    leftLayout->addWidget(browser);
    leftLayout->setSpacing(0);
    leftLayout->setContentsMargins(0, 0, 0, 0);

    leftContainer->setLayout(leftLayout);

    mainSplitter->addWidget(leftContainer);
    mainSplitter->addWidget(historyPanel);

    this->setCentralWidget(mainSplitter);
    this->setMinimumSize(500, 400);
    this->resize(850, 850);

    // Logic
    clipper = new clipboard();

    // Handle History file
    // TODO: ugly
    auto p = QDir::home();
    p.cd(KPDICT_PATH);
    historyFile.setFileName(p.absoluteFilePath("history"));

    // load existing history to cachedHistory
    historyFile.open(QIODevice::ReadOnly | QIODevice::Text);
    historyIO.setDevice(&historyFile);
    QStringList cachedHistory;
    while (!historyIO.atEnd()) {
        QString line = historyIO.readLine();
        if (!line.isEmpty()) {
            cachedHistory << line;
        }
    }
    historyFile.close();


    // If existing length > HISTORY_CAP, nuke the file
    // We only want last 100 history

    const int HISTORY_CAP = 200;
    const int HISTORY_EXPECTED_LENGTH = 100;
    assert(HISTORY_CAP > HISTORY_EXPECTED_LENGTH);

    if (cachedHistory.length() > HISTORY_CAP) {
        historyFile.resize(0);
        cachedHistory.remove(0, cachedHistory.length() - HISTORY_EXPECTED_LENGTH);

        historyFile.open(QIODevice::WriteOnly | QIODevice::Text);
        historyIO.setDevice(&historyFile);
        for (const auto &s: cachedHistory) {
            historyIO << s << Qt::endl;
        }
        historyFile.close();

    }

    historyFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text | QIODevice::Unbuffered);
    historyIO.setDevice(&historyFile);

    for (const auto &s: cachedHistory) {
        historyPanel->addItem(s);
    }


    cachedHistory.clear();

    // At this point, the historyIO is at the end pos which can be written in other func

    connect(clipper, &clipboard::clipChanged,
            this, [=] {
                wordInputField->setText(clipper->getWord());
                triggerSearch();
                newHistory(this->wordInputField->text());
            });

    connect(wordInputField, &QLineEdit::editingFinished,
            this, [=] {
                this->triggerSearch();
                newHistory(this->wordInputField->text());
            });

}

void kpDict::addDict(const QString &name, const QString &dictPrefix) {
    auto gbtn = new QPushButton(name, this);
    connect(gbtn, &QPushButton::clicked,
            this, [=] {
                this->currentSearchSource = dictPrefix;
                triggerSearch();
            });

    connect(autoCheckBtn, &QCheckBox::stateChanged,
            this, [=](int state) {
                if (Qt::CheckState::Checked == state) {
                    clipper->observe();
                } else if (Qt::CheckState::Unchecked == state) {
                    clipper->stop();
                }
            });

    autoCheckBtn->setCheckState(Qt::Checked);
    dictRow->addWidget(gbtn);
}


void kpDict::triggerSearch() {
    browser->load(this->currentSearchSource + this->wordInputField->text());
}

void kpDict::newHistory(const QString &word) {
    historyIO << wordInputField->text() << Qt::endl;;
    historyPanel->insertItem(0, word);
}

kpDict::~kpDict()
= default;

