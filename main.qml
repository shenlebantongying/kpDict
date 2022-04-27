import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
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

    function addDictBtn (name:string,m_url:string){
        Qt.createQmlObject('import QtQuick;import QtQuick.Controls;
            Button {
                text: "'+name+'"
                onClicked: {
                    toplevel.searchPrefix = "'+m_url+'";
                    triggerSearch();
                }
            }',
            btnRow,
            m_url);
    }

    ColumnLayout {
        anchors.fill: parent

        TextField {
            id: wordField
            objectName: "aWordField"
            Keys.onReturnPressed: {
                triggerSearch();
            }

            Layout.fillWidth: true
            padding: 5
            font.pointSize: 16
        }

        Row {
            id: btnRow
            Button {
                text: "Google"
                onClicked: {
                    toplevel.searchPrefix = "https://www.google.com/search?q=";
                    triggerSearch();
                    addDictBtn("nice","https://www.google.com/search?q=");
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
            Layout.fillWidth: true
            Layout.preferredWidth: 1024
            Layout.preferredHeight: 750
        }
    }
}
