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
	return true;
}

float AVManager::GetBaseActorValue(std::string a_actorValue, RE::Actor* a_actor)
{
	auto avInterface = registeredInterfaces.at(a_actorValue);
	return avInterface->GetBaseActorValue(a_actor);
}

float AVManager::GetActorValueMax(std::string a_actorValue, RE::Actor* a_actor)
{
	auto avInterface = registeredInterfaces.at(a_actorValue);
	return avInterface->GetActorValueMax(a_actor);
}

void AVManager::DamageActorValue(std::string a_actorValue, RE::Actor* a_actor, [[maybe_unused]] float a_damage)
{
	if (avStorage[a_actor->formID] == nullptr)
		avStorage[a_actor->formID] = { 0.0f, 0.f, 0.0f };

	auto avInterface = registeredInterfaces.at(a_actorValue);

	avStorage[a_actor->formID][2] = std::clamp(avStorage[a_actor->formID][2] + a_damage, 0.0f, avInterface->GetActorValueMax(a_actor));
}

void AVManager::RestoreActorValue(std::string a_actorValue, RE::Actor* a_actor, float a_restore)
{
	if (avStorage[a_actor->formID] == nullptr)
		avStorage[a_actor->formID] = { 0.0f, 0.f, 0.0f };

	auto avInterface = registeredInterfaces.at(a_actorValue);

	avStorage[a_actor->formID][2] = std::clamp(avStorage[a_actor->formID][2] - a_restore, 0.0f, avInterface->GetActorValueMax(a_actor));
}

float AVManager::GetActorValue(std::string a_actorValue, RE::Actor* a_actor)
{
	auto avInterface = registeredInterfaces.at(a_actorValue);
	return avInterface->GetActorValue(a_actor);
}
