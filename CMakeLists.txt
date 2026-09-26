# CMakeLists.txt — Collatinus-Qt6
#
# Builds the Qt 6 / CMake modernization of Collatinus 12.3.  The legacy qmake
# projects (collatinus.pro, Client_C11.pro) are kept for historical reference
# and for reproducing the original Qt 5 baseline; they are no longer the
# supported build system.

cmake_minimum_required(VERSION 3.20)

project(Collatinus
    VERSION 12.3.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Single source of truth for the version and product name.  The version
# inherits upstream's major.minor (12.3) and appends the fork's own revision
# (.0); it is shown by --version, in the About box and by the packages.
add_compile_definitions(
    VERSION=\"${PROJECT_VERSION}\"
    COLLATINUS_PRODUCT=\"Collatinus-Qt6\"
)

# Build the executable under <build>/bin.
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
# No .ui files: the whole UI is built in code.

include(GNUInstallDirs)

# --- dependencies ------------------------------------------------------------

find_package(Qt6 6.4 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Network
    Svg
    PrintSupport
    LinguistTools
)

# QuaZip: prefer the distribution CMake package (QuaZip::QuaZip) and fall
# back to pkg-config when only a .pc file is shipped (SPEC 3.4).  Either way
# no include path and no shared object is hard-coded.
#
# COLLATINUS_QUAZIP_USE_PKGCONFIG forces the pkg-config path; it is needed
# when a CMake package exists but is not relocatable (e.g. when building
# against a Qt/QuaZip installed outside /usr).
option(COLLATINUS_QUAZIP_USE_PKGCONFIG
       "Resolve QuaZip through pkg-config instead of its CMake package" OFF)

set(QuaZip-Qt6_FOUND FALSE)
if(NOT COLLATINUS_QUAZIP_USE_PKGCONFIG)
    find_package(QuaZip-Qt6 CONFIG QUIET)
endif()

if(QuaZip-Qt6_FOUND)
    set(COLLATINUS_QUAZIP_TARGET QuaZip::QuaZip)
    message(STATUS "QuaZip: using the QuaZip-Qt6 CMake package")
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(QUAZIP REQUIRED IMPORTED_TARGET quazip1-qt6)
    set(COLLATINUS_QUAZIP_TARGET PkgConfig::QUAZIP)
    message(STATUS "QuaZip: using pkg-config module quazip1-qt6")
endif()

# --- application sources (explicit; no GLOB as the primary source) -----------

set(COLLATINUS_SOURCES
    src/ch.cpp
    src/dicos.cpp
    src/flexion.cpp
    src/irregs.cpp
    src/lasla.cpp
    src/lemcore.cpp
    src/lemmatiseur.cpp
    src/lemme.cpp
    src/mainwindow.cpp
    src/maj.cpp
    src/modele.cpp
    src/modules.cpp
    src/mot.cpp
    src/paths.cpp
    src/reglevg.cpp
    src/scandeur.cpp
    src/tagueur.cpp
    src/theme.cpp
    src/translationmanager.cpp
    src/vargraph.cpp
)

set(COLLATINUS_HEADERS
    src/ch.h
    src/dicos.h
    src/flexion.h
    src/irregs.h
    src/lasla.h
    src/lemcore.h
    src/lemmatiseur.h
    src/lemme.h
    src/mainwindow.h
    src/maj.h
    src/modele.h
    src/modules.h
    src/mot.h
    src/paths.h
    src/reglevg.h
    src/scandeur.h
    src/tagueur.h
    src/theme.h
    src/translationmanager.h
    src/vargraph.h
)

# The engine + GUI, without an entry point.  An OBJECT library (rather than
# STATIC) guarantees the Qt resource object is always linked by consumers.
add_library(collatinus_core OBJECT
    ${COLLATINUS_SOURCES}
    ${COLLATINUS_HEADERS}
    collatinus.qrc
)

target_include_directories(collatinus_core PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# COLLATINUS_INSTALL_DATADIR is the FHS data directory resolved at runtime.
target_compile_definitions(collatinus_core PRIVATE
    COLLATINUS_INSTALL_DATADIR=\"${CMAKE_INSTALL_FULL_DATADIR}/collatinus\"
)

target_compile_options(collatinus_core PRIVATE -Wall -Wextra)

target_link_libraries(collatinus_core PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
    Qt6::Svg
    Qt6::PrintSupport
    ${COLLATINUS_QUAZIP_TARGET}
)

# --- translations (SPEC section 11.1) ----------------------------------------

# Compile the .ts catalogs and embed them into collatinus_core under
# :/i18n/collatinus_<locale>.qm, so every consumer (GUI and tests) finds
# them without copying .qm files into the source tree.
qt_add_translations(collatinus_core
    TS_FILES
        i18n/collatinus_fr.ts
        i18n/collatinus_en.ts
        i18n/collatinus_zh_CN.ts
    RESOURCE_PREFIX "/i18n"
)

# --- executables -------------------------------------------------------------

qt_add_executable(collatinus src/main.cpp)
target_link_libraries(collatinus PRIVATE collatinus_core)

# Historical console TCP client (Client_C11.pro).
qt_add_executable(collatinus-client src/client_main.cpp)
target_link_libraries(collatinus-client PRIVATE
    Qt6::Core
    Qt6::Network
    Qt6::Widgets
)

# --- installation (FHS layout, SPEC section 10) ------------------------------

install(TARGETS collatinus RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY bin/data/ DESTINATION ${CMAKE_INSTALL_DATADIR}/collatinus/data)
install(DIRECTORY bin/doc/  DESTINATION ${CMAKE_INSTALL_DATADIR}/collatinus/doc)

# --- desktop integration (SPEC section 13) -----------------------------------

install(FILES resources/org.collatinus.Collatinus.desktop
        DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)
install(FILES resources/org.collatinus.Collatinus.metainfo.xml
        DESTINATION ${CMAKE_INSTALL_DATADIR}/metainfo)
install(FILES resources/icons/collatinus-256.png
        DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/256x256/apps
        RENAME collatinus.png)
install(FILES res/collatinus.svg
        DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps
        RENAME collatinus.svg)

# Manual page (from the Debian documentation patch applied at import time).
install(FILES doc/collatinus.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
