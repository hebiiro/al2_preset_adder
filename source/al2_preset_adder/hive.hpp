#pragma once

namespace apn::preset_adder
{
	//
	// このクラスは他クラスから共通して使用される変数を保持します。
	//
	inline struct hive_t
	{
		//
		// このアドインのインスタンスハンドルです。
		//
		HINSTANCE instance = nullptr;

		//
		// プラグインウィンドウです。
		//
		HWND plugin_window = nullptr;

		//
		// アセットのファイル名です。
		//
		std::wstring assets_file_name;

		//
		// コンフィグのファイル名です。
		//
		std::wstring config_file_name;

		//
		// このクラスはダイアログ名(正規表現パターン)です。
		//
		struct dialog_name_t
		{
			//
			// 「プロジェクトを新規作成」のダイアログ名です。
			//
			std::wstring new_project = L"プロジェクトを新規作成|New Project";

			//
			// 「シーンを作成」のダイアログ名です。
			//
			std::wstring new_scene = L"シーンを作成|New Scene";

			//
			// 「シーンの設定」のダイアログ名です。
			//
			std::wstring set_scene = L"シーンの設定|Scene Settings";

			//
			// 「レイヤー名を変更」のダイアログ名です。
			//
			std::wstring set_layer_name = L"レイヤー名を変更|Rename Layer";
		} dialog_name;

		//
		// メッセージボックスを表示します。
		//
		int32_t message_box(const std::wstring& text, HWND hwnd = nullptr, int32_t type = MB_OK | MB_ICONWARNING) {
			if (!hwnd) hwnd = plugin_window;
			return ::MessageBoxW(hwnd, text.c_str(), version.information.c_str(), type);
		}
	} hive;
}
