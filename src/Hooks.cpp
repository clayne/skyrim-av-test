#include "Hooks.h"
#include "HitEventHandler.h"

namespace Hooks
{
	void Hooks::Install()
	{
		HitEventHandler::InstallHooks();
		logger::info("Installed all hooks");
	}
}
