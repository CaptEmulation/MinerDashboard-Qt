import QtQuick 2.0



Rectangle {
    property int max: 11
    property int min: 0
    property int value: 0
    property string unitText
    property real textScale: 1.0
    property int fontPixelSize: width / 15

    onMaxChanged: {
        var step = (max - min) / 10;
        var valuesArray = values.getAllLabels();
        for (var i = 0; i < valuesArray.length; i++) {
            valuesArray[i].text = min + Math.round(i * step);
        }

    }


    width: 360
    height: 360
    color: '#000000'
    smooth: true

    Image {
        anchors.fill: parent
        id:guageBg
        source: 'img/SpeedGaugeBackground.PNG'
    }

    Item {
        id: dial

        property int value: parent.value
        property int max:parent.max
        x: 0.46 * parent.width
        y: 0.115 * parent.height
        width: 0.08125 * parent.width
        height: 0.45 * parent.height

        Image {
            id: pin
            source: 'img/Pin.PNG'
            smooth: true
            anchors.fill: parent
            transform: Rotation {
                id: rot
                angle: -150 + ((value - min) / (max - min)) * 300
                origin.x: pin.width / 2
                origin.y: pin.height * 0.9
                Behavior on angle {
                    NumberAnimation{ duration: 1000 }
                }
            }
        }
    }

    Rectangle {
        id: values
        color: 'transparent'
        anchors.fill: parent

        property string unitText: parent.unitText
        property real textScale: parent.textScale
        property int fontPixelSize: textScale * parent.fontPixelSize

        function setFontPixelSize(pixels) {
            getAllLabels().foreach(function (element) {
               element.font.pixelSize = pixels;
            });
        }


        function getAllLabels() {
            return [one, two, three, four, five, six, seven, eight, nine, ten, eleven];
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height * 0.25
            font.pixelSize: parent.fontPixelSize * 1.2
            color: 'white'
            text: parent.unitText
        }

        Text {
            id: one
            color: 'white'
            font.pixelSize: parent.fontPixelSize
            transformOrigin: Item.Center
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0.16667 * parent.height
            anchors.left: parent.left
            anchors.leftMargin: 0.29166666666667 * parent.width
            text: "1"
        }

        Text {
            id: two
            text: "2"
            color: 'white'
            font.pixelSize: parent.fontPixelSize
            transformOrigin: Item.Center
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0.29166666666667 * parent.width
            anchors.left: parent.left
            anchors.leftMargin: 0.16667 * parent.height
        }

        Text {
            id: three
            text: "3"
            color: 'white'
            font.pixelSize: parent.fontPixelSize
            transformOrigin: Item.Center
            anchors.left: parent.left
            anchors.leftMargin: 0.125 * parent.width
            anchors.verticalCenter: parent.verticalCenter
        }


        Text {
            id: four
            text: "4"
            color: 'white'
            font.pixelSize: parent.fontPixelSize
            transformOrigin: Item.Center
            anchors.top: parent.top
            anchors.topMargin: 0.29166666666667 * parent.width
            anchors.left: parent.left
            anchors.leftMargin: 0.16667 * parent.height
        }

        Text {
            id: five
            text: "5"
            color: 'white'
            font.pixelSize: parent.fontPixelSize
            transformOrigin: Item.Center
            anchors.top: parent.top
            anchors.topMargin: 0.16667 * parent.height
            anchors.left: parent.left
            anchors.leftMargin: 0.29166666666667 * parent.width
        }

        Text {
            id: six
            color: 'white'
            font.pixelSize: parent.fontPixelSize
            transformOrigin: Item.Center
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 0.125 * parent.width
            text: "6"
        }

        Text {
            id: seven
            text: "7"
            color: 'white'
            font.pixelSize: parent.fontPixelSize
            transformOrigin: Item.Center
            anchors.top: parent.top
            anchors.topMargin: 0.16667 * parent.height
            anchors.right: parent.right
            anchors.rightMargin: 0.29166666666667 * parent.width
        }

        Text {
            id: eight
            text: "8"
            color: 'white'
            font.pixelSize: parent.fontPixelSize
            transformOrigin: Item.Center
            anchors.top: parent.top
            anchors.topMargin: 0.29166666666667 * parent.width
            anchors.right: parent.right
            anchors.rightMargin: 0.16667 * parent.height
        }

        Text {
            id: nine
            text: "9"
            color: 'white'
            font.pixelSize: parent.fontPixelSize
            transformOrigin: Item.Center
            anchors.right: parent.right
            anchors.rightMargin: 0.125 * parent.width
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            id: ten
            text: "10"
            color: 'white'
            font.pixelSize: parent.fontPixelSize
            transformOrigin: Item.Center
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0.29166666666667 * parent.width
            anchors.right: parent.right
            anchors.rightMargin: 0.16667 * parent.height
        }

        Text {
            id: eleven
            color: 'white'
            text: "11"
            font.pixelSize: parent.fontPixelSize
            transformOrigin: Item.Center
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0.16667 * parent.height
            anchors.right: parent.right
            anchors.rightMargin: 0.29166666666667 * parent.width
        }
    }

}

