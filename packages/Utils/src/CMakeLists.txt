
TRIBITS_CONFIGURE_FILE(${PACKAGE_NAME}_config.hpp)

SET(HEADERS "")
SET(SOURCES "")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

SET(HEADERS ${HEADERS}
  ${CMAKE_CURRENT_BINARY_DIR}/${PACKAGE_NAME}_config.hpp
  )

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

APPEND_SET(HEADERS
  DTK_ConfigDefs.hpp
  DTK_DBC.hpp
  DTK_KokkosHelpers.hpp
  DTK_SanitizerMacros.hpp
  )

APPEND_SET(SOURCES
  DTK_DBC.cpp
  )

TRIBITS_ADD_LIBRARY(
  dtk_utils
  HEADERS ${HEADERS}
  SOURCES ${SOURCES}
  )
