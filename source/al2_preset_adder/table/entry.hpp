#pragma once

namespace apn::preset_adder::table
{
	//
	// このクラスはテーブルのエントリです。
	//
	struct entry_t
	{
		//
		// エントリのコレクションです。
		//
		inline static std::vector<entry_t*> entries;

		//
		// コンストラクタです。
		//
		entry_t() { entries.emplace_back(this); }

		//
		// テーブルファイルをコピーします。
		//
		inline static BOOL copy_file(const std::filesystem::path& from, const std::filesystem::path& to)
		{
			MY_TRACE_FUNC("");

			for (auto entry : entries)
			{
				// テーブルファイルのファイル名を取得します。
				auto filename = entry->on_get_file_name();

				// テーブルファイルをコピーします。例外は無視します。
				try { std::filesystem::copy(from / filename, to / filename); } catch (...) {}
			}

			return TRUE;
		}

		//
		// テーブルファイルをリロードします。
		//
		inline static BOOL reload(const std::filesystem::path& dir)
		{
			MY_TRACE_FUNC("");

			for (auto entry : entries)
			{
				// テーブルファイルのフルパスを取得します。
				auto path = dir / entry->on_get_file_name();

				// ファイルリーダーを作成します。
				auto reader = reader_t(path);

				// エントリにリロードさせます。
				if (!entry->on_reload(reader)) return FALSE;
			}

			return TRUE;
		}

		virtual std::filesystem::path on_get_file_name() = 0;
		virtual BOOL on_reload(const reader_t& reader) = 0;
	};
}
