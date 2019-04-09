add_executable (scg3_example
    main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/scg3)

target_link_libraries(scg3_example ${LIBRARY_NAME} ${LIBS})

install(TARGETS scg3_example
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)
