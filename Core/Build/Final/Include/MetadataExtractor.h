//
// JPEGMetaExtractor
// Include/MetadataExtractor.h
//
#ifndef __JPEGMETAEXTRACTOR_METADATAEXTRACTOR_H__
#define __JPEGMETAEXTRACTOR_METADATAEXTRACTOR_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ExtractorMacros.h"

#include "ExifTypes.h"
#include "ImageMetadata.h"

#define PAD_BYTE 0xFF
#define SOI_BYTE 0xD8
#define EOI_BYTE 0xD9
#define APP1_TAG 0xE1

#define BYTE_ORDER_INTEL    0
#define BYTE_ORDER_MOTOROLA 1

// Byte-Swap-for-16-bits reference: http://stackoverflow.com/a/2182184/6052290
LIB_EXPORT ExifShort getShort
(
    void *pShort,
    int fileByteOrder
);

// Byte-Swap-for-32-bits reference: http://stackoverflow.com/a/2182184/6052290
LIB_EXPORT ExifLong getLong
(
    void *pLong,
    int fileByteOrder
);

LIB_EXPORT int getTypeBytes
(
    int typeId
);

LIB_EXPORT MetadataAttributesContainer *extractMetadata
(
    MetadataAttributesContainer *pAttributesContainer,
    const char *pImageFilePath
);

LIB_EXPORT bool isValidEXIFFile
(
    FILE *pImageFile
);

LIB_EXPORT int32_t getFileByteOrder
(
    FILE *pImageFile
);

LIB_EXPORT char *getExifAttributeInfoSegment
(
    FILE *pImageFile,
    int32_t fileByteOrder
);

LIB_EXPORT void parseExifAttributeInfoSegment
(
    MetadataAttributesContainer *pAttributeContainer,
    char *pAttributeInfoSegment,
    int32_t fileByteOrder
);

LIB_EXPORT uint32_t getImageFileDirectoryLength
(
    char *pDirectory,
    int32_t fileByteOrder
);

LIB_EXPORT bool processImageFileDirectory
(
    MetadataAttributesContainer *pAttributesContainer,
    char *pDirectory,
    uint32_t offsetFromTIFF,
    int32_t fileByteOrder
);

LIB_EXPORT bool processAttribute
(
    MetadataAttributesContainer *pAttributesContainer,
    char *pIFD,
    char *pAttributeStart,
    uint32_t offsetFromTIFF,
    int32_t fileByteOrder
);

LIB_EXPORT void *getAttributeValue
(
    char *pValueStart,
    ExifShort valueBytes,
    ExifShort valueType,
    ExifLong valueCount,
    int32_t fileByteOrder
);

LIB_EXPORT void printAttribute
(
    MetadataAttribute *pAttribute
);

#endif