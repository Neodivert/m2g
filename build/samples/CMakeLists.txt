# Project files
#file( GLOB_RECURSE SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp" ) # TODO: Remove sample and test files.
#list( REMOVE_ITEM SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/tests/main.cpp" )

set( SAMPLES_SOURCE_DIR "${PROJECT_SOURCE_DIR}/../src/samples" )

set(
    SAMPLES_SOURCE_FILES
    ""
)
set(
    SAMPLES_HEADER_FILES
    ""
)

include_directories( ${SAMPLES_SOURCE_DIR} )
