#pragma once

namespace apn::preset_adder::table
{
	//
	// このクラスはプロジェクトのテーブルです。
	//
	inline struct project_t : entry_t
	{
		//
		// このクラスはプロジェクトのノードです。
		//
		struct node_t {
			std::wstring scene_name;
			std::wstring video_width;
			std::wstring video_height;
			std::wstring video_rate;
			std::wstring audio_rate;
			std::wstring display_name;
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
			return L"project.tsv";
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
				if (vec.size() < 6) return FALSE;

				// コレクションにノードを追加します。
				nodes.emplace_back(vec[0], vec[1], vec[2], vec[3], vec[4], vec[5]);

				return TRUE;
			});

			return TRUE;
		}
	} project;
}
