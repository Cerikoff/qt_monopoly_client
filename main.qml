import QtQuick 1.1
//import Validator 1.0

Rectangle {
    id: rectangle2
    width: 600
    height: 400
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#ffffff"
        }

        GradientStop {
            position: 1
            color: "#000000"
        }
    }
    anchors.fill: parent

    SimpleButton
    {
        id:change_interface
        y: 185

        buttonColor: "black"
        borderColor: "black"

        text: "OK"
        anchors.right: parent.right
        anchors.rightMargin: 100
        anchors.left: rectangle1.right
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter

        height: 30
        onClicked: window.change_interface(ip_input.text)
    }



    Rectangle {
        id: rectangle1
        y: 185
        height: 30
        color: "#000000"
        anchors.right: parent.right
        anchors.rightMargin: 200
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 100

        TextInput {
            id: ip_input
            color: "#ffffff"
            text: qsTr("")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.left: parent.left
            font.pixelSize: 20
            validator: RegExpValidator { regExp: /^(([0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){3}[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5]/ }
        }
    }

    Text {
        id: text1
        y: 149
        height: 30
        text: qsTr("Введите IP-адрес сервера")
        anchors.right: parent.right
        anchors.rightMargin: 100
        anchors.left: parent.left
        anchors.leftMargin: 100
        anchors.bottom: rectangle1.top
        anchors.bottomMargin: 6
        font.pixelSize: 20
    }
}

