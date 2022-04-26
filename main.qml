import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtWebEngine

Window {
    id: toplevel
    title: qsTr("KopperDict")

    width: 1024
    height: 750
    visible: true

    property string searchPrefix: "https://www.google.com/search?q="

    function triggerSearch() {
        webview.url = searchPrefix + wordField.text;
    }

    Column {
        anchors.fill: parent

        TextField {
            id: wordField
            objectName: "aWordField"
            Keys.onReturnPressed: {
                triggerSearch();
            }

            width: 1024
            padding: 10
            font.pointSize: 16
        }

        Row {
            Button {
                text: "Google"
                onClicked: {
                    toplevel.searchPrefix = "https://www.google.com/search?q=";
                    triggerSearch();
                }
            }

            Button {
                text: "Merriam-Webster"
                onClicked: {
                    toplevel.searchPrefix = "https://www.merriam-webster.com/dictionary/";
                    triggerSearch();
                }
            }

            Button {
                text: "Wiktionary"
                onClicked: {
                    toplevel.searchPrefix = "https://en.wiktionary.org/wiki/nice";
                    triggerSearch();
                }
            }

            Button {
                text: "Oxford"
                onClicked: {
                    toplevel.searchPrefix = "https://www.lexico.com/definition/";
                    triggerSearch();
                }
            }

            Button {
                text: "Longman"
                onClicked: {
                    toplevel.searchPrefix = "https://www.ldoceonline.com/dictionary/";
                    triggerSearch();
                }
            }

            Button {
                text: "Cambridge"
                onClicked: {
                    toplevel.searchPrefix = "https://dictionary.cambridge.org/dictionary/english/";
                    triggerSearch();
                }
            }
        }

        WebEngineView {
            id: webview
            width: 1024
            height: 800
        }
    }
}
