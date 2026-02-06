#pragma once

namespace apn::preset_adder
{
	//
	// このクラスはコンフィグの入出力を担当します。
	//
	inline struct config_io_t : config_io_base2_t
	{
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

			return __super::read_node(root);
		}

		//
		// ノードにコンフィグを書き込みます。
		//
		virtual BOOL write_node(n_json& root)
		{
			MY_TRACE_FUNC("");

			write_dialog_title(root);

			return __super::write_node(root);
		}
	} config_io;
}
