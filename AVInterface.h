#pragma once

class AVInterface
{

public:

	const std::string avName;


	float GetBaseActorValue();
	float GetBaseAV()
	{
		return GetBaseActorValue();
	}

	float GetActorValueMax();
	float GetAVMax()
	{
		return GetActorValueMax();
	}


	void DamageActorValue(float afDamage);
	void DamageAV(float afDamage)
	{
		DamageActorValue(afDamage);
	}

	void RestoreActorValue(float afAmount);
	void RestoreAV(float afAmount)
	{
		return RestoreActorValue(afAmount);
	}

	void ModActorValue(float afAmount);
	void ModAV(float afAmount)
	{
		return ModActorValue(afAmount);
	}


	float GetActorValue();
	float GetAV()
	{
		return GetActorValue();
	}

	float GetActorValuePercentage();
	float GetAVPercentage()
	{
		return GetActorValuePercentage();
	}


	void ForceActorValue(float afNewValue);
	void ForceAV(float afNewValue)
	{
		return ForceAV(afNewValue);
	}

protected:

	bool Register();

};
