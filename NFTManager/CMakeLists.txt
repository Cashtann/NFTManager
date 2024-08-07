cmake_minimum_required(VERSION 3.16)

project(NFTManager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Widgets)

qt_standard_project_setup()

qt_add_executable(appNFTManager
    main.cpp
)

qt_add_qml_module(appNFTManager
    URI NFTManager
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES Global.h Global.cpp
        QML_FILES CustomTabButton.qml
        QML_FILES FeatureWindow.qml
        SOURCES Controller.h Controller.cpp
        SOURCES NFTables.h NFTables.cpp
        QML_FILES CustomButton.qml
        SOURCES Utilities.h Utilities.cpp
        QML_FILES
        SOURCES IpBlockInfo.h IpBlockInfo.cpp
        SOURCES IpBlockController.h IpBlockController.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appNFTManager PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appNFTManager
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appNFTManager
    PRIVATE Qt6::Quick Qt6::Widgets
)

include(GNUInstallDirs)
install(TARGETS appNFTManager
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
