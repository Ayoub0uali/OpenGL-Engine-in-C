project('gltest', 'c')
glfw_deps = [dependency('glfw3'), dependency('glx')]
x11_deps = [dependency('X11'), dependency('libpsx'), dependency('xrandr'), dependency('xi'), dependency('dl')] # in case of a port to another os this should be chanded

src = ['glad.c', 'gl_basics.c', 'geometry.c', 'main.c']
executable('gltest', src, dependencies: [glfw_deps, x11_deps])
