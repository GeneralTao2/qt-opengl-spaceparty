TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -g3
QT += opengl

LIBS += -lopengl32

SOURCES += \
        main.cpp \
        settings/classes/objects/background.cpp \
        settings/classes/objects/body_part.cpp \
        settings/classes/objects/ground.cpp \
        settings/classes/objects/plain_map.cpp \
        settings/classes/objects/player.cpp \
        settings/classes/objects/rig.cpp \
        settings/classes/tools/game.cpp \
        settings/classes/tools/process_input.cpp \
        settings/classes/tools/rm_config.cpp \
        settings/libs/imgui-master/examples/imgui_impl_glfw.cpp \
        settings/libs/imgui-master/examples/imgui_impl_opengl3.cpp \
        settings/libs/imgui-master/imgui.cpp \
        settings/libs/imgui-master/imgui_demo.cpp \
        settings/libs/imgui-master/imgui_draw.cpp \
        settings/libs/imgui-master/imgui_widgets.cpp \
        settings/classes/objects/camera.cpp \
        settings/classes/objects/plain.cpp \
        settings/classes/objects/triangle.cpp \
        settings/classes/tools/decor.cpp \
        settings/classes/tools/framebuffer.cpp \
        settings/classes/tools/imgu_manager.cpp \
        settings/classes/tools/main_tool.cpp \
        settings/classes/tools/resource_manager.cpp \
        settings/classes/tools/shader.cpp \
        settings/classes/tools/shader_arg_structs.cpp \
        settings/classes/tools/shader_global_buffer.cpp \
        settings/classes/tools/stb_image.cpp \
        settings/classes/tools/text_renderer.cpp \
        settings/classes/tools/texture.cpp

win32: LIBS += -L$$PWD/../GLFW/lib-mingw/ -lglfw3

INCLUDEPATH += $$PWD/../GLFW/lib-mingw
DEPENDPATH += $$PWD/../GLFW/lib-mingw

win32: LIBS += -L$$PWD/../GLFW/lib-mingw/ -lglfw3dll

INCLUDEPATH += $$PWD/../GLFW/lib-mingw
DEPENDPATH += $$PWD/../GLFW/lib-mingw


INCLUDEPATH += $$PWD/../GLFW/include/GLFW/

win32: LIBS += -LE:/Programs/qt/Tools/mingw530_32/i686-w64-mingw32/lib/ -lgdi32

INCLUDEPATH += E:/Programs/qt/Tools/mingw530_32/i686-w64-mingw32/include
DEPENDPATH += E:/Programs/qt/Tools/mingw530_32/i686-w64-mingw32/include


win32: LIBS += -L$$PWD/../irrKlang-1.5.0/lib/Win32-gcc/ -lirrKlang

INCLUDEPATH += $$PWD/../irrKlang-1.5.0/lib/Win32-gcc
DEPENDPATH += $$PWD/../irrKlang-1.5.0/lib/Win32-gcc

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../irrKlang-1.5.0/lib/Win32-gcc/irrKlang.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../irrKlang-1.5.0/lib/Win32-gcc/libirrKlang.a

LIBS += -L$$PWD/../irrKlang-1.5.0/bin/win32-gcc/ -likpMP3
INCLUDEPATH += $$PWD/../irrKlang-1.5.0/include

LIBS += -L$$PWD/../irrKlang-1.5.0/bin/win32-gcc/ -lirrKlang
INCLUDEPATH += $$PWD/../irrKlang-1.5.0/include


win32: LIBS += -L$$PWD/../GnuWin32/lib/f/ -lfreetype

INCLUDEPATH += $$PWD/../GnuWin32/include
DEPENDPATH += $$PWD/../GnuWin32/include

INCLUDEPATH += $$PWD/settings/libs/imgui-master
INCLUDEPATH += $$PWD/settings/libs/imgui-master/examples

HEADERS += \
    ../GLFW/include/GLFW/glfw3.h \
    ../GLFW/include/GLFW/glfw3native.h \
    settings/classes/objects/background.h \
    settings/classes/objects/body_part.h \
    settings/classes/objects/ground.h \
    settings/classes/objects/plain_map.h \
    settings/classes/objects/player.h \
    settings/classes/objects/rig.h \
    settings/classes/tools/game.h \
    settings/classes/tools/process_input.h \
    settings/libs/imgui-master/examples/imgui_impl_glfw.h \
    settings/libs/imgui-master/examples/imgui_impl_opengl2.h \
    settings/libs/imgui-master/examples/imgui_impl_opengl3.h \
    settings/libs/imgui-master/imconfig.h \
    settings/libs/imgui-master/imgui.h \
    settings/libs/imgui-master/imgui_internal.h \
    settings/libs/imgui-master/imstb_rectpack.h \
    settings/libs/imgui-master/imstb_textedit.h \
    settings/libs/imgui-master/imstb_truetype.h \
    settings/classes/objects/camera.h \
    settings/classes/objects/plain.h \
    settings/classes/objects/triangle.h \
    settings/classes/tools/decor.h \
    settings/classes/tools/framebuffer.h \
    settings/classes/tools/imgu_manager.h \
    settings/classes/tools/main_tool.h \
    settings/classes/tools/resource_manager.h \
    settings/classes/tools/shader.h \
    settings/classes/tools/shader_arg_structs.h \
    settings/classes/tools/shader_global_buffer.h \
    settings/classes/tools/stb_image.h \
    settings/classes/tools/text_renderer.h \
    settings/classes/tools/texture.h
