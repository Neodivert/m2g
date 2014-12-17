TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../src/tests/main.cpp \
    ../src/drawables/tileset.cpp \
    ../src/drawables/sprite.cpp \
    ../src/drawables/drawable.cpp \
    ../src/drawables/animation.cpp \
    ../src/drawables/animation_data.cpp \
    ../src/text/text_renderer.cpp \
    ../src/text/bitmap_font.cpp \
    ../src/utilities/tilesets_buffer.cpp \
    ../src/graphics_library.cpp \
    ../src/dependencies/GL3W/gl3w.c \
    ../src/dependencies/msl/src/shader_loader.cpp \
    ../src/drawables/particles_systems/particle_systems_group.cpp \
    ../src/drawables/particles_systems/particle_system.cpp \
    ../src/dependencies/SDL_SavePNG/savepng.cpp \
    ../src/drawables/particles_systems/particles_set.cpp \
    ../src/drawables/particles_systems/ps_tileset_info.cpp

HEADERS += \
    ../src/dependencies/dependencies.hpp \
    ../src/drawables/tileset.hpp \
    ../src/drawables/sprite.hpp \
    ../src/drawables/drawable.hpp \
    ../src/drawables/animation.hpp \
    ../src/drawables/animation_data.hpp \
    ../src/text/text_renderer.hpp \
    ../src/text/bitmap_font.hpp \
    ../src/utilities/tilesets_buffer.hpp \
    ../src/graphics_library.hpp \
    ../src/dependencies/GL3W/gl3w.h \
    ../src/dependencies/GL3W/gl3.h \
    ../src/dependencies/msl/src/shader_loader.hpp \
    ../src/drawables/particles_systems/particle_systems_group.hpp \
    ../src/drawables/particles_systems/particle_system.hpp \
    ../src/dependencies/SDL_SavePNG/savepng.hpp \
    ../src/drawables/particles_systems/particles_set.hpp \
    ../src/drawables/particles_systems/ps_tileset_info.hpp

LIBS += -lGL -lGLU -lpng -lSDL2 -lSDL2_image -lSDL2_ttf `sdl-config --libs`

#LDFLAGS += `sdl-config --libs`

#QMAKE_CFLAGS += $$system(sdl-config --cflags)
#QMAKE_CXXFLAGS += $$system(sdl-config --cflags)

#CXXFLAGS += -Wall -Werrors -pedantic-errors

INCLUDEPATH += /usr/local/include/SDL2

#CFLAGS += -g `sdl-config --cflags`
#LDFLAGS += `sdl-config --libs` -lpng

# http://qt-project.org/forums/viewthread/19989
CONFIG += c++11
