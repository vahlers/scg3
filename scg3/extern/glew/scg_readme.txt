GLEW 1.10.0
===========
See full resource at http://glew.sourceforge.net/

Modifications by Volker Ahlers <VA>:

- include only directory include and file src/glew.c in scg3
- define macro GLEW_STATIC to link as static library in glew.c:34 (necessary for Windows only)
- include local GLEW header files in glxew.h:102 and glew.c:39/44/48
