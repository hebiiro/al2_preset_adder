#pragma once

namespace apn::preset_adder
{
	//
	// このクラスはアプリケーションです。
	//
	inline struct app_t : app_interface_t
	{
		//
		// コンストラクタです。
		//
		app_t() { app = this; }

		//
		// dllの初期化処理を実行します。
		//
		virtual BOOL dll_init() override
		{
			MY_TRACE_FUNC("");

			// 各種開始処理を実行します。
			table::manager.init();
			dialog::manager.init();
			hook::manager.init();
			config_dialog.init();
			config_io.init();

			// コンフィグをファイルから読み込みます。
			config_io.read();

			return TRUE;
		}

		//
		// dllの後始末処理を実行します。
		//
		virtual BOOL dll_exit() override
		{
			MY_TRACE_FUNC("");

			// コンフィグをファイルに書き込みます。
			config_io.write();

			// 各種終了処理を実行します。
			config_io.exit();
			config_dialog.exit();
			hook::manager.exit();
			dialog::manager.exit();
			table::manager.exit();

			return TRUE;
		}
	} app_impl;
}
