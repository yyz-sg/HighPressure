#ifndef ZIP_STRUCT_H
#define ZIP_STRUCT_H

#include <string>

#define LOCALHEADERSIGNATURE       (0x04034b50)
#define MIN_ZIP_VERSION            (20)
#define DEFLATE_COMPRESSION_METHOD (8)

#ifndef VERSIONMADEBY
#define VERSIONMADEBY   (0x0) /* platform depedent */
#endif

typedef struct {
	uint32_t localHeaderSignature;
	uint16_t minVersion;
	uint16_t genPurposeFlag;
	uint16_t compressionMethod;
	uint16_t lastModTime;
	uint16_t lastModDate;
	uint32_t uncompressedCRC32;
	uint32_t compressedSize;
	uint32_t uncompressedSize;
	uint16_t fileNameLength;
	uint16_t extraFieldLength;
	const char* fileName;
}LocalFileHeader;

typedef struct {

}CentralDirectoryFileHeader;

#endif