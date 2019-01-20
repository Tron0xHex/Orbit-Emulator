#pragma once

namespace mg::orbitclient {
	class IRemoveSavegameListener {
	public:
		typedef void(__thiscall *CallBackPtr)(void*, unsigned int requestUniqueId, bool deleted);
		void(**callBackPtr)(unsigned int requestUniqueId, bool deleted);
	};
}