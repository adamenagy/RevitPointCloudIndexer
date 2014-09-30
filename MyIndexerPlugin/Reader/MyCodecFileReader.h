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

#pragma once

#include <CodecFileReader.h>
#include <stdio.h>
#include <tchar.h>
#include <float.h>

class MyCodecFileReader : public CodecFileReader
{
public:
  MyCodecFileReader() : m_pFile(NULL), m_numPoints(0) 
  { 
    m_minPt[0] = m_maxPt[0] = 
      m_minPt[1] = m_maxPt[1] = 
      m_minPt[2] = m_maxPt[2] = 0;
  };

private:
  FILE * m_pFile;
  double m_minPt[3];
  double m_maxPt[3];
  long long m_numPoints;
  void getFileStats();
  void setPt(double ptDst[], double ptSrc[]);
  void setIfSmaller(double ptDst[], double ptSrc[]);
  void setIfGreater(double ptDst[], double ptSrc[]);

  // CodecFileReader functions
public:
  virtual bool open(const __wchar_t * sourceFile);
  // returns true if file is opened and is readable.
  virtual void close();

  virtual void fileStats(double * minPt, double * maxPt, long long& numPoints);
  // if the file is open, sets
  //   minPt[0] to min x of all points in the file,
  //   minPt[1] to min y of all points in the file,
  //   minPt[2] to min z of all points in the file,
  //   maxPt[0], maxPt[1], maxPt[2] to max x,y,z of all points,
  //   numPoints to total number of points in the file.

  virtual bool readFirstPoint(double& x, double& y, double& z,
    unsigned char& red, unsigned char& green, unsigned char& blue,
    unsigned char& classification, float& intensity);
  virtual bool readNextPoint(double& x, double& y, double& z,
    unsigned char& red, unsigned char& green, unsigned char& blue,
    unsigned char& classification, float& intensity);
  // These two functions sequentially read all the valid points in the file,
  // returning false when there are no more.
  // If point isn't classified, set classification to 0xff.
  // If point doesn't have intensity, set intensity to -1.
};

