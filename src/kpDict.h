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
#include <QWebEngineProfile>
#include <QWebEngineView>

#include "clipboard.h"
#include "kpWebView.h"
#include "settingsDialog.h"

class kpDict : public QMainWindow {
    Q_OBJECT

public:
    QString currentSearchSource;

    explicit kpDict(QWidget * parent = nullptr);

    void addDict(const QString & name, const QString & dictPrefix);

    ~kpDict();

private:
    QLineEdit * wordInputField;
    kpWebView * webview;
    QCheckBox * autoCheckBtn;

    QListWidget * historyPanel;
    QHBoxLayout * dictRow;
    clipboard * clipper;

    settingsDialog * settings;

    QFile historyFile;

    QTextStream historyIO;

    void triggerSearch();

    void newHistory(const QString & word);
};
