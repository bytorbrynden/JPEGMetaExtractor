//
// ExifExtractC
// Source/entry.c
//
#include <stdio.h>

#include "MetadataExtractor.h"

int main
(
    int argc, const char **argv
)
{
    if (2 > argc)
    {
        printf("A minimum of 2 arguments is required!\n");
        
        return 1;
    }
    
    for (int argumentIndex = 1; argumentIndex < argc; ++argumentIndex)
    {
        const char *pCurrentArgument = *(argv + argumentIndex);
        
        printf("Current file: \"%s\"\n", pCurrentArgument);
        
        MetadataAttributesContainer *pMetadata = extractMetadata(pCurrentArgument);
        
        if (NULL != pMetadata)
        {
            printf("Got metadata!\n");
            
            deallocateMetadataAttributesContainer(pMetadata);
        }
    }
    
    return 0;
}