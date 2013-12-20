import QtQuick 2.0
import TcpSocket 1.0

Item {
    id: root

    property string response;
    property string host: "localhost"
    property int port: 4028
    function tellMiner(command, parameter) {
        var request = { command: command };
        if (parameter) {
            request.parameter = parameter;
        }
        socket.request = JSON.stringify(request);
        socket.connect();
    }



    TcpSocket {
        id: socket
        port: root.port
        hostname: root.host

        onReadyToReadResponse: {
            root.response = socket.response();
        }
    }
}
