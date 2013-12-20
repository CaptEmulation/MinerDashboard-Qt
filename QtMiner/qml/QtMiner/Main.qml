import QtQuick 2.0
import Process 1.0
import TcpSocket 1.0
import QtQuick.Controls 1.1

Rectangle {
    width: 720
    height: 300
    color: 'black'

    MinerApi{
        id: minerApi
        host: "127.0.0.1"
    }

    MinerApi {
        id: gpuApi
        host: "192.168.1.64"
        onResponseChanged: {
            var json = JSON.parse(response);
            var speed = json.GPU[0]['MHS 5s'];
            var enabled = json.GPU[0]['Enabled'];
            var temp = json.GPU[0]['Temperature'];
            var rpm = json.GPU[0]['Fan Speed'];
            mhsGuage.value = 1000 * speed;
            tempGuage.value = temp;
            fanGuage.value = rpm;
        }
    }

    MinerApi {
        id: payApi
        onResponseChanged: {
            var json = JSON.parse(response);
        }
    }

    Timer {
        interval: 1000
        repeat: true
        running: true
        onTriggered: {
            gpuApi.tellMiner("gpu", "0");
        }
    }

//    Timer {
//        interval: 500
//        repeat: true
//        running: true
//        onTriggered: {
//            payApi.tellMiner("status");
//        }
//    }

    Timer {
        id: restartFastTimer
        interval: 2 * 60 * 60 * 1000;
        onTriggered: {
            minerApi.tellMiner("gpuenable", "0");
            minerApi.tellMiner("gpuintensity", "16");
        }
    }

    Process {
        id: cgminer
        command: 'open foo.app'
        onStarted: console.log('Started: ' + cgminer.readAllStandardOutput());
        onError: console.log('Error: ' + cgminer.exitCode + ":" +cgminer.exitStatus + ":" + cgminer.readAllStandardError());
        onFinished: console.log('Finished: '+ arg1)
    }

    SpeedGuage {
        id: mhsGuage
        width: parent.width / 4 - 10
        height: width
        anchors.top: parent.top
        anchors.topMargin: 25
        anchors.left: parent.left
        anchors.leftMargin: 25
        unitText: 'KH/s'
        max: 500
        value: 0
    }

    SpeedGuage {
        id: tempGuage
        width: parent.width / 4 - 10
        height: width
        anchors.top: parent.top
        anchors.topMargin: 25
        anchors.left: mhsGuage.right
        anchors.leftMargin: 25
        unitText: '°C'
        max: 110
        min: 20
        value: 50
    }

    SpeedGuage {
        id: fanGuage
        width: parent.width / 4 - 10
        height: width
        anchors.top: parent.top
        anchors.topMargin: 25
        anchors.left: tempGuage.right
        anchors.leftMargin: 25
        unitText: 'Fan RPM'
        max: 5000
        min: 250
        value: 1000
    }

    Text {
        id: intensityText
        color: 'white'
        text: intensitySlider.value
        anchors.top: intensitySlider.bottom
        anchors.topMargin: 8
        anchors.horizontalCenter: intensitySlider.horizontalCenter
    }

    Text {
        color: 'white'
        text: 'Intensity'
        anchors.bottom: intensitySlider.top
        anchors.topMargin: 8
        anchors.horizontalCenter: intensitySlider.horizontalCenter
    }

    Slider {
        id: intensitySlider
        width: 24
        height: fanGuage.height
        anchors.top: parent.top
        anchors.topMargin: 32
        anchors.right: parent.right
        anchors.rightMargin: 25
        tickmarksEnabled: true
        orientation: Qt.Vertical
        minimumValue: 8
        maximumValue: 18
        value: 10
        stepSize: 1
        onValueChanged: {
            minerApi.tellMiner("gpuintensity", "0," + value);
        }


    }

    Button {
        id: fastButton
        anchors.right: parent.right
        anchors.rightMargin: 15
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15
        text: "Fast"
        width: parent.width/4 -10


        onClicked: {
            minerApi.tellMiner("gpuenable", "0");
            minerApi.tellMiner("gpuintensity", "0,16");
            restartFastTimer.stop();
        }
    }

    Button {
        id: slowButton
        anchors.right: fastButton.left
        anchors.rightMargin: 15
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15
        text: "Slow"
        width: parent.width/4 -10


        onClicked: {
            minerApi.tellMiner("gpuenable", "0");
            minerApi.tellMiner("gpuintensity", "0,d");
            restartFastTimer.start();
        }
    }

    Button {
        id: stopButton
        anchors.right: slowButton.left
        anchors.rightMargin: 15
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15
        text: "Stop"
        width: parent.width/4 -10


        onClicked: {
            minerApi.tellMiner("gpudisable", "0");
            restartFastTimer.start();
        }
    }
}
