#pragma once

#include "AVInterface.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class AVManager
{

public:
	static AVManager* GetSingleton()
	{
		static AVManager manager;
		return &manager;
	}

	bool SerializeSave(SKSE::SerializationInterface* a_intfc);
	bool SerializeSave(SKSE::SerializationInterface* a_intfc, uint32_t a_type, uint32_t a_version);
	bool DeserializeLoad(SKSE::SerializationInterface* a_intfc);
	void Revert();

	bool RegisterActorValue(std::string avName, AVInterface* avInterface);

private:

	std::unordered_map<std::string, AVInterface*> registeredInterfaces;

	json avStorage;
		
};
