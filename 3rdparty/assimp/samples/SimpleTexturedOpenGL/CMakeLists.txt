FIND_PACKAGE(OpenGL)
FIND_PACKAGE(GLUT)

IF ( NOT GLUT_FOUND )
  IF ( MSVC )
    SET ( GLUT_FOUND 1 )
    SET ( GLUT_INCLUDE_DIR ${Assimp_SOURCE_DIR}/samples/glut/ )
    SET ( GLUT_LIBRARIES ${Assimp_SOURCE_DIR}/samples/glut/glut32.lib )
  ELSE ( MSVC )
    MESSAGE( WARNING "Please install glut." )
  ENDIF ( MSVC )
ENDIF ( NOT GLUT_FOUND )

INCLUDE_DIRECTORIES(
  ${Assimp_SOURCE_DIR}/include
  ${Assimp_SOURCE_DIR}/code
  ${OPENGL_INCLUDE_DIR}
  ${GLUT_INCLUDE_DIR}
  ${Assimp_SOURCE_DIR}/samples/DevIL/include/
)

LINK_DIRECTORIES(
  ${Assimp_BINARY_DIR}
  ${Assimp_BINARY_DIR}/lib/
  ${Assimp_SOURCE_DIR}/samples/DevIL/lib/
)

ADD_EXECUTABLE( assimp_simpletexturedogl WIN32
  SimpleTexturedOpenGL/include/boost_includes.h
  SimpleTexturedOpenGL/src/model_loading.cpp
)

SET_PROPERTY(TARGET assimp_simpletexturedogl PROPERTY DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

TARGET_LINK_LIBRARIES( assimp_simpletexturedogl assimp ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} DevIL.lib )

SET_TARGET_PROPERTIES( assimp_simpletexturedogl PROPERTIES
  OUTPUT_NAME assimp_simpletexturedogl
)

INSTALL( TARGETS assimp_simpletexturedogl
  DESTINATION "${ASSIMP_BIN_INSTALL_DIR}" COMPONENT assimp-dev
)
