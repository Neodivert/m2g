set( SAMPLES_SOURCE_DIR "${PROJECT_SOURCE_DIR}/../src/samples" )
include_directories( ${SAMPLES_SOURCE_DIR} )

add_subdirectory( text_area )
add_subdirectory( book )

# TODO: Install samples (where?).
