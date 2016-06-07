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

typedef struct metadataAttribute
{
    const char *pName;

    uint16_t tag;
    uint16_t type;
} MetadataAttribute;

struct metadataAttributesContainer;

typedef struct metadataAttributesContainer
{
    MetadataAttribute *pAttributes;
    
    size_t attributesAllocated;
    
    void (*addAttribute)
    (
        struct metadataAttributesContainer *pSelf,
        const char *pAttributeName,
        uint16_t attributeTag,
        uint16_t attributeType
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

MetadataAttribute createAttribute
(
    const char *pAttributeName,
    uint16_t attributeTag,
    uint16_t attributeType
);

void addAttribute
(
    MetadataAttributesContainer *pSelf,
    const char *pAttributeName,
    uint16_t attributeTag,
    uint16_t attributeType
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