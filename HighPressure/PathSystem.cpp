/*****************************************************
File Name	: PathSystem.cpp

Author		: YYZ

Description	: Source file for path system object.
			  Check path existance and return if path
			  is directory, regular file or others
******************************************************/

#include "PathSystem.hpp"
#include <boost/filesystem.hpp>


PathType PathSystem::CheckPath(std::string Path)
{
	fs::path p(Path);
	PathType returnType = PathType::Not_Path;
	if (fs::exists(p))
	{
		if (fs::is_directory(p))
		{
			returnType = PathType::Directory;
		}
		else if (fs::is_regular_file(p))
		{
			returnType = PathType::Regular_File;
		}
		else
		{
			returnType = PathType::Others;
		}
	}
	return returnType;
}

fs::directory_iterator PathSystem::GetDirectoryIterator(std::string Path)
{
	fs::directory_iterator it{};
	if (CheckPath(Path) == PathType::Directory)
	{
		fs::path p(Path);
		it->assign(p);
	}
	return it;
}