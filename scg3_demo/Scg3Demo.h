/**
 * \file Scg3Demo.h
 * \brief A simple scg3 test application.
 *
 * Requires C++11 and OpenGL 3.2 (or later versions).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#ifndef SCG3_DEMO_H_
#define SCG3_DEMO_H_

#include <scg3.h>
#include <scg3_ext.h>

#ifndef SCG_CPP11_INITIALIZER_LISTS
//#error C++11 inititalizer lists (GCC 4.6 or higher) are required; see workaround in scg3_example.
#endif


/**
 * \brief scg3 test class.
 *
 * Note: Set configuration parameters in Scg3Test.cpp, struct SCGConfiguration.
 */
class Scg3Demo {

public:

  Scg3Demo();

  virtual ~Scg3Demo();

  void run();

protected:

  void createRGBScene_(scg::ViewerSP viewer, scg::CameraSP camera, scg::GroupSP& scene);

  void createLightedShape_(scg::ViewerSP viewer, scg::CameraSP camera, scg::GroupSP& scene);

  void createLightedScene_(scg::ViewerSP viewer, scg::CameraSP camera, scg::GroupSP& scene);

  void createTableScene_(scg::ViewerSP viewer, scg::CameraSP camera, scg::GroupSP& scene);

  void createTestScene_(scg::ViewerSP viewer, scg::CameraSP camera, scg::GroupSP& scene);

};


#endif /* SCG3_DEMO_H_ */
