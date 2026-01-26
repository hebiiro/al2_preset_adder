#pragma once

namespace apn::preset_adder
{
	//
	// このクラスはこのプログラムのバージョンを管理します。
	//
	inline struct version_t {
		//
		// プラグイン名とプラグイン情報です。
		//
		const std::wstring name = L"プリセット追加MOD";
		const std::wstring information = L"🐍" + name + L"🔖";
		const std::wstring revision = L"r2";
	} version;
}
