/*****************************************************
File Name	: CompressorImplementation.hpp

Author		: YYZ

Description	: Header file for actual compressing implementation
			  that deals with zlib interface.
******************************************************/

#ifndef COMPRESSOR_IMPLEMENTATION_HPP
#define COMPRESSOR_IMPLEMENTATION_HPP

#include <string>

#include "zlib.h"
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

void compress_buffer(void* in_buffer, size_t in_buffer_size, std::vector<uint8_t>& outData);

#ifdef __cplusplus
}
#endif

#endif