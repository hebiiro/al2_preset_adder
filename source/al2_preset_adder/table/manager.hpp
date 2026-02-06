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

			// 基準となるパスを取得します。
			base_path_t base;

			// テーブルフォルダのパスを取得します。
			dir = base.config_dir;

			// アセットフォルダからコンフィグフォルダにファイルをコピーします。
			// ただし、上書きはしません。既存のファイルを優先します。
			{
				auto from = base.assets_dir;
				auto to = base.config_dir;

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
