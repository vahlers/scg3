/**
 * \file Core.h
 * \brief Base class for all cores (abstract).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef CORE_H_
#define CORE_H_

namespace scg {


class RenderState;

/**
 * \brief Base class for all cores (abstract).
 */
class Core {

public:

  /**
   * Constructor.
   */
  Core();

  /**
   * Destructor.
   */
  virtual ~Core() = 0;

  /**
   * Render core.
   */
  virtual void render(RenderState* renderState) = 0;

  /**
   * Render core after traversing sub-tree, e.g., to restore previous state.
   */
  virtual void renderPost(RenderState* renderState);

};


} /* namespace scg */

#endif /* CORE_H_ */
