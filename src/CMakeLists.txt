IF ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  message("TRACE on")
  add_definitions(-DWITH_TRACE)
ELSE ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  message("TRACE off")
ENDIF ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")

ADD_SUBDIRECTORY(apps)
ADD_SUBDIRECTORY(paradevs)
