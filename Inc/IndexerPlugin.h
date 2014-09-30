// (C) Copyright 2011 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software
// in object code form for any purpose and without fee is hereby
// granted, provided that the above copyright notice appears in
// all copies and that both that copyright notice and the limited
// warranty and restricted rights notice below appear in all
// supporting documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK,
// INC. DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL
// BE UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is
// subject to restrictions set forth in FAR 52.227-19 (Commercial
// Computer Software - Restricted Rights) and DFAR 252.227-7013(c)
// (1)(ii)(Rights in Technical Data and Computer Software), as
// applicable.
//

#ifndef __INDEXER_PLUGIN_H__
#define __INDEXER_PLUGIN_H__

#pragma once

#include <CodecFileReader.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
// Class IndexerPlugin

class IIndexerPlugin
{
// construction/destruction
public:
  virtual ~IIndexerPlugin() {}

// Interface
public:
   virtual const wchar_t* getCodecs() = 0 ; // semi-colon delimited list of "codecs" (Extensions) supported by the plugin
                                            // i.e. (.ptg;.ptx)
   virtual CodecFileReader* getFileReader(const wchar_t* codec) = 0;  // return the reader for the specified codec.
   virtual bool canImport(const wchar_t* inputFile) = 0; // true if supports the specified input/codec. 
   virtual void destroy() = 0;  // called when we are done with the plugin and it should destroy itself and all 
                                // resources.
};


// Function implemented by plugin provider to return plugin implementation for the indexer
#if defined(INDEXERPLUGIN_DLL)
# define INDEXERPLUGIN_API __declspec(dllexport)
#else
# define INDEXERPLUGIN_API __declspec(dllimport)
#endif

extern "C" INDEXERPLUGIN_API IIndexerPlugin* getIndexerPlugin();

#endif //  __INDEXING_PLUGIN_H__

