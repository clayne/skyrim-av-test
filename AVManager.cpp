#pragma once

#include "AVManager.h"
#include "Serialization.h"

bool AVManager::SerializeSave(SKSE::SerializationInterface* a_intfc)
{
	if (!Serialization::Save(a_intfc, this->avStorage)) {
		logger::error("Failed to write actor values");
		return false;
	}
	return true;
}

bool AVManager::SerializeSave(SKSE::SerializationInterface* a_intfc, uint32_t a_type, uint32_t a_version)
{
	if (!a_intfc->OpenRecord(a_type, a_version)) {
		logger::error("Failed to open actor values record!");
		return false;
	} else {
		return SerializeSave(a_intfc);
	}
}

bool AVManager::DeserializeLoad(SKSE::SerializationInterface* a_intfc)
{
	if (!Serialization::Load(a_intfc, this->avStorage)) {
		logger::info("Failed to load actor values!");
		return false;
	}

	return true;
}

void AVManager::Revert()
{
	this->avStorage.clear();
}

bool AVManager::RegisterActorValue(std::string avName, AVInterface* avInterface)
{
	if (registeredInterfaces[avName])
		return false;
	registeredInterfaces[avName] = avInterface;
	return false;
}
