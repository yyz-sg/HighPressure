/*****************************************************
File Name	: Compressor.cpp

Author		: YYZ

Description	: Source file for compressor class. Compressing 
			  directory with input path, output file name 
			  and recursive compressing requirement.
******************************************************/
#include "Compressor.hpp"
#include "PathSystem.hpp"
#include "CompressImplementation.hpp"
#include <cstdio>
#include "ZipStruct.h"

Compressor::Compressor(std::string inputPath, std::string outputFileName, bool recursive)
{
	m_enErrorStatus = CompressorErrorStatus::NoError;
	m_strInputPath = "";
	m_strOutputFileName = "";
	m_boRecursive = false;
	if (PathSystem::GetInstance().CheckPath(inputPath) == PathType::Directory)
	{
		if (PathSystem::GetInstance().CheckFileName(outputFileName + ".zip"))
		{
			m_strInputPath = inputPath;
			m_strOutputFileName = outputFileName + ".zip";
			m_boRecursive = recursive;
		}
		else
		{
			m_enErrorStatus = CompressorErrorStatus::OutputFileNameNotValid;
		}
	}
	else
	{
		m_enErrorStatus = CompressorErrorStatus::InputFilePathError;
	}
}

const CompressorErrorStatus Compressor::Compress()
{
	static bool written = false;
	if (m_enErrorStatus == CompressorErrorStatus::NoError)
	{
		//first contains name to be stored in zip, second contains absolute path
		std::vector<std::pair<std::string, std::string>> fileList;
		PathSystem::GetInstance().GetListOfFilePaths(fileList, m_strInputPath, "", m_boRecursive);

		//Open zip file
		PathSystem::GetInstance().OpenZipFile(PathSystem::GetInstance().GetOutputFilePath(m_strInputPath, m_strOutputFileName));
		
		if (PathSystem::GetInstance().GetFileStreamOn())
		{
			for (auto& filePath : fileList)
			{
				//Creating of local file header
				LocalFileHeader zLHeader;
				zLHeader.genPurposeFlag = 0;
				zLHeader.compressionMethod = 0;
				zLHeader.uncompressedCRC32 = 0;
				zLHeader.compressedSize = 0;
				zLHeader.uncompressedSize = 0;
				zLHeader.fileNameLength = filePath.first.length();
				zLHeader.extraFieldLength = 0;
				zLHeader.fileName = filePath.first;
				tm ltm;
				PathSystem::GetInstance().GetLastWriteTime(&ltm, filePath.second);
				zLHeader.lastModTime = ltm.tm_hour << 11 | ltm.tm_min << 5 | (ltm.tm_sec / 2); // 5 bit sec (divide by 2), 6 bit min, 5 bit hour
				//zip date format is from 1980 but tm format is from 1900 so minus 80 but remain 0 if there is no date
				//5 bit day, 4 bit month, 7 bit year
				zLHeader.lastModDate = (ltm.tm_year < 80 ? 0 : ltm.tm_year - 80) << 9 | (ltm.tm_mon + 1) << 5 | ltm.tm_mday; 
				//Actual compressing of Data
				if (PathSystem::GetInstance().CheckPath(filePath.second) == PathType::Regular_File)
				{
					FILE* fileptr;
					fopen_s(&fileptr, filePath.second.c_str(), "rb");
					long filelen;
					if (fileptr != nullptr)
					{
						fseek(fileptr, 0, SEEK_END);
						filelen = ftell(fileptr);
						rewind(fileptr);

						char* buffer = (char*)malloc(filelen * sizeof(char));
						if (buffer != nullptr)
						{
							fread(buffer, filelen, 1, fileptr);
							std::vector<uint8_t> outBuffer;
							compress_buffer((void*)buffer, filelen, outBuffer);
							//Adding remaining data to local file header
							zLHeader.compressionMethod = DEFLATE_COMPRESSION_METHOD;
							zLHeader.compressedSize = sizeof(outBuffer);
							zLHeader.uncompressedSize = filelen;
							zLHeader.uncompressedCRC32 = 0; //TODO add CRC to file
							//Adding local file header then buffer to zip
							if (!PathSystem::GetInstance().WriteLocalFileHeader(&zLHeader, outBuffer))
							{
								m_enErrorStatus = CompressorErrorStatus::CompressionFailed;
								break;
							}
						}
						else
						{
							fclose(fileptr);
							m_enErrorStatus = CompressorErrorStatus::CompressionFailed;
							break;
						}
					}
					else
					{
						m_enErrorStatus = CompressorErrorStatus::CompressionFailed;
						break;
					}
				}
				else
				{
					//Directly write folder data to zip
					std::vector<uint8_t> emptyVec;
					if (!PathSystem::GetInstance().WriteLocalFileHeader(&zLHeader, emptyVec))
					{
						m_enErrorStatus = CompressorErrorStatus::CompressionFailed;
						break;
					}	
				}

			}

			//TODO : Add central directory file header & End of central directory file header
		}
		else
		{
			m_enErrorStatus = CompressorErrorStatus::CompressionFailed;
		}
	}
	return m_enErrorStatus;
}