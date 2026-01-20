#pragma once

namespace apn::preset_adder::table
{
	//
	// このクラスはレイヤー名のテーブルです。
	//
	inline struct layer_name_t : entry_t
	{
		//
		// このクラスはレイヤー名のノードです。
		//
		struct node_t {
			std::wstring layer_name;
		};

		//
		// ノードのコレクションです。
		//
		std::vector<node_t> nodes;

		//
		// テーブルファイルのファイル名を返します。
		//
		virtual std::filesystem::path on_get_file_name() override
		{
			return L"layer_name.tsv";
		}

		//
		// テーブルをリロードします。
		//
		virtual BOOL on_reload(const reader_t& reader) override
		{
			// すべてのノードを消去します。
			nodes.clear();

			// テーブルファイルを読み込みます。
			reader([&](int index, const std::vector<std::wstring>& vec)
			{
				// 先頭行は除外します。
				if (index == 0) return FALSE;

				// 要素数が無効の場合は除外します。
				if (vec.size() < 1) return FALSE;

				// コレクションにノードを追加します。
				nodes.emplace_back(vec[0]);

				return TRUE;
			});

			return TRUE;
		}
	} layer_name;
}
