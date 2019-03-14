# Set SOURCES variable
file(GLOB SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/extern/glew/src/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/extern/glm/glm/detail/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src_ext/*.cpp")

# Set HEADERS variable
file(GLOB HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/extern/glew/include/GL/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/extern/glm/glm/detail/*.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/extern/glm/glm/detail/*.inl"
	"${CMAKE_CURRENT_SOURCE_DIR}/extern/glm/glm/ext/*.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/extern/glm/glm/ext/*.inl"
	"${CMAKE_CURRENT_SOURCE_DIR}/extern/glm/glm/gtc/*.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/extern/glm/glm/gtc/*.inl"
	"${CMAKE_CURRENT_SOURCE_DIR}/extern/glm/glm/gtx/*.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/extern/glm/glm/gtx/*.inl"
	"${CMAKE_CURRENT_SOURCE_DIR}/extern/glm/glm/simd/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/extern/glm/glm/*.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/extern/stb_image/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src_ext/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.h")

include(${CMAKE_SOURCE_DIR}/cmake/LibraryConfig.cmake)
