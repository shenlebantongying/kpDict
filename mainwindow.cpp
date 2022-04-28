#include "mainwindow.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    clipper = new clipboard();
    connect(clipper,
            &clipboard::clipChanged,
            this,
            [=]{ currentWord->setText(clipper->getWord());
                 triggerSearch();});

    this->setMinimumSize(800,950);

    toplevel = new QVBoxLayout(this);

    currentWord = new QLineEdit();
    currentWord->setPlaceholderText("Enter your words here...");

    connect(currentWord,
            &QLineEdit::editingFinished,
            this,
            [=]{this->triggerSearch();});

    toplevel->addWidget(currentWord);

    dictRow = new QHBoxLayout(this);

    toplevel->addLayout(dictRow);

    browser = new QWebEngineView();

    QWidget *centralWidget = new QWidget();
    centralWidget->setLayout(toplevel);

    toplevel->addWidget(browser);
    this->setCentralWidget(centralWidget);

    toplevel->setContentsMargins(0,0,0,0);

    currentSearchSource = "https://www.google.com/search?q=";

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



