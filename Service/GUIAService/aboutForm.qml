import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Universal 2.12
import QtQuick.Layouts 1.14

Page {
    id: page
    width: 800
    height: 600
    objectName: "aboutForm"
    signal switchClicked()
    title: qsTr("О программе")
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
            text: qsTr("Разработчики:")
            Layout.bottomMargin: 20
            font.kerning: true
            font.preferShaping: true
            font.pointSize: 30
            layer.smooth: true
            renderType: Text.QtRendering
        }

        Column {
            id: dataList
            width: 200
            height: 400
            Layout.bottomMargin: 20
            Label {
                id: group
                text: qsTr("Студенты группы БВТ1702")
                font.pointSize: 15
            }
            Pane {
                width: parent.width
                background: Rectangle {
                    //color: "#eeeeee"
                }

                Label {
                    id: dev1
                    text: qsTr("Тимчук Андрей Васильевич")
                }

            }
            Pane {
                width: parent.width
                background: Rectangle {
                    //color: "#eeeeee"
                }

                Label {
                    id: dev2
                    text: qsTr("Рыбаков Даниил Виктович")
                }

            }
            Pane {
             width: parent.width
                background: Rectangle {
                    //color: "#eeeeee"
                }

                Label {
                    id: dev3
                    text: qsTr("Жмакин Евгений Вячеславович")
                }

            }




        }





    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}D{i:1;anchors_x:0;anchors_y:0}
}
##^##*/

