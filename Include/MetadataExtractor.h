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

#include "ExifTypes.h"
#include "ImageMetadata.h"

#define PAD_BYTE 0xFF
#define SOI_BYTE 0xD8
#define EOI_BYTE 0xD9
#define APP1_TAG 0xE1

#define BYTE_ORDER_INTEL    0
#define BYTE_ORDER_MOTOROLA 1

// Byte-Swap-for-16-bits reference: http://stackoverflow.com/a/2182184/6052290
ExifShort getShort
(
    void *pShort,
    int fileByteOrder
);

// Byte-Swap-for-32-bits reference: http://stackoverflow.com/a/2182184/6052290
ExifLong getLong
(
    void *pLong,
    int fileByteOrder
);

int getTypeBytes
(
    int typeId
);

MetadataAttributesContainer *extractMetadata
(
    const char *pImageFilePath
);

bool isValidEXIFFile
(
    FILE *pImageFile
);

int32_t getFileByteOrder
(
    FILE *pImageFile
);

char *getExifAttributeInfoSegment
(
    FILE *pImageFile,
    int32_t fileByteOrder
);

void parseExifAttributeInfoSegment
(
    MetadataAttributesContainer *pAttributeContainer,
    char *pAttributeInfoSegment,
    int32_t fileByteOrder
);

// void readIFD
// (
//     MetadataAttributesContainer *pAttributeContainer,
//     char *pAPP1Segment,
//     ExifLong offset,
//     int32_t fileByteOrder
// );

bool processImageFileDirectory
(
    MetadataAttributesContainer *pAttributesContainer,
    char *pDirectory,
    uint32_t offsetFromTIFF,
    int32_t fileByteOrder
);

// bool processAttribute
// (
//     MetadataAttributesContainer *pAttributesContainer,
//     char *pAttributeInfoSegment,
//     void *pAttribute,
//     int32_t fileByteOrder
// );

bool processAttribute
(
    MetadataAttributesContainer *pAttributesContainer,
    char *pIFD,
    void *pAttributeStart,
    uint32_t offsetFromTIFF,
    int32_t fileByteOrder
);

void *getAttributeValue
(
    void *pValueStart,
    ExifShort valueBytes,
    ExifShort valueType,
    int32_t fileByteOrder
);

#endif