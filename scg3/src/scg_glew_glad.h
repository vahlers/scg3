/**
 * \file scg_glew_glad.h
 * \brief Local header file for GLEW library.
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@hs-hannover.de
 */

/*
 * Copyright 2014 Volker Ahlers
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef SCG_GLEW_H_
#define SCG_GLEW_H_

// define macro to link as static library (necessary for Windows only)
#if defined(_WIN32) && !defined(GLEW_STATIC)
#define GLEW_STATIC
#endif

// experimental: use Glad instead of GLEW if macro SCG_GLAD_VERSION is defined
#define SCG_GLAD_VERSION "0.1.36"

#ifndef SCG_GLAD_VERSION
#include "../extern/glew/include/GL/glew.h"
#else
#include "../extern/glad/glad.h"
#endif

#endif /* SCG_GLEW_H_ */
