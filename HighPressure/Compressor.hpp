/*****************************************************
File Name	: Compressor.hpp

Author		: YYZ

Description	: Header file for compressor class. Actual
			  implementation of compressing directory
			  with input path, output file name and recursive
			  compressing requirement.
******************************************************/

#ifndef COMPRESSOR_HPP
#define COMPRESSOR_HPP

#include <string>

enum class CompressorErrorStatus
{
	NoError = 0,
	InputFilePathError = 1,
	OutputFileNameNotAvailable = 2,
	CompressionFailed = 3
};

class Compressor
{
	CompressorErrorStatus m_enErrorStatus;
public:
	Compressor(std::string inputPath, std::string outputFileName, bool recursive);

	const CompressorErrorStatus GetCompressStatus() { return m_enErrorStatus; }
};
#endif