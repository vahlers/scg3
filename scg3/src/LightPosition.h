/**
 * \file LightPosition.h
 * \brief A light position node to define the position of an associated light
 *    within the scene graph (leaf node).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef LIGHTPOSITION_H_
#define LIGHTPOSITION_H_


#include "Leaf.h"
#include "scg_internals.h"

namespace scg {


/**
 * \brief A light position node to define the position of an associated light
 *    within the scene graph (leaf node).
 *
 * Light defines the logical position of a light source (i.e., which sub-tree
 * of the scene graph the light is applied to), while LightPosition defines its
 * physical position within the transformation hierarchy.
 */
class LightPosition: public Leaf {

public:

  /**
   * Constructor with associated Light.
   */
  LightPosition(LightSP light);

  /**
   * Destructor.
   */
  virtual ~LightPosition();

  /**
   * Create shared pointer.
   */
  static LightPositionSP create(LightSP light);

  /**
   * Get associated Light.
   */
  LightSP getLight();

  /**
   * Set associated Light.
   * \return this pointer for method chaining
   */
  LightPosition* setLight(LightSP light);

  /**
   * Accept traverser (visitor pattern).
   */
  void accept(Traverser* traverser);

protected:

  LightSP light_;

};


} /* namespace scg */

#endif /* LIGHTPOSITION_H_ */
