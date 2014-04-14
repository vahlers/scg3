/**
 * \file Group.cpp
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
