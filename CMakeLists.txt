#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(EdGen)
set(useROOT true)        # use true or false
include(FindROOT.cmake)

set(WITHBOS $ENV{CLAS6LIB})
if(WITHBOS)
	include_directories(${PROJECT_SOURCE_DIR} ${ROOT_INCLUDE_DIR} $ENV{CLAS6INC})
	set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR} $ENV{CLAS6LIB} $ENV{CERNLIB}
)
else()
	include_directories(${PROJECT_SOURCE_DIR} ${ROOT_INCLUDE_DIR} )
	set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
)
endif()

link_directories( ${LINK_DIRECTORIES})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cxx)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.h)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(EdGen ${sources} ${headers})
if(WITHBOS)
	set(LINK_LIBRARIES
  ${ROOT_LIBRARIES} -lThread -lHtml -lGed -lEG -lGeom -lc_bos_io -lbankdefs -lbosio -lpacklib
)
else()
	set(LINK_LIBRARIES
  ${ROOT_LIBRARIES} -lThread -lHtml -lGed -lEG -lGeom
)
endif()
target_link_libraries(EdGen ${LINK_LIBRARIES})


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output) 
#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS EdGen DESTINATION bin)


