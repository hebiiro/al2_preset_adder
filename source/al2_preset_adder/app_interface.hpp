#pragma once

namespace apn::preset_adder
{
	//
	// このクラスはアプリケーションのインターフェイスです。
	//
	inline struct app_interface_t {
		virtual BOOL dll_init() = 0;
		virtual BOOL dll_exit() = 0;
	} *app = nullptr;
}
