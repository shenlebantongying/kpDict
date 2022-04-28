#include "mainwindow.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // News
    clipper     = new clipboard();
    toplevel    = new QVBoxLayout(this);
    currentWord = new QLineEdit();
    dictRow     = new QHBoxLayout(this);
    browser     = new QWebEngineView();

    QWidget *centralWidget = new QWidget();

    currentSearchSource = "https://www.google.com/search?q=";


    // Composition
    toplevel->addWidget(currentWord);
    toplevel->addLayout(dictRow);
    toplevel->addWidget(browser);

    centralWidget->setLayout(toplevel);
    this->setCentralWidget(centralWidget);

    // Styling
    this->setMinimumSize(800,950);

    toplevel->setSpacing(0);
    currentWord->setContentsMargins(0,0,0,0);
    dictRow->setContentsMargins(0,0,0,0);
    toplevel->setContentsMargins(0,0,0,0);

    currentWord->setPlaceholderText("Enter your words here...");

    // Logic

    connect(clipper,
            &clipboard::clipChanged,
            this,
            [=]{ currentWord->setText(clipper->getWord());
                 triggerSearch();});

    connect(currentWord,
            &QLineEdit::editingFinished,
            this,
            [=]{this->triggerSearch();});

}

void MainWindow::addDict(const QString& name, const QString& dictPrefix){
    auto gbtn = new QPushButton(name,this);
    connect(gbtn,&QPushButton::clicked,
            this,[=]{ this->currentSearchSource=dictPrefix;
                      triggerSearch();});

    dictRow->addWidget(gbtn);
}

void MainWindow::triggerSearch(){
    browser->load(this->currentSearchSource + this->currentWord->text());
}

MainWindow::~MainWindow()
= default;

bool MainWindow::event(QEvent *e) {
    if (e->type() == QEvent::WindowActivate) {
        clipper->stop();
    } else if (e->type() == QEvent::WindowDeactivate){
        clipper->observe();
    }
    return QMainWindow::event(e);
}



