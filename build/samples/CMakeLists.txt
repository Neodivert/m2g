set( SAMPLES_SOURCE_DIR "${PROJECT_SOURCE_DIR}/../src/samples" )
include_directories( ${SAMPLES_SOURCE_DIR} )

# Text area sample
add_executable(
    "text_area_sample"
    "${SAMPLES_SOURCE_DIR}/text/text_area_sample.cpp"
)
target_link_libraries(
    "text_area_sample"
    "${PROJECT_SOURCE_DIR}/lib/libm2g.so;${LIBRARIES}"
)
