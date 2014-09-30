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

#include "StdAfx.h"
#include "MyCodecFileReader.h"

void MyCodecFileReader::setPt(double ptDst[], double ptSrc[])
{
  for (int i = 0; i < 3; i++)
    ptDst[i] = ptSrc[i];
}

void MyCodecFileReader::setIfSmaller(double ptDst[], double ptSrc[])
{
  for (int i = 0; i < 3; i++)
    if (ptSrc[i] < ptDst[i])
      ptDst[i] = ptSrc[i];
}

void MyCodecFileReader::setIfGreater(double ptDst[], double ptSrc[])
{
  for (int i = 0; i < 3; i++)
    if (ptSrc[i] > ptDst[i])
      ptDst[i] = ptSrc[i];
}

// CodecFileReader functions

void MyCodecFileReader::getFileStats()
{
  double pt[3];
  unsigned char red, green, blue, classification;
  float intensity;

  m_numPoints = 0;

  if (readFirstPoint(pt[0], pt[1], pt[2], red, green, blue, classification, intensity))
  {
    setPt(m_minPt, pt);
    setPt(m_maxPt, pt);

    m_numPoints = 1;

    while(readNextPoint(pt[0], pt[1], pt[2], red, green, blue, classification, intensity))
    {
      setIfSmaller(m_minPt, pt);
      setIfGreater(m_maxPt, pt);

      m_numPoints++;
    }
  }
}

bool MyCodecFileReader::open(const __wchar_t * sourceFile)
{
  if (m_pFile)
  {
    fclose(m_pFile);
    m_pFile = NULL;
  }

  _wfopen_s( &m_pFile, sourceFile, L"r" );

  // In case of this specific file type we need to
  // read in all the points from it in order to implement the
  // fileStats() function. You may as well cache all the read
  // points in memory so that you do not need to read it twice
  // from the file

  getFileStats();

  return (m_pFile != NULL);
}

void MyCodecFileReader::close()
{
  if (m_pFile != NULL)
  {
    fclose(m_pFile);
    m_pFile = NULL;
  }
}

void MyCodecFileReader::fileStats(double minPt[], double maxPt[], long long& numPoints)
{
  setPt(minPt, m_minPt);
  setPt(maxPt, m_maxPt);
  numPoints = m_numPoints;
}

bool MyCodecFileReader::readFirstPoint(double& x, double& y, double& z,
  unsigned char& red, unsigned char& green, unsigned char& blue,
  unsigned char& classification, float& intensity)
{
  if (NULL == m_pFile)
    return false;

  fseek(m_pFile, 0L, SEEK_SET);

  return readNextPoint(x, y, z, red, green, blue, classification, intensity); 
}

bool MyCodecFileReader::readNextPoint(double& x, double& y, double& z,
  unsigned char& red, unsigned char& green, unsigned char& blue,
  unsigned char& classification, float& intensity)
{
  if ((NULL == m_pFile) || feof(m_pFile))
    return false;

  int ret = fwscanf_s(m_pFile, _T("%Lf\t%Lf\t%Lf\n"), &x, &y, &z);
  if (ret < 1)
    return false;

  // If you do not know what to set then set it to these

  classification = 0xff;
  intensity = -1;

  return true;
}
