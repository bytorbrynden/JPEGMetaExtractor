//
// JPEGMetaExtractor
// Include/ImageMetadata.h
//
#ifndef __JPEGMETAEXTRACTOR_IMAGEMETADATA_H__
#define __JPEGMETAEXTRACTOR_IMAGEMETADATA_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ExifTypes.h"

#define ATTRIBUTE_SPECIALTY_NORMAL 0x0
#define ATTRIBUTE_SPECIALTY_IFD_OFFSET 0x1

typedef struct metadataAttribute
{
    const char *pName;
    void *pValue;

    uint16_t tag;
    uint16_t type;
    uint16_t count;
    
    int specialty;
} MetadataAttribute;

struct metadataAttributesContainer;

typedef struct metadataAttributesContainer
{
    MetadataAttribute **ppAttributes;
    
    size_t attributesAllocated;
    
    void (*addAttribute)
    (
        struct metadataAttributesContainer *pSelf,
        const char *pAttributeName,
        uint16_t attributeTag,
        uint16_t attributeType,
        int attributeSpecialty
    );
    
    MetadataAttribute *(*getAttributeByTag)
    (
        struct metadataAttributesContainer *pSelf,
        uint16_t tag
    );
    
    MetadataAttribute *(*getAttributeByName)
    (
        struct metadataAttributesContainer *pSelf,
        const char *pAttributeName
    );
} MetadataAttributesContainer;

MetadataAttributesContainer *allocateMetadataAttributesContainer();

void deallocateMetadataAttributesContainer
(
    MetadataAttributesContainer *pContainer
);

MetadataAttribute *createAttribute
(
    const char *pAttributeName,
    uint16_t attributeTag,
    uint16_t attributeType,
    int attributeSpecialty
);

void addAttribute
(
    MetadataAttributesContainer *pSelf,
    const char *pAttributeName,
    uint16_t attributeTag,
    uint16_t attributeType,
    int attributeSpecialty
);

MetadataAttribute *getAttributeByTag
(
    MetadataAttributesContainer *pSelf,
    uint16_t tag
);

MetadataAttribute *getAttributeByName
(
    MetadataAttributesContainer *pSelf,
    const char *pAttributeName
);

#endif