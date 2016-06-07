//
// ExifExtractC
// Source/ImageMetadata.c
//
#include "ImageMetadata.h"

MetadataAttributesContainer *allocateMetadataAttributesContainer()
{
    MetadataAttributesContainer *pContainer = (MetadataAttributesContainer *)
        malloc(sizeof(MetadataAttributesContainer));
    
    // Initialize members
    pContainer->pAttributes         = (MetadataAttribute *) malloc(0x0);
    pContainer->attributesAllocated = 0x0;
    
    // Initialize function pointers
    pContainer->addAttribute       = addAttribute;
    pContainer->getAttributeByTag  = getAttributeByTag;
    pContainer->getAttributeByName = getAttributeByName;
    
    // Register attributes
    pContainer->addAttribute(pContainer, "Make",           0x010F, EXIF_ASCII);
    pContainer->addAttribute(pContainer, "Model",          0x0110, EXIF_ASCII);
    pContainer->addAttribute(pContainer, "XResolution",    0x011A, EXIF_RATIONAL);
    pContainer->addAttribute(pContainer, "YResolution",    0x011B, EXIF_RATIONAL);
    pContainer->addAttribute(pContainer, "ResolutionUnit", 0x0128, EXIF_SHORT);
    pContainer->addAttribute(pContainer, "Software",       0x0131, EXIF_ASCII);
    
    return pContainer;
}

void deallocateMetadataAttributesContainer
(
    MetadataAttributesContainer *pContainer
)
{
    if (NULL == pContainer ||
        NULL == pContainer->pAttributes)
        return;
    
    free(pContainer->pAttributes);
    free(pContainer);
}

MetadataAttribute createAttribute
(
    const char *pAttributeName,
    uint16_t attributeTag,
    uint16_t attributeType
)
{
    MetadataAttribute attribute;
    
    attribute.pName = pAttributeName;
    attribute.tag   = attributeTag;
    attribute.type  = attributeType;
    
    return attribute;
}

void addAttribute
(
    MetadataAttributesContainer *pSelf,
    const char *pAttributeName,
    uint16_t attributeTag,
    uint16_t attributeType
)
{
    // If either of the following variables are non-existant (or NULL), we're
    //  not going to go any further.
    if (NULL == pSelf || NULL == pAttributeName)
        return;
    
    // By now, our attributes "array" should have been allocated. If it hasn't,
    //  we're just going to exit the function.
    if (NULL == pSelf->pAttributes)
        return;
    
    pSelf->pAttributes = (MetadataAttribute *) realloc(
        pSelf->pAttributes,
        sizeof(MetadataAttribute) * (pSelf->attributesAllocated + 1)
    );
    
    *(pSelf->pAttributes + pSelf->attributesAllocated) = createAttribute(pAttributeName, attributeTag, attributeType);
    
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
        MetadataAttribute *pCurrentAttribute = &(*(pSelf->pAttributes + i));
        
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
        MetadataAttribute *pCurrentAttribute = &(*(pSelf->pAttributes + i));
        
        if (!strncmp(pCurrentAttribute->pName, pAttributeName, strlen(pAttributeName)))
            return pCurrentAttribute;
    }
    
    return NULL;
}