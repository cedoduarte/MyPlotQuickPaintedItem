import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    width: 800
    height: 800
    visible: true
    title: qsTr("Hello World")

    MyPlot {
        anchors.centerIn: parent
    }

    Button {
        anchors.bottom: parent.bottom
        text: "EXIT"
        onClicked: {
            Qt.quit();
        }
    }
}
