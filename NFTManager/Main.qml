import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import app.Global
import app.Controller

Window {
    id: root
    width: Global.appWidth
    height: Global.appHeight
    visible: true
    title: qsTr("NFTManager")
    opacity: 1

    color: Global.color_bg1
    minimumWidth: Global.appMinWidth
    minimumHeight: Global.appMinHeight

    Window {
        id: test
        width: 200
        height: 200
        title: qsTr("test")
        visible: true
        opacity: bma.containsMouse ? 0 : 1
       MouseArea{
            id: bma
           anchors.fill: parent
       }
    }

    Column {

        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        Rectangle {
            id: selectionBar
            height: Global.selectionBarHeight
            color: Global.color_bg2
            anchors {
                left: parent.left
                right: parent.right
            }

            ///////////// TAB BAR BUTTONS BEGIN ///////////////
            TabBar {
                id: tabBar
                width: parent.width
                height: parent.height

                CustomTabButton {
                    stackLayoutItem: stackLayout
                    selfIndex: 0
                    name: "Feature1"
                }

                CustomTabButton {
                    stackLayoutItem: stackLayout
                    selfIndex: 1
                    name: "Feature2"
                }

                CustomTabButton {
                    stackLayoutItem: stackLayout
                    selfIndex: 2
                    name: "Feature3"
                }

                CustomTabButton {
                    stackLayoutItem: stackLayout
                    selfIndex: 3
                    name: "Feature4"
                }

                CustomTabButton {
                    stackLayoutItem: stackLayout
                    selfIndex: 4
                    name: "Feature5"
                }

                CustomTabButton {
                    stackLayoutItem: stackLayout
                    selfIndex: 5
                    name: "Feature6"
                }

                CustomTabButton {
                    stackLayoutItem: stackLayout
                    selfIndex: 6
                    name: "Feature7"
                }
            }

            ///////////// TAB BAR BUTTONS END ///////////////
        }

        ////////////////// TABS WINDOWS BEGIN //////////////
        StackLayout {
            id: stackLayout
            height: root.height - Global.selectionBarHeight
            anchors {
                left: parent.left
                right: parent.right
            } // Feature Windows below are index'ed one by one as they are listed (first is 0, then 1, then 2 etc.)

            FeatureWindow { // FIRST TAB (1)
                id: feature1
                Button{
                    onClicked: Controller.debug()
                }

            }

            FeatureWindow { // SECOND TAB (2)
                id: feature2

            }

            FeatureWindow { // THIRD TAB (3)
                id: feature3

            }

            FeatureWindow { // FOURTH TAB (4)
                id: feature4

            }

            FeatureWindow { // FIFTH TAB (5)
                id: feature5

            }

            FeatureWindow { // SIXTH TAB (6)
                id: feature6

            }

            FeatureWindow { // SEVENTH TAB (7)
                id: feature7

            }
        }
        ////////////////// TABS WINDOWS END //////////////////
    }
}
