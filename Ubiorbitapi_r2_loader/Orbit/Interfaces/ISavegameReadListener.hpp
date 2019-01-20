#pragma once

namespace mg::orbitclient {
	class ISavegameReadListener {
	public:
		typedef void(__thiscall *CallBackPtr)(void*, unsigned int requestUniqueId, unsigned int bytesReaded);
		void (**callBackPtr)(unsigned int requestId, unsigned int bytesReaded);
	};
}