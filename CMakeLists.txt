cmake_minimum_required(VERSION 3.5)

project(AutoPlateform VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES QT6 Qt5 COMPONENTS Widgets Xml  REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Xml  REQUIRED)
find_package(NodeEditor REQUIRED)



set ( PROJECT_SOURCES
        main.cpp
        dialogs/mainwindow.h dialogs/mainwindow.cpp dialogs/mainwindow.ui
        dialogs/projectdialog.h dialogs/projectdialog.cpp dialogs/projectdialog.ui
        dialogs/editordialog.h dialogs/editordialog.cpp dialogs/editordialog.ui
        dialogs/nodeparametersdialog.h dialogs/nodeparametersdialog.cpp dialogs/nodeparametersdialog.ui

        image.qrc
        TextData.hpp
        TreeViewReadonlyDelegate.h
        aicctreewidget.hpp
        aiccmodel.hpp
        aiccflowview.hpp
        calculator/aicccalculator.hpp
        datamodel/aiccsourcedatamodel.hpp
        datamodel/aiccdisplaydatamodel.hpp
)

add_executable(AutoPlateform
    ${PROJECT_SOURCES}
)
target_link_libraries(AutoPlateform PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Xml NodeEditor::nodes)

