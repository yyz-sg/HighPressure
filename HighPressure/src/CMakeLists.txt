add_library(SCode 
    CommandLineParser.cpp
	CompressImplementation.cpp
	Compressor.cpp
    PathChecker.cpp
	PathSystem.cpp
)

FIND_PACKAGE(Boost 1.77.0 COMPONENTS program_options filesystem REQUIRED)
IF (Boost_FOUND)
	target_include_directories(SCode PUBLIC ${Boost_INCLUDE_DIR} )
	target_link_directories(SCode PRIVATE ${Boost_LIBRARIES})
	target_link_libraries(SCode PUBLIC ${Boost_LIBRARIES})
ELSE()
	message(STATUS "Unable to find boost package.\nPlease ensure that boost 1.77.0 or "
	"above is properly installed and installation path is included")
ENDIF()

#using zlib static link instead of dynamic. Program will not require zlib.dll to work.
set(_CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES})
set(CMAKE_FIND_LIBRARY_SUFFIXES "static.lib") 
find_package(ZLIB ${ZLIB_VERSION} REQUIRED MODULE) 
set(CMAKE_FIND_LIBRARY_SUFFIXES ${_CMAKE_FIND_LIBRARY_SUFFIXES}) 
unset(_CMAKE_FIND_LIBRARY_SUFFIXES) 
IF (ZLIB_FOUND)
	target_include_directories(SCode PUBLIC ${ZLIB_INCLUDE_DIRS} )
	target_link_directories(SCode PRIVATE ${ZLIB_LIBRARIES})
	target_link_libraries(SCode PUBLIC ${ZLIB_LIBRARIES})
ELSE()
	message(STATUS "Unable to find zlib.\n"
	"Please ensure that zlib is properly installed.\n"
	"This build is linking static zlib library.\n" 
	"Please ensure zlibstatic.lib is available in installation path.")
ENDIF()