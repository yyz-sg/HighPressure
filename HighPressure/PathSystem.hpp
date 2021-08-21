/*****************************************************
File Name	: PathSystem.hpp

Author		: YYZ

Description	: Header file for path system object.
			  Check path existance and return if path 
			  is directory, regular file or others.
			  Get list of files in directory that are
			  regular files.
******************************************************/

#ifndef PATH_SYSTEM_HPP
#define PATH_SYSTEM_HPP

#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include "ZipStruct.h"

enum class PathType
{
	Not_Path = 0,
	Directory = 1,
	Regular_File = 2,
	Others = 3
};

class PathSystem
{
	std::ofstream m_ofsFileStream;
	bool m_boIsFileStreamOn;
private:
	PathSystem() { m_boIsFileStreamOn = false; }
	~PathSystem();
	PathSystem(PathSystem const&) = delete;
	void operator=(PathSystem const&) = delete;
	bool writeContent(uint16_t& content);
	bool writeContent(uint32_t& content);
	bool writeContent(const char* content, uint16_t& length);
public:
	static PathSystem& GetInstance()
	{
		static PathSystem instance;
		return instance;
	}
	const bool GetFileStreamOn() { return m_boIsFileStreamOn; }
	PathType CheckPath(std::string path);
	bool CheckFileName(std::string fileName);
	std::string GetParentFolderPath(std::string path);
	std::string GetOutputFilePath(std::string inputPath, std::string outputFileName);
	void GetListOfFilePaths(std::vector<std::pair<std::string, std::string>>& filePathList, std::string folder, std::string mainPath, bool recursive);
	bool OpenZipFile(std::string outputFilePath);
	bool WriteLocalFileHeader(LocalFileHeader* localFileHeader, std::vector<uint8_t>& buffer);
	void GetLastWriteTime(tm* ltm, std::string path);
};

#endif