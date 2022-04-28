#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>

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

    clipboard * clipper;

    QString currentSearchSource;
    QVBoxLayout * toplevel;
    QHBoxLayout * dictRow;
    QWebEngineView * browser;

    void triggerSearch();

    bool event(QEvent *e) override;
};
#endif // MAINWINDOW_H
