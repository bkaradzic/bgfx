//-----------------------------------------------------------------------------
//
// ImageLib Utility Sources
// Copyright (C) 2000-2002 by Denton Woods
// Last modified: 07/09/2002 <--Y2K Compliant! =]
//
// Filename: src-ILU/src/ilu_region.h
//
// Description: Creates an image region.
//
//-----------------------------------------------------------------------------

#ifndef ILU_REGION_H
#define ILU_REGION_H

typedef struct Edge
{
	ILint	yUpper;
	ILfloat	xIntersect, dxPerScan;
	struct	Edge *next;
} Edge;


#endif//ILU_REGION_H

