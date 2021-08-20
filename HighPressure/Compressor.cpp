/*****************************************************
File Name	: Compressor.cpp

Author		: YYZ

Description	: Source file for compressor class. Actual
			  implementation of compressing directory
			  with input path, output file name and recursive
			  compressing requirement.
******************************************************/
#include "Compressor.hpp"
#include "PathChecker.hpp"

Compressor::Compressor(std::string inputPath, std::string outputFileName, bool recursive)
{
	m_enErrorStatus = CompressorErrorStatus::NoError;
	PathChecker pathCheck;
	if (pathCheck.CheckPath(inputPath) == PathType::Directory)
	{

	}
	else
	{
		m_enErrorStatus = CompressorErrorStatus::InputFilePathError;
	}
}