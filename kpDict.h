#pragma once

#include <QCheckBox>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWebEngineView>
#include <QDir>
#include <QListWidget>
#include <QSplitter>
#include <QStringListModel>

#include "clipboard.h"

class kpDict : public QMainWindow {
    Q_OBJECT

public:
    QString currentSearchSource;

    explicit kpDict(QWidget *parent = nullptr);

    void addDict(const QString &name, const QString &dictPrefix);

    ~kpDict();

private:
    QLineEdit *wordInputField;
    QWebEngineView *browser;
    QCheckBox *autoCheckBtn;

    QListWidget *historyPanel;
    QHBoxLayout *dictRow;
    clipboard *clipper;

    QFile historyFile;

    QTextStream historyIO;

    void triggerSearch();

    void newHistory(const QString &word);
};
