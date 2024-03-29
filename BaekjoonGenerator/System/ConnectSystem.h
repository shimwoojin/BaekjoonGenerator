#pragma once

#include "IConnectInterface.h"
#include "Util/Singleton.h"

class ConnectSystem : public IConnectInterface, public Singleton<ConnectSystem>
{
	friend class Singleton<ConnectSystem>;

public:
	ConnectSystem();

	virtual bool ConnectTo(std::string address) override;

private:
	std::wstring chrome_directory;
};