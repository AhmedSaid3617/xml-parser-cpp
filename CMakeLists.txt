cmake_minimum_required(VERSION 3.16)

project(xml_parser VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE XML_PARSER_CORE_CPP src/core/*.cpp)

include_directories(src/core)
include_directories(src/console)

file(GLOB_RECURSE XML_PARSER_CONSOLE_CPP src/console/*.cpp)

add_executable(console ${XML_PARSER_CONSOLE_CPP} ${XML_PARSER_CORE_CPP}
        src/core/convert/Conversion_Function.cpp
)

include(CTest)

add_executable(xml_consistency_check test/xml_consistency.cpp ${XML_PARSER_CORE_CPP})
add_test(NAME XML_CONSISTENCY_CHECK COMMAND xml_consistency_check)

add_executable(xml_to_json test/xml_to_json.cpp ${XML_PARSER_CORE_CPP})
add_test(NAME XML_TO_JSON_CHECK COMMAND xml_to_json)

add_executable(xml_to_tree test/xml_to_tree.cpp ${XML_PARSER_CORE_CPP})
add_test(NAME XML_TO_TREE_CHECK COMMAND xml_to_tree)

add_executable(string_formatting test/string_formatting.cpp ${XML_PARSER_CORE_CPP})
add_test(NAME STRING_FORMATTING_CHECK COMMAND string_formatting)

add_executable(xml_compression test/xml_compression.cpp ${XML_PARSER_CORE_CPP})
add_test(NAME XML_COMPRESSION COMMAND xml_compression)

add_executable(graphs_and_dynamic_arrays test/graphs_and_dynamic_arrays.cpp ${XML_PARSER_CORE_CPP})
add_test(NAME GRAPHS_AND_DYNAMIC_ARRAYS_CHECK COMMAND graphs_and_dynamic_arrays)

add_executable(social_network test/social_network.cpp ${XML_PARSER_CORE_CPP})
add_test(NAME SOCIAL_NETWORK_CHECK COMMAND social_network)

add_executable(data_extraction test/data_extraction.cpp ${XML_PARSER_CORE_CPP})
add_test(NAME DATA_EXTRACTION_CHECK COMMAND data_extraction)

if (${COMPILE_GUI})
    set (CMAKE_PREFIX_PATH ${COMPILE_GUI_QT_GCC_64_FOLDER})

    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

    set(PROJECT_SOURCES
        src/gui/gui_main.cpp
        src/gui/mainwindow.cpp
        src/gui/mainwindow.h
        src/gui/mainwindow.ui)

    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)

    if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
        qt_add_executable(xml_editor_gui
                MANUAL_FINALIZATION
                ${PROJECT_SOURCES}
                ${XML_PARSER_CORE_CPP}

        )
        # Define target properties for Android with Qt 6 as:
        #    set_property(TARGET xml_editor_gui APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
        #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
        # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
    else()
        if(ANDROID)
            add_library(xml_editor_gui SHARED
                    ${PROJECT_SOURCES}
            )
            # Define properties for Android with Qt 5 after find_package() calls as:
            #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
        else()
            add_executable(xml_editor_gui
                    ${PROJECT_SOURCES}
            )
        endif()
    endif()

    target_link_libraries(xml_editor_gui PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

    # Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
    # If you are developing for iOS or macOS you should consider setting an
    # explicit, fixed bundle identifier manually though.
    if(${QT_VERSION} VERSION_LESS 6.1.0)
        set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.xml_editor_gui)
    endif()
    set_target_properties(xml_editor_gui PROPERTIES
            ${BUNDLE_ID_OPTION}
            MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
            MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
            MACOSX_BUNDLE TRUE
            WIN32_EXECUTABLE TRUE
    )

    include(GNUInstallDirs)
    install(TARGETS xml_editor_gui
            BUNDLE DESTINATION .
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

    if(QT_VERSION_MAJOR EQUAL 6)
        qt_finalize_executable(xml_editor_gui)
    endif()

endif ()