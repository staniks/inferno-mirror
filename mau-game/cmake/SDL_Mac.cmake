# Copyright (C) 2020 by Marin Saric
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR
# IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#
# Note from author: OK to relicense as anything, including GPLv3, etc.

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_mixer REQUIRED sdl2_mixer)

list(GET SDL2_LIBRARY_DIRS 0 SDL2_LIBDIR)

if (NOT SDL2_LIBDIR)
  message(FATAL_ERROR "Can't find SDL2 libraries")
endif()

set(SDL2_CONFIG /usr/local/bin/sdl2-config)
if (NOT SDL2_CONFIG)
    message( FATAL_ERROR "Failed to locate sdl2-config." )
else()
    message( STATUS "Found sdl2-config: ${SDL2_CONFIG}" )
endif()

exec_program(${SDL2_CONFIG} ARGS --static-libs OUTPUT_VARIABLE SDL2_LIBRARIES)
string(REPLACE "-lSDL2" "" SDL2_LIBRARIES "${SDL2_LIBRARIES}")

include_directories(${SDL2_INCLUDE_DIRS})

set(SDL2_LINK_LIBRARIES
  ${SDL2_LIBRARIES}
  ${SDL2_LIBDIR}/libSDL2.a
  ${SDL2_LIBDIR}/libSDL2main.a
  ${SDL2_LIBDIR}/libSDL2_image.a
  ${SDL2_LIBDIR}/libSDL2_mixer.a
  -lmodplug -ltiff -lpng -ljpeg -logg -lvorbis -lvorbisfile -lwebp)
