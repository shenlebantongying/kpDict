#include "kpWebView.h"

kpWebView::kpWebView(QWidget *parent)
    : QWebEngineView(parent) {
  profile_s = new QWebEngineProfile();

  // copied form web, no idea about the accuracy
  profile_s->setHttpUserAgent("Mozilla/5.0 (Linux; Android 10) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.5195.136 Mobile Safari/537.36");

  page_s = new QWebEnginePage(profile_s);
  this->setPage(page_s);
}
void kpWebView::loadUrl(const QString& s) {
  page_s->load(s);
}
