import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Universal 2.12
import QtQuick.Layouts 1.14
import ScanStatus 1.0

Page {
    id: page
    objectName: "page2Form"
    width: 800
    height: 600
    title: qsTr("Сканировать файлы...")

    signal addDir()
    signal switchClicked()
    signal remDir(string path)
    signal foundThreats()

    ColumnLayout{
        id: mainLayout
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 25
        width: page.width - 50
        spacing: 20

        ColumnLayout {
            id: columnLayout
            width: parent.width - 50


            Label {
                id: windowTitle
                text: qsTr("Мониторинг директорий")
                Layout.bottomMargin: 10
                font.kerning: true
                font.preferShaping: true
                font.pointSize: 30
                layer.smooth: true
                renderType: Text.QtRendering
            }

            Label {
                id: watcherStateText
                text: qsTr("Состояние работы")
            }
            Switch {
                id: stateSwitch
                objectName: "stateSwitch"
                checked: WatchProperties.watcherOn
                enabled: !WatchProperties.watcherTurningOn
                text: checked ? qsTr("вкл.") : qsTr("выкл.")
                padding: 0
                bottomPadding: 5
                topPadding: 5

                onClicked: {
                    switchClicked()
            }
            }
            Button {
                id: chooseButton
                width: 195
                text: qsTr("Добавить директорию для мониторинга...")
                Layout.fillWidth: false
                icon.source: "icons/folder.png"
                onClicked: addDir()
            }


        }

        ColumnLayout{
            spacing: 10
            Label {
                id: stateText
                text: qsTr("Наблюдаемые директории")
                font.pointSize: 16
            }
            ListView{
                id: listView
                width: mainLayout.width
                height: 260
                Layout.rightMargin: 0
                Layout.leftMargin: 0
                //                anchors.top: columnLayout.bottom
                //                anchors.topMargin: 15
                //spacing: 20
                clip: true
                model: WatchingDirectoriesModel{
                    list: DirectoriesList
                }

//                model: ListModel{
//                    ListElement{
//                        dir: "C:\\Papka"
//                    }

//                    ListElement{
//                        dir: "C:\\EshoPapka"
//                    }

//                    ListElement{
//                        dir: "C:\\DrugayaPapka\\PapkaVPapke"
//                    }

//                    ListElement{
//                        dir: "C:\\Games\\Counter-strike"
//                    }
//                }
                //model:
                delegate: delegateComponent
            }


        }
        Button {
            id: threatsButton
            width: 195
            text: qsTr("Найденные угрозы...")
            Layout.fillWidth: false
            onClicked: foundThreats()
            //icon.source: "icons/folder.png"
        }

        Component{
            id: delegateComponent
            ItemDelegate{
                id: itemDelegate
                //state: "expanded"
                height: 40
                width: page.width - 50
                Row {
                    leftPadding: 10
                    rightPadding: 10
                    id: dirRow
                    spacing: 6
                    height: parent.height
                    width: parent.width
                    /*
                    anchors.top: row.bottom
                    anchors.topMargin: 20
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 5
                    anchors.left: parent.left
                    anchors.leftMargin: 5*/
                    Text {
                        id: dirName
                        /*
                        anchors.left: parent.left
                        anchors.leftMargin: 10*/
                        anchors.top: parent.top
                        anchors.topMargin: parent.height/2 - height/2
                        text: path
                        font.pointSize: 14

                    }
                }

//                Button {
//                    visible: false
//                    id: moreButton
//                    text: qsTr("Подробнее")
//                    //anchors.verticalCenter: dirName.verticalCenter
//                    anchors.right: delButton.left
//                    anchors.rightMargin: 10
//                    anchors.bottom: parent.bottom
//                    anchors.bottomMargin: 10
//                }

                Button {
                    visible: false
                    id: delButton
                    text: qsTr("Снять с наблюдения")
                    //anchors.verticalCenter: dirName.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 10
                    icon.source: "icons/close.png"
                    onClicked: remDir(path)
                }

                states:[
                    State{
                        name: "expanded"
                        PropertyChanges { target: itemDelegate; height: 75}
                        PropertyChanges { target: delButton; visible: true}
                        PropertyChanges { target: dirName; anchors.topMargin: 10}
                    }

                ]

                onClicked: state = state === "" ? "expanded" : ""
            }

        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
