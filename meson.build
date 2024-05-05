project('gltest', 'c')
glfw_deps = [dependency('glfw3'), dependency('glx')]

 # in case of a port to another os this should be changed:
x11_deps = [dependency('X11'), dependency('libpsx'), dependency('xrandr'), dependency('xi'), dependency('dl')]

incdir = include_directories('include')

src = ['glad.c', 'gl_basics.c', 'shaders.c', 'geometry.c', 'main.c']

executable('gltest', src, dependencies: [glfw_deps, x11_deps], include_directories : incdir )
