#pragma once
#include <QDialog>

/**
 * @brief This class has a single vbox ruling everything.
 * If we need secondary setting panel, it means we failed to deliver a simple app.
 */
class settingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit settingsDialog(QWidget *parent = nullptr);
signals:

};
