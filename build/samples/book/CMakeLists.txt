set( SAMPLES_SOURCE_DIR "${PROJECT_SOURCE_DIR}/../src/samples" )
include_directories( ${SAMPLES_SOURCE_DIR} )

# Text area sample
add_executable(
    "book"
    "${SAMPLES_SOURCE_DIR}/book/book.cpp"
)
target_link_libraries(
    "book"
    "${PROJECT_SOURCE_DIR}/lib/libm2g.so;${LIBRARIES}"
)
