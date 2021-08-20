/*****************************************************
File Name	: PathChecker.cpp

Author		: YYZ

Description	: Source file for path checking object.
			  Check path existance and return if path
			  is directory, regular file or others
******************************************************/

#include "PathChecker.hpp"
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

PathType PathChecker::CheckPath(std::string Path)
{
	fs::path p(Path);
	PathType returnType = Not_Path;
	if (fs::exists(p))
	{
		if (fs::is_directory(p))
		{
			returnType = Directory;
		}
		else if (fs::is_regular_file(p))
		{
			returnType = Regular_File;
		}
		else
		{
			returnType = Others;
		}
	}
	return returnType;
}