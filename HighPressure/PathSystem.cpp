/*****************************************************
File Name	: PathSystem.cpp

Author		: YYZ

Description	: Source file for path system object.
			  Check path existance and return if path
			  is directory, regular file or others.
			  Get list of files in directory that are
			  regular files.
******************************************************/

#include "PathSystem.hpp"
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

namespace fs = boost::filesystem;

PathSystem::~PathSystem()
{
	//Close the file during deconstructor ie save zip file
	if (m_ofsFileStream.is_open())
	{
		m_ofsFileStream.close();
	}
}

PathType PathSystem::CheckPath(std::string path)
{
	fs::path p(path);
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

bool PathSystem::CheckFileName(std::string fileName)
{
	return fs::portable_name(fileName);
}

std::string PathSystem::GetParentFolderPath(std::string path)
{
	fs::path p(path);
	if (fs::exists(p))
		return p.parent_path().string();
	else
		return std::string();
}

std::string PathSystem::GetOutputFilePath(std::string inputPath, std::string outputFileName)
{
	fs::path parent(GetParentFolderPath(inputPath));
	fs::path output(outputFileName);
	return (parent / output).string();
}

void PathSystem::GetListOfFilePaths(std::vector<std::pair<std::string, std::string>>& filePathList, std::string folder, std::string mainPath, bool recursive)
{
	fs::path p(folder);
	if (fs::exists(p))
	{
		if (fs::is_directory(p))
		{
			std::string newMainPath = "";
			if (mainPath != "")
			{
				newMainPath = fs::path(mainPath).string() +  p.leaf().string() + "\\";
			}
			else
			{
				newMainPath = p.leaf().string() + "\\";
			}
			filePathList.push_back(std::pair<std::string,std::string>(newMainPath, folder));
			for (auto& entry : boost::make_iterator_range(fs::directory_iterator(p), {}))
			{
				if (fs::is_directory(entry.path()) && recursive)
				{
					GetListOfFilePaths(filePathList, entry.path().string(), newMainPath, recursive);
				}
				else if (fs::is_regular_file(entry.path()))
				{
					std::string entryPath = fs::path(newMainPath).string() + entry.path().filename().string();
					filePathList.push_back(std::pair<std::string, std::string>(entryPath, entry.path().string()));
				}
			}
		}
	}
}

bool PathSystem::OpenZipFile(std::string outputFilePath)
{
	//Remove file if exist
	if(fs::exists(fs::path(outputFilePath)))
	{
		fs::remove(fs::path(outputFilePath));
	}
	m_ofsFileStream.open(outputFilePath, std::ios::binary);
	if (!m_ofsFileStream.fail())
	{
		m_boIsFileStreamOn = true;
		return true;
	}
	return false;
}

bool PathSystem::writeContent(uint16_t& content)
{
	try
	{
		char* b = (char*)&content;
		m_ofsFileStream.write(b, 2);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool PathSystem::writeContent(uint32_t& content)
{
	try
	{
		char* b = (char*)&content;
		m_ofsFileStream.write(b, 4);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool PathSystem::writeContent(const char* content, uint16_t& length)
{
	try
	{
		m_ofsFileStream.write(content, length);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool PathSystem::WriteLocalFileHeader(LocalFileHeader* localFileHeader, std::vector<uint8_t>& buffer)
{
	bool ret = true;
	try
	{
		ret = writeContent(localFileHeader->localHeaderSignature);
		ret = writeContent(localFileHeader->minVersion);
		ret = writeContent(localFileHeader->genPurposeFlag);
		ret = writeContent(localFileHeader->compressionMethod);
		ret = writeContent(localFileHeader->lastModTime);
		ret = writeContent(localFileHeader->lastModDate);
		ret = writeContent(localFileHeader->uncompressedCRC32);
		ret = writeContent(localFileHeader->compressedSize);
		ret = writeContent(localFileHeader->uncompressedSize);
		ret = writeContent(localFileHeader->fileNameLength);
		ret = writeContent(localFileHeader->extraFieldLength);
		ret = writeContent(localFileHeader->fileName, localFileHeader->fileNameLength);
		//only write buffer in if its not empty, i.e. regular file
		if (!buffer.empty())
		{
			char* streamPtr = (char*)&buffer[0];
			m_ofsFileStream.write(streamPtr, sizeof(buffer));
		}
	}
	catch (...)
	{
		ret = false;
	}
	return ret;
}

void PathSystem::GetLastWriteTime(tm* ltm, std::string path)
{
	fs::path p(path);
	std::time_t pathModTime = fs::last_write_time(p);
	localtime_s(ltm, &pathModTime);
}