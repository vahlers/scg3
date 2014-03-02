/**
 * \file Group.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include <cassert>
#include <memory>
#include <stdexcept>
#include "Group.h"
#include "MaterialCore.h"
#include "ShaderCore.h"
#include "TextureCore.h"
#include "Traverser.h"

namespace scg {


Group::Group() {
}


Group::~Group() {
}


GroupSP Group::create() {
  return std::make_shared<Group>();
}


Group* Group::addCore(CoreSP core) {
  // check for disallowed core types
  if (std::dynamic_pointer_cast<GeometryCoreSP>(core)) {
    throw std::runtime_error("Disallowed core type GeometryCore [Group::addCore()]");
  }
  cores_.push_back(core);
  return this;
}

void Group::accept(Traverser* traverser) {
  traverser->visitGroup(this);
}


void Group::acceptPost(Traverser* traverser) {
  traverser->visitPostGroup(this);
}


void Group::render(RenderState* renderState) {
  processCores_(renderState);
}


void Group::renderPost(RenderState* renderState) {
  postProcessCores_(renderState);
}


} /* namespace scg */
