//
// JPEGMetaExtractor
// CLI/Source/ImageMetaExtractorCLI.c
//
#include "ImageMetaExtractorCLI.h"

int main(int argc, const char **argv)
{
    if (2 > argc)
    {
        printf("A minimum of 2 arguments is required!\n");
        return 1;
    }
    
    for (int argumentIndex = 1; argumentIndex < argc; ++argumentIndex)
    {
        const char *pCurrentArgument = *(argv + argumentIndex);
        MetadataAttributesContainer *pMetadataContainer =
            setupAttributesContainer();
        
        printf("Current file: \"%s\"\n", pCurrentArgument);
        
        pMetadataContainer = extractMetadata(pMetadataContainer,
            pCurrentArgument);
        
        if (NULL == pMetadataContainer)
            continue;
        
        for (int attributeIndex = 0; attributeIndex <
            pMetadataContainer->attributesAllocated; ++attributeIndex)
        {
            printAttribute(*(pMetadataContainer->ppAttributes + attributeIndex));
        }
        
        deallocateMetadataAttributesContainer(pMetadataContainer);
    }
    
    return 0;
}

MetadataAttributesContainer *setupAttributesContainer()
{
    MetadataAttributesContainer *pAttributesContainer =
        allocateMetadataAttributesContainer();
    
    pAttributesContainer->addAttribute(pAttributesContainer, "Make",             0x010F, EXIF_ASCII,    ATTRIBUTE_SPECIALTY_NORMAL);
    pAttributesContainer->addAttribute(pAttributesContainer, "Model",            0x0110, EXIF_ASCII,    ATTRIBUTE_SPECIALTY_NORMAL);
    pAttributesContainer->addAttribute(pAttributesContainer, "XResolution",      0x011A, EXIF_RATIONAL, ATTRIBUTE_SPECIALTY_NORMAL);
    pAttributesContainer->addAttribute(pAttributesContainer, "YResolution",      0x011B, EXIF_RATIONAL, ATTRIBUTE_SPECIALTY_NORMAL);
    pAttributesContainer->addAttribute(pAttributesContainer, "ResolutionUnit",   0x0128, EXIF_SHORT,    ATTRIBUTE_SPECIALTY_NORMAL);
    pAttributesContainer->addAttribute(pAttributesContainer, "Software",         0x0131, EXIF_ASCII,    ATTRIBUTE_SPECIALTY_NORMAL);
    pAttributesContainer->addAttribute(pAttributesContainer, "DateTimeOriginal", 0x9003, EXIF_ASCII,    ATTRIBUTE_SPECIALTY_NORMAL);
    pAttributesContainer->addAttribute(pAttributesContainer, "GPSVersionID",     0x0000, EXIF_BYTE,     ATTRIBUTE_SPECIALTY_NORMAL);
    pAttributesContainer->addAttribute(pAttributesContainer, "GPSLatitudeRef",   0x0001, EXIF_ASCII,    ATTRIBUTE_SPECIALTY_NORMAL);
    pAttributesContainer->addAttribute(pAttributesContainer, "GPSLatitude",      0x0002, EXIF_RATIONAL, ATTRIBUTE_SPECIALTY_NORMAL);
    pAttributesContainer->addAttribute(pAttributesContainer, "GPSLongitudeRef",  0x0003, EXIF_ASCII,    ATTRIBUTE_SPECIALTY_NORMAL);
    pAttributesContainer->addAttribute(pAttributesContainer, "GPSLongitude",     0x0004, EXIF_RATIONAL, ATTRIBUTE_SPECIALTY_NORMAL);
    pAttributesContainer->addAttribute(pAttributesContainer, "GPSAltitudeRef",   0x0005, EXIF_BYTE,     ATTRIBUTE_SPECIALTY_NORMAL);
    pAttributesContainer->addAttribute(pAttributesContainer, "GPSAltitude",      0x0006, EXIF_RATIONAL, ATTRIBUTE_SPECIALTY_NORMAL);
    
    return pAttributesContainer;
}