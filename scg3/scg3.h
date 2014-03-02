/**
 * \file scg3.h
 * \brief Main header file for scg3 scene graph library, including all class headers.
 *
 * Requires C++11 and OpenGL 3.2 (or later versions).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@hs-hannover.de
 */

#ifndef SCG3_H_
#define SCG3_H_

/**
 * \mainpage scg3: An OpenGL3/C++11 Scene Graph Library
 *
 * Version 0.4
 *
 * Prof. Dr. Volker Ahlers\n
 * Hochschule Hannover &ndash; University of Applied Sciences and Arts\n
 * Dept. of Computer Science\n
 * Hannover, Germany\n
 * volker.ahlers@hs-hannover.de
 *
 * &copy; 2006&ndash;2014 by Volker Ahlers
 *
 * \section sec_architecture Architecture
 *
 * This scene graph library is based on OpenGL 3.2/GLSL 1.5 %Core Profile and
 * C++11.
 * It is primarily intended for educational use in the master lecture
 * <em>Computer Graphics and Interaction</em> (CGI) and the accompanying exercises.
 *
 * Cf. CGI lecture notes, chapter 4 (Scene Graphs)
 *
 * The central classes are scg::Viewer, scg::Renderer, scg::Traverser, scg::Node, and scg::Core
 * as well as its sub-classes.
 * The rendering is controlled by Viewer::startMainLoop() and performed by Renderer::render(),
 * Node::render(), Core::render() as well as the render() methods of the appropriate sub-classes.
 *
 * The Names of vertex attributes and uniform variables are defined in the class
 * OGLConstants (file \link src/scg_internals.cpp\endlink ) and in the GLSL structs Light and
 * Material (file \link shaders/blinn_phong_lighting.glsl\endlink ).
 * They can also be found as in attributes and uniform variables in the supplied
 * shaders (folder shaders).
 *
 * \subsection sec_directory Directory structure
 *
 * - src: source code of scene graph base;
 *   all header files are included in \link scg3.h scg3.h\endlink
 * - src_ext: source code of scene graph extensions, e.g., for virtual reality applications;
 *   all header files are included in \link scg3_ext.h scg3_ext.h\endlink
 * - extern: source code of external libraries GLEW, GLM, and stb_image
 * - models: OBJ geometry models (scg3 has a very basic OBJ parser)
 * - shaders: GLSL shader code
 * - textures: JPEG, PNG, GIF, BMP texture images (plus a few other file formats supported by stb_image)
 *
 * Models, shaders, and textures are provided for test applications.
 * Real applications should use their own folders independent of the scg3 source directory.
 *
 * \section sec_usage Usage
 *
 * \subsection sec_installation Installation and Linking
 *
 * Cf. cgi_manual_opengl_eclipse.pdf (folder doc)
 *
 * Build of library scg3:
 * Project files for Eclipse (Linux and Windows/MinGW) and Visual Studio 10/2010 and 11/2012 (Windows) are provided.
 *
 * Build of application under Linux:
 *
 * \verbatim
   g++ -g -c -std=c++0x -I../scg3 my_prog.cpp
   g++ -L../scg3/Debug -o my_prog my_prog.o -lscg3 -lglfw3 -lGL -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lrt\endverbatim
 *
 * Build of application under Windows/MinGW:
 *
 * \verbatim
   g++ -g -c -std=c++0x -I../scg3 my_prog.cpp
   g++ -L../scg3/DebugWin -o my_prog.exe my_prog.o -lscg3 -lglfw3 -lopengl32 -lgdi32\endverbatim
 *
 * \subsection sec_example Example Application
 *
 * Cf. CGI lecture notes, chapter 4 (Scene Graphs)
 *
 * \include scg3_minimal_example.cpp
 *
 * See also the more advanced example \link scg3_table_scene_example.cpp scg3_table_scene_example.cpp\endlink
 * (folder doc) and the supplied shaders (folder shaders).
 *
 * \section sec_acknowledgements Acknowledgments
 *
 * This scene graph implementation utilizes ideas of Prof. Dr. Henrik Tramberend,
 * Prof. Dr. Frauke Sprengel, Jan Gericke, Bastian Hellmann, Benedikt K&ouml;hler,
 * and Alexander Schulz.
 *
 * It is further influenced by the open-source scene graph libraries
 * OpenSceneGraph and OpenSG.
 *
 * http://www.openscenegraph.org/
 *
 * http://www.opensg.org/
 *
 * The open-source libraries GLEW 1.10.0, GLFW 3.0.2, GLM 0.9.4.5, and stb_image 1.33 are used.
 * GLEW, GLM, and stb_image are included as source code in folder extern.
 * GLFW 3 has to be installed by the user (cf. http://www.glfw.org/).
 *
 * http://glew.sourceforge.net/
 *
 * http://www.glfw.org/
 *
 * http://glm.g-truc.net/
 *
 * http://nothings.org/stb_image.c
 *
 * \section sec_release_notes Release Notes
 *
 * Version 0.5 (March 2014)
 *
 * - rename vascg3 to scg3
 * - add OS X build configurations, support Clang compiler
 *
 * Version 0.4 (January 2014)
 *
 * - include GLEW 1.10.0 as source code
 * - fix bug in Camera::getViewDirection()
 *
 * Version 0.3 (October 2013):
 *
 * - introduced in CGI lecture of winter 2013/14
 * - remove dependency on GLU
 * - update to GLFW 3.0.2 and GLM 0.9.4.5
 * - remove GLEW and GLFW from source code, link as external libraries instead
 * - fix bug in ShaderCore::checkLinkError_()
 * - fix exception handling
 * - add Renderer::setGlobalAmbientLight(), Renderer::setLighting, and RenderState::setLighting()
 * - add GeometryCoreFactory::createTeapotFlat()
 *
 * Version 0.2 (February 2013):
 *
 * - introduced in ICG lecture of summer 2013
 * - integrate CameraTransformation into Camera, making CameraTransformation obsolete
 * - new, more intuitive and more exact camera control
 * - support method chaining for nodes, cores, and viewer
 * - new method Viewer::initSimpleRenderer() to reduce code for simple applications
 * - several other minor improvements
 * - update GLFW to 2.7.7
 * - update GLM to 0.9.4.2
 * - integrate GLEW 1.9.0 as source code
 *
 * Version 0.1 (October 2012):
 *
 * - introduced in SVR lecture of winter 2012/13
 * - scene graph extensions src_ext for stereo rendering
 * - several modifications to existing classes required for stereo rendering
 * - integrate GLFW as source code
 *
 * Version 0.0 (March 2012):
 *
 * - introduced in ICG lecture of summer 2012
 * - OpenGL 3 rewrite of library vascg2
 * - integrate GLFW as source code
 *
 */

/**
 * \example scg3_minimal_example.cpp
 * \example scg3_table_scene_example.cpp
 */

#include <src/scg_glew.h>
#include <GLFW/glfw3.h>

#include "src/Animation.h"
#include "src/BumpMapCore.h"
#include "src/Camera.h"
#include "src/CameraController.h"
#include "src/ColorCore.h"
#include "src/Composite.h"
#include "src/Controller.h"
#include "src/Core.h"
#include "src/CubeMapCore.h"
#include "src/GeometryCore.h"
#include "src/GeometryCoreFactory.h"
#include "src/Group.h"
#include "src/InfoTraverser.h"
#include "src/KeyboardController.h"
#include "src/Leaf.h"
#include "src/Light.h"
#include "src/LightPosition.h"
#include "src/MaterialCore.h"
#include "src/MouseController.h"
#include "src/Node.h"
#include "src/OrthographicCamera.h"
#include "src/PerspectiveCamera.h"
#include "src/PreTraverser.h"
#include "src/Renderer.h"
#include "src/RenderState.h"
#include "src/RenderTraverser.h"
#include "src/scg_glm.h"
#include "src/scg_internals.h"
#include "src/scg_stb_image.h"
#include "src/scg_utilities.h"
#include "src/ShaderCore.h"
#include "src/ShaderCoreFactory.h"
#include "src/Shape.h"
#include "src/StandardRenderer.h"
#include "src/Texture2DCore.h"
#include "src/TextureCore.h"
#include "src/TextureCoreFactory.h"
#include "src/TransformAnimation.h"
#include "src/Transformation.h"
#include "src/Traverser.h"
#include "src/Viewer.h"
#include "src/ViewState.h"

#endif /* SCG3_H_ */
