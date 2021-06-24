import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Dialogs 1.1
//import QtQuick.Shapes 1.11
import QtQuick.Layouts 1.11

ApplicationWindow  {
    id: root
    visible: false
    flags: Qt.FramelessWindowHint | Qt.Window | Qt.WindowStaysOnTopHint
    x: 1920
    y: 50
    width: 1250
    height: 1000
    //color: "#80646464"
    title: qsTr("Функцианальный контроль")
    property int widthElement: 80
    property int heightElement: 80
    color: "transparent"

    signal qmlReceive(bool flag)
    onQmlReceive:{
        //if (root.visible != flag)
          root.visible = flag
        }

    /*header: ToolBar {
        Label {
            text: "Краткое описание проблемных подсистем и основных показателей работоспособности"
            elide: Label.ElideRight
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            Layout.fillWidth: true
        }
    }*/


    ColorDialog {
        id: colorDialog
        visible: false
        modality: Qt.WindowModal
        title: "Choose a color"
        color: "green"
        showAlphaChannel: true
        onAccepted: {
            console.log("Accepted: " + color)
            //swipeView.customizedRect.color = color
        }
        onRejected: {
            console.log("Rejected")
        }
    }


    Canvas {
        id: firstDataBus
        visible: false
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        width: widthElement * 6; height: heightElement * 2

        onPaint: {
            var ctx = getContext("2d")

            // setup the stroke
            ctx.lineWidth = 2
            ctx.strokeStyle = "black"

            // create a path
            ctx.beginPath()
            ctx.moveTo(widthElement * 6,heightElement / 2)
            ctx.lineTo(widthElement * 2.3,heightElement / 2)
            ctx.lineTo(widthElement * 2.3,heightElement * 1.5)

            ctx.moveTo(widthElement * 6,heightElement * 0.9)
            ctx.lineTo(widthElement * 2.7,heightElement  * 0.9)
            ctx.lineTo(widthElement * 2.7,heightElement * 1.5)

            for (var i = 1; i < 5; i++) {
                ctx.moveTo(widthElement * i, heightElement * 1.5)
                ctx.lineTo(widthElement * i, heightElement * 2)
            }

            ctx.stroke()

            ctx.lineWidth = 8
            ctx.beginPath()
            ctx.moveTo(10, heightElement * 1.5)
            ctx.lineTo(widthElement * 5 - 10, heightElement * 1.5)

            // stroke path
            ctx.stroke()
        }
    }

    Rectangle {
        id: mainRectangle
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: firstDataBus.bottom
        //anchors.topMargin: heightElement * 2
        width: widthElement * 5; height: heightElement * 10
        color: "lightgrey"; border.color: Qt.darker(color)
        radius: 10

        Text {
            id: headerText
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 5
            color: "black"
            text: qsTr("Антенная решетка")
            font.pointSize: 15
            minimumPointSize: 5
            fontSizeMode: Text.Fit
        }

        Column {
            id: mainColumn
            clip: true
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.top: headerText.bottom
            anchors.topMargin: 5

            //anchors.fill: parent

            /*Page {
                visible: true
                background: Rectangle {
                    color:"transparent"
                }*/

                Rectangle {
                    x: 10; y: 10
                    //anchors.fill: swipeView
                    width: widthElement * 4.4; height: heightElement * 4.6
                    color: "lightgrey"; border.color: Qt.lighter(color)
                    radius: 10

                    Text {
                        id: headerTextHL
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        color: "black"
                        text: qsTr("Фрагменты")
                        font.pointSize: 12
                        minimumPointSize: 5
                        fontSizeMode: Text.Fit
                    }

                    Grid {
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.top: headerTextHL.bottom
                        anchors.topMargin: 5
                        columns: 4
                        spacing: 3
                        Repeater {
                            model: 6
                            Rectangle {
                                width: widthElement; height: heightElement
                                color: "forestgreen"
                                border.color: Qt.lighter(color)
                                radius: 12
                                Text {
                                    anchors.centerIn: parent
                                    font.pointSize: 10
                                    color: "black"
                                    text: index + 1
                                }
                            }
                        }

                        Rectangle {
                            width: widthElement; height: heightElement
                            color: "goldenrod"
                            border.color: Qt.lighter(color)
                            radius: 12
                            Text {
                                anchors.centerIn: parent
                                font.pointSize: 10
                                color: "black"
                                text: "7"
                            }
                        }

                        Repeater {
                            model: 9
                            Rectangle {
                                width: widthElement; height: heightElement
                                color: "forestgreen"
                                border.color: Qt.lighter(color)
                                radius: 12
                                Text {
                                    anchors.centerIn: parent
                                    font.pointSize: 10
                                    color: "black"
                                    text: index + 8
                                }
                            }
                        }
                    }
                }
            //}

            /*Page {
                visible: true
                background: Rectangle{
                    color:"transparent"
                }*/

                Rectangle {
                    x: 10; y: 10
                    //anchors.fill: swipeView
                    width: widthElement * 4.4; height: heightElement * 4.8
                    color: "lightgrey"; border.color: Qt.lighter(color)
                    radius: 10

                    Text {
                        id: headerTextML
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        color: "black"
                        text: qsTr("ППМы фрагмента №7")
                        font.pointSize: 12
                        minimumPointSize: 5
                        fontSizeMode: Text.Fit
                    }

                    Column {
                        anchors.left: parent.left
                        anchors.leftMargin: 15
                        anchors.top: headerTextML.bottom
                        anchors.topMargin: 5

                        spacing: 2

                        Column {
                            Row {
                                Repeater {
                                    model: 9
                                    Rectangle {
                                        width: widthElement / 4; height: heightElement / 4
                                        color: "forestgreen"
                                        border.color: Qt.darker(color)
                                        radius: 2
                                        Text {
                                            anchors.centerIn: parent
                                            font.pointSize: 8
                                            color: "black"
                                            text: index + 1
                                        }
                                    }
                                }

                                Rectangle {
                                    width: widthElement / 4; height: heightElement / 4
                                    color: "firebrick"
                                    border.color: Qt.darker(color)
                                    radius: 2
                                    Text {
                                        anchors.centerIn: parent
                                        font.pointSize: 8
                                        color: "black"
                                        text: "10"
                                    }
                                }

                                Rectangle {
                                    width: widthElement / 4; height: heightElement / 4
                                    color: "firebrick"
                                    border.color: Qt.darker(color)
                                    radius: 2
                                    Text {
                                        anchors.centerIn: parent
                                        font.pointSize: 8
                                        color: "black"
                                        text: "11"
                                    }
                                }

                                Repeater {
                                    model: 5
                                    Rectangle {
                                        width: widthElement / 4; height: heightElement / 4
                                        color: "forestgreen"
                                        border.color: Qt.darker(color)
                                        radius: 2
                                        Text {
                                            anchors.centerIn: parent
                                            font.pointSize: 8
                                            color: "black"
                                            text: index + 12
                                        }
                                    }
                                }
                            }

                            Row {
                                spacing: 2
                                Repeater {
                                    model: 9
                                    Column {
                                        Repeater {
                                            model: 8
                                            Rectangle {
                                                x: 1
                                                width: widthElement / 4 - 2; height: heightElement / 6
                                                color: "forestgreen"
                                            }
                                        }
                                    }
                                }
                                Column {
                                    Repeater {
                                        model: 8
                                        Rectangle {
                                            x: 1
                                            width: widthElement / 4 - 2; height: heightElement / 6
                                            color: "firebrick"
                                        }
                                    }
                                }
                                Column {
                                    Repeater {
                                        model: 8
                                        Rectangle {
                                            x: 1
                                            width: widthElement / 4 - 2; height: heightElement / 6
                                            color: "firebrick"
                                        }
                                    }
                                }
                                Repeater {
                                    model: 5
                                    Column {
                                        Repeater {
                                            model: 8
                                            Rectangle {
                                                x: 1
                                                width: widthElement / 4 - 2; height: heightElement / 6
                                                color: "forestgreen"
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        Column {
                            Row {
                                Repeater {
                                    model: 3
                                    Rectangle {
                                        width: widthElement / 4; height: heightElement / 4
                                        color: "forestgreen"
                                        border.color: Qt.darker(color)
                                        radius: 2
                                        Text {
                                            anchors.centerIn: parent
                                            font.pointSize: 8
                                            color: "black"
                                            text: index + 1 + 16
                                        }
                                    }
                                }

                                Rectangle {
                                    width: widthElement / 4; height: heightElement / 4
                                    color: "firebrick"
                                    border.color: Qt.darker(color)
                                    radius: 2
                                    Text {
                                        anchors.centerIn: parent
                                        font.pointSize: 8
                                        color: "black"
                                        text: "20"
                                    }
                                }

                                Repeater {
                                    model: 12
                                    Rectangle {
                                        width: widthElement / 4; height: heightElement / 4
                                        color: "forestgreen"
                                        border.color: Qt.darker(color)
                                        radius: 2
                                        Text {
                                            anchors.centerIn: parent
                                            font.pointSize: 8
                                            color: "black"
                                            text: index + 1 + 20
                                        }
                                    }
                                }
                            }

                            Row {
                                spacing: 2
                                Repeater {
                                    model: 3
                                    Column {
                                        Repeater {
                                            model: 8
                                            Rectangle {
                                                x: 1
                                                width: widthElement / 4 - 2; height: heightElement / 6
                                                color: "forestgreen"
                                            }
                                        }
                                    }
                                }
                                Column {
                                    Repeater {
                                        model: 8
                                        Rectangle {
                                            x: 1
                                            width: widthElement / 4 - 2; height: heightElement / 6
                                            color: "firebrick"
                                        }
                                    }
                                }
                                Repeater {
                                    model: 12
                                    Column {
                                        Repeater {
                                            model: 8
                                            Rectangle {
                                                x: 1
                                                width: widthElement / 4 - 2; height: heightElement / 6
                                                color: "forestgreen"
                                            }
                                        }
                                    }
                                }
                            }
                        }


                        Column {
                            Row {
                                Rectangle {
                                    //anchors.right: parent.right
                                    width: widthElement * 2; height: heightElement / 2
                                    color: "forestgreen"
                                    border.color: Qt.lighter(color)
                                    radius: 10

                                    Text {
                                        /*anchors.left: parent.left
                                        anchors.leftMargin: 10
                                        anchors.top: parent.top
                                        anchors.topMargin: 10*/
                                        anchors.fill: parent
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                        color: "black"
                                        text: qsTr("Модуль управления и\nкотроля")
                                        font.pointSize: 8
                                        minimumPointSize: 5
                                        fontSizeMode: Text.Fit
                                    }
                                }

                                Rectangle {
                                    x: widthElement / 2
                                    //anchors.right: parent.right
                                    width: widthElement * 2; height: heightElement / 2
                                    color: "forestgreen"
                                    border.color: Qt.lighter(color)
                                    radius: 10

                                    Text {
                                        /*anchors.left: parent.left
                                        anchors.leftMargin: 10
                                        anchors.top: parent.top
                                        anchors.topMargin: 5*/
                                        anchors.fill: parent
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                        color: "black"
                                        text: qsTr("Преобразователь\nна ПЧ")
                                        font.pointSize: 8
                                        minimumPointSize: 5
                                        fontSizeMode: Text.Fit
                                    }
                                }
                            }

                            Column {

                                Row {
                                    Rectangle {
                                        //anchors.right: parent.right
                                        width: widthElement * 2; height: heightElement / 2
                                        color: "forestgreen"
                                        border.color: Qt.lighter(color)
                                        radius: 10

                                        Text {
                                            /*anchors.left: parent.left
                                            anchors.leftMargin: 10
                                            anchors.top: parent.top
                                            anchors.topMargin: 5*/
                                            anchors.fill: parent
                                            horizontalAlignment: Text.AlignHCenter
                                            verticalAlignment: Text.AlignVCenter
                                            color: "black"
                                            text: qsTr("Делитель/Сумматор 32x1")
                                            font.pointSize: 8
                                            minimumPointSize: 5
                                            fontSizeMode: Text.Fit
                                        }
                                    }

                                    Rectangle {
                                        //anchors.right: parent.right
                                        width: widthElement * 2; height: heightElement / 2
                                        color: "forestgreen"
                                        border.color: Qt.lighter(color)
                                        radius: 10

                                        Text {
                                            /*anchors.left: parent.left
                                            anchors.leftMargin: 10
                                            anchors.top: parent.top
                                            anchors.topMargin: 5*/
                                            anchors.fill: parent
                                            horizontalAlignment: Text.AlignHCenter
                                            verticalAlignment: Text.AlignVCenter
                                            color: "black"
                                            text: qsTr("Делитель/Сумматор 32x1")
                                            font.pointSize: 8
                                            minimumPointSize: 5
                                            fontSizeMode: Text.Fit
                                        }
                                    }
                                }

                            }
                        }
                    }

                    /*Grid {
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.top: headerTextML.bottom
                        anchors.topMargin: 5
                        columns: 16
                        spacing: 2


                        Repeater {
                            model: 16 * 9
                            Rectangle {
                                width: widthElement / 5; height: heightElement / 5
                                color: "forestgreen"
                                border.color: Qt.darker(color)
                                radius: 2
                                Text {
                                    anchors.centerIn: parent
                                    font.pointSize: 8
                                    color: "black"
                                    text: index + 1
                                }
                            }
                        }*/


                        /*Grid {
                            columns: 4
                            spacing: 3
                            Repeater {
                                model: 10
                                Rectangle {
                                    width: widthElement / 2; height: heightElement / 2
                                    color: "forestgreen"
                                    border.color: Qt.lighter(color)
                                    radius: 20
                                    Text {
                                        anchors.centerIn: parent
                                        font.pointSize: 10
                                        color: "black"
                                        text: index + 1
                                    }
                                }
                            }

                            Rectangle {
                                width: widthElement / 2; height: heightElement / 2
                                color: "firebrick"
                                border.color: Qt.lighter(color)
                                radius: 20
                                Text {
                                    anchors.centerIn: parent
                                    font.pointSize: 10
                                    color: "black"
                                    text: "11"
                                }
                            }

                            Rectangle {
                                width: widthElement / 2; height: heightElement / 2
                                color: "firebrick"
                                border.color: Qt.lighter(color)
                                radius: 20
                                Text {
                                    anchors.centerIn: parent
                                    font.pointSize: 10
                                    color: "black"
                                    text: "12"
                                }
                            }

                            Repeater {
                                model: 12
                                Rectangle {
                                    width: widthElement / 2; height: heightElement / 2
                                    color: "forestgreen"
                                    border.color: Qt.lighter(color)
                                    radius: 20
                                    Text {
                                        anchors.centerIn: parent
                                        font.pointSize: 10
                                        color: "black"
                                        text: index + 1 + 12
                                    }
                                }
                            }

                            Rectangle {
                                width: widthElement / 2; height: heightElement / 2
                                color: "firebrick"
                                border.color: Qt.lighter(color)
                                radius: 20
                                Text {
                                    anchors.centerIn: parent
                                    font.pointSize: 10
                                    color: "black"
                                    text: "25"
                                }
                            }

                            Rectangle {
                                width: widthElement / 2; height: heightElement / 2
                                color: "firebrick"
                                border.color: Qt.lighter(color)
                                radius: 20
                                Text {
                                    anchors.centerIn: parent
                                    font.pointSize: 10
                                    color: "black"
                                    text: "26"
                                }
                            }

                            Repeater {
                                model: 6
                                Rectangle {
                                    width: widthElement / 2; height: heightElement / 2
                                    color: "forestgreen"
                                    border.color: Qt.lighter(color)
                                    radius: 20
                                    Text {
                                        anchors.centerIn: parent
                                        font.pointSize: 10
                                        color: "black"
                                        text: index + 1 + 26
                                    }
                                }
                            }
                        }*/

                        /*Column {
                            spacing: 10
                            Rectangle {
                                //anchors.right: parent.right
                                width: widthElement * 1.8; height: heightElement * 0.6
                                color: "forestgreen"
                                border.color: Qt.lighter(color)
                                radius: 10

                                Text {
                                    anchors.left: parent.left
                                    anchors.leftMargin: 10
                                    anchors.top: parent.top
                                    anchors.topMargin: 5
                                    color: "black"
                                    text: qsTr("Модуль управления и\nкотроля")
                                    font.pointSize: 10
                                    minimumPointSize: 5
                                    fontSizeMode: Text.Fit
                                }
                            }

                            Rectangle {
                                //anchors.right: parent.right
                                width: widthElement * 1.8; height: heightElement * 0.6
                                color: "forestgreen"
                                border.color: Qt.lighter(color)
                                radius: 10

                                Text {
                                    anchors.left: parent.left
                                    anchors.leftMargin: 10
                                    anchors.top: parent.top
                                    anchors.topMargin: 5
                                    color: "black"
                                    text: qsTr("Делитель/Сумматор\n32/1")
                                    font.pointSize: 10
                                    minimumPointSize: 5
                                    fontSizeMode: Text.Fit
                                }
                            }

                            Rectangle {
                                //anchors.right: parent.right
                                width: widthElement * 1.8; height: heightElement * 0.6
                                color: "forestgreen"
                                border.color: Qt.lighter(color)
                                radius: 10

                                Text {
                                    anchors.left: parent.left
                                    anchors.leftMargin: 10
                                    anchors.top: parent.top
                                    anchors.topMargin: 5
                                    color: "black"
                                    text: qsTr("Преобразователь\nна ПЧ")
                                    font.pointSize: 10
                                    minimumPointSize: 5
                                    fontSizeMode: Text.Fit
                                }
                            }

                            Rectangle {
                                //anchors.right: parent.right
                                width: widthElement * 1.8; height: heightElement * 0.6
                                color: "forestgreen"
                                border.color: Qt.lighter(color)
                                radius: 10

                                Text {
                                    anchors.left: parent.left
                                    anchors.leftMargin: 10
                                    anchors.top: parent.top
                                    anchors.topMargin: 5
                                    color: "black"
                                    text: qsTr("Делитель/Сумматор\n32/1")
                                    font.pointSize: 10
                                    minimumPointSize: 5
                                    fontSizeMode: Text.Fit
                                }
                            }
                        }*/
                    //}
                }
            //}

/*        SwipeView {
            id: swipeView
            interactive: false
            clip: true
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.top: headerText.bottom
            anchors.topMargin: 5

            background: Rectangle {
                color: "transparent"
            }

            //anchors.fill: parent

            Page {
                visible: true
                background: Rectangle {
                    color:"transparent"
                }

                Rectangle {
                    x: 10; y: 10
                    //anchors.fill: swipeView
                    width: widthElement * 4.4; height: heightElement * 4.6
                    color: "lightgrey"; border.color: Qt.lighter(color)
                    radius: 10

                    Text {
                        id: headerTextHL
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        color: "black"
                        text: qsTr("Фрагменты")
                        font.pointSize: 12
                        minimumPointSize: 5
                        fontSizeMode: Text.Fit
                    }

                    Grid {
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.top: headerTextHL.bottom
                        anchors.topMargin: 5
                        columns: 4
                        spacing: 3
                        Repeater {
                            model: 16
                            Rectangle {
                                width: widthElement; height: heightElement
                                color: "forestgreen"
                                border.color: Qt.lighter(color)
                                radius: 12
                                Text {
                                    anchors.centerIn: parent
                                    font.pointSize: 10
                                    color: "black"
                                    text: index + 1
                                }
                            }
                        }
                    }
                }
            }

            Page {
                visible: false
                background: Rectangle{
                    color:"transparent"
                }

                Rectangle {
                    x: 10; y: 10
                    //anchors.fill: swipeView
                    width: widthElement * 4.4; height: heightElement * 4.6
                    color: "lightgrey"; border.color: Qt.lighter(color)
                    radius: 10

                    Text {
                        id: headerTextML
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        color: "black"
                        text: qsTr("ППМы")
                        font.pointSize: 12
                        minimumPointSize: 5
                        fontSizeMode: Text.Fit
                    }

                    Grid {
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                        anchors.top: headerTextML.bottom
                        anchors.topMargin: 5
                        columns: 8
                        spacing: 3
                        Repeater {
                            model: 32
                            Rectangle {
                                width: widthElement / 2; height: heightElement
                                color: "forestgreen"
                                border.color: Qt.lighter(color)
                                radius: 12
                                Text {
                                    anchors.centerIn: parent
                                    font.pointSize: 10
                                    color: "black"
                                    text: index + 1
                                }
                            }
                        }
                    }
                }
            }

            Page {
                visible: false
                background: Rectangle{
                    color:"transparent"
                }

                Rectangle {
                    x: 10; y: 10
                    //anchors.fill: swipeView
                    width: widthElement * 4.4; height: heightElement * 4.6
                    color: "lightgrey"; border.color: Qt.lighter(color)
                    radius: 10

                    Text {
                        id: headerTextLL
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        color: "black"
                        text: qsTr("Состояние ППМ №##")
                        font.pointSize: 12
                        minimumPointSize: 5
                        fontSizeMode: Text.Fit
                    }

                    ScrollView {
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.top: headerTextLL.bottom
                        anchors.topMargin: 5
                        width: widthElement * 4.4; height: heightElement * 4.6
                        clip: true
                        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                        ScrollBar.vertical.width: 5
                        ScrollBar.vertical.policy: ScrollBar.AsNeeded

                        Column {


                            Text {
                                color: "black"
                                text: qsTr("Температурный график")
                                font.pointSize: 9
                                minimumPointSize: 5
                                fontSizeMode: Text.Fit
                            }

                            ChartView {
                                //title: "Температурный график"
                                width: widthElement * 4.5; height: heightElement * 2                                
                                legend.visible: false
                                antialiasing: true
                                //backgroundRoundness: 10
                                backgroundColor: "transparent"
                                clip: true
                                LineSeries {
                                    axisX: ValueAxis {
                                        //name: "min"
                                        min: 0
                                        max: 5
                                    }
                                    axisY: ValueAxis {
                                        //name: "deg"
                                        min: 0
                                        max: 100
                                        labelFormat: "%d&deg;C"
                                    }

                                    XYPoint { x: 0; y: 5 }
                                    XYPoint { x: 1; y: 25 }
                                    XYPoint { x: 2; y: 50 }
                                    XYPoint { x: 3; y: 70 }
                                    XYPoint { x: 4; y: 80 }
                                }
                            }

                            Text {
                                color: "black"
                                text: qsTr("Амплитуда ПВ: ххх мВ")
                                font.pointSize: 10
                                minimumPointSize: 5
                                fontSizeMode: Text.Fit
                            }

                            Row{
                                Column {
                                    Repeater {
                                        model: ["Тестовый сигнал ПрМ: ",
                                                "Тестовый сигнал ПрД: ",
                                                "Исправность фазовращ. ПрМ: ",
                                                "Исправность фазовращ. ПрД: ",
                                                "Исправность аттеню. ПрМ: ",
                                                "Исправность аттеню. ПрД: "]
                                        Text {
                                            color: "black"
                                            text: modelData
                                            font.pointSize: 10
                                        }
                                    }
                                }
                                Column {
                                    Repeater {
                                        model: 6
                                        Row {
                                            Repeater {
                                                model: 8
                                                Rectangle {
                                                    radius: 8
                                                    width: radius * 2; height: radius * 2
                                                    color: "forestgreen"
                                                    border.color: Qt.lighter(color)

                                                }

                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }*/

            /*function hideLowLevelPage(tindex) {
                itemAt(currentIndex).visible = false
                itemAt(tindex).visible = true
                currentIndex = tindex
            }*/

        }

        /*PageIndicator {
            anchors.left: headerText.right
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10

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
                        swipeView.hideLowLevelPage(index)
                    }
                }
            }
        }*/

    }

    Rectangle {
        id: secondRectangle
        anchors.left: firstDataBus.right
        anchors.top: parent.top
        anchors.topMargin: 10
        width: widthElement * 3; height: heightElement
        color: "lightgrey"; border.color: Qt.darker(color)
        radius: 10

        Text {
            id: headerTextSecond
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 5
            color: "black"
            text: qsTr("ППС")
            font.pointSize: 15
            minimumPointSize: 5
            fontSizeMode: Text.Fit
        }
    }

    Canvas {
        id: secondDataBus
        visible: false
        anchors.left: firstDataBus.right
        anchors.top: secondRectangle.bottom
        width: secondRectangle.width; height: secondRectangle.height

        onPaint: {
            var ctx = getContext("2d")

            // setup the stroke
            ctx.lineWidth = 2
            ctx.strokeStyle = "black"

            // create a path
            ctx.beginPath()
            ctx.moveTo(width / 2, 0)
            ctx.lineTo(width / 2, height)

            ctx.stroke()
        }
    }

    Canvas {
        id: thirdDataBus
        visible: false
        anchors.left: mainRectangle.right
        anchors.top: secondRectangle.bottom
        width: widthElement; height: mainRectangle.height

        onPaint: {
            var ctx = getContext("2d")

            // setup the stroke
            ctx.lineWidth = 2
            ctx.strokeStyle = "black"

            // create a path
            ctx.beginPath()
            for (var j = 0; j < 4; j++) {
                ctx.moveTo(0, heightElement * (1.7 + j))
                ctx.lineTo(widthElement, heightElement * (1.7 + j))
            }

            for (var i = 0; i < 9; i++) {
                ctx.moveTo(widthElement, heightElement * (1.2 + (0.5 * i)))
                ctx.lineTo(widthElement * 2, heightElement * (1.2 + (0.5 * i)))
            }

            ctx.stroke()

            ctx.lineWidth = 8
            ctx.beginPath()
            ctx.moveTo(widthElement, heightElement)
            ctx.lineTo(widthElement, height - 10)

            // stroke path
            ctx.stroke()
        }
    }

    Rectangle {
        id: thirdRectangle
        anchors.left: thirdDataBus.right
        anchors.top: secondDataBus.bottom
        width: widthElement * 3; height: heightElement * 4
        color: "lightgrey"; border.color: Qt.darker(color)
        radius: 10

        Text {
            id: headerTextThird
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 5
            color: "black"
            text: qsTr("Спецвычислители")
            font.pointSize: 15
            minimumPointSize: 5
            fontSizeMode: Text.Fit
        }

        SwipeView {
            id: swipeViewThird
            interactive: false
            clip: true
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.top: headerTextThird.bottom
            anchors.topMargin: 5

            background: Rectangle {
                color: "transparent"
            }

            Page {
                visible: true
                //anchors.top: headerTextThird.bottom
                //anchors.topMargin: 10
                background: Rectangle {
                    color:"transparent"
                }

                Rectangle {
                    //x: 5; y: 5
                    //anchors.fill: swipeView
                    width: widthElement * 2.5; height: heightElement * 3.5
                    color: "lightgrey"; border.color: Qt.lighter(color)
                    radius: 10

                    Column {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 10

                        Rectangle {
                            width: widthElement * 2; height: heightElement * 1.5
                            color: "darkgray" //forestgreen
                            border.color: Qt.lighter(color)
                            radius: 10
                            Text {
                                id: swipeViewThirdText
                                anchors.left: parent.left
                                anchors.leftMargin: 10
                                anchors.top: parent.top
                                anchors.topMargin: 5
                                font.pointSize: 10
                                color: "black"
                                text: "Основной ВС"
                            }

                            Row {
                                anchors.top: swipeViewThirdText.bottom
                                anchors.left: parent.left
                                anchors.leftMargin: 10
                                spacing: 5
                                Rectangle {
                                    width: widthElement - 15; height: heightElement
                                    color: "darkgray" //forestgreen //firebrick //goldenrod
                                    border.color: Qt.lighter(color)
                                    radius: 10
                                    Text {
                                        anchors.centerIn: parent
                                        font.pointSize: 10
                                        horizontalAlignment: Text.AlignHCenter
                                        color: "black"
                                        text: "Модуль\n1"
                                    }
                                }
                                Rectangle {
                                    width: widthElement - 15; height: heightElement
                                    color: "darkgray" //forestgreen
                                    border.color: Qt.lighter(color)
                                    radius: 10
                                    Text {
                                        anchors.centerIn: parent
                                        font.pointSize: 10
                                        horizontalAlignment: Text.AlignHCenter
                                        color: "black"
                                        text: "Модуль\n2"
                                    }
                                }
                            }
                        }

                        Rectangle {
                            width: widthElement * 2; height: heightElement * 1.5
                            color: "darkgray"//"darkseagreen"//"#356954" //"darkgray"
                            border.color: Qt.lighter(color)
                            radius: 10
                            Text {
                                id: swipeViewThirdText2
                                anchors.left: parent.left
                                anchors.leftMargin: 10
                                anchors.top: parent.top
                                anchors.topMargin: 5
                                font.pointSize: 10
                                color: "black"
                                text: "Резеврный СВ"
                            }

                            Row {
                                anchors.top: swipeViewThirdText2.bottom
                                anchors.left: parent.left
                                anchors.leftMargin: 10
                                spacing: 5
                                Rectangle {
                                    width: widthElement - 15; height: heightElement
                                    color: "darkgray"
                                    border.color: Qt.lighter(color)
                                    radius: 10
                                    Text {
                                        anchors.centerIn: parent
                                        font.pointSize: 10
                                        horizontalAlignment: Text.AlignHCenter
                                        color: "black"
                                        text: "Модуль\n1"
                                    }
                                }
                                Rectangle {
                                    width: widthElement - 15; height: heightElement
                                    color: "darkgray"
                                    border.color: Qt.lighter(color)
                                    radius: 10
                                    Text {
                                        anchors.centerIn: parent
                                        font.pointSize: 10
                                        horizontalAlignment: Text.AlignHCenter
                                        color: "black"
                                        text: "Модуль\n2"
                                    }
                                }
                            }
                        }
                    }
                }
            }

            /*Page {
                visible: false
                //anchors.top: headerTextThird.bottom
                //anchors.topMargin: 10
                background: Rectangle {
                    color:"transparent"
                }

                Rectangle {
                    //x: 5; y: 5
                    //anchors.fill: swipeView
                    width: widthElement * 2.5; height: heightElement * 3.5
                    color: "lightgrey"; border.color: Qt.lighter(color)
                    radius: 10

                    Text {
                        id: calcTextLL
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        color: "black"
                        text: qsTr("Основной")
                        font.pointSize: 9
                        minimumPointSize: 5
                        fontSizeMode: Text.Fit
                    }

                    Column {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.top: calcTextLL.bottom
                        spacing: 10

                        Rectangle {
                            width: widthElement * 2; height: heightElement * 1.5
                            color: "forestgreen"
                            border.color: Qt.lighter(color)
                            radius: 12
                            Text {
                                anchors.centerIn: parent
                                font.pointSize: 10
                                color: "black"
                                text: "Вычислитель 1"
                            }
                        }

                        Rectangle {
                            width: widthElement * 2; height: heightElement * 1.5
                            color: "forestgreen"
                            border.color: Qt.lighter(color)
                            radius: 12
                            Text {
                                anchors.centerIn: parent
                                font.pointSize: 10
                                color: "black"
                                text: "Вычислитель 2"
                            }
                        }
                    }
                }
            }*/

            Page {
                visible: false
                //anchors.top: headerTextThird.bottom
                //anchors.topMargin: 10
                background: Rectangle {
                    color:"transparent"
                }

                Rectangle {
                    //x: 5; y: 5
                    //anchors.fill: swipeView
                    width: widthElement * 2.5; height: heightElement * 3.5
                    color: "lightgrey"; border.color: Qt.lighter(color)
                    radius: 10

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        color: "black"
                        text: qsTr("Состояние Вычислителя №#")
                        font.pointSize: 9
                        minimumPointSize: 5
                        fontSizeMode: Text.Fit
                    }
                }
            }


            function hideLowLevelPage(tindex) {
                itemAt(currentIndex).visible = false
                itemAt(tindex).visible = true
                currentIndex = tindex
            }

        }

        PageIndicator {
            anchors.left: headerTextThird.right
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10

            interactive: true

            currentIndex: swipeViewThird.currentIndex
            count: swipeViewThird.count

            delegate: Rectangle {
                implicitWidth: 8
                implicitHeight: 8

                radius: width / 2
                color: "#494d8f"

                opacity: index === swipeViewThird.currentIndex ? 0.95 : pressed ? 0.7 : 0.45

                Behavior on opacity {
                    OpacityAnimator {
                        duration: 100
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        swipeViewThird.hideLowLevelPage(index)
                    }
                }
            }
        }
    }

    Canvas {
        id: fourDataBus
        visible: false
        anchors.left: thirdRectangle.right
        anchors.top: secondRectangle.bottom
        width: widthElement; height: mainRectangle.height

        onPaint: {
            var ctx = getContext("2d")

            // setup the stroke
            ctx.lineWidth = 2
            ctx.strokeStyle = "black"

            // create a path
            ctx.beginPath()
            for (var j = 0; j < 5; j++) {
                ctx.moveTo(0, heightElement * (j + 1.2))
                ctx.lineTo(widthElement, heightElement * (j + 1.2))
                ctx.lineTo(2 * widthElement, heightElement * (j + 1.2))
            }

            /*for (var i = 0; i < 9; i++) {
                ctx.moveTo(widthElement, heightElement * (1.2 + (0.5 * i)))
                ctx.lineTo(widthElement * 2, heightElement * (1.2 + (0.5 * i)))
            }*/

            ctx.stroke()

            ctx.lineWidth = 8
            ctx.beginPath()
            ctx.moveTo(widthElement, heightElement)
            ctx.lineTo(widthElement, height - 10)

            // stroke path
            ctx.stroke()
        }
    }

    Rectangle {
        id: fourRectangle
        anchors.left: fourDataBus.right
        anchors.bottom: thirdRectangle.top
        //anchors.topMargin: 10
        width: widthElement * 3; height: heightElement
        color: "lightgrey"; border.color: Qt.darker(color)
        radius: 10

        Text {
            id: headerTextFour
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 5
            color: "black"
            text: qsTr("Инклинометр")
            font.pointSize: 15
            minimumPointSize: 5
            fontSizeMode: Text.Fit
        }
    }

    Rectangle {
        id: fiveRectangle
        anchors.left: fourDataBus.right
        anchors.top: fourRectangle.bottom
        anchors.topMargin: 10
        width: widthElement * 3; height: heightElement * 2
        color: "lightgrey"; border.color: Qt.darker(color)
        radius: 10

        Text {
            id: headerTextFive
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 5
            color: "black"
            text: qsTr("ОПУ")
            font.pointSize: 15
            minimumPointSize: 5
            fontSizeMode: Text.Fit
        }

        SwipeView {
            id: swipeViewFive
            interactive: false
            clip: true
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.top: headerTextFive.bottom
            //anchors.topMargin: 5

            background: Rectangle {
                color: "transparent"
            }

            Page {
                visible: true
                //anchors.top: headerTextFive.bottom
                //anchors.topMargin: 10
                background: Rectangle {
                    color:"transparent"
                }

                Rectangle {
                    x: 10; y: 10
                    //anchors.fill: swipeView
                    width: widthElement * 2.5; height: heightElement * 1.4
                    color: "lightgrey"; border.color: Qt.lighter(color)
                    radius: 10

                    Row {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 10

                        Rectangle {
                            width: widthElement; height: heightElement
                            color: "forestgreen"
                            border.color: Qt.lighter(color)
                            radius: 12
                            Text {
                                anchors.centerIn: parent
                                font.pointSize: 10
                                color: "black"
                                text: "Привод АЗМ"
                            }
                        }

                        Rectangle {
                            width: widthElement; height: heightElement
                            color: "forestgreen"
                            border.color: Qt.lighter(color)
                            radius: 12
                            Text {
                                anchors.centerIn: parent
                                font.pointSize: 10
                                color: "black"
                                text: "Привод УГМ"
                            }
                        }
                    }
                }
            }

            Page {
                visible: false
                //anchors.top: headerTextFive.bottom
                //anchors.topMargin: 10
                background: Rectangle {
                    color:"transparent"
                }

                Rectangle {
                    x: 10; y: 10
                    //anchors.fill: swipeView
                    width: widthElement * 2.5; height: heightElement * 1.4
                    color: "lightgrey"; border.color: Qt.lighter(color)
                    radius: 10

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        color: "black"
                        text: qsTr("Состояние привода УГМ")
                        font.pointSize: 9
                        minimumPointSize: 5
                        fontSizeMode: Text.Fit
                    }
                }
            }


            function hideLowLevelPage(tindex) {
                itemAt(currentIndex).visible = false
                itemAt(tindex).visible = true
                currentIndex = tindex
            }

        }

        PageIndicator {
            anchors.left: headerTextFive.right
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10

            interactive: true

            currentIndex: swipeViewFive.currentIndex
            count: swipeViewFive.count

            delegate: Rectangle {
                implicitWidth: 8
                implicitHeight: 8

                radius: width / 2
                color: "#494d8f"

                opacity: index === swipeViewFive.currentIndex ? 0.95 : pressed ? 0.7 : 0.45

                Behavior on opacity {
                    OpacityAnimator {
                        duration: 100
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        swipeViewFive.hideLowLevelPage(index)
                    }
                }
            }
        }
    }

    Rectangle {
        id: sixRectangle
        anchors.left: fourDataBus.right
        anchors.top: fiveRectangle.bottom
        anchors.topMargin: 10
        width: widthElement * 3; height: heightElement
        color: "lightgrey"; border.color: Qt.darker(color)
        radius: 10

        Text {
            id: headerTextSix
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 5
            color: "black"
            text: qsTr("Датчик АЗМ")
            font.pointSize: 15
            minimumPointSize: 5
            fontSizeMode: Text.Fit
        }
    }

    Rectangle {
        id: sevenRectangle
        anchors.left: fourDataBus.right
        anchors.top: sixRectangle.bottom
        anchors.topMargin: 10
        width: widthElement * 3; height: heightElement
        color: "lightgrey"; border.color: Qt.darker(color)
        radius: 10

        Text {
            id: headerTextSeven
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 5
            color: "black"
            text: qsTr("Датчик УГМ")
            font.pointSize: 15
            minimumPointSize: 5
            fontSizeMode: Text.Fit
        }
    }

    Canvas {
        id: sixDataBus
        visible: false
        anchors.left: thirdRectangle.left
        anchors.top: thirdRectangle.bottom
        width: thirdRectangle.width; height: heightElement

        onPaint: {
            var ctx = getContext("2d")

            // setup the stroke
            ctx.lineWidth = 2
            ctx.strokeStyle = "black"

            // create a path
            ctx.beginPath()
            for (var j = 1; j < 5; j++) {
                ctx.moveTo(width * j / 5, 0)
                ctx.lineTo(width * j / 5, height)
            }
            ctx.stroke()
        }
    }

    Rectangle {
        id: eightRectangle
        anchors.left: sixDataBus.left
        anchors.top: sixDataBus.bottom
        width: widthElement * 3; height: heightElement * 2
        color: "lightgrey"; border.color: Qt.darker(color)
        radius: 10

        Text {
            id: headerTextEight
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 5
            color: "black"
            text: qsTr("Коммутация")
            font.pointSize: 15
            minimumPointSize: 5
            fontSizeMode: Text.Fit
        }

        SwipeView {
            id: swipeViewEight
            interactive: false
            clip: true
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.top: headerTextEight.bottom
            //anchors.topMargin: 5

            background: Rectangle {
                color: "transparent"
            }

            Page {
                visible: true
                //anchors.top: headerTextEight.bottom
                //anchors.topMargin: 10
                background: Rectangle {
                    color:"transparent"
                }

                Rectangle {
                    x: 10; y: 10
                    //anchors.fill: swipeView
                    width: widthElement * 2.5; height: heightElement * 1.4
                    color: "lightgrey"; border.color: Qt.lighter(color)
                    radius: 10

                    Row {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 10

                        Rectangle {
                            width: widthElement; height: heightElement
                            color: "forestgreen"
                            border.color: Qt.lighter(color)
                            radius: 12
                            Text {
                                anchors.centerIn: parent
                                font.pointSize: 10
                                color: "black"
                                text: "ESP BOX 1"
                            }
                        }

                        Rectangle {
                            width: widthElement; height: heightElement
                            color: "forestgreen"
                            border.color: Qt.lighter(color)
                            radius: 12
                            Text {
                                anchors.centerIn: parent
                                font.pointSize: 10
                                color: "black"
                                text: "ESP BOX 2"
                            }
                        }
                    }
                }
            }

            Page {
                visible: false
                //anchors.top: headerTextEight.bottom
                //anchors.topMargin: 10
                background: Rectangle {
                    color:"transparent"
                }

                Rectangle {
                    x: 10; y: 10
                    //anchors.fill: swipeView
                    width: widthElement * 2.5; height: heightElement * 1.4
                    color: "lightgrey"; border.color: Qt.lighter(color)
                    radius: 10

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        color: "black"
                        text: qsTr("Состояние ESP BOX 1")
                        font.pointSize: 9
                        minimumPointSize: 5
                        fontSizeMode: Text.Fit
                    }
                }
            }


            function hideLowLevelPage(tindex) {
                itemAt(currentIndex).visible = false
                itemAt(tindex).visible = true
                currentIndex = tindex
            }

        }

        PageIndicator {
            anchors.left: headerTextEight.right
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10

            interactive: true

            currentIndex: swipeViewEight.currentIndex
            count: swipeViewEight.count

            delegate: Rectangle {
                implicitWidth: 8
                implicitHeight: 8

                radius: width / 2
                color: "#494d8f"

                opacity: index === swipeViewEight.currentIndex ? 0.95 : pressed ? 0.7 : 0.45

                Behavior on opacity {
                    OpacityAnimator {
                        duration: 100
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        swipeViewEight.hideLowLevelPage(index)
                    }
                }
            }
        }
    }

    Canvas {
        id: sevenDataBus
        visible: false
        anchors.left: eightRectangle.right
        anchors.top: eightRectangle.top
        width: widthElement; height: eightRectangle.height

        onPaint: {
            var ctx = getContext("2d")

            // setup the stroke
            ctx.lineWidth = 2
            ctx.strokeStyle = "black"

            // create a path
            ctx.beginPath()
            for (var j = 1; j < 3; j++) {
                ctx.moveTo(0, height * j / 3)
                ctx.lineTo(width, height * j / 3)
            }
            ctx.stroke()
        }
    }

    Rectangle {
        id: nineRectangle
        anchors.left: sevenDataBus.right
        anchors.top: sevenDataBus.top
        width: widthElement * 3; height: heightElement * 2
        color: "lightgrey"; border.color: Qt.darker(color)
        radius: 10

        Text {
            id: headerTextNine
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 5
            color: "black"
            text: qsTr("РМО")
            font.pointSize: 15
            minimumPointSize: 5
            fontSizeMode: Text.Fit
        }
    }


    /*
    GroupBox {
        id: radarGrid
        title: qsTr("Антенная решетка")
        //anchors.top: parent.top
        //anchors.left: parent.left
        anchors.fill: parent
        width: 400
        height: 400

        background: Rectangle {
            //y: control.topPadding - control.padding
            //width: parent.width
            //height: parent.height - control.topPadding + control.padding
            color: "transparent"
            //border.color: "#21be2b"
            //radius: 2
        }

       SwipeView {
            id: swipeViewRadar
            anchors.centerIn: parent
            Page {
                id: topLevel
                visible: true
                //anchors.fill: parent
                Grid{
                    //anchors.fill: parent
                    //anchors.horizontalCenter: parent.horizontalCenter
                    //anchors.margins: 4
                    columns: 4
                    //spacing: 4
                    Repeater {
                        model: 16
                        Rectangle {
                            width: 80; height: 80
                            color: "forestgreen"
                            border.color: Qt.lighter(color)
                            Text {
                                anchors.centerIn: parent
                                color: "#f0f0f0"
                                text: "Фрагмент " + (index + 1)
                            }
                        }
                    }
                }
            }

            Page {
                id: middleLevel
                visible: false
                Grid{
                    //anchors.fill: parent
                    //anchors.horizontalCenter: parent.horizontalCenter
                    //anchors.margins: 4
                    columns: 8
                    //spacing: 4
                    Repeater {
                        model: 32
                        Rectangle {
                            width: 40; height: 80
                            color: "forestgreen"
                            border.color: Qt.lighter(color)
                            Text {
                                anchors.centerIn: parent
                                color: "#f0f0f0"
                                text: "ППМ " + (index + 1)
                            }
                        }
                    }
                }
            }

            function hideLowLevelPage(tindex) {
                itemAt(currentIndex).visible = false
                itemAt(tindex).visible = true
                currentIndex = tindex
            }

        }

        PageIndicator {
            anchors.top: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            interactive: true

            currentIndex: swipeViewRadar.currentIndex
            count: swipeViewRadar.count

            delegate: Rectangle {
                implicitWidth: 8
                implicitHeight: 8

                radius: width / 2
                color: "#494d8f"

                opacity: index === swipeViewRadar.currentIndex ? 0.95 : pressed ? 0.7 : 0.45

                Behavior on opacity {
                    OpacityAnimator {
                        duration: 100
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        swipeViewRadar.hideLowLevelPage(index)
                    }
                }
            }
        }

    }
    */

/*
    Column {

        anchors.left: radarGrid.right
        anchors.top: parent.top

        Rectangle {
            width: widthElement * 2
            height: heightElement
            color: "forestgreen"
            border.color: Qt.lighter(color)
            Text {
                anchors.centerIn: parent
                color: "#f0f0f0"
                text: "ППС"
            }
        }

        GroupBox {
            id: specialСalculatorBox
            title: qsTr("Спецвычислители")
            //anchors.fill
            width: widthElement * 2
            height: heightElement * 3

            background: Rectangle {
                //y: control.topPadding - control.padding
                //width: parent.width
                //height: parent.height - control.topPadding + control.padding
                color: "transparent"
                //border.color: "#21be2b"
                //radius: 2
            }

            SwipeView {
                 id: swipeViewSC
                 anchors.centerIn: parent
                 Page {
                     id: topLevelSC
                     visible: true
                     //anchors.fill: parent
                     Column{
                         //anchors.fill: parent
                         //anchors.horizontalCenter: parent.horizontalCenter
                         //anchors.margins: 4
                         //columns: 4
                         spacing: 8

                         Rectangle {
                             width: widthElement * 2; height: heightElement
                             color: "forestgreen"
                             border.color: Qt.lighter(color)
                             Text {
                                 anchors.centerIn: parent
                                 color: "#f0f0f0"
                                 text: "Основной"
                             }

                         }

                         Rectangle {
                             width: widthElement * 2; height: heightElement
                             color: "darkgray"
                             border.color: Qt.lighter(color)
                             Text {
                                 anchors.centerIn: parent
                                 color: "#f0f0f0"
                                 text: "Резервный"
                             }

                         }
                     }
                 }

                 Page {
                     id: middleLevelSC
                     visible: false
                     Column {
                         //anchors.fill: parent
                         //anchors.horizontalCenter: parent.horizontalCenter
                         //anchors.margins: 4
                         //columns: 8
                         spacing: 8
                         Rectangle {
                             width: widthElement * 2; height: heightElement
                             color: "forestgreen"
                             border.color: Qt.lighter(color)
                             Text {
                                 anchors.centerIn: parent
                                 color: "#f0f0f0"
                                 text: "Вычислитель 1"
                             }

                         }

                         Rectangle {
                             width: widthElement * 2; height: heightElement
                             color: "forestgreen"
                             border.color: Qt.lighter(color)
                             Text {
                                 anchors.centerIn: parent
                                 color: "#f0f0f0"
                                 text: "Вычислитель 2"
                             }

                         }
                     }
                 }

                 function hideLowLevelPage(tindex) {
                     itemAt(currentIndex).visible = false
                     itemAt(tindex).visible = true
                     currentIndex = tindex
                 }

             }

             PageIndicator {
                 anchors.top: parent.top
                 anchors.right: parent.right
                 interactive: true

                 currentIndex: swipeViewSC.currentIndex
                 count: swipeViewSC.count

                 delegate: Rectangle {
                     implicitWidth: 8
                     implicitHeight: 8

                     radius: width / 2
                     color: "#494d8f"

                     opacity: index === swipeViewSC.currentIndex ? 0.95 : pressed ? 0.7 : 0.45

                     Behavior on opacity {
                         OpacityAnimator {
                             duration: 100
                         }
                     }

                     MouseArea {
                         anchors.fill: parent
                         onClicked: {
                             swipeViewSC.hideLowLevelPage(index)
                         }
                     }
                 }
             }
        }

        GroupBox {
            id: commutatorBox
            title: qsTr("Коммутация")
            //anchors.fill
            width: widthElement * 2
            height: heightElement * 3

            background: Rectangle {
                //y: control.topPadding - control.padding
                //width: parent.width
                //height: parent.height - control.topPadding + control.padding
                color: "transparent"
                //border.color: "#21be2b"
                //radius: 2
            }

            SwipeView {
                 id: swipeViewComm
                 anchors.centerIn: parent
                 Page {
                     id: topLevelComm
                     visible: true
                     //anchors.fill: parent
                     Column{
                         //anchors.fill: parent
                         //anchors.horizontalCenter: parent.horizontalCenter
                         //anchors.margins: 4
                         //columns: 4
                         spacing: 8

                         Rectangle {
                              width: widthElement * 2; height: heightElement
                             color: "forestgreen"
                             border.color: Qt.lighter(color)
                             Text {
                                 anchors.centerIn: parent
                                 color: "#f0f0f0"
                                 text: "ESP BOX 1"
                             }

                         }

                         Rectangle {
                              width: widthElement * 2; height: heightElement
                             color: "forestgreen"
                             border.color: Qt.lighter(color)
                             Text {
                                 anchors.centerIn: parent
                                 color: "#f0f0f0"
                                 text: "ESP BOX 1"
                             }

                         }
                     }
                 }

                 Page {
                     id: middleLevelComm
                     visible: false

                 }

                 function hideLowLevelPage(tindex) {
                     itemAt(currentIndex).visible = false
                     itemAt(tindex).visible = true
                     currentIndex = tindex
                 }

             }

             PageIndicator {
                 anchors.top: parent.bottom
                 anchors.horizontalCenter: parent.horizontalCenter
                 interactive: true

                 currentIndex: swipeViewComm.currentIndex
                 count: swipeViewComm.count

                 delegate: Rectangle {
                     implicitWidth: 8
                     implicitHeight: 8

                     radius: width / 2
                     color: "#494d8f"

                     opacity: index === swipeViewComm.currentIndex ? 0.95 : pressed ? 0.7 : 0.45

                     Behavior on opacity {
                         OpacityAnimator {
                             duration: 100
                         }
                     }

                     MouseArea {
                         anchors.fill: parent
                         onClicked: {
                             swipeViewComm.hideLowLevelPage(index)
                         }
                     }
                 }
             }
        }

        GroupBox {
            id: workplaceBox
            title: qsTr("РМО")
            //anchors.fill
            width: widthElement * 2
            height: heightElement * 3

            background: Rectangle {
                //y: control.topPadding - control.padding
                //width: parent.width
                //height: parent.height - control.topPadding + control.padding
                color: "transparent"
                //border.color: "#21be2b"
                //radius: 2
            }

            SwipeView {
                 id: swipeViewWp
                 anchors.centerIn: parent
                 Page {
                     id: topLevelWp
                     visible: true
                     //anchors.fill: parent
                     Column{
                         //anchors.fill: parent
                         //anchors.horizontalCenter: parent.horizontalCenter
                         //anchors.margins: 4
                         //columns: 4
                         spacing: 8

                         Rectangle {
                              width: widthElement * 2; height: heightElement
                             color: "forestgreen"
                             border.color: Qt.lighter(color)
                             Text {
                                 anchors.centerIn: parent
                                 color: "#f0f0f0"
                                 text: "ESP BOX 1"
                             }

                         }
                     }
                 }

                 Page {
                     id: middleLevelWp
                     visible: false

                 }

                 function hideLowLevelPage(tindex) {
                     itemAt(currentIndex).visible = false
                     itemAt(tindex).visible = true
                     currentIndex = tindex
                 }

             }

             PageIndicator {
                 anchors.top: parent.bottom
                 anchors.horizontalCenter: parent.horizontalCenter
                 interactive: true

                 currentIndex: swipeViewWp.currentIndex
                 count: swipeViewWp.count

                 delegate: Rectangle {
                     implicitWidth: 8
                     implicitHeight: 8

                     radius: width / 2
                     color: "#494d8f"

                     opacity: index === swipeViewWp.currentIndex ? 0.95 : pressed ? 0.7 : 0.45

                     Behavior on opacity {
                         OpacityAnimator {
                             duration: 100
                         }
                     }

                     MouseArea {
                         anchors.fill: parent
                         onClicked: {
                             swipeViewWp.hideLowLevelPage(index)
                         }
                     }
                 }
             }
        }

    }

*/

    /*GroupBox {
        title: qsTr("Антенная решетка")
        width: 400
        height: 400

        anchors.left: parent.left
        anchors.top: parent.top

        ColumnLayout{
            anchors.fill: parent

            SwipeView {
                id: swipeView
                //anchors.fill: parent

                Page {
                    //anchors.fill: parent
                    Grid{
                        anchors.fill: parent
                        anchors.margins: 8
                        columns: 4
                        spacing: 4
                        Repeater {
                            model: 16
                            Rectangle {
                                width: 32; height: 32
                                color: "forestgreen"
                                border.color: Qt.lighter(color)
                                Text {
                                    anchors.centerIn: parent
                                    color: "#f0f0f0"
                                    text: "Фрагмент " + index
                                }
                            }
                        }
                    }
                }

                Page {
                    //anchors.fill: parent
                    Grid{
                        anchors.fill: parent
                        anchors.margins: 8
                        columns: 4
                        spacing: 4
                        Repeater {
                            model: 32
                            Rectangle {
                                width: 16; height: 16
                                color: "forestgreen"
                                border.color: Qt.lighter(color)
                                Text {
                                    anchors.centerIn: parent
                                    color: "#f0f0f0"
                                    text: "Фрагмент " + index
                                }
                            }
                        }
                    }
                }

            }

            PageIndicator {
                //anchors.bottom: parent.bottom
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
        }
    }*/
}

