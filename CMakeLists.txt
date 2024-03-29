﻿cmake_minimum_required(VERSION 3.12)

project(AutoPlateform VERSION 0.1 LANGUAGES CXX)

if(UNIX)
    set(CMAKE_BUILD_RPATH "$ORIGIN")
endif(UNIX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sqlite/node.db3 DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/sqlite)

file(GLOB allCopyFiles "${CMAKE_CURRENT_SOURCE_DIR}/nodeconfig/*.hpp")
file(COPY ${allCopyFiles} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/nodeconfig)

#find_package(Qt5 COMPONENTS Widgets Xml Sql REQUIRED)
find_package(QT NAMES QT6 Qt5 COMPONENTS Widgets Xml Sql Concurrent REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Xml Sql Concurrent REQUIRED)
find_package(NodeEditor REQUIRED)
find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)
find_package(Boost REQUIRED COMPONENTS system graph)


set ( PROJECT_SOURCES
    main.cpp
    dialogs/mainwindow.h dialogs/mainwindow.cpp dialogs/mainwindow.ui
    dialogs/projectdialog.h dialogs/projectdialog.cpp dialogs/projectdialog.ui
    dialogs/editordialog.h dialogs/editordialog.cpp dialogs/editordialog.ui
    dialogs/nodeparametersdialog.h dialogs/nodeparametersdialog.cpp dialogs/nodeparametersdialog.ui
    dialogs/nodetreedialog.h dialogs/nodetreedialog.cpp dialogs/nodetreedialog.ui
    dialogs/importscriptdialog.h dialogs/importscriptdialog.cpp dialogs/importscriptdialog.ui

    image.qrc
    TextData.hpp
    itemreadonlydelegate.h
    aicctreewidget.hpp
    aiccmodel.hpp
    utils.h utils.cpp
    calculator/aicccalculator.hpp
    datamodel/aiccsourcedatamodel.hpp
    datamodel/aiccdisplaydatamodel.hpp

    controllers/aicctoolbutton.hpp
    controllers/aiccbreadcrumbnavigation.hpp
    controllers/aiccflowview.hpp
    controllers/aiccstackedwidget.hpp

    nodeparser/invocable.hpp
    nodeparser/invocable_parser.hpp
    nodeparser/models.hpp
    nodeparser/models.cpp
    nodeparser/module_library.hpp
    nodeparser/module_library.cpp
    nodeparser/source_generator.hpp

    sqlite/aiccsqlite.hpp

    nodeconfig/adas/node.hpp
    nodeconfig/adas/asio_can.h
    nodeconfig/adas/can.h
    nodeconfig/adas/runtime.hpp
    )

add_executable(AutoPlateform
    ${PROJECT_SOURCES}
    )

target_compile_options(AutoPlateform PRIVATE -Wall -fvisibility=hidden -fno-rtti)
target_include_directories(AutoPlateform
    PRIVATE
    ${LLVM_INCLUDE_DIRS}
    ${CLANG_INCLUDE_DIRS}
    )
target_link_libraries(AutoPlateform
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Concurrent
    NodeEditor::nodes
    ${LLVM_AVAILABLE_LIBS}
    clangAST
    clangBasic
    clangFrontend
    clangSerialization
    clangTooling
    Boost::headers Boost::system Boost::graph
    )

