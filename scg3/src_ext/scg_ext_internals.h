/**
 * \file scg_ext_internals.h
 * \brief Internal definitions required by most classes.
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
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
