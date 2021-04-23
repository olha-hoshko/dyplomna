import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

ApplicationWindow {
    id: windowTests
    width: 1280
    height: 720
    background: Rectangle {
        anchors.fill: parent
        color: "#FCFCFC"
    }

    signal exitWindowTests

    property int currentQuestionNumber: 1
    property string currentQuestion: qsTr("Here should be a question")
    property string firstAnswer: qsTr("first");
    property string secondAnswer: qsTr("second");
    property string thirdAnswer: qsTr("third");
    property string fourthAnswer: qsTr("4");

    Rectangle {
        id: header
        anchors.top: parent.top
        width: parent.width
        height: 50
        color: '#F0F0F0'
        visible: true

        ClientRegistrationButton {
            id: goBackButton
            width: header.width * 0.25
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: width * 0.05
            fontSize: 20
            text: qsTr("Quit test and go back to lecture")
            font.bold: true
            Connections {
                target: goBackButton
                function onClicked() {
                    testWindow.hide()
                    lecturesWindow.show()
                }
            }
        }
    }

    Rectangle {
        id: mainBody
        anchors.top: header.bottom
        anchors.bottom: footer.top
        anchors.bottomMargin: parent.height * 0.45
        width: parent.width
        Text {
            id: questionNumber
            text: qsTr("QUESTION " + currentQuestionNumber)
            color: "#0E0E0E"
            font.bold: true
            anchors.top: parent.top
            anchors.topMargin: parent.height * 0.1
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 27
            font.family: ClientLoginConstants.font.family
        }
        Text {
            id: testsView
            text: currentQuestion
            color: "#272727"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: questionNumber.bottom
            anchors.topMargin: parent.height * 0.3
            font.pixelSize: 25
            font.family: "Corbel"
        }
    }

    Rectangle {
        id: answersButtons
        anchors.bottom: footer.top
        width: parent.width
        height: parent.height * 0.45
        Grid {
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            columns: 2
            rows: 2
            spacing: parent.height * 0.05
            ClientAnswerButton {
                id: firstAnswerButton
                text: qsTr("➊   " + firstAnswer)
                width: answersButtons.width * 0.4
                height: answersButtons.height * 0.45
            }
            ClientAnswerButton {
                id: secondAnswerButton
                text: qsTr("➋   " + secondAnswer)
                buttonColor: "#6EE7CC"
                width: answersButtons.width * 0.4
                height: answersButtons.height * 0.45
            }
            ClientAnswerButton {
                id: thirdAnswerButton
                text: qsTr("➌   " + thirdAnswer)
                buttonColor: "#F89DBE"
                width: answersButtons.width * 0.4
                height: answersButtons.height * 0.45
            }
            ClientAnswerButton {
                id: fourthAnswerButton
                text: qsTr("➍   " + fourthAnswer)
                buttonColor: "#92C4FB"
                width: answersButtons.width * 0.4
                height: answersButtons.height * 0.45
            }
        }
    }
    Rectangle {
        id: footer
        anchors.bottom: parent.bottom
        width: parent.width
        height: 100
        Row {
            id: footerButtons
            anchors.top: parent.top
            anchors.topMargin: parent.height * 0.3
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: windowTests.height * 0.45 * 0.05
            ClientLoginButton {
                id: previousButton
                width: footer.width * 0.1
                text: qsTr("Previous")
                opacity: 1
                visible: true
                Connections {
                    target: previousButton
                    function onClicked() {

                    }
                }
            }
            ClientLoginButton {
                id: nextButton
                width: footer.width * 0.1
                text: qsTr("Next")
                opacity: 1
                visible: true
                Connections {
                    target: nextButton
                    function onClicked() {

                    }
                }
            }
        }
    }
}
