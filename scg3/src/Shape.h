/**
 * \file Shape.h
 * \brief A shape node that contains geometry to be rendered (leaf node).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "Leaf.h"
#include "scg_internals.h"

namespace scg {


/**
 * \brief A shape node that contains geometry to be rendered (leaf node).
 *
 * Allowed core types: ColorCore, GeometryCore, MaterialCore, ShaderCore, TextureCore.
 *
 * Note: When the node is rendered, its cores are procesed in the order they
 * have been added to the node.
 */
class Shape: public Leaf {

public:

  /**
   * Constructor.
   */
  Shape();

  /**
   * Constructor with GeometryCore.
   */
  Shape(GeometryCoreSP geometryCore);

  /**
   * Destructor.
   */
  virtual ~Shape();

  /**
   * Create shared pointer.
   */
  static ShapeSP create();

  /**
   * Create shared pointer with GeometryCore.
   */
  static ShapeSP create(GeometryCoreSP geometryCore);

  /**
   * Add core to be applied to sub-tree.
   *
   * Note: When the node is rendered, its cores are processed in the order they
   * have been added to the node.
   *
   * Allowed core types: ColorCore, GeometryCore, MaterialCore, ShaderCore, TextureCore.
   *
   * \return this pointer for method chaining
   */
  Shape* addCore(CoreSP core);

  /**
   * Add texture to be applied to following geometry cores.
   */
  void addTextureCore(Texture2DCoreSP core);

  /**
   * Get approximate number of triangles, called by InfoTraverser::visitShape().
   */
  int getNTriangles() const;

  /**
   * Accept traverser (visitor pattern).
   */
  virtual void accept(Traverser* traverser);

  /**
   * Render shape, i.e., process cores.
   */
  virtual void render(RenderState* renderState);

};


} /* namespace scg */

#endif /* SHAPE_H_ */
