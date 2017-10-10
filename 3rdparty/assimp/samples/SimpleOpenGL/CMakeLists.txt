FIND_PACKAGE(OpenGL)
FIND_PACKAGE(GLUT)
IF ( MSVC )
  SET(M_LIB)
ELSE ( MSVC )
  find_library(M_LIB m)
ENDIF ( MSVC )

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
)

LINK_DIRECTORIES(
  ${Assimp_BINARY_DIR}
  ${Assimp_BINARY_DIR}/lib
)

ADD_EXECUTABLE( assimp_simpleogl
  Sample_SimpleOpenGL.c
)

SET_PROPERTY(TARGET assimp_simpleogl PROPERTY DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

TARGET_LINK_LIBRARIES( assimp_simpleogl assimp ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${M_LIB} )
SET_TARGET_PROPERTIES( assimp_simpleogl PROPERTIES
  OUTPUT_NAME assimp_simpleogl
)

INSTALL( TARGETS assimp_simpleogl
  DESTINATION "${ASSIMP_BIN_INSTALL_DIR}" COMPONENT assimp-dev
)
