#pragma once

namespace apn::preset_adder::table
{
	//
	// このクラスはテーブルファイルを読み込みます。
	// テーブルファイルはutf-8のtsvファイルです。
	//
	struct reader_t
	{
		//
		// テーブルファイルのパスです。
		//
		std::filesystem::path path;

		//
		// テーブルファイルを読み込みます。
		//
		BOOL operator()(const auto& func) const
		{
			MY_TRACE_FUNC("{/}", path);

			//
			// この関数は指定された行を正規化して返します。
			//
			const auto normalize = [](const std::string& u8)
			{
				return trim(my::cp_to_wide(u8, CP_UTF8), L"\xfeff\r\n");
			};

			try
			{
				// 現在のセクションです。
				auto section = std::wstring {};

				// ファイルストリームを開きます。
				std::ifstream stream(path);
				if (!stream) return FALSE;

				// 最初の一行目を読み込みます。
				auto raw_line = std::string {};
				if (!std::getline(stream, raw_line)) return FALSE;

				// 行を配列に変換します。
				auto first_vec = split(normalize(raw_line), L'\t');

				// 列数を取得しておきます。
				const auto nb_cols = first_vec.size();

				// 行のインデックスです。
				auto index = 0;

				// 指定された関数に処理させます。
				func(index++, first_vec);

				// 残りを一行ずつ読み込みます。
				while (std::getline(stream, raw_line))
				{
					// 行を正規化します。
					auto line = normalize(raw_line);

					// 行を配列に変換します。
					auto vec = split(line, L'\t');

					// 列数が固定になるように調整します。
					vec.resize(nb_cols);

					// 指定された関数に処理させます。
					func(index++, vec);
				}

				return TRUE;
			}
			// 例外が発生した場合は
			catch (std::exception& error)
			{
				// メッセージボックスでユーザーに通知します。
				hive.message_box(my::ws(error.what()));
			}

			return TRUE;
		}
	};
}
