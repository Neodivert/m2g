set( SAMPLES_SOURCE_DIR "${PROJECT_SOURCE_DIR}/../src/samples" )
set( LIBRARY_PATH ${PROJECT_SOURCE_DIR}/lib/libm2g.so )
include_directories( ${SAMPLES_SOURCE_DIR} )

function( create_sample executable sources )
	add_executable( ${executable} ${sources} )
	add_dependencies( ${executable} ${LIBRARY_NAME} )
	target_link_libraries( ${executable} ${LIBRARY_PATH};${LIBRARIES} )
endfunction()

add_subdirectory( text_area )

# TODO: Install samples (where?).
