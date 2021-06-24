import QtQuick 2.12
import QtQuick.Controls 2.12

Page {
    property alias text: label.text

    header: Label {
        id: label
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }


}
