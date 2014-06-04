#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(EdGen)
set(useROOT true)        # use true or false
#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
#option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
#if(WITH_GEANT4_UIVIS)
#  find_package(Geant4 REQUIRED ui_all vis_all gdml)
#else()
#  find_package(Geant4 REQUIRED gdml)
#endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(FindROOT.cmake)
#include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR} ${ROOT_INCLUDE_DIR} /group/clas/builds/include/ )
set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR} /group/clas/builds/lib/ /usr/lib64/cernlib/2006/lib/
)

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
set(LINK_LIBRARIES
  ${ROOT_LIBRARIES} -lThread -lHtml -lGed -lEG -lGeom -lc_bos_io -lbankdefs -lbosio -lpacklib
)
target_link_libraries(EdGen ${LINK_LIBRARIES})


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output) 
#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS EdGen DESTINATION bin)


