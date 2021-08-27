#ifndef ZIP_STRUCT_H
#define ZIP_STRUCT_H

#include <string>
#include <vector>

#define MIN_ZIP_VERSION            (20)
#define DEFLATE_COMPRESSION_METHOD (8)

#ifndef VERSIONMADEBY
#define VERSIONMADEBY   (0x0) /* platform depedent */
#endif

const uint32_t localHeaderSingnature = 0x04034b50;
const uint32_t centralHeaderSignature = 0x02014b50;
const uint32_t endOfCentralRecordSignature = 0x504b0506;
const uint16_t minVersion = 20;
const uint16_t diskStart = 0;

typedef struct {
	uint16_t genPurposeFlag;
	uint16_t compressionMethod;
	uint16_t lastModTime;
	uint16_t lastModDate;
	uint32_t uncompressedCRC32;
	uint32_t compressedSize;
	uint32_t uncompressedSize;
	uint16_t fileNameLength;
	uint16_t extraFieldLength;
	uint16_t commentLength;
	uint16_t internalAttr;
	uint32_t externalAttr;
	uint32_t offsetOfLocalHeader;
	std::string fileName;
	std::string extraField;
	std::string fileComment;
}LocalFileHeader;

typedef struct {
	uint16_t totalEntries;
	std::vector<LocalFileHeader> entries;
	uint32_t centralDirectorySize;
	uint32_t cdOffset;
	uint16_t commentLength;
	std::string comment;
}EndOfCentralFileRecord;

#endif