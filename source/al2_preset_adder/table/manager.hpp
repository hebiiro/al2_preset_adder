#pragma once

namespace apn::preset_adder::table
{
	//
	// このクラスはテーブルを管理します。
	//
	inline struct manager_t
	{
		//
		// テーブルフォルダのパスです。
		//
		std::filesystem::path dir;

		//
		// 初期化処理を実行します。
		//
		BOOL init()
		{
			MY_TRACE_FUNC("");

			// 基準となるモジュールファイルのパスを取得します。
			auto base_path = my::get_module_file_name(hive.instance);

			// テーブルフォルダのパスを取得します。
			dir = base_path.parent_path() / L"al2" / L"config" / base_path.stem();

			// テーブルフォルダを作成しておきます。
			try { std::filesystem::create_directories(dir); } catch (...) {}

			// アセットフォルダからコンフィグフォルダにファイルをコピーします。
			// ただし、上書きはしません。既存のファイルを優先します。
			{
				auto from = base_path.parent_path() / L"al2" / L"assets" / base_path.stem();
				auto to = dir;

				entry_t::copy_file(from, to);
			}

			// テーブルを読み込みます。
			return reload();
		}

		//
		// 後始末処理を実行します。
		//
		BOOL exit()
		{
			MY_TRACE_FUNC("");

			return TRUE;
		}

		//
		// テーブルをリロードします。
		//
		BOOL reload()
		{
			MY_TRACE_FUNC("");

			// エントリにリロードさせます。
			return entry_t::reload(dir);
		}
	} manager;
}
