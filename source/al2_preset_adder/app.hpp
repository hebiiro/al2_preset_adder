#pragma once

namespace apn::preset_adder
{
	//
	// このクラスはアプリケーションです。
	//
	inline struct app_t : app_base_t
	{
		//
		// プラグインの初期化処理を実行します。
		//
		virtual BOOL on_initialize_plugin(DWORD version) override
		{
			MY_TRACE_FUNC("");

			// 各種開始処理を実行します。
			debug.init();
			config_io.init();
			table::manager.init();
			dialog::manager.init();
			hook::manager.init();
			config_dialog.init(idd_config);

			// コンフィグをファイルから読み込みます。
			config_io.read();

			return TRUE;
		}

		//
		// プラグインの後始末処理を実行します。
		//
		virtual BOOL on_uninitialize_plugin() override
		{
			MY_TRACE_FUNC("");

			// 各種終了処理を実行します。
			config_dialog.exit();
			hook::manager.exit();
			dialog::manager.exit();
			table::manager.exit();
			config_io.exit();
			debug.exit();

			return TRUE;
		}
	} app_impl;
}
