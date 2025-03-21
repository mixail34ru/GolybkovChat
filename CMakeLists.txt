cmake_minimum_required(VERSION 3.16)

project(GolybkovChat VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

file(GLOB CORE_SOURCE source/*.cpp source/controller/*.cpp source/view/*.cpp source/model/*.cpp)
file(GLOB CORE_HEADERS include/*.h include/controller/*.h include/view/private/*.h include/view/*.h include/model/*.h)

include_directories(include include/controller include/view/private include/view include/model)

set(LIBS libs)

# Подключение библиотеки ws2
set(LIB_WS2 ${LIBS}/ws2)
include_directories(${LIB_WS2})
file(GLOB LIB_WS2_SOURCE ${LIB_WS2}/*cpp)
file(GLOB LIB_WS2_HEADERS ${LIB_WS2}/*h)
add_library(ws2 ${LIB_WS2_SOURCE} ${LIB_WS2_HEADERS})

# Подключение библиотеки wstd
set(LIB_WSTD ${LIBS}/wstd)
include_directories(${LIB_WSTD})
file(GLOB LIB_WSTD_SOURCE ${LIB_WSTD}/*cpp)
file(GLOB LIB_WSTD_HEADERS ${LIB_WSTD}/*h)
add_library(wstd ${LIB_WSTD_SOURCE} ${LIB_WSTD_HEADERS})

set(PROJECT_SOURCES
  ${CORE_SOURCE} ${CORE_HEADERS}
  #${LIB_WS2_SOURCE} ${LIB_WS2_HEADERS}
  #${LIB_WSTD_SOURCE} ${LIB_WSTD_HEADERS}\
  ${ws2}
  ${wstd}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GolybkovChat
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET GolybkovChat APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(GolybkovChat SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(GolybkovChat
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(GolybkovChat PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ws2 wstd ws2_32.lib)

#target_link_libraries(${CMAKE_PROJECT_NAME} ws2_32)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.GolybkovChat)
endif()
set_target_properties(GolybkovChat PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS GolybkovChat
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GolybkovChat)
endif()
