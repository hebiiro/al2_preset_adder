#include "pch.h"
#include "resource.h"
#include "version.hpp"
#include "app_interface.hpp"
#include "lockable.hpp"
#include "hive.hpp"
#include "utils.hpp"
#include "table/reader.hpp"
#include "table/entry.hpp"
#include "table/manager.hpp"
#include "table/entry/project.hpp"
#include "table/entry/video_size.hpp"
#include "table/entry/video_rate.hpp"
#include "table/entry/audio_rate.hpp"
#include "table/entry/scene_name.hpp"
#include "table/entry/layer_name.hpp"
#include "dialog/manager.hpp"
#include "dialog/entity/new_project.hpp"
#include "dialog/entity/set_layer_name.hpp"
#include "hook/entry.hpp"
#include "hook/manager.hpp"
#include "hook/entry/call_wnd_proc_ret.hpp"
#include "config_dialog.hpp"
#include "io_base.hpp"
#include "config_io.hpp"
#include "app.hpp"

namespace apn::preset_adder
{
	//
	// エントリポイントです。
	//
	EXTERN_C BOOL APIENTRY DllMain(HMODULE instance, DWORD reason, LPVOID reserved)
	{
		switch (reason)
		{
		case DLL_PROCESS_ATTACH:
			{
				::DisableThreadLibraryCalls(hive.instance = instance);

				// このdllがアンロードされないようにします。
				::LoadLibrary(my::get_module_file_name(instance).c_str());

				break;
			}
		case DLL_PROCESS_DETACH:
			{
				break;
			}
		}

		return TRUE;
	}

	//
	// プラグインDLL初期化関数です。
	//
	EXTERN_C bool InitializePlugin(DWORD version)
	{
		if (version < 2003000) return false;
#ifdef _DEBUG
		// デバッグ用のコードです。
		{
			if (0)
			{
				// カスタムロガーを設定します。
				static struct Logger : my::Tracer::Logger {
					virtual void output(LPCTSTR raw, LPCTSTR text) override {
						// SHIFTキーが押されているときだけログを出力します。
						if (::GetKeyState(VK_SHIFT) < 0) ::OutputDebugString(text);
					}
				} logger;
				my::Tracer::logger = &logger;
			}
		}
#endif
		app->dll_init();

		return true;
	}

	//
	// プラグインDLL終了関数です。
	//
	EXTERN_C void UninitializePlugin()
	{
		app->dll_exit();

		return;
	}

	//
	// プラグイン登録関数です。
	//
	EXTERN_C void RegisterPlugin(HOST_APP_TABLE* host)
	{
		host->set_plugin_information(version.information.c_str());

		host->register_window_client(version.name.c_str(), hive.plugin_window);
	}

	//
	// aviutl2のコンフィグを取得します。
	//
	EXTERN_C void InitializeConfig(CONFIG_HANDLE* config)
	{
		hive.aviutl2.config = config;
	}
}
