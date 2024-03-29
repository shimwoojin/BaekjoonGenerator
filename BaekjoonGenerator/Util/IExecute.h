#pragma once
#include "stdafx.h"

class IExecute
{
public:
	virtual void Init() = 0;
	virtual void Execute() = 0;
};