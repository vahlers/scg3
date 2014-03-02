/**
 * \file scg_glew.h
 * \brief Local header file for GLEW library.
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */


#ifndef SCG_GLEW_H_
#define SCG_GLEW_H_

// define macro to link as static library (necessary for Windows only)
#if defined(_WIN32) && !defined(GLEW_STATIC)
#define GLEW_STATIC
#endif

#include "../extern/glew/include/GL/glew.h"

#endif /* SCG_GLEW_H_ */
