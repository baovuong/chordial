cmake_minimum_required(VERSION 2.8)
project (chordial)

# setting stuff
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -std=c99")
set (CMAKE_REQUIRED_INCLUDES /usr/local/include)
#set (CMAKE_VERBOSE_MAKEFILE ON)


# output
add_custom_command (OUTPUT layout_html.c COMMAND otemplate views/layout.html layout_html.c DEPENDS views/layout.html)
add_custom_command (OUTPUT index_html.c COMMAND otemplate views/index.html index_html.c DEPENDS views/index.html layout_html.c)
add_custom_command (OUTPUT chordial_data.c COMMAND opack static -o chordial_data.c DEPENDS static/*)
add_executable (chordial main.c music_note.c interval.c chord.c chordial_data.c layout_html.c index_html.c)

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