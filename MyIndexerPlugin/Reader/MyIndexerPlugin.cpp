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

#include <stdafx.h>
#include "MyIndexerPlugin.h"
#include "MyCodecFileReader.h"

// File type we support

#define kASC _T(".asc")

// Entry point of indexer plugin

INDEXERPLUGIN_API IIndexerPlugin* getIndexerPlugin()
{ 
  return new MyIndexerPlugin();
}

// IIndexerPlugin functions

const wchar_t* MyIndexerPlugin::getCodecs()
{
  return kASC;
}

CodecFileReader* MyIndexerPlugin::getFileReader(const wchar_t* codec)
{
  // Just a safety check - it does not seem needed
  if (_wcsicmp(codec, kASC) != 0)
    return NULL;

  if (m_pCodecFileReader == NULL)
    m_pCodecFileReader = new MyCodecFileReader();

  return m_pCodecFileReader;
}

bool MyIndexerPlugin::canImport(const wchar_t* inputFile)
{
  wchar_t ext[_MAX_EXT];
  _wsplitpath_s(inputFile, NULL, 0, NULL, 0, NULL, 0, ext, _MAX_EXT);

  return (_wcsicmp(ext, kASC) == 0); 
}

void MyIndexerPlugin::destroy()
{
  delete this;
}
