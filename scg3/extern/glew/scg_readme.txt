GLEW 2.1.0
==========
See full resource at http://glew.sourceforge.net/

Modifications by Volker Ahlers <VA>:

- include only directory include and file src/glew.c in scg3
- define macro GLEW_STATIC to link as static library in glew.c:35 (necessary for Windows only)
- include local GLEW header files in glxew.h:103 and glew.c:41/52/64/68
