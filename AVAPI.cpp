#pragma once

#include "AVAPI.h"

bool AVManager::RegisterActorValue(std::string avName, AVInterface* avInterface)
{
	if (registeredInterfaces[avName])
		return false;
	registeredInterfaces[avName] = avInterface;
	return false;
}
