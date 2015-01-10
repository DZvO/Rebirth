#pragma once
class CRenderContentProvider
{
public:
	CRenderContentProvider();
	virtual void process() = 0;
	~CRenderContentProvider();
};

