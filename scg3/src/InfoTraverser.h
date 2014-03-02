/**
 * \file InfoTraverser.h
 * \brief A traverser that gathers information about the scene graph (visitor pattern).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef INFOTRAVERSER_H_
#define INFOTRAVERSER_H_

#include "scg_internals.h"
#include "Traverser.h"

namespace scg {


/**
 * \brief A traverser that gathers information about the scene graph (visitor pattern).
 */
class InfoTraverser: public Traverser {

public:

  /**
   * Constructor.
   */
  InfoTraverser(RenderState* renderState);

  /**
   * Destructor.
   */
  virtual ~InfoTraverser();

  /**
   * Clear stored information.
   */
  void clear();

  /**
   * Get number of nodes of scene graph.
   */
  int getNNodes() const;

  /**
   * Get number of core pointers of scene graph.
   */
  int getNCores() const;

  /**
   * Get approximate number of triangles of scene graph.
   */
  int getNTriangles() const;

  // leaf nodes

  /**
   * Visit LightPosition node, update nNodes_ and nCores_.
   */
  virtual void visitLightPosition(LightPosition* node);

  /**
   * Visit Shape node, update nNodes_, nCores_, and nTriangles_.
   */
  virtual void visitShape(Shape* node);

  // composite nodes

  /**
   * Visit Camera node, update nNodes_ and nCores_.
   */
  virtual void visitCamera(Camera* node);

  /**
   * Visit Group node, update nNodes_ and nCores_.
   */
  virtual void visitGroup(Group* node);

  /**
   * Visit Light node, update nNodes_ and nCores_.
   */
  virtual void visitLight(Light* node);

  /**
   * Visit Transformation node, update nNodes_ and nCores_.
   */
  virtual void visitTransformation(Transformation* node);

protected:

  int nNodes_;
  int nCores_;
  int nTriangles_;

};


} /* namespace scg */

#endif /* INFOTRAVERSER_H_ */
