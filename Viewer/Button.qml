import QtQuick 2.12

Rectangle {
    id: button
    signal clicked
    property alias text: text.text
    border.width: 2
    property real textHeight: height - 2
    property real fontHeight: 0.15
    property bool pressed: mouse.pressed
    property real implicitMargin: (width - text.implicitWidth) / 2

    Text {
        id: text
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: parent.textHeight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: height * fontHeight
        color: "#1b1c1d"
        font.family: "Calibri"
        //font.pointSize: 12
    }

    MouseArea {
        id: mouse
        anchors.fill: parent
        onClicked: button.clicked()
    }
}
