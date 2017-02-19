
# - Find Lame
# This module can be used to find Lame
# Once done this will define
#
# MP3LAME_FOUND        If false, don't try to use Lame
#
# MP3LAME_INCLUDE_DIRS The Lame include directory
# MP3LAME_LIBRARIES    Link these to use Lame


if(MP3LAME_INCLUDE_DIR AND MP3LAME_LIBRARY)
	set(MP3LAME_FOUND true)
else()
	find_path(MP3LAME_INCLUDE_DIR "lame/lame.h")
	find_library(MP3LAME_LIBRARY mp3lame)

	if(MP3LAME_INCLUDE_DIR AND MP3LAME_LIBRARY)
		set(MP3LAME_FOUND true)
		message(STATUS "Found Mp3Lame: ${MP3LAME_LIBRARY}")
	else()
		set(MP3LAME_FOUND false)
		message(STATUS "Could not find Mp3Lame")
	endif()

	mark_as_advanced(MP3LAME_INCLUDE_DIR MP3LAME_LIBRARY)
endif()
