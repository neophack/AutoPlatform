cmake_minimum_required(VERSION 3.5)

project(AutoPlateform VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES QT6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(NodeEditor REQUIRED)



set(PROJECT_SOURCES
        aicctreewidget.hpp
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        TreeViewReadonlyDelegate.h
        image.qrc
        datamodel/aiccsourcedatamodel.hpp
        datamodel/aiccdisplaydatamodel.hpp
#        aiccsourcedatamodel.cpp
        TextData.hpp

#        aiccdisplaydatamodel.cpp
        aiccmodel.hpp
        aiccflowview.hpp
        calculator/aicccalculator.hpp

)

        add_executable(AutoPlateform
            ${PROJECT_SOURCES}
        )

target_link_libraries(AutoPlateform PRIVATE Qt${QT_VERSION_MAJOR}::Widgets NodeEditor::nodes)

