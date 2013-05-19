import QtQuick 2.0
import Process 1.0
import TcpSocket 1.0

Rectangle {
    width: 720
    height: 300
    color: 'black'

    MinerApi{
        id: minerApi
    }

    MinerApi {
        id: gpuApi
        onResponseChanged: {
            var json = JSON.parse(response);
            var speed = json.GPU[0]['MHS 5s'];
            mhsGuage.value = speed;
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
            minerApi.tellMiner("gpuintensity", "8");
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
        unitText: 'MH/s'
        max: 100
        value: 0
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
            minerApi.tellMiner("gpuintensity", "0,8");
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
