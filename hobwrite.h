#ifndef _HOBWRITE_H
#define _HOBWRITE_H

#pragma once

#include "data3d.h"


class HDXHOBWriter
{	
	
public:
	HDXHOBWriter();
	~HDXHOBWriter();
	void WriteHob(int xFormat, char* filename, LPVOID mesh, HDXMaterialArray matArray, HDXMaterialList matList, CPoints m_Points, CMAKERPTGROUPS m_PtGrps);

};
#endif // _HOBWRITE_H