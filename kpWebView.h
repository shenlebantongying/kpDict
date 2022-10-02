#pragma once

#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineProfile>

/**
 * @brief Even though kpWebView inherits QWebEngineView, it should be considered
 * as a mega-class that encapsulate/wrap methods from related classes QWebEnginePage
 * Some methods are just a wrapper around QWebEnginePage or things deeper.
 *
 */
class kpWebView : public QWebEngineView
{
    Q_OBJECT
public:
  explicit kpWebView(QWidget *parent = nullptr);
  void loadUrl(const QString& s);
private:
  // _s means single page, since this app only use single page forever
  QWebEnginePage * page_s;
  QWebEngineProfile * profile_s;
};

