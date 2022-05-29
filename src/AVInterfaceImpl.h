#pragma once

#include "AVInterface.h"

class AVInterfaceImpl : public AVInterface
{

public:

	static AVInterface* GetSingleton()
	{
		static AVInterface avInterface;
		return &avInterface;
	}

	inline static const std::string avName;


protected:

	bool Register();

};
