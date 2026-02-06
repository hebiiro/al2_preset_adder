#pragma once

namespace apn::preset_adder
{
	//
	// このクラスは他クラスから共通して使用される変数を保持します。
	//
	inline struct hive_t : hive_base_t
	{
		//
		// このクラスはダイアログ名です。
		//
		struct dialog_title_t
		{
			//
			// 「プロジェクトを新規作成」のダイアログ名です。
			//
			std::wstring new_project = L"プロジェクトを新規作成";

			//
			// 「シーンを作成」のダイアログ名です。
			//
			std::wstring new_scene = L"シーンを作成";

			//
			// 「シーンの設定」のダイアログ名です。
			//
			std::wstring set_scene = L"シーンの設定";

			//
			// 「レイヤー名を変更」のダイアログ名です。
			//
			std::wstring set_layer_name = L"レイヤー名を変更";
		} dialog_title;
	} hive;
}
