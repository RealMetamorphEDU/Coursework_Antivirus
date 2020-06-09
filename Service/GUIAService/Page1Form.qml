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

        delegate: delegateComponent
    }
    Component{
        id: delegateComponent
        ItemDelegate {
            id: itemDelegate
            width: page.width - 50
            height: 50
            state: completed ? "" : "expanded"
            //state: "expanded"
            property bool completed : !scanning && objLeft === 0 && lastObject === ""
            property bool paused : !scanning && objLeft > 0

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
                                   (completed ? "Готово" : paused ? "Приостановлено" : "В процессе"))
                        anchors.left: parent.left
                        anchors.leftMargin: parent.width + 10
                        anchors.top: parent.top
                        anchors.topMargin: parent.height / 2 - height / 2

                        font.pointSize: 14
                        BusyIndicator {
                            visible: !completed && !paused
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
            Row{
                visible: false
                id: runningRow
                spacing: 6
                anchors.top: row.bottom
                anchors.topMargin: 20
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 5
                ColumnLayout{
                    Row{

                        spacing: 6
                        Text{
                            id: lastFileText
                            text: qsTr("Последний файл: " + lastObject + "  ")
                            font.pointSize: 12
                        }
                        ProgressBar{
                            width: itemDelegate.width * 0.38
                            anchors.verticalCenter: lastFileText.verticalCenter
                            to: objScanned+objLeft
                            value: objScanned

                        }

                        Text{
                            text: qsTr(objScanned.toString() + " из " + (objScanned+objLeft).toString())
                            font.pointSize: 12
                        }
                        Button{
                            text: qsTr(!paused ? "Пауза" : "Продолжить")
                            anchors.verticalCenter: lastFileText.verticalCenter
                            icon.source: !paused ? "icons/pause.png" : "icons/play-button.png"
                        }
                    }
                    Row{
                        spacing: 6

                        Button{
                            id: moreButton2
                            text: "Подробности"
                        }
                        Text{
                            text: qsTr("Найдено угроз: " + foundCount)
                            anchors.verticalCenter: moreButton2.verticalCenter
                            font.pointSize: 12
                            color: foundCount > 0 ? "Red" : "Black"
                        }
                    }

                }
            }



            Button{
                id: deleteButton
                visible: false
                text: qsTr("")
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 11
                icon.source: "icons/close.png"
            }
            onClicked: state = state == "" ? "expanded" : ""

            states:[
                State{
                    name: "expanded"

                    PropertyChanges { target: completedRow; visible: completed }
                    PropertyChanges { target: runningRow; visible: !completed }
                    PropertyChanges { target: itemDelegate; height: completed ? 95 : 135}
                    PropertyChanges { target: deleteButton; visible: true}
                }

            ]
        }
    }

}
