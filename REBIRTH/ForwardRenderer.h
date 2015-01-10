#pragma once

#include <iostream>
#include <vector>

#include "RenderContentProvider.h"

class CForwardRenderer
{
private:
	std::vector<CRenderContentProvider> mContentProviders;
public:
	CForwardRenderer();
	~CForwardRenderer();

	void begin();
	void render();
	void end();
};

