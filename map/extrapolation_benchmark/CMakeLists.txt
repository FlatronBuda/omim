project(extrapolation_benchmark)

include_directories(
  ${OMIM_ROOT}/3party/gflags/src
  ${OMIM_ROOT}/3party/jansson/src
)

set(
  SRC
  extrapolation_benchmark.cpp
)

omim_add_executable(${PROJECT_NAME} ${SRC})

omim_link_libraries(
  ${PROJECT_NAME}
  map
  routing
  metrics
  platform
  geometry
  coding
  base
  stats_client
  gflags
  ${LIBZ}
)

link_qt5_core(${PROJECT_NAME})
