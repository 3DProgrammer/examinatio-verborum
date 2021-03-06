cmake_minimum_required(VERSION 3.5)

project(examinatio-verborum VERSION 0.6 LANGUAGES CXX)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        wordChooser.cpp wordChooser.h wordlistParser.cpp wordlistParser.h settingsWindow/settingswindow.cpp settingsWindow/settingswindow.h settingsWindow/settingswindow.ui style/NoxStyle.cpp style/NoxStyle.h style/NeonStyle.cpp style/NeonStyle.h addword/addnoun.cpp addword/addnoun.h addword/addnoun.ui addword/addverb.cpp addword/addverb.h addword/addverb.ui util.h)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(examinatio-verborum
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
        qt_add_resources(examinatio-verborum "style_resources"
                PREFIX "/"
                FILES
                res/noxbackground.png
                res/noxbutton.png
                )
    qt_add_resources(examinatio-verborum "example-wordlists"
            PREFIX "/"
            FILES
            example-wordlists/CLCStage1.wordList
            example-wordlists/exampleVocab.wordList
            example-wordlists/L2GCSE9.wordList)
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET examinatio-verborum APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(examinatio-verborum SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(examinatio-verborum
            ${PROJECT_SOURCES}
                res/style_res.qrc
                example-wordlists/example_wordlists.qrc
        )
    endif()
endif()
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/bibliotheca)
target_link_libraries(examinatio-verborum PRIVATE Qt${QT_VERSION_MAJOR}::Widgets bibliotheca)
target_include_directories(examinatio-verborum PRIVATE ${BIBLIOTHECA_INCLUDE_DIRS})
set_target_properties(examinatio-verborum PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(examinatio-verborum)
endif()
message(STATUS "QT Major version is ${QT_VERSION_MAJOR}")
message(STATUS "QT Minor version is ${QT_VERSION_MINOR}")
message(STATUS "Bibliotheca include dir is ${BIBLIOTHECA_INCLUDE_DIRS}")
target_compile_definitions(examinatio-verborum PUBLIC PROJECT_VERSION_MAJOR=${CMAKE_PROJECT_VERSION_MAJOR})
target_compile_definitions(examinatio-verborum PUBLIC PROJECT_VERSION_MINOR=${CMAKE_PROJECT_VERSION_MINOR})
target_compile_definitions(examinatio-verborum PUBLIC PROJECT_VERSION_STRING="${CMAKE_PROJECT_VERSION}")