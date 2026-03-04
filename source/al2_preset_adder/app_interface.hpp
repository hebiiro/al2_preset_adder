#pragma once

namespace apn::preset_adder
{
	//
	// このクラスはアプリケーションのインターフェイスです。
	//
	inline struct app_interface_t : app_base_t
	{
		//
		// コンストラクタです。
		//
		app_interface_t() { app = this; }
	} *app = nullptr;
}
