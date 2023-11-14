# include_directories('/usr/include/')
incdir = include_directories('imgui/', '.', 'imgui/backends')

libsPath = '/usr/lib/x86_64-linux-gnu/'
compiler = meson.get_compiler('cpp')
glutDep = compiler.find_library('glut', dirs: libsPath)
freeimageDep = compiler.find_library('freeimage', dirs: libsPath)

deps = [dependency('GL'), dependency('glu'), glutDep, freeimageDep, dependency('glfw3'), dependency('glew')]
# deps = [dependency('gtkmm-4.0'), dependency('glu'), glutDep, freeimageDep, dependency('glfw3'), dependency('glew')]
# srcs = ['main.cpp', 'functions.cpp', 'shapes.cpp', 'Window.cpp']
srcs = [
        'main.cpp',
        'shapes.cpp',
        'Window.cpp',
        'Window.h',
        'shapes.h',
        'variables.h',
        'functions.h',
        'functions.cpp',
        'paint_area.h',

        # OpenGL
        # 'opengl/indexBuffer.h',
        # 'opengl/renderer.h',
        # 'opengl/shader.h',
        # 'opengl/vertexArray.h',
        # 'opengl/vertexBuffer.h',
        # 'opengl/vertexBufferLayout.h',
        # 'opengl/helpers.h',
        'opengl/indexBuffer.cpp',
        'opengl/renderer.cpp',
        'opengl/shader.cpp',
        'opengl/vertexArray.cpp',
        'opengl/vertexBuffer.cpp',
        'opengl/helpers.cpp',

        # IMGUI
        'imgui/imgui.cpp',
        'imgui/imgui.h',
        'imgui/imgui_demo.cpp',
        'imgui/imgui_draw.cpp',
        'imgui/imgui_tables.cpp',
        'imgui/imgui_widgets.cpp',
        'imgui/imconfig.h',
        'imgui/imgui_internal.h',
        'imgui/imstb_rectpack.h',
        'imgui/imstb_textedit.h',
        'imgui/imstb_truetype.h',
        'imgui/backends/imgui_impl_glfw.cpp',
        'imgui/backends/imgui_impl_glfw.h',
        'imgui/backends/imgui_impl_opengl3.cpp',
        'imgui/backends/imgui_impl_opengl3.h',
        'imgui/misc/cpp/imgui_stdlib.cpp',
        'imgui/misc/cpp/imgui_stdlib.h'
    ]
executable('glpaint', sources: srcs, include_directories : incdir, dependencies: deps, install: true, cpp_args: '-DGLEW_STATIC')
