/**
 * \file Group.h
 * \brief A group node to be used as root of a sub-tree of nodes (composite node).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef GROUP_H_
#define GROUP_H_

#include "Composite.h"

namespace scg {


/**
 * \brief A group node to be used as root of a sub-tree of nodes (composite node).
 *
 * Allowed core types: ColorCore, MaterialCore, ShaderCore, TextureCore.
 *
 * Note: When the node is rendered, its cores are procesed in the order they
 * have been added to the node.
 */
class Group: public Composite {

public:

  /**
   * Constructor.
   */
  Group();

  /**
   * Destructor.
   */
  virtual ~Group();

  /**
   * Create shared pointer.
   */
  static GroupSP create();

  /**
   * Add core to be applied to sub-tree.
   *
   * Note: When the node is rendered, its cores are processed in the order they
   * have been added to the node.
   *
   * Allowed core types: ColorCore, MaterialCore, ShaderCore, TextureCore.
   *
   * \return this pointer for method chaining
   */
  Group* addCore(CoreSP core);

  /**
   * Accept traverser (visitor pattern).
   */
  virtual void accept(Traverser* traverser);

  /**
   * Accept traverser after traversing sub-tree (visitor pattern).
   */
  virtual void acceptPost(Traverser* traverser);

  /**
   * Render group, i.e., process cores.
   */
  virtual void render(RenderState* renderState);

  /**
   * Render group after traversing sub-tree, i.e., post-process cores to restore
   * previous state.
   */
  virtual void renderPost(RenderState* renderState);

};


} /* namespace scg */

#endif /* GROUP_H_ */
