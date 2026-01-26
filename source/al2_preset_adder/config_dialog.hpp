#pragma once

namespace apn::preset_adder
{
	//
	// このクラスはコンフィグダイアログです。
	//
	inline struct config_dialog_t : my::Dialog, lockable_t
	{
		virtual void on_update_controls() {}
		virtual void on_update_config() {}
		virtual void on_init_dialog() {}
		virtual void on_command(UINT code, UINT id, HWND control) {}

		//
		// 初期化処理を実行します。
		//
		BOOL init()
		{
			MY_TRACE_FUNC("");

			{
				// 初期化中にエディットボックスがコマンドを発行してしまうので、
				// それを防ぐためにロックしておきます。
				locker_t locker(this);

				// ダイアログを作成します。
				if (!__super::create(hive.instance, MAKEINTRESOURCE(idd_config), nullptr))
				{
					hive.message_box(L"コンフィグダイアログの作成に失敗しました");

					return FALSE;
				}
			}

			return TRUE;
		}

		//
		// 後始末処理を実行します。
		//
		BOOL exit()
		{
			MY_TRACE_FUNC("");

			// ダイアログを破壊します。
			return __super::destroy();
		}

		//
		// コンフィグでコントロールを更新します。
		//
		BOOL to_ui()
		{
			MY_TRACE_FUNC("");

			if (is_locked()) return FALSE;

			locker_t locker(this);

			set_text(idc_dialog_title_new_project, hive.dialog_title.new_project);
			set_text(idc_dialog_title_new_scene, hive.dialog_title.new_scene);
			set_text(idc_dialog_title_set_scene, hive.dialog_title.set_scene);
			set_text(idc_dialog_title_set_layer_name, hive.dialog_title.set_layer_name);

			return TRUE;
		}

		//
		// コントロールでコンフィグを更新します。
		//
		BOOL from_ui()
		{
			MY_TRACE_FUNC("");

			if (is_locked()) return FALSE;

			get_text(idc_dialog_title_new_project, hive.dialog_title.new_project);
			get_text(idc_dialog_title_new_scene, hive.dialog_title.new_scene);
			get_text(idc_dialog_title_set_scene, hive.dialog_title.set_scene);
			get_text(idc_dialog_title_set_layer_name, hive.dialog_title.set_layer_name);

			return TRUE;
		}

		//
		// ウィンドウプロシージャです。
		//
		virtual LRESULT on_wnd_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param) override
		{
			switch (message)
			{
			case WM_CREATE:
				{
					// このウィンドウをプラグインウィンドウに設定します。
					hive.plugin_window = hwnd;

					break;
				}
			case WM_DESTROY:
				{
					break;
				}
			case WM_INITDIALOG:
				{
					// スコープ終了時(デフォルト処理の後)に実行します。
					my::scope_exit scope_exit([&]()
					{
						// 子ウィンドウを列挙します。
						::EnumChildWindows(hwnd, [](HWND child, LPARAM l_param) -> BOOL
						{
							// 子ウィンドウを翻訳します。
							::SetWindowTextW(child, tr(my::get_window_text(child)));

							return TRUE;
						},
						0);
					});

					return __super::on_wnd_proc(hwnd, message, w_param, l_param);
				}
			case WM_COMMAND:
				{
					// ロックされている場合はWM_COMMANDを処理しません。
					if (is_locked()) break;

					auto control_id = LOWORD(w_param);
					auto code = HIWORD(w_param);
					auto control = (HWND)l_param;

					switch (control_id)
					{
					case idc_dialog_title_new_project:
					case idc_dialog_title_new_scene:
					case idc_dialog_title_set_scene:
					case idc_dialog_title_set_layer_name:
						if (code == EN_UPDATE) from_ui(); break;
					}

					break;
				}
			}

			return __super::on_wnd_proc(hwnd, message, w_param, l_param);
		}
	} config_dialog;
}
