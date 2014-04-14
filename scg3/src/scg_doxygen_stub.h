/**
 * \file scg_doxygen_stub.h
 * \brief C++11 class definition stubs required by doxygen.
 * This header file is not included by any library file.
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

#ifndef SCG_DOXYGEN_STUB_H_
#define SCG_DOXYGEN_STUB_H_

namespace scg {


/**
 * \brief C++11 smart pointer class definition stubs required by doxygen to generate
 * correct collaboration diagrams; not to be used by the library.
 */
#define SCG_DOXYGEN_STUB(TypeName) \
    /** doxygen stub for std::shared_ptr<TypeName> */ \
    typedef TypeName##* TypeName##SP; \
    /** doxygen stub for std::unique_ptr<TypeName> */ \
    typedef TypeName##* TypeName##UP;

SCG_DOXYGEN_STUB(Animation);
SCG_DOXYGEN_STUB(BumpMapCore);
SCG_DOXYGEN_STUB(Camera);
SCG_DOXYGEN_STUB(CameraController);
SCG_DOXYGEN_STUB(ColorCore);
SCG_DOXYGEN_STUB(Composite);
SCG_DOXYGEN_STUB(Controller);
SCG_DOXYGEN_STUB(Core);
SCG_DOXYGEN_STUB(GeometryCore);
SCG_DOXYGEN_STUB(GeometryCoreFactory);
SCG_DOXYGEN_STUB(Group);
SCG_DOXYGEN_STUB(InfoTraverser);
SCG_DOXYGEN_STUB(KeyboardController);
SCG_DOXYGEN_STUB(Leaf);
SCG_DOXYGEN_STUB(Light);
SCG_DOXYGEN_STUB(LightPosition);
SCG_DOXYGEN_STUB(MaterialCore);
SCG_DOXYGEN_STUB(MouseController);
SCG_DOXYGEN_STUB(Node);
SCG_DOXYGEN_STUB(OrthographicCamera);
SCG_DOXYGEN_STUB(PerspectiveCamera);
SCG_DOXYGEN_STUB(PreTraverser);
SCG_DOXYGEN_STUB(Renderer);
SCG_DOXYGEN_STUB(RenderState);
SCG_DOXYGEN_STUB(RenderTraverser);
SCG_DOXYGEN_STUB(ShaderCore);
SCG_DOXYGEN_STUB(ShaderCoreFactory);
SCG_DOXYGEN_STUB(Shape);
SCG_DOXYGEN_STUB(StandardRenderer);
SCG_DOXYGEN_STUB(Texture2DCore);
SCG_DOXYGEN_STUB(TextureCore);
SCG_DOXYGEN_STUB(TextureCoreFactory);
SCG_DOXYGEN_STUB(TransformAnimation);
SCG_DOXYGEN_STUB(Transformation);
SCG_DOXYGEN_STUB(Traverser);
SCG_DOXYGEN_STUB(Viewer);
SCG_DOXYGEN_STUB(ViewState);


} // namespace scg

#endif /* SCG_DOXYGEN_STUB_H_ */
