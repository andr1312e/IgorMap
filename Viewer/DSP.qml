import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Dialogs 1.1
import QtQuick.Shapes 1.11
import QtQuick.Layouts 1.11

ApplicationWindow  {
    id: root2
    visible: true
    //flags: Qt.FramelessWindowHint
    width: 400
    height: 400
    color: "transparent"

    Grid {
        anchors.fill: parent
        //spacing: 1
        columns: 300
        rows: 150

        Repeater {
            model: 150 * 300
            Rectangle {
                width: 2; height: 2
                color: "blue"
            }
        }
    }
}
