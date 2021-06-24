import QtQuick 2.11
//import QtQuick.Window 2.0
import QtQuick.Controls 2.4
import QtQuick.Dialogs 1.1
import QtQuick.Shapes 1.11

ApplicationWindow  {
    id: root
    visible: true
    width: 800
    height: 600
    color: "#3d3d3d"
    title: qsTr("Side-by-side")    

    ColorDialog {
        id: colorDialog
        visible: false
        modality: Qt.WindowModal
        title: "Choose a color"
        color: "green"
        showAlphaChannel: true
        onAccepted: {
            console.log("Accepted: " + color)
            swipeView.customizedRect.color = color
        }
        onRejected: {
            console.log("Rejected")
        }
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        property Rectangle customizedRect: radar

        Page {
            id: topLevel
            visible: true

            header: Label {
                id: headerLabel
                text: qsTr("Верхний уровень представления")
                font.pixelSize: Qt.application.font.pixelSize * 2
                padding: 10
            }

            Column {
                id: simpleColumn
                anchors.top: parent.top
                anchors.centerIn: parent
                spacing: 30
                leftPadding: 30
                rightPadding: 30

                CustomRectangle {
                    id: radar
                    textName: "РЛС"
                    heightDiv: 5
                    dependentPage: radarLevel

                }

                CustomRectangle {
                    id: commutator
                    textName: "Сетевой коммутатор"
                    heightDiv: 5
                    dependentPage: commutatorLevel
                }

                CustomRectangle {
                    id: operatorWorkplace
                    textName: "РМО"
                    heightDiv: 5
                    dependentPage: workplaceLevel
                }

                /*Rectangle {
                    id: radar
                    property text textName: "text"
                    height: root.height / 5
                    width: root.width - 60
                    color: "darkgray"
                    radius: 20

                    Text {
                        text: "РЛС"
                        anchors.centerIn: parent
                        font.pixelSize: Qt.application.font.pixelSize * 2
                    }

                    CustomMouseArea {
                        id: areaRadar
                        onClicked: {
                            clickMouse(radarLevel, mouse.button)
                        }
                    }
                }


                Rectangle {
                    id: commutator
                    height: root.height /5
                    width: root.width - 60
                    color: "darkgray"
                    radius: 20

                    Text {
                        text: "Сетевой коммутатор"
                        font.pixelSize: Qt.application.font.pixelSize * 2
                        anchors.centerIn: parent
                    }

                    CustomMouseArea {
                        id: areaCommutator
                        onClicked: {
                            clickMouse(commutatorLevel, mouse.button)
                        }
                    }
                }



                Rectangle {
                    id: operatorWorkplace
                    height: root.height / 5
                    width: root.width - 60
                    color: "darkgray"
                    radius: 20

                    Text {
                        text: "РМО"
                        font.pixelSize: Qt.application.font.pixelSize * 2
                        anchors.centerIn: parent
                    }

                    CustomMouseArea {
                        id: areaWorkplace
                        onClicked: {
                            clickMouse(workplaceLevel, mouse.button)
                        }
                    }
                }*/
            }
        }


        /*Page {

            header: Label {
                text: qsTr("Community Stats")
                font.pixelSize: Qt.application.font.pixelSize * 2
                padding: 10
            }

            Column {
                anchors.centerIn: parent
                spacing: 10
                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("Community statistics")
                }
                Button {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("Back")
                    onClicked: swipeView.setCurrentIndex(0);
                }
            }
        }*/
        function hideLowLevelPage() {
            var tcount = countVisiblePage();
            for (var child in swipeView.contentChildren) {
                if (swipeView.contentChildren[child].visible) {
                    swipeView.contentChildren[child].visible = false;
                }
            }
        }


        function countVisiblePage() {
            var tcount = 0;
            for (var child in swipeView.contentChildren) {
                if (swipeView.contentChildren[child].visible) {
                    tcount++;
                }
            }
            return tcount;
        }

        function addPage(page) {
            addItem(page)
            page.visible = true
        }

        function removePage() {
            for (var n = currentIndex + 1; n < count;) {
                itemAt(n).visible = false
                removeItem(n)
                //console.log("Count: " + count)

            }
            /*var ind = currentIndex
            console.log("cIndex: " + currentIndex)
            console.log("cvIndex: " + countVisiblePage)
            while (ind < countVisiblePage()) {
                itemAt(ind + 1).visible = false
                removeItem(ind + 1)
                console.log("Count: " + count)
            }*/
        }

        function removeAllPage() {
            for (var n = 0; n < count; n++) {
                if (itemAt(n) === topLevel)
                    continue;
                itemAt(n).visible = false
                removeItem(n);
            }
        }

    }

    PageIndicator {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        interactive: true

        currentIndex: swipeView.currentIndex
        count: swipeView.count

        delegate: Rectangle {
            implicitWidth: 8
            implicitHeight: 8

            radius: width / 2
            color: "#494d8f"

            opacity: index === swipeView.currentIndex ? 0.95 : pressed ? 0.7 : 0.45

            Behavior on opacity {
                OpacityAnimator {
                    duration: 100
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    swipeView.currentIndex = index
                }
            }
        }
    }


    Page {
        id: radarLevel
        visible: false

        header: Label {
            //id: headerLabel1
            text: qsTr("Представление РЛС")
            font.pixelSize: Qt.application.font.pixelSize * 2
            padding: 10
        }

        Column {
            anchors.top: parent.top
            anchors.centerIn: parent
            spacing: 30
            leftPadding: 30
            rightPadding: 30

            CustomRectangle {
                id: radarGrid
                textName: "Антенная решетка"
                heightDiv: 4
                dependentPage: emptyPage
            }

            CustomRectangle {
                id: hardwareContainer
                textName: "Аппаратный контейнер"
                heightDiv: 4
                dependentPage: emptyPage
            }

            CustomRectangle {
                id: slewingRings
                textName: "ОПУ"
                heightDiv: 4
                dependentPage: slewingRingsLevel
            }

            /*Rectangle {
                id: radarGrid
                height: root.height / 4
                width: root.width - 60
                color: "darkgray"
                radius: 20

                Text {
                    text: "Антенная решетка"
                    font.pixelSize: Qt.application.font.pixelSize * 2
                    anchors.centerIn: parent
                }

                CustomMouseArea {
                    onClicked: {
                        clickMouse(workplaceLevel, mouse.button)
                    }
                }
            }

            Rectangle {
                id: hardwareContainer
                height: root.height / 4
                width: root.width - 60
                color: "darkgray"
                radius: 20

                Text {
                    text: "Аппаратный контейнер"
                    font.pixelSize: Qt.application.font.pixelSize * 2
                    anchors.centerIn: parent
                }

                CustomMouseArea {
                    onClicked: {
                        clickMouse(workplaceLevel, mouse.button)
                    }
                }
            }

            Rectangle {
                id: slewingRings
                height: root.height / 4
                width: root.width - 60
                color: "darkgray"
                radius: 20

                Text {
                    text: "ОПУ"
                    font.pixelSize: Qt.application.font.pixelSize * 2
                    anchors.centerIn: parent
                }

                CustomMouseArea {
                    onClicked: {
                        clickMouse(workplaceLevel, mouse.button)
                    }
                }
            }*/
        }
    }

    Page {

        id: commutatorLevel
        visible: false

        header: Label {
            //id: headerLabel1
            text: qsTr("Представление Коммутации")
            font.pixelSize: Qt.application.font.pixelSize * 2
            padding: 10
        }

        Column {
            anchors.top: parent.top
            anchors.centerIn: parent
            spacing: 30
            leftPadding: 30
            rightPadding: 30

            CustomRectangle {
                id: espBox1
                textName: "ESP BOX 1"
                heightDiv: 3
                dependentPage: emptyPage
            }

            CustomRectangle {
                id: espBox2
                textName: "ESP BOX 2"
                heightDiv: 3
                dependentPage: emptyPage
            }

            /*Rectangle {
                id: espBox1
                height: root.height / 3
                width: root.width - 60
                color: "darkgray"
                radius: 20

                Text {
                    text: "ESP BOX 1"
                    font.pixelSize: Qt.application.font.pixelSize * 2
                    anchors.centerIn: parent
                }

                CustomMouseArea {
                    onClicked: {
                        clickMouse(workplaceLevel, mouse.button)
                    }
                }
            }

            Rectangle {
                id: espBox2
                height: root.height / 3
                width: root.width - 60
                color: "darkgray"
                radius: 20

                Text {
                    text: "ESP BOX 2"
                    font.pixelSize: Qt.application.font.pixelSize * 2
                    anchors.centerIn: parent
                }

                CustomMouseArea {
                    onClicked: {
                        clickMouse(workplaceLevel, mouse.button)
                    }
                }
            }*/
        }

    }

    Page {

        id: workplaceLevel
        visible: false

        header: Label {
            //id: headerLabel1
            text: qsTr("Представление РМО")
            font.pixelSize: Qt.application.font.pixelSize * 2
            padding: 10
        }

        Column {
            anchors.top: parent.top
            anchors.centerIn: parent
            spacing: 30
            leftPadding: 30
            rightPadding: 30

            CustomRectangle {
                id: rarm
                textName: "RaRM"
                heightDiv: 4
                color: "forestgreen"
                dependentPage: emptyPage
            }

            CustomRectangle {
                id: muo
                textName: "MUO"
                heightDiv: 4
                color: "forestgreen"
                dependentPage: emptyPage
            }

            CustomRectangle {
                id: modBus
                textName: "ModBus"
                heightDiv: 4
                color: "forestgreen"
                dependentPage: emptyPage
            }

            /*Rectangle {
                id: rarm
                height: root.height / 4
                width: root.width - 60
                color: "forestgreen"
                radius: 20

                Text {
                    text: "RaRM"
                    font.pixelSize: Qt.application.font.pixelSize * 2
                    anchors.centerIn: parent
                }

                CustomMouseArea {
                    onClicked: {
                        clickMouse(workplaceLevel, mouse.button)
                    }
                }
            }

            Rectangle {
                id: muo
                height: root.height / 4
                width: root.width - 60
                color: "forestgreen"
                radius: 20

                Text {
                    text: "MUO"
                    font.pixelSize: Qt.application.font.pixelSize * 2
                    anchors.centerIn: parent
                }

                CustomMouseArea {
                    onClicked: {
                        clickMouse(workplaceLevel, mouse.button)
                    }
                }
            }

            Rectangle {
                id: modBus
                height: root.height / 4
                width: root.width - 60
                color: "forestgreen"
                radius: 20

                Text {
                    text: "ModBus"
                    font.pixelSize: Qt.application.font.pixelSize * 2
                    anchors.centerIn: parent
                }

                CustomMouseArea {
                    onClicked: {
                        clickMouse(workplaceLevel, mouse.button)
                    }
                }
            }*/
        }
    }

    Page {

        id: slewingRingsLevel
        visible: false

        header: Label {
            text: qsTr("Представление ОПУ")
            font.pixelSize: Qt.application.font.pixelSize * 2
            padding: 10
        }

        Column {
            anchors.top: parent.top
            anchors.centerIn: parent
            spacing: 30
            leftPadding: 30
            rightPadding: 30

            CustomRectangle {
                id: athimuthDrive
                textName: "Привод АЗМ"
                heightDiv: 3
                dependentPage: athimuthDriveLevel
            }

            CustomRectangle {
                id: elevationDrive
                textName: "Привод УГМ"
                heightDiv: 3
                dependentPage: elevationDriveLevel
            }
        }
    }

    Page {

        id: elevationDriveLevel
        visible: false

        header: Label {
            text: qsTr("Привод УГМ")
            font.pixelSize: Qt.application.font.pixelSize * 2
            padding: 10
        }

        /*Column {
            anchors.top: parent.top
            anchors.centerIn: parent
            spacing: 30
            leftPadding: 30
            rightPadding: 30
        }*/
    }


    Page {

        id: athimuthDriveLevel
        visible: false

        header: Label {
            text: qsTr("Привод АЗМ")
            font.pixelSize: Qt.application.font.pixelSize * 2
            padding: 10
        }

        /*Column {
            anchors.top: parent.top
            anchors.centerIn: parent
            spacing: 30
            leftPadding: 30
            rightPadding: 30
        }*/
    }

    Page {
        id: emptyPage
        visible: false
    }
}



