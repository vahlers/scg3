/**
 * \file Node.h
 * \brief Base class for all nodes (composite pattern, abstract).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <unordered_map>
#include <vector>
#include "scg_internals.h"

namespace scg {


/**
 * \brief Base class for all nodes (composite pattern, abstract).
 *
 * The node tree of the scene graph is organized as a left-child right-sibling tree.
 * While all nodes may have siblings and a parent, only composite nodes may have
 * children (cf. Composite).
 * Certain nodes may possess one or several cores (cf. Core).
 *
 * Note: When the node is rendered, its cores are procesed in the order they
 * have been added to the node.
 */
class Node {

  friend class Composite;

public:

  /**
   * Constructor.
   */
  Node();

  /**
   * Destructor.
   */
  virtual ~Node() = 0;

  /**
   * Clear node data.
   */
  virtual void clear();

  /**
   * Remove node from scene graph, clear node data.
   */
  virtual void destroy();

  /**
   * Get number of cores associated with this node.
   */
  int getNCores() const;

  /**
   * Get meta-information value for a given key.
   * \param key key to search for
   * \return value for the key or an empty string if there is no such key
   */
  const std::string& getMetaInfo(const std::string& key) const;

  /**
   * Set meta-information as key-value pair.
   * \param key key; if there is already a key with that name, the value is overwritten
   * \param value value for the key
   */
  void setMetaInfo(const std::string& key, const std::string& value);

  /**
   * Check if node is visible.
   */
  bool isVisible() const;

  /**
   * Set visibility of this node.
   */
  void setVisible(bool isVisible = true);

  /**
   * Traverse node tree (depth-first, pre-order) with given traverser.
   */
  virtual void traverse(Traverser* traverser) = 0;

  /**
   * Accept traverser (visitor pattern).
   */
  virtual void accept(Traverser* traverser);

  /**
   * Render node.
   */
  virtual void render(RenderState* renderState);

protected:

  /**
   * Add sibling to this node, i.e., child to its parent (recursively).
   * Called by Composite::addChild().
   */
  void addSibling_(NodeSP sibling);

  /**
   * Remove sibling from this node, i.e., child from its parent (recursively).
   * Called by Composite::removeChild().
   * \param node pointer to node to be removed
   * \param result true if node has been found and removed
   */
  void removeSibling_(Node* node, bool& result);

  /**
   * Process node cores by calling their render() methods,
   * accessing vector from first to last element.
   */
  void processCores_(RenderState* renderState);

  /**
   * Post-process node cores by calling their renderPost() methods,
   * accessing vector from last to first element.
   */
  void postProcessCores_(RenderState* renderState);

protected:

  NodeSP rightSibling_;
  Composite* parent_;
  std::vector<CoreSP> cores_;
  bool isVisible_;
  mutable std::unordered_map<std::string, std::string> metaInfo_;

};


} /* namespace scg */

#endif /* NODE_H_ */
