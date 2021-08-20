/*****************************************************
File Name	: PathSystem.hpp

Author		: YYZ

Description	: Header file for path system object.
			  Check path existance and return if path 
			  is directory, regular file or others
******************************************************/

#ifndef PATH_SYSTEM_HPP
#define PATH_SYSTEM_HPP

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

enum class PathType
{
	Not_Path = 0,
	Directory = 1,
	Regular_File = 2,
	Others = 3
};

class PathSystem
{
public:
	PathType CheckPath(std::string Path);

	fs::directory_iterator GetDirectoryIterator(std::string Path);
};

#endif