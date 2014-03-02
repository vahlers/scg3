/**
 * \file scg_glm.h
 * \brief Local header file for GLM OpenGL Mathematics library.
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */


#ifndef SCG_GLM_H_
#define SCG_GLM_H_


#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#elif defined(_MSC_VER)
#pragma warning(disable: 4996)
#endif

#ifdef GLM_MESSAGES
#undef GLM_MESSAGES
#endif

#include "../extern/glm/glm.hpp"
#include "../extern/glm/gtc/matrix_transform.hpp"
#include "../extern/glm/gtc/quaternion.hpp"
#include "../extern/glm/gtc/type_ptr.hpp"


#if defined(__GNUC__)
#pragma GCC diagnostic warning "-Wstrict-aliasing"
#elif defined(_MSC_VER)
#pragma warning(default: 4996)
#endif


#endif /* SCG_GLM_H_ */
