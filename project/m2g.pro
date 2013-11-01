TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../src/tests/main.cpp \
    ../src/dependencies/tinyxml2/tinyxml2.cpp \
    ../src/drawables/tileset.cpp \
    ../src/drawables/sprite.cpp \
    ../src/drawables/drawable.cpp \
    ../src/drawables/animation.cpp \
    ../src/drawables/animation_data.cpp \
    ../src/drawables/particles_systems/particlesystem.cpp \
    ../src/drawables/particles_systems/particles_generation.cpp \
    ../src/text/text_renderer.cpp \
    ../src/text/bitmap_font.cpp \
    ../src/utilities/tilesets_buffer.cpp \
    ../src/graphics_library.cpp \
    ../src/dependencies/GL3W/gl3w.c \
    ../src/dependencies/msl/src/shader_loader.cpp

HEADERS += \
    ../src/dependencies/tinyxml2/tinyxml2.h \
    ../src/dependencies/dependencies.hpp \
    ../src/drawables/tileset.hpp \
    ../src/drawables/sprite.hpp \
    ../src/drawables/drawable.hpp \
    ../src/drawables/animation.hpp \
    ../src/drawables/animation_data.hpp \
    ../src/drawables/particles_systems/particlesystem.hpp \
    ../src/drawables/particles_systems/particles_generation.hpp \
    ../src/drawables/particles_systems/particle.hpp \
    ../src/text/text_renderer.hpp \
    ../src/text/bitmap_font.hpp \
    ../src/utilities/tilesets_buffer.hpp \
    ../src/graphics_library.hpp \
    ../src/dependencies/GL3W/gl3w.h \
    ../src/dependencies/GL3W/gl3.h \
    ../src/dependencies/msl/src/shader_loader.hpp

LIBS += -lGL -lGLU -lSDL2 -lSDL2_image -lSDL2_ttf

CXXFLAGS += -Wall -Werrors -pedantic-errors

# http://qt-project.org/forums/viewthread/19989
CONFIG += c++11
