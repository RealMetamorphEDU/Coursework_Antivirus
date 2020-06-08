import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Universal 2.12
import QtQuick.Layouts 1.14

import ScanStatus 1.0

Page {
    id: page
    width: 800
    height: 600
    objectName: "homeForm"

    title: qsTr("Главная")

//    ColumnLayout {
//        id: columnLayout
//        width: 550
//        height: 0
//        anchors.left: parent.left
//        anchors.leftMargin: 25
//        anchors.top: parent.top
//        anchors.topMargin: 30

//        spacing: 20

        Label {
            id: pseudoLogo
            text: qsTr("Найденные файлы")
            Layout.bottomMargin: 20
            font.kerning: true
            font.preferShaping: true
            font.pointSize: 30
            layer.smooth: true
            renderType: Text.QtRendering
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 25
            anchors.topMargin: 35
        }

        ListView{
            id: listView
            width: parent.width - 50
            height: 480
            anchors.left: pseudoLogo.left
            anchors.top: pseudoLogo.bottom
            anchors.topMargin: 15
            spacing: 10
            clip: true
            model: ListModel{
                ListElement{
                    fileName: "Minecraft.exe"
                    infectionReason: "вы сейчас в него играете"
                    infected: false
                    brek: true
                }
                ListElement{
                    fileName: "Photoshop CRACK 100% WORKS 100% NOT A VIRUS.exe"
                    infectionReason: "virus"
                    infected: true
                    brek: false
                }
                ListElement{
                    fileName: "Minecraft.exe"
                    infectionReason: "вы сейчас в него играете"
                    infected: false
                    brek: true
                }
                ListElement{
                    fileName: "Photoshop CRACK 100% WORKS 100% NOT A VIRUS.exe"
                    infectionReason: "virus"
                    infected: true
                    brek: false
                }
                ListElement{
                    fileName: "Minecraft.exe"
                    infectionReason: "вы сейчас в него играете"
                    infected: false
                    brek: true
                }
                ListElement{
                    fileName: "Photoshop CRACK 100% WORKS 100% NOT A VIRUS.exe"
                    infectionReason: "virus"
                    infected: true
                    brek: false
                }
            }


            delegate: delegateComponent
        }

        Component{
            id: delegateComponent
            Row{
                height: 45
                width: listView.width - 5
                anchors.left: parent.left
                anchors.leftMargin: 5
                Layout.topMargin: 5
                spacing: 10
                Image {
                    id: fileIcon
                    source: "icons/file.png"
                    width: height
                    height: parent.height
                }
                Text{
                    text: "Файл: " + fileName
                    font.pointSize: 12
                    anchors.verticalCenter: fileIcon.verticalCenter
                }
                Text{
                    text: infected ? "Заражен: " + infectionReason : (brek ? "ОШИБКА: " + infectionReason: "")
                    font.pointSize: 12
                    anchors.verticalCenter: fileIcon.verticalCenter
                    color: infected  ? "#ff4444" : "Orange"

                }
            }
        }






}
