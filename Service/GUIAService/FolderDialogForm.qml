import QtQuick 2.2
import QtQuick.Dialogs 1.0

FileDialog {
    id: fileDialog
    objectName: "fileDialog"
    title: qsTr("Выберите файл...")
    folder: shortcuts.home
    selectFolder: true
    signal choseFile(string dir)
    onAccepted: {
        choseFile(fileDialog.folder)
        console.log("You chose: " + fileDialog.folder)
    }
    onRejected: {
        console.log("Canceled")
    }
    Component.onCompleted: visible = true
}
