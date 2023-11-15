# Not windows paint

This is not windows paint.

## Usage:

The paint color is displayed in the top left corner and can be changed from there.

Multiple brush shapes are accessible from the left side menu.

The brushes can also be made hollow and the size can be changed from the same menu.

## Development:

### Dependencies:

- Clang compiler ( A specific bug in gcc causes issues )
- GLFW3 ( OpenGL library)
- GLEW ( Required for OpenGL)
- ImGui ( UI library )
- FreeImage ( Required for saving the image )
- Meson ( For building )

### Compiling:

#### Linux:

First get the repository, either download it as zip from github and extract it or git clone it:

``` sh
git clone https://github.com/Purgeme/GL_Paint 
```

Then go to the project directory and compile it with g++:

``` sh
CC=clang CXX=clang++ meson setup builddir
```

The compiled binary is in `builddir/src/glpaint`

#### Windows:

( Well, you are kind of on your own here (for now ))

Open the project in Visual Studio or your preferred program, make sure you add the dependecies in the program and compile.