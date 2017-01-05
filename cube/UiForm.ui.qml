import QtQuick 2.4

Item {
    width: 512
    height: 512
    property alias main_display: main_display
    clip: false

    Rectangle {
        id: main_display
        x: 0
        y: 0
        width: 512
        height: 512
        color: "#ffffff"
    }

    Rectangle {
        id: cam1
        x: 512
        y: 0
        width: 128
        height: 128
        color: "#ffffff"
    }

    Rectangle {
        id: cam2
        x: 512
        y: 128
        width: 128
        height: 128
        color: "#ffffff"
    }

    Rectangle {
        id: cam3
        x: 512
        y: 256
        width: 128
        height: 128
        color: "#ffffff"
    }

    Rectangle {
        id: cam4
        x: 512
        y: 384
        width: 128
        height: 128
        color: "#ffffff"
    }
}
