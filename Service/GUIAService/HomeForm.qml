import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Universal 2.12
import QtQuick.Layouts 1.14

Page {
    id: page
    width: 800
    height: 600


    title: qsTr("Главная")

    ColumnLayout {
        id: columnLayout
        width: 550
        height: 0
        anchors.left: parent.left
        anchors.leftMargin: 25
        anchors.top: parent.top
        anchors.topMargin: 30

        Label {
            id: pseudoLogo
            text: qsTr("Антивирус")
            Layout.bottomMargin: 20
            font.kerning: true
            font.preferShaping: true
            font.pointSize: 30
            layer.smooth: true
            renderType: Text.QtRendering
        }

        Column {
            id: stateColumn
            width: 200
            height: 400
            Layout.bottomMargin: 20

            Label {
                id: stateText
                text: qsTr("Состояние работы")
            }

            Switch {
                id: stateSwitch
                text: checked ? qsTr("вкл.") : qsTr("выкл.")
                anchors.left: parent.left
                anchors.leftMargin: -5
                Layout.leftMargin: -5
            }
        }

        Button {
            id: button
            text: qsTr("Сканировать файлы...")
            Layout.fillWidth: false
            display: AbstractButton.TextBesideIcon
            layer.smooth: true
            antialiasing: true
            icon.name: "system-search"
            icon.source: "icons/search.png"
            width: button1.width
            onClicked: {
                stackView.push("Page1Form.qml")
                drawer.close()
            }
        }

        Button {
            id: button1
            width: 195
            text: qsTr("Монитор директорий")
            Layout.fillWidth: false
            icon.source: "icons/eye.png"
            onClicked: {
                stackView.push("Page2Form.qml")
                drawer.close()
            }
        }




    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}D{i:1;anchors_x:0;anchors_y:0}
}
##^##*/

