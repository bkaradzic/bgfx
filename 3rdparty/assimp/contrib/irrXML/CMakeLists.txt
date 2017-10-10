set( IrrXML_SRCS
  CXMLReaderImpl.h
  heapsort.h
  irrArray.h
  irrString.h
  irrTypes.h
  irrXML.cpp
  irrXML.h
)

add_library(IrrXML STATIC ${IrrXML_SRCS})
set(IRRXML_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" CACHE INTERNAL "IrrXML_Include" )
set(IRRXML_LIBRARY "IrrXML" CACHE INTERNAL "IrrXML" )
