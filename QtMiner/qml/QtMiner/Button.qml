import QtQuick 2.0

Rectangle {
    id: button
    signal clicked
    property alias text: btnText.text

    height: 50
    //radius: 10
    border.color:"#6a6363"

    gradient: off

     Gradient {
        id:off
        GradientStop { position: -1.0; color: "lightsteelblue" }
        GradientStop { position: 0; color: "lightsteelblue" }
        GradientStop { position: 0; color: "black" }
        GradientStop { position: 1.0; color: "black" }
    }

    Gradient {
        id:onn
        GradientStop { position: -1.0; color: "steelblue" }
        GradientStop { position: 0; color: "steelblue" }
        GradientStop { position: 0; color: "black" }
        GradientStop { position: 1.0; color: "black" }
    }

    Text {
        id:btnText
        anchors.centerIn:parent
        color:"white"
        text: "text"
    }

    MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked:  {
                button.clicked();
            }

            onEntered:{
                button.gradient=onn
                border.color= "steelblue"
            }

            onCanceled:{
                border.color= "#6a6363"
                button.gradient=off
            }

            onExited: {
                border.color= "#6a6363"
                button.gradient=off
            }
        }
}
