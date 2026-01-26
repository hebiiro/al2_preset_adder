#pragma once

namespace apn::preset_adder
{
	//
	// このクラスはコンフィグの入出力を担当します。
	//
	inline struct config_io_t : io_base_t
	{
		//
		// 初期化処理を実行します。
		//
		BOOL init()
		{
			MY_TRACE_FUNC("");

			auto module_file_path = my::get_module_file_name(hive.instance);
			auto config_folder_path = module_file_path.parent_path() / L"config";

			path = hive.config_file_name = config_folder_path /
				module_file_path.filename().replace_extension(L".json");
			MY_TRACE_STR(hive.config_file_name);

			// コンフィグフォルダを作成しておきます。
			try { std::filesystem::create_directories(config_folder_path); } catch (...) {}

			return TRUE;
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
		// 更新処理を実行します。
		//
		BOOL update()
		{
			MY_TRACE_FUNC("");

			return config_dialog.to_ui();
		}

		//
		// ノードからダイアログ名の設定を読み込みます。
		//
		BOOL read_dialog_title(n_json& root)
		{
			MY_TRACE_FUNC("");

			read_string(root, "dialog_title.new_project", hive.dialog_title.new_project);
			read_string(root, "dialog_title.new_scene", hive.dialog_title.new_scene);
			read_string(root, "dialog_title.set_scene", hive.dialog_title.set_scene);
			read_string(root, "dialog_title.set_layer_name", hive.dialog_title.set_layer_name);

			return TRUE;
		}

		//
		// ノードにダイアログ名の設定を書き込みます。
		//
		BOOL write_dialog_title(n_json& root)
		{
			MY_TRACE_FUNC("");

			write_string(root, "dialog_title.new_project", hive.dialog_title.new_project);
			write_string(root, "dialog_title.new_scene", hive.dialog_title.new_scene);
			write_string(root, "dialog_title.set_scene", hive.dialog_title.set_scene);
			write_string(root, "dialog_title.set_layer_name", hive.dialog_title.set_layer_name);

			return TRUE;
		}

		//
		// ノードからコンフィグを読み込みます。
		//
		virtual BOOL read_node(n_json& root)
		{
			MY_TRACE_FUNC("");

			read_dialog_title(root);

			return TRUE;
		}

		//
		// ノードにコンフィグを書き込みます。
		//
		virtual BOOL write_node(n_json& root)
		{
			MY_TRACE_FUNC("");

			write_dialog_title(root);

			return TRUE;
		}
	} config_io;
}
