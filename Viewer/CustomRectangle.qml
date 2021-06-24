import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    property string textName: "text"
    property int heightDiv: 5
    property int widthOffset: 60
    property int customRadius: 20
    property Page dependentPage: emptyPage
    height: root.height / heightDiv
    width: root.width - widthOffset
    color: "darkgray"
    radius: customRadius

    Text {
        text: textName
        anchors.centerIn: parent
        font.pixelSize: Qt.application.font.pixelSize * 2
    }

    MouseArea {
        anchors.fill: parent
        width: parent.width
        height: parent.height
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onClicked: {
            if (mouse.button == Qt.LeftButton) {
                if (!dependentPage.visible) {
                    swipeView.removePage();
                    swipeView.addPage(dependentPage);
                }
                /*else {

                }*/
                swipeView.incrementCurrentIndex()
            }
            else if (mouse.button == Qt.RightButton) {
                swipeView.customizedRect = parent
                colorDialog.visible = true
                //console.log("Visible: " + colorDialog.visible)
            }
        }

        /*function clickMouse(mouseButton) {
            if (mouseButton === Qt.LeftButton) {
                if (!dependentPage.visible) {
                    swipeView.removeAllPage();
                    swipeView.addPage(dependentPage);
                }
                swipeView.currentIndex++
            }
            else if (mouseButton === Qt.RightButton) {
                swipeView.customizedRect = parent
                colorDialog.visible = true
                //console.log("Visible: " + colorDialog.visible)
            }
        }*/
    }
}
