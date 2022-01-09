add_library(SCode 
    CommandLineParser.cpp 
    PathChecker.cpp
)

FIND_PACKAGE(Boost 1.77.0 COMPONENTS program_options filesystem REQUIRED)
IF (Boost_FOUND)
	target_include_directories(SCode PUBLIC ${Boost_INCLUDE_DIR} )
	target_link_directories(SCode PRIVATE ${Boost_LIBRARIES})
	target_link_libraries(SCode PUBLIC ${Boost_LIBRARIES})
ELSE()
	message(STATUS "Unable to find boost.\nPlease ensure that boost 1.77.0 or "
	"above is properly installed and installation path is included")
ENDIF()