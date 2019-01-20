#pragma once

#include "../stdafx.h"

namespace mg::orbitclient {
	struct __declspec(dllexport) SavegameInfo {
	private:
		wstring name_;
		unsigned int id_;
		unsigned long size_;
		unsigned long productId_;
	public:
		SavegameInfo(unsigned int, unsigned int, unsigned long, const wstring&);
		unsigned int GetSavegameId();
		unsigned int GetSize();
		unsigned short const * GetName();
	};
}

inline mg::orbitclient::SavegameInfo::SavegameInfo(const unsigned int id, const unsigned int productId, const unsigned long size, const wstring& name)
{
	id_ = id;
	size_ = size;
	name_ = name;
	productId_ = productId;
}

inline unsigned int mg::orbitclient::SavegameInfo::GetSavegameId()
{
	return id_;
}

inline unsigned int mg::orbitclient::SavegameInfo::GetSize()
{
	return size_;
}

inline unsigned short const * mg::orbitclient::SavegameInfo::GetName()
{
	return reinterpret_cast<const unsigned short*>(&name_.c_str()[0]);
}