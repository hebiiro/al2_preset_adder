#pragma once

namespace apn::preset_adder::dialog
{
	//
	// このクラスは『レイヤー名を変更』ダイアログをサブクラス化します。
	//
	struct set_layer_name_t : entity_t
	{
		//
		// このクラスは既存のコントロールです。
		//
		struct control_t {
			HWND hwnd;
			RECT rc;
			operator HWND() const { return hwnd; }
		};

		//
		// 既存のコントロールのコレクションです。
		//
		std::vector<control_t> controls;
		//
		// 既存のコントロールです。
		//
		struct readymade_t {
			const control_t* name_stc;
			const control_t* name;
		} readymade = {};

		//
		// 後付けのコントロールです。
		//
		struct retrofit_t {
			HWND name_preset; // "名前プリセット"のコンボボックスです。
			HWND ok; // OKボタンです。
			HWND cancel; // キャンセルボタンです。
		} retrofit = {};


		//
		// 初期化処理です。
		//
		virtual BOOL subclass(HWND hwnd) override
		{
			// ウィンドウ名がマッチしない場合は失敗します。
			if (!match(my::get_window_text(hwnd), hive.dialog_name.set_layer_name)) return FALSE;

			return __super::subclass(hwnd);
		}

		//
		// コントロール配列を初期化します。
		//
		BOOL init_controls(HWND hwnd)
		{
			MY_TRACE_FUNC("{/hex}", hwnd);

			// 既存のコントロールを列挙します。
			::EnumChildWindows(hwnd,
				[](HWND child, LPARAM l_param) -> BOOL
			{
				MY_TRACE_HWND(child);

				// thisポインタを取得します。
				auto p = (set_layer_name_t*)l_param;

				// 既存のコントロールの矩形を取得します。
				auto rc = my::get_window_rect(child);
				my::map_window_points(nullptr, *p, &rc);

				// 既存のコントロールをコレクションに追加します。
				p->controls.emplace_back(child, rc);

				return TRUE;
			},
			(LPARAM)this);

			// 既存のコントロールの数が無効の場合は失敗します。
			if (controls.size() < 2) return FALSE;

			{
				// コントロールのインデックスです。
				auto index = size_t {};

				readymade.name_stc = &controls[index++];
				readymade.name = &controls[index++];
			}

			return TRUE;
		}

		//
		// コントロールを再配置します。
		//
		BOOL arrange_controls(HWND hwnd)
		{
			MY_TRACE_FUNC("{/hex}", hwnd);

			// クライアント矩形を取得します。
			auto client_rc = my::get_client_rect(hwnd);

			// 基準サイズを取得します。
			auto base = SIZE {
				my::get_width(readymade.name->rc),
				my::get_height(readymade.name->rc),
			};

			// 余白サイズを取得します。
			auto space = SIZE { 5, 5 };

			// 移動予定のオフセットサイズを取得します。
			auto offset = SIZE {
				base.cx + space.cx,
				base.cy + space.cy,
			};

			// 追加のコントロールを作成します。
			{
				// コントロールのフォントです。
				auto font = (HFONT)::SendMessage(*readymade.name, WM_GETFONT, 0, 0);

				// 追加コントロールの基準X座標です。
				auto x = readymade.name->rc.right + space.cx;

				{
					//
					// この関数はコントロールを作成します。
					//
					const auto create_control = [&](
						LPCWSTR class_name, LPCWSTR window_name,
						DWORD style, int x, int y, int w, int h)
					{
						style |= WS_VISIBLE | WS_CHILD;

						auto control = ::CreateWindowExW(
							0, class_name, window_name, style, x, y, w, h,
							hwnd, nullptr, hive.instance, nullptr);
						::SendMessage(control, WM_SETFONT, (WPARAM)font, TRUE);
						return control;
					};

					//
					// この関数はコンボボックスを作成します。
					//
					const auto create_combobox = [&](int x, int y, int w, int h)
					{
						return create_control(
							WC_COMBOBOXW, nullptr,
							WS_VSCROLL |
							CBS_DISABLENOSCROLL | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
							x, y, w, h * 20);
					};

					retrofit.name_preset = create_combobox(x, readymade.name_stc->rc.top, base.cx, base.cy);

					{
						auto button_size = SIZE {
							::MulDiv(my::get_width(readymade.name_stc->rc), 5, 2),
							base.cy,
						};
						auto button_pos = POINT {
							x + base.cx - button_size.cx,
//							client_rc.right + offset.cx - button_size.cx,
							client_rc.bottom + offset.cy - button_size.cy,
						};

						retrofit.cancel = create_control(WC_BUTTONW, L"キャンセル", BS_PUSHBUTTON, button_pos.x, button_pos.y, button_size.cx, button_size.cy);
						button_pos.x -= button_size.cx + space.cx;
						retrofit.ok = create_control(WC_BUTTONW, L"OK", BS_DEFPUSHBUTTON, button_pos.x, button_pos.y, button_size.cx, button_size.cy);
					}

					//
					// この関数はコンボボックスをカスタマイズします。
					//
					const auto customize_combobox = [](HWND combobox) {
						auto rc = my::get_window_rect(combobox);
						auto dropped_width = my::get_width(rc) * 2;
						::SendMessage(combobox, CB_SETDROPPEDWIDTH, dropped_width, 0);
					};

					{
						// 名前プリセットのコンボボックスを初期化します。
						auto combobox = retrofit.name_preset;
						customize_combobox(combobox);
						for (const auto& preset : table::layer_name.nodes)
							my::combobox::add_text(combobox, preset.layer_name.c_str());
					}
				}
			}

			// ダイアログのサイズを変更します。
			{
				WINDOWPLACEMENT wp = { sizeof(wp) };
				::GetWindowPlacement(hwnd, &wp);
				wp.rcNormalPosition.right += offset.cx;
				wp.rcNormalPosition.bottom += offset.cy + space.cy * 2;
				::SetWindowPlacement(hwnd, &wp);
			}
#if 0
			// コントロールの位置を変更します。
			{
				my::DeferWindowPos dwp;

				for (const auto& control : controls)
				{
					auto rc = control.rc;
					::OffsetRect(&rc, 0, offset.cy);
					dwp.set_window_pos(control, nullptr, &rc, SWP_NOZORDER);
				}
			}
#endif
			return TRUE;
		}

		//
		// ウィンドウプロシージャです。
		//
		virtual LRESULT on_wnd_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param) override
		{
			MY_TRACE_FUNC("{/hex}, {/}, {/hex}, {/hex}", hwnd, my::message_to_string(message), w_param, l_param);

			switch (message)
			{
			case WM_INITDIALOG:
				{
					// スコープ終了時(デフォルト処理の後)に実行します。
					my::scope_exit scope_exit([&]()
					{
						locker_t locker(this);

						if (init_controls(hwnd))
							arrange_controls(hwnd);
					});

					return __super::on_wnd_proc(hwnd, message, w_param, l_param);
				}
			case WM_COMMAND:
				{
					//
					// この関数はコントロールのテキストを変更します。
					//
					const auto set_control_text = [this](const control_t* control, const std::wstring& text)
					{
						if (control)
							::SetWindowTextW(*control, text.c_str());
					};

					// ロックされている場合は何もしません。
					if (is_locked()) break;

					locker_t locker(this);

//					auto control_id = LOWORD(w_param);
					auto code = HIWORD(w_param);
					auto control = (HWND)l_param;

					// コントロールが無効の場合は何もしません。
					if (!control) break;

					if (control == retrofit.name_preset)
					{
						if (code != CBN_SELCHANGE) break;

						// コンボボックスから選択されているプリセットのインデックスを取得します。
						auto index = (size_t)my::combobox::get_cur_sel(control);
						if (index >= table::layer_name.nodes.size()) break;

						// テーブルからプリセットを取得します。
						const auto& preset = table::layer_name.nodes[index];

						// レイヤー名のエディットボックスにプリセットを適用します。
						set_control_text(readymade.name, preset.layer_name);
					}
					else if (control == retrofit.ok)
					{
						MY_TRACE("OKボタンがクリックされました\n");

						// エンターキーをエミュレートします。
						::PostMessage(hwnd, WM_KEYDOWN, VK_RETURN, 0);
					}
					else if (control == retrofit.cancel)
					{
						MY_TRACE("キャンセルボタンがクリックされました\n");

						// エスケープキーをエミュレートします。
						::PostMessage(hwnd, WM_KEYDOWN, VK_ESCAPE, 0);
					}

					break;
				}
			}

			return __super::on_wnd_proc(hwnd, message, w_param, l_param);
		}
	};
}
