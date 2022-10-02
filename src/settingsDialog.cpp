#include "settingsDialog.h"
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QListWidget>

settingsDialog::settingsDialog(QWidget *parent)
    : QDialog{parent}
{
    auto vbox = new QVBoxLayout();

    // About
    auto aboutBox = new QGroupBox("About");
    auto aboutLayout = new QFormLayout();

    auto homePageLabel = new QLabel(R"(<a href=https://gitlab.com/slbtty/kopperdict>https://gitlab.com/slbtty/kopperdict</a>)");
    homePageLabel->setTextFormat(Qt::RichText);
    homePageLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    homePageLabel->setOpenExternalLinks(true);

    aboutLayout->addRow("website",homePageLabel);
    aboutBox->setLayout(aboutLayout);

    // Finalize
    vbox->addWidget(aboutBox);
    this->setLayout(vbox);

}