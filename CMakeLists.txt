cmake_minimum_required(VERSION 3.0)
project (chordial)

# setting stuff
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -std=c99")
set (CMAKE_REQUIRED_INCLUDES /usr/local/include)
#set (CMAKE_VERBOSE_MAKEFILE ON)
set (SRC_FILES src/music_note.c src/interval.c src/chord.c src/helper_functions.c)
set (TEST_FILES test/test_main.c test/test_note.c test/test_interval.c test/test_chord.c)

enable_testing ()

# output
add_custom_command (OUTPUT layout_html.c COMMAND otemplate views/layout.html layout_html.c DEPENDS views/layout.html)
add_custom_command (OUTPUT index_html.c COMMAND otemplate views/index.html index_html.c DEPENDS views/index.html layout_html.c)
add_custom_command (OUTPUT chordial_data.c COMMAND opack static -o chordial_data.c DEPENDS static/*)
add_executable (chordial ${SRC_FILES} src/controller.c  src/main.c chordial_data.c layout_html.c index_html.c)

add_executable (test_chordial ${TEST_FILES} ${SRC_FILES})
target_link_libraries (test_chordial cunit)
target_link_libraries (test_chordial ${JSON_LIBRARY})
add_test (test_chordial test_chordial)

# libraries
find_package (FluidSynth REQUIRED)
find_package (Mp3Lame REQUIRED)
find_package (Onion REQUIRED)
find_package (Json REQUIRED)

include_directories (${FLUIDSYNTH_INCLUDE_DIR})
include_directories (${MP3LAME_INCLUDE_DIR})
include_directories (${ONION_INCLUDE_DIR})
include_directories (${JSON_INCLUDE_DIR})

target_link_libraries (chordial ${FLUIDSYNTH_LIBRARY})
target_link_libraries (chordial ${MP3LAME_LIBRARY})
target_link_libraries (chordial ${ONION_LIBRARY})
target_link_libraries (chordial ${JSON_LIBRARY})
