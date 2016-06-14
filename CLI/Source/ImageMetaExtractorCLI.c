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
        MetadataAttributesContainer *pMetadata = NULL;
        const char *pCurrentArgument = *(argv + argumentIndex);
        
        printf("Current file: \"%s\"\n", pCurrentArgument);
        
        if (NULL == (pMetadata = extractMetadata(pCurrentArgument)))
            continue;
        
        for (int attributeIndex = 0; attributeIndex <
            pMetadata->attributesAllocated; ++attributeIndex)
        {
            printAttribute(*(pMetadata->ppAttributes + attributeIndex));
        }
        
        deallocateMetadataAttributesContainer(pMetadata);
    }
    
    return 0;
}