import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Universal 2.12

ApplicationWindow {
    id: window
    visible: true
    width: 1000
    height: 600
    signal page1Created(string name)
    signal page2Created(string name)
    signal homeCreated(string name)
//    maximumHeight: height
//    maximumWidth: width

//    minimumHeight: height
//    minimumWidth: width
    title: qsTr("Stack")

//    header: ToolBar {
//        contentHeight: toolButton.implicitHeight

//        Label {
//            text: stackView.currentItem.title
//            anchors.centerIn: parent
//        }
//    }

//    Drawer {
//        id: drawer
//        width: window.width * 0.66
//        height: window.height
//        Column {
//            anchors.fill: parent

//            ItemDelegate {
//                text: qsTr("Page 1")
//                width: parent.width
//                onClicked: {
//                    stackView.push("Page1Form.qml")
//                    drawer.close()
//                }
//            }
//            ItemDelegate {
//                text: qsTr("Page 2")
//                width: parent.width
//                onClicked: {
//                    stackView.push("Page2Form.qml")
//                    drawer.close()
//                }
//            }
//        }
//    }

    StackView {
        id: stackView
        objectName: "mainStackView"
        initialItem: "HomeForm.qml"
        width: 800
        height: 600
        anchors.right: parent.right
        anchors.bottom: parent.bottom


        //anchors.fill: parent
    }
    ToolSeparator {
        id: toolSeparator
        opacity: 0.3
        width: 200
        height: 600
        rightPadding: 0
        bottomPadding: 0
        leftPadding: 0
        topPadding: 0
        anchors.left: column.left
        anchors.top: column.top
    }

    Column {
        id: column
        width: 200
        height: 600
        anchors.left: parent.left
        anchors.bottom: parent.bottom

//        ItemDelegate {
//            id: antDelegate
//            text: qsTr("")
//            width: parent.width
//            onClicked: stackView.push("HomeForm.qml")
//        }

        Rectangle{
            width: parent.width
            height: mainDelegate.height*0.6
            color: "#e1e1e1"
        }

        ItemDelegate {
            id: mainDelegate
            objectName: "mainDelegate"
            text: qsTr("Главная")
            width: parent.width
            onClicked: {
//              stackView.pop()
                stackView.replace("HomeForm.qml")
                window.homeCreated(objectName);
                highlighted: true
            }
        }
        ItemDelegate {
            id: scanDelegate
            objectName: "scanDelegate"
            text: qsTr("Сканирование файлов")
            width: parent.width
            onClicked: {
//                stackView.pop()
                stackView.replace("Page1Form.qml")
                window.page1Created(objectName);
            }



        }
        ItemDelegate {
            id: monitorDelegate
            objectName: "monitorDelegate"
            text: qsTr("Файловый монитор")
            width: parent.width
            onClicked: {
//                stackView.pop()
                stackView.replace("Page2Form.qml")
                window.page2Created(objectName);
            }
        }
    }


}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
