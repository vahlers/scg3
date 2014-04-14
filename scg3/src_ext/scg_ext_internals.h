/**
 * \file scg_ext_internals.h
 * \brief Internal definitions required by most classes.
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


#ifndef SCG_EXT_INTERNALS_H_
#define SCG_EXT_INTERNALS_H_

#include "../src/scg_internals.h"

namespace scg {


/**
 * Forward declaration of classes with shared and unique pointers.\n
 *   Class\n
 *   ClassSP - shared_pointer<Class>\n
 *   classUP - unique_pointer<Class>
 */
SCG_DECLARE_CLASS(StereoCamera);
SCG_DECLARE_CLASS(StereoRenderer);
SCG_DECLARE_CLASS(StereoRendererActive);
SCG_DECLARE_CLASS(StereoRendererAnaglyph);
SCG_DECLARE_CLASS(StereoRendererPassive);


} /* namespace scg */


#endif /* SCG_EXT_INTERNALS_H_ */
