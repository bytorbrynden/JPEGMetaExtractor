//
// JPEGMetaExtractor
// Source/ImageMetadata.c
//
#include "ImageMetadata.h"

MetadataAttributesContainer *allocateMetadataAttributesContainer()
{
    MetadataAttributesContainer *pContainer = (MetadataAttributesContainer *)
        malloc(sizeof(MetadataAttributesContainer));
    
    // Initialize members
    pContainer->ppAttributes         = (MetadataAttribute **) malloc(0x0);
    pContainer->attributesAllocated = 0x0;
    
    // Initialize function pointers
    pContainer->addAttribute       = addAttribute;
    pContainer->getAttributeByTag  = getAttributeByTag;
    pContainer->getAttributeByName = getAttributeByName;
    
    // Register IFD offset attributes
    pContainer->addAttribute(pContainer, "ExifIFDOffset", 0x8769, EXIF_LONG, ATTRIBUTE_SPECIALTY_IFD_OFFSET);
    pContainer->addAttribute(pContainer, "GPSIFDOffset",  0x8825, EXIF_LONG, ATTRIBUTE_SPECIALTY_IFD_OFFSET);
    
    return pContainer;
}

void deallocateMetadataAttributesContainer
(
    MetadataAttributesContainer *pContainer
)
{
    if (NULL == pContainer ||
        NULL == pContainer->ppAttributes)
        return;
    
    for (size_t attrIndex = 0; attrIndex < pContainer->attributesAllocated;
        ++attrIndex)
    {
        if (NULL != *(pContainer->ppAttributes + attrIndex))
        {
            int attributeType = (*(pContainer->ppAttributes + attrIndex))->type;
            
            if (EXIF_ASCII == attributeType && NULL !=
                (*(pContainer->ppAttributes + attrIndex))->pAsciiValues)
            {
                free((*(pContainer->ppAttributes + attrIndex))->pAsciiValues);
            }
            else if (EXIF_RATIONAL == attributeType && NULL !=
                (*(pContainer->ppAttributes + attrIndex))->pRationalValues)
            {
                free((*(pContainer->ppAttributes + attrIndex))->pRationalValues);
            }
            
            free(*(pContainer->ppAttributes + attrIndex));
        }
    }
    
    free(pContainer->ppAttributes);
    free(pContainer);
}

MetadataAttribute *createAttribute
(
    const char *pAttributeName,
    uint16_t attributeTag,
    uint16_t attributeType,
    int attributeSpecialty
)
{
    MetadataAttribute *pAttribute = (MetadataAttribute *) malloc(sizeof(
        MetadataAttribute));
    
    pAttribute->pName     = pAttributeName;
    pAttribute->tag       = attributeTag;
    pAttribute->type      = attributeType;
    pAttribute->count     = 0x0;
    pAttribute->specialty = attributeSpecialty;
    
    return pAttribute;
}

void addAttribute
(
    MetadataAttributesContainer *pSelf,
    const char *pAttributeName,
    uint16_t attributeTag,
    uint16_t attributeType,
    int attributeSpecialty
)
{
    MetadataAttribute *pNewAttribute = NULL;
    
    // If either of the following variables are non-existant (or NULL), we're
    //  not going to go any further.
    if (NULL == pSelf || NULL == pAttributeName)
        return;
    
    // By now, our attributes "array" should have been allocated. If it hasn't,
    //  we're just going to exit the function.
    if (NULL == pSelf->ppAttributes)
        return;
    
    pSelf->ppAttributes = (MetadataAttribute **) realloc(
        pSelf->ppAttributes,
        sizeof(MetadataAttribute *) * (pSelf->attributesAllocated + 1)
    );
    
    pNewAttribute = createAttribute(pAttributeName, attributeTag, attributeType,
        attributeSpecialty);
    
    if (NULL != pNewAttribute)
    {
        *(pSelf->ppAttributes + pSelf->attributesAllocated) = pNewAttribute;
    }
    
    // *(pSelf->ppAttributes + pSelf->attributesAllocated) = createAttribute(
    //     pAttributeName, attributeTag, attributeType, attributeSpecialty);
    
    // Increase the value of the variable that keeps track of how many attributes
    //  we've allocated space for.
    pSelf->attributesAllocated++;
}

MetadataAttribute *getAttributeByTag
(
    MetadataAttributesContainer *pSelf,
    uint16_t tag
)
{
    // If the pointer to the current "instance", is NULL, then we probably
    //  shouldn't go any further. So we won't.
    if (NULL == pSelf)
        return NULL;
    
    for (size_t i = 0; i < pSelf->attributesAllocated; ++i)
    {
        MetadataAttribute *pCurrentAttribute = *(pSelf->ppAttributes + i);
        
        if (tag == pCurrentAttribute->tag)
            return pCurrentAttribute;
    }
    
    return NULL;
}

MetadataAttribute *getAttributeByName
(
    MetadataAttributesContainer *pSelf,
    const char *pAttributeName
)
{
    // If the pointer to the current "instance", is NULL, then we probably
    //  shouldn't go any further. So we won't.
    if (NULL == pSelf)
        return NULL;
    
    for (size_t i = 0; i < pSelf->attributesAllocated; ++i)
    {
        MetadataAttribute *pCurrentAttribute = *(pSelf->ppAttributes + i);
        
        if (!strncmp(pCurrentAttribute->pName, pAttributeName, strlen(pAttributeName)))
            return pCurrentAttribute;
    }
    
    return NULL;
}