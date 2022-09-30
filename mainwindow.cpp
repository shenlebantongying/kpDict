#include "mainwindow.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // News
    clipper     = new clipboard();

    toplevel    = new QVBoxLayout(this);
    autoCheckBtn = new QCheckBox();
    searchBar = new QHBoxLayout(this);
    currentWord = new QLineEdit();

    dictRow     = new QHBoxLayout(this);
    browser     = new QWebEngineView();

    QWidget *centralWidget = new QWidget();

    currentSearchSource = "https://www.google.com/search?q=";

    autoCheckBtn->setStyleSheet("QCheckBox::indicator { width:23px; height: 23px; }");
    autoCheckBtn->setToolTip("Auto update from clipboard");

    searchBar->addWidget(autoCheckBtn);
    searchBar->addWidget(currentWord);

    // Composition
    toplevel->addLayout(searchBar);
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

    connect(autoCheckBtn,&QCheckBox::stateChanged,
            this,[=](int state) {
              if ( Qt::CheckState::Checked == state){
                clipper->observe();
              } else if (Qt::CheckState::Unchecked == state) {
                clipper -> stop();
              }
    });

    autoCheckBtn->setCheckState(Qt::Checked);


    dictRow->addWidget(gbtn);
}

void MainWindow::triggerSearch(){
    browser->load(this->currentSearchSource + this->currentWord->text());
}

MainWindow::~MainWindow()
= default;

// Hard to design. You cannot perfectly determine if user want to copy & search the word

//bool MainWindow::event(QEvent *e) {
//    if (e->type() == QEvent::WindowActivate) {
//        clipper->stop();
//    } else if (e->type() == QEvent::WindowDeactivate){
//        clipper->observe();
//    }
//    return QMainWindow::event(e);
//}
//


