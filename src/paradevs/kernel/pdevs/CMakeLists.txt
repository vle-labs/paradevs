INCLUDE_DIRECTORIES(
  ${PARADEVS_BINARY_DIR}/src
  ${PARADEVS_SOURCE_DIR}/src
  ${Boost_INCLUDE_DIRS}
  ${GLIBMM_INCLUDE_DIRS}
  ${LIBXML_INCLUDE_DIRS})

LINK_DIRECTORIES(
  ${GLIBMM_LIBRARY_DIRS}
  ${LIBXML_LIBRARY_DIR})

SET(PDEVS_HPP Coordinator.hpp Dynamics.hpp GraphManager.hpp Simulator.hpp)

INSTALL(FILES ${PDEVS_HPP} DESTINATION ${PARADEVS_INCLUDE_DIRS}/kernel/pdevs)

ADD_SUBDIRECTORY(multithreading)
ADD_SUBDIRECTORY(mpi)