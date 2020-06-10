import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Universal 2.12
import QtQuick.Layouts 1.14
import QtQuick.Dialogs 1.2
import ScanStatus 1.0
import QtQuick.Window 2.12

Window {
    visible: true
    title: "Подробности о сканировании"
    width: 800
    height: 600
    maximumHeight: height
    maximumWidth: width

    minimumHeight: height
    minimumWidth: width

    Page {
        id: page
        width: parent.width
        height: parent.height
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
            text: qsTr("Подробности о сканировании #"  + taskIndex)
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

        Label {
            id: amountLabel
            text: qsTr("Проверено файлов: " + listView.model.objectCount)

            font.pointSize: 16
            anchors.left: pseudoLogo.left
            anchors.top: pseudoLogo.bottom
            anchors.topMargin: 25
        }

        Label {
            id: checkedLabel
            text: qsTr("Проверенные файлы и найденные угрозы:")
            font.pointSize: 16
            anchors.left: amountLabel.left
            anchors.top: amountLabel.bottom
            anchors.topMargin: 20
        }
        ListView{
            id: listView
            width: parent.width - 50
            height: 360
//            flickableDirection: Flickable.VerticalFlick
//            boundsBehavior: Flickable.StopAtBounds
            anchors.left: checkedLabel.left
            anchors.top: checkedLabel.bottom
            anchors.topMargin: 15
            spacing: 10
            clip: true
            model: ObjectStatusModel{
                statusList: objectList
            }

            ScrollBar.vertical: ScrollBar{
                width:20
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                height: parent.height
                //policy: ScrollBar.AsNeeded
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
                function trunc(str){
                    if (str.length > 70){
                        return str.slice(0,32) + " ... " + str.slice(str.length-36,str.length)
                    }
                    return str;
                }

                Image {
                    id: fileIcon
                    source: "icons/file.png"
                    width: height
                    height: parent.height
                }
                Text{
                    text: "Файл: " + trunc(path)
                    font.pointSize: 12
                    anchors.verticalCenter: fileIcon.verticalCenter
                }
                Text{
                    text: infected ? "Заражен: " + infection : (brek ? "ОШИБКА: " + infection: "")
                    font.pointSize: 12
                    anchors.verticalCenter: fileIcon.verticalCenter
                    color: infected  ? "#ff4444" : "Orange"

                }
            }
        }






    }
}
