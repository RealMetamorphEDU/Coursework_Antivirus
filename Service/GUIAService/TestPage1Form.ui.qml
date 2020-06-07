import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Universal 2.12
import QtQuick.Layouts 1.14

import ScanStatus 1.0

Page {
    width: 800
    height: 600

    title: qsTr("Page 1")

    ColumnLayout {
        id: columnLayout
        width: parent.width - 50
        height: 0
        anchors.left: parent.left
        anchors.leftMargin: 25
        anchors.top: parent.top
        anchors.topMargin: 30

        Label {
            id: windowTitle
            text: qsTr("Сканирование объектов")
            Layout.bottomMargin: 20
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

        Button {
            id: chooseButton
            width: 195
            text: qsTr("Открыть...")
            Layout.fillWidth: false
            icon.source: "icons/folder.png"
        }

        Label {
            id: label
            width: 318
            height: 20
            text: qsTr("Можно открыть как файл, так и целую папку")
            wrapMode: Text.WordWrap
        }

        RowLayout {
            id: rowLayout
            width: columnLayout.width
            height: 380

//            delegate: Column {
//                Text {
//                    text: model.scanning.toString()
//                }

//                Text {
//                    text: model.taskIndex.toString()
//                }

//                Text {
//                    text: model.taskCount.toString()
//                }

//                Text {
//                    text: model.lastObject.toString()
//                }

//                Text {
//                    text: model.objLeft.toString()
//                }

//                Text {
//                    text: model.objScanned.toString()
//                }
//            }

            Row {
                id: row
                width: parent.width
                height: parent.height / 6 - 10
                anchors.top: parent.top
                anchors.topMargin: 10


                Image {
                    id: image
                    width: row.height * 0.8
                    height: row.height * 0.8
                    fillMode: Image.PreserveAspectFit
                    source: "icons/file.png"
                    anchors.top: row.verticalCenter
                    anchors.topMargin: -height/2
                }

                Text {
                    id: element
                    text: qsTr("Сканирование #")
//                    anchors.left: image.right
//                    anchors.leftMargin: 0
                    anchors.top: row.verticalCenter
                    anchors.topMargin: -height/2
                    font.pixelSize: 14
                }
                Text {
                    id: element1
                    text: qsTr("3")
                    font.pixelSize: 14
                    anchors.top: row.verticalCenter
                    anchors.topMargin: -height/2
//                    anchors.left: element.right
//                    anchors.leftMargin: 0
                }

                ProgressBar {
                    id: progressBar
                    width: row.width * 0.6
//                    anchors.left: element1.right
//                    anchors.leftMargin: 20
                    value: 0.5
                    anchors.top: parent.verticalCenter
                    anchors.topMargin: -height/2 + 1
                }

            }


        }
    }
}
