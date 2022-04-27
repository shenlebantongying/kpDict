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
            name);
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
            placeholderText:"Enter your word here..."
        }

        Row {
            id: btnRow
        }

        WebEngineView {
            id: webview
            Layout.fillWidth: true
            Layout.preferredWidth: 1024
            Layout.preferredHeight: 750
        }
    }
}
