cmake_minimum_required(VERSION 2.8)
project (chordial)

# setting stuff
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -std=c99")
set(CMAKE_REQUIRED_INCLUDES /usr/local/include)

# output
add_executable(chordial main.c chord.c)

# libraries
find_package(FluidSynth REQUIRED)
find_package(Mp3Lame REQUIRED)
find_Package(Onion REQUIRED)
include_directories(${FLUIDSYNTH_INCLUDE_DIR} ${MP3LAME_INCLUDE_DIR} ${ONION_INCLUDE_DIR})
target_link_libraries (chordial ${FLUIDSYNTH_LIBRARY} ${MP3LAME_LIBRARY} ${ONION_LIBRARY})
