//
// JPEGMetaExtractor
// Core/Include/ExtractorMacros.h
//
#ifndef __JPEGMETAEXTRACTOR_EXTRACTORMACROS_H__
#define __JPEGMETAEXTRACTOR_EXTRACTORMACROS_H__

#if defined(_WIN32) || defined(_WIN64)
# define LIB_EXPORT __declspec(dllexport)
#else
# define LIB_EXPORT
#endif

#endif