#pragma once

namespace apn::preset_adder
{
	//
	// このクラスはこのプログラムのバージョンを管理します。
	//
	inline struct version_t : version_base_t {
		//
		// コンストラクタです。
		//
		version_t() : version_base_t(L"プリセット追加MOD", L"🐍プリセット追加MOD🔖", L"r3") {}
	} version;
}
