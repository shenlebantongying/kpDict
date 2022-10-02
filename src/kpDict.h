#pragma once

#include <QCheckBox>
#include <QDir>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QSplitter>
#include <QStringListModel>
#include <QVBoxLayout>
#include <QWebEngineView>
#include <QWebEngineProfile>

#include "clipboard.h"
#include "kpWebView.h"

class kpDict : public QMainWindow {
    Q_OBJECT

public:
    QString currentSearchSource;

    explicit kpDict(QWidget *parent = nullptr);

    void addDict(const QString &name, const QString &dictPrefix);

    ~kpDict();

private:
    QLineEdit *wordInputField;
    kpWebView *webview;
    QCheckBox *autoCheckBtn;

    QListWidget *historyPanel;
    QHBoxLayout *dictRow;
    clipboard *clipper;

    QFile historyFile;

    QTextStream historyIO;

    void triggerSearch();

    void newHistory(const QString &word);
};
