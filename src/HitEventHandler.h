#pragma once

class HitEventHandler
{
public:
	[[nodiscard]] static HitEventHandler* GetSingleton()
	{
		static HitEventHandler singleton;
		return std::addressof(singleton);
	}

	static void InstallHooks()
	{
		Hooks::Install();
	}

	void PreProcessHitEvent(RE::Actor* target, RE::HitData& hitData);
	void PostProcessHitEvent(RE::Actor* target, RE::HitData& hitData);

protected:
	static void TryStagger(RE::Actor* target, float staggerMult, RE::Actor* aggressor)
	{
		using func_t = decltype(&TryStagger);
		REL::Relocation<func_t> func{ REL::RelocationID(36700, 36700) };
		return func(target, staggerMult, aggressor);
	}

	static void ApplyPerkEntryPoint(int entry, RE::Actor* actor_a, RE::Actor* actor_b, float& out)
	{
		using func_t = decltype(&ApplyPerkEntryPoint);
		REL::Relocation<func_t> func{ REL::RelocationID(23073, 23073) };  // 1.5.97 14032ECE0
		return func(entry, actor_a, actor_b, out);
	}

	static float RecalculateStagger(RE::Actor* target, RE::Actor* aggressor, RE::HitData& hitData)
	{
		float stagger = hitData.weapon->GetStagger() * (1.0f - hitData.percentBlocked);
		stagger += stagger * hitData.attackData.get()->data.staggerOffset;

		ApplyPerkEntryPoint(34, aggressor, target, stagger);
		ApplyPerkEntryPoint(33, target, aggressor, stagger);

		stagger *= 33;

		return stagger;
	}

	struct Hooks
	{
		struct ProcessHitEvent
		{
			static void thunk(RE::Actor* target, RE::HitData& hitData)
			{
				auto manager = GetSingleton();
				manager->PreProcessHitEvent(target, hitData);
				func(target, hitData);
				manager->PostProcessHitEvent(target, hitData);
			}
			static inline REL::Relocation<decltype(thunk)> func;
		};

		struct Nullify_ApplyPerkEntryPoint_Aggressor
		{
			static void thunk([[maybe_unused]] INT32 entry, [[maybe_unused]] RE::Actor* actor_a, [[maybe_unused]] RE::Actor* actor_b, [[maybe_unused]] INT64 out)
			{
				return;
			}
			static inline REL::Relocation<decltype(thunk)> func;
		};

		struct Nullify_ApplyPerkEntryPoint_Target
		{
			static void thunk([[maybe_unused]] INT32 entry, [[maybe_unused]] RE::Actor* actor_a, [[maybe_unused]] RE::Actor* actor_b, [[maybe_unused]] INT64 out)
			{
				return;
			}
			static inline REL::Relocation<decltype(thunk)> func;
		};

		static void Install()
		{
			stl::write_thunk_call<ProcessHitEvent>(REL::RelocationID(37673, 37673).address() + REL::Relocate(0x3C0, 0x3C0, 0x3C0));                     // 1.5.97 140628C20
			stl::write_thunk_call<Nullify_ApplyPerkEntryPoint_Aggressor>(REL::RelocationID(36700, 36700).address() + REL::Relocate(0x9A, 0x90, 0x9A));  // 1.5.97 1405FA1B0
			stl::write_thunk_call<Nullify_ApplyPerkEntryPoint_Target>(REL::RelocationID(36700, 36700).address() + REL::Relocate(0xAE, 0xAE, 0xAE));     // 1.5.97 1405FA1B0
		}
	};

private:
	constexpr HitEventHandler() noexcept = default;
	HitEventHandler(const HitEventHandler&) = delete;
	HitEventHandler(HitEventHandler&&) = delete;

	~HitEventHandler() = default;

	HitEventHandler& operator=(const HitEventHandler&) = delete;
	HitEventHandler& operator=(HitEventHandler&&) = delete;
};
