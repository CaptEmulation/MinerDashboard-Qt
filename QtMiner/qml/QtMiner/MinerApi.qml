import QtQuick 2.0
import TcpSocket 1.0

Item {
    id: root

    property string response;

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
        port: 4028

        onReadyToReadResponse: {
            root.response = socket.response();
        }
    }
}
