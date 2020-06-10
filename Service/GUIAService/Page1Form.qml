import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Universal 2.12
import QtQuick.Layouts 1.14

import ScanStatus 1.0

Page {
    id: page
    objectName: "page1Form"
    width: 800
    height: 600
    signal chooseFileButtonClicked()
    signal chooseFolderButtonClicked()
    signal pauseClicked(int taskID)
    signal stopClicked(int taskID)
    signal continueClicked(int taskID)
    signal objectInfoClicked(int taskID)
    title: qsTr("Сканировать файлы...")

    ColumnLayout {
        id: columnLayout
        width: parent.width - 50
        anchors.left: parent.left
        anchors.leftMargin: 25
        anchors.top: parent.top
        anchors.topMargin: 30

        Label {
            id: windowTitle
            text: qsTr("Сканирование объектов")
            Layout.bottomMargin: 10
            font.kerning: true
            font.preferShaping: true
            font.pointSize: 30
            layer.smooth: true
            renderType: Text.QtRendering
        }

        Label {
            id: stateText
            text: qsTr("Открытие объекта для сканирования")
            font.pointSize: 16
        }
        Row{
            spacing: 5
            Button {
                id: chooseFileButton
                objectName: "chooseFileButton"
                width: 195
                text: qsTr("Открыть файл...")
                Layout.fillWidth: false
                icon.source: "icons/file.png"
                onClicked:
                {
                    console.log(chooseFileButton.text)
                    chooseFileButtonClicked();
                }

            }
            Button {
                id: chooseFolderButton
                objectName: "chooseFolderButton"
                width: 195
                text: qsTr("Открыть папку...")
                Layout.fillWidth: false
                icon.source: "icons/folder.png"
                onClicked:
                {
                    console.log(chooseFolderButton.text)
                    chooseFolderButtonClicked();
                }

            }

        }

        Label {
            id: label
            width: 318
            height: 20
            text: qsTr("Можно открыть как файл, так и целую папку")
            wrapMode: Text.WordWrap
        }
    }
    ListView {
        id: listView
        width: columnLayout.width
        height: 360
        anchors.left: parent.left
        anchors.leftMargin: 25
        anchors.top: columnLayout.bottom
        anchors.topMargin: 15
        spacing: 5
        clip: true

        model: ScanStatusModel {
            statusList: StatusList
        }
//        model: ListModel{
//            ListElement{
//                scanning: true
//                pause: false
//                taskIndex: 3
//                lastObject: "D:\\Users\\aineb\\Documents\\DuckGame\\ChallengeData\\1abc0a39-09e1-424f-9e21-9602c41b7da9.dat"
//                objLeft: 300000
//                objScanned: 300000
//                foundCount: 0
//            }
//        }

        delegate: delegateComponent
    }
    Component{
        id: delegateComponent
        ItemDelegate {
            id: itemDelegate
            width: page.width - 50
            height: 50
            state: !scanning ? "" : "expanded"
            //state: "expanded"
            padding: 5


            function trunc(str){
                if (str.length > 40){
                    return str.slice(0,19) + " ... " + str.slice(str.length-21,str.length)
                }
                return str;
            }

            Row {
                id: row
                spacing: 20
                anchors.left: parent.left
                anchors.leftMargin: 5
                //height: delegateComponent.state === "" ? parent.height : parent.height-25

                Image {
                    id: image
                    height: 35
                    width: height
                    fillMode: Image.PreserveAspectFit
                    source: "icons/search.png"
                    anchors.top: row.top
                    anchors.topMargin: 8
                    Text {
                        text: qsTr("Сканирование #" + taskIndex.toString() + " - " +
                                   (!scanning ? "Готово" : pause ? "Приостановлено" : "В процессе"))
                        anchors.left: parent.left
                        anchors.leftMargin: parent.width + 10
                        anchors.top: parent.top
                        anchors.topMargin: parent.height / 2 - height / 2

                        font.pointSize: 14
                        BusyIndicator {
                            visible: scanning && !pause
                            anchors.left: parent.left
                            anchors.leftMargin: parent.width + 10
                            anchors.top: parent.top
                            anchors.topMargin: parent.height / 2 - height / 2
                            width: parent.parent.width
                            height: parent.parent.height
                        }
                    }
                }
            }

            Row{

                visible: false
                id: completedRow
                spacing: 10
                anchors.top: row.bottom
                anchors.topMargin: 20
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 5

                Button{
                    id: moreButton
                    text: "Подробности"
                    onClicked: objectInfoClicked(taskIndex)
                }
                Text{
                    text: qsTr("Найдено угроз: " + foundCount)
                    anchors.verticalCenter: moreButton.verticalCenter
                    font.pointSize: 12
                    color: foundCount > 0 ? "Red" : "Black"
                }
            }


//            Row{
//                visible: false
//                id: runningRow
//                spacing: 6
//                anchors.top: row.bottom
//                anchors.topMargin: 20
//                anchors.bottom: parent.bottom
//                //                anchors.bottomMargin: 5
//                anchors.left: parent.left
//                anchors.leftMargin: 5
//                anchors.right: parent.right

                Text{
                    visible: false
                    id: lastFileText
                    anchors.top: row.bottom
                    anchors.topMargin: 20
                    anchors.left: row.left
                    text: qsTr("Последний файл: " + trunc(lastObject) + "  ")
                    font.pointSize: 12
                }

                Row{
                    visible: false
                    id: ppRow
                    parent: itemDelegate
                    anchors.verticalCenter: lastFileText.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    spacing: 10
                    Text{
                        text: qsTr(objScanned + " из " + (objScanned+objLeft))
                        font.pointSize: 12
                        //                    anchors.right: ppButton.left
                        //                    anchors.rightMargin: 10
                        anchors.verticalCenter: ppButton.verticalCenter
                    }
                    Button{
                        id: ppButton
                        text: qsTr(!pause ? "Пауза" : "Продолжить")
                        enabled: enabledState
                        icon.source: !pause ? "icons/pause.png" : "icons/play-button.png"
                        onClicked: !pause ? pauseClicked(taskIndex) : continueClicked(taskIndex)
                    }
                }
                ProgressBar{
                    visible: false
                    id: progressBar
                    width: itemDelegate.width - 14
                    //anchors.verticalCenter: lastFileText.verticalCenter
                    //anchors.fill: parent
                    anchors.top: lastFileText.bottom
                    anchors.topMargin: 15
                    anchors.left: lastFileText.left
                    to: objScanned+objLeft
                    value: objScanned

                }
                Row{
                    visible: false
                    id: mtRow
                    //anchors.top: progressBar.bottom
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 11
                    anchors.left: progressBar.left
                    spacing: 6

                    Button{
                        id: moreButton2
                        text: "Подробности"
                        onClicked: objectInfoClicked(taskIndex)
                    }
                    Text{
                        text: qsTr("Найдено угроз: " + foundCount)
                        anchors.verticalCenter: moreButton2.verticalCenter
                        font.pointSize: 12
                        color: foundCount > 0 ? "Red" : "Black"
                    }
                }






            Button{
                id: deleteButton
                visible: false
                text: qsTr("")
                enabled: enabledState
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 11
                icon.source: "icons/close.png"
                onClicked: stopClicked(taskIndex)
            }
            onClicked: state = state == "" ? "expanded" : ""

            states:[
                State{
                    name: "expanded"

                    PropertyChanges { target: completedRow; visible: !scanning }
                    PropertyChanges { target: lastFileText; visible: scanning }
                    PropertyChanges { target: ppRow; visible: scanning }
                    PropertyChanges { target: progressBar; visible: scanning }
                    PropertyChanges { target: mtRow; visible: scanning }
                    PropertyChanges { target: itemDelegate; height: !scanning ? 95 : 155}
                    PropertyChanges { target: deleteButton; visible: true}
                }

            ]
        }
    }

}
