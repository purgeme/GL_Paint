include_directories('/usr/include/')

libsPath = '/usr/lib/x86_64-linux-gnu/'
compiler = meson.get_compiler('cpp')

# deps = [dependency('GL'), dependency('glfw3'), dependency('glew')]
deps = [dependency('glfw3'), dependency('glew')]
srcs = ['main.cpp', 'indexBuffer.cpp', 'vertexBuffer.cpp', 'renderer.cpp', 'vertexArray.cpp', 'shader.cpp']

executable('opengl', sources: srcs, dependencies: deps, install: true, cpp_args : '-DGLEW_STATIC')
