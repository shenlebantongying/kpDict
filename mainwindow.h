#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCheckBox>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWebEngineView>

#include "clipboard.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void addDict(const QString& name, const QString& dictPrefix);

    ~MainWindow();
private:
    // Yes, use currentWord to hold current word,
    // So that the need for sync data is eliminated.
    QLineEdit * currentWord;
    QWebEngineView * browser;
    QCheckBox * autoCheckBtn;


    clipboard * clipper;
    QString currentSearchSource;

    // Layout related
    QVBoxLayout * toplevel;
    QHBoxLayout * searchBar;
    QHBoxLayout * dictRow;


    void triggerSearch();

};
#endif // MAINWINDOW_H
