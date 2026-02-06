#pragma once

namespace apn::preset_adder
{
	//
	// このクラスはコンフィグダイアログです。
	//
	inline struct config_dialog_t : config_dialog_base_t
	{
		//
		// コンフィグでコントロールを更新します。
		//
		virtual BOOL on_to_ui() override
		{
			MY_TRACE_FUNC("");

			set_text(idc_dialog_title_new_project, hive.dialog_title.new_project);
			set_text(idc_dialog_title_new_scene, hive.dialog_title.new_scene);
			set_text(idc_dialog_title_set_scene, hive.dialog_title.set_scene);
			set_text(idc_dialog_title_set_layer_name, hive.dialog_title.set_layer_name);

			return TRUE;
		}

		//
		// コントロールでコンフィグを更新します。
		//
		virtual BOOL on_from_ui() override
		{
			MY_TRACE_FUNC("");

			get_text(idc_dialog_title_new_project, hive.dialog_title.new_project);
			get_text(idc_dialog_title_new_scene, hive.dialog_title.new_scene);
			get_text(idc_dialog_title_set_scene, hive.dialog_title.set_scene);
			get_text(idc_dialog_title_set_layer_name, hive.dialog_title.set_layer_name);

			return TRUE;
		}

		//
		// WM_COMMANDを処理します。
		//
		virtual void on_command(UINT code, UINT control_id, HWND control) override
		{
			switch (control_id)
			{
			// エディットボックス用の処理です。
			case idc_dialog_title_new_project:
			case idc_dialog_title_new_scene:
			case idc_dialog_title_set_scene:
			case idc_dialog_title_set_layer_name:
				if (code == EN_UPDATE) from_ui(); break;
			}
		}
	} config_dialog;
}
