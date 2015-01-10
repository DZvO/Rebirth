#pragma once
#include "RenderContentProvider.h"
#include <iostream>

class CTextRenderContentProvider :
	public CRenderContentProvider
{
public:
	CTextRenderContentProvider();
	void process();
	~CTextRenderContentProvider();
};

