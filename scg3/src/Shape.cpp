/**
 * \file Shape.cpp
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

#include "GeometryCore.h"
#include "MaterialCore.h"
#include "ShaderCore.h"
#include "Shape.h"
#include "TextureCore.h"
#include "Traverser.h"

namespace scg {


Shape::Shape() {
}


Shape::Shape(GeometryCoreSP geometryCore) {
  addCore(geometryCore);
}


Shape::~Shape() {
}


ShapeSP Shape::create() {
  return std::make_shared<Shape>();
}


ShapeSP Shape::create(GeometryCoreSP geometryCore) {
  return std::make_shared<Shape>(geometryCore);
}


Shape* Shape::addCore(CoreSP core) {
  // Note: check here for disallowed core types (if any)
  cores_.push_back(core);
  return this;
}


int Shape::getNTriangles() const {
  int result = 0;
#ifdef CPP11_RANGE_BASED_FOR
  for (auto core : cores_) {
    auto geometryCore = std::dynamic_pointer_cast<GeometryCore>(core);
    if (geometryCore) {
      result += geometryCore->getNTriangles();
    }
  }
#else
 for (auto it = cores_.begin(); it < cores_.end(); ++it) {
   auto geometryCore = std::dynamic_pointer_cast<GeometryCore>(*it);
   if (geometryCore) {
     result += geometryCore->getNTriangles();
   }
 }
#endif
  return result;
}


void Shape::accept(Traverser* traverser) {
  traverser->visitShape(this);
}


void Shape::render(RenderState* renderState) {
  processCores_(renderState);

  // restore render state (material, texture, etc.)
  postProcessCores_(renderState);
}


} /* namespace scg */
