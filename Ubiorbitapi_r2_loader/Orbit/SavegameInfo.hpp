#pragma once

#include "../stdafx.h"

namespace mg::orbitclient
{
	class UPLAY_API SavegameInfo
	{
		wstring name;
		unsigned int id;
		unsigned long size;
		unsigned long productId;
	public:
		SavegameInfo(unsigned int, unsigned int, unsigned long, const wstring&);
		unsigned int GetSavegameId();
		unsigned int GetSize();
		unsigned short const* GetName();
	};
}

//------------------------------------------------------------------------------
inline mg::orbitclient::SavegameInfo::SavegameInfo(const unsigned int id, const unsigned int productId,
                                                   const unsigned long size, const wstring& name)
{
	this->id = id;
	this->size = size;
	this->name = name;
	this->productId = productId;
}

//------------------------------------------------------------------------------
inline unsigned int mg::orbitclient::SavegameInfo::GetSavegameId()
{
	return id;
}

//------------------------------------------------------------------------------
inline unsigned int mg::orbitclient::SavegameInfo::GetSize()
{
	return size;
}

//------------------------------------------------------------------------------
inline unsigned short const* mg::orbitclient::SavegameInfo::GetName()
{
	return reinterpret_cast<const unsigned short*>(&name.c_str()[0]);
}
