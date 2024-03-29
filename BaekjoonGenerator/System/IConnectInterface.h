#pragma once
#include "stdafx.h"

class IConnectInterface
{
public:
	virtual bool ConnectTo(std::string address) = 0;
};