/**
 * \file Shape.cpp
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
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
