#pragma once

namespace apn::preset_adder::dialog
{
	//
	// このクラスは『プロジェクトを新規作成』ダイアログをサブクラス化します。
	//
	struct new_project_t : entity_t
	{
		//
		// このクラスは既存のコントロールです。
		//
		struct readymade_t
		{
			//
			// このクラスはコントロールです。
			//
			struct control_t
			{
				//
				// ウィンドウハンドルです。
				//
				HWND hwnd;

				//
				// 元のコントロール矩形です。
				//
				RECT rc;

				//
				// デフォルトコンストラクタです。
				//
				control_t() {}

				//
				// コンストラクタです。
				//
				control_t(HWND parent, HWND hwnd)
					: hwnd(hwnd)
				{
					rc = my::get_window_rect(hwnd);
					my::map_window_points(nullptr, parent, &rc);
				}

				//
				// HWNDを返します。
				//
				operator HWND() const { return hwnd; }
			};

			control_t name_stc, name;
			control_t video_size_stc, video_width, video_height;
			control_t video_rate_stc, video_rate;
			control_t audio_rate_stc, audio_rate;
/*
			control_t background_color_stc, background_color, background_color_picker;
			control_t horz_border;
*/
			control_t output_size_stc, output_width, output_height;
/*
			control_t output_audio_stc, output_audio;
			control_t tip_stc;
			control_t horz_border_2;
			control_t preset, add_preset;
*/
			control_t ok;
		} readymade = {};

		//
		// 後付けのコントロールです。
		//
		struct retrofit_t {
			HWND preset_stc; // "プリセット"のスタティックコントロールです。
			HWND preset; // "プリセット"のコンボボックスです。
			HWND swap_video_size; // "縦横反転"のチェックボックスです。
			HWND name_preset; // "名前プリセット"のコンボボックスです。
			HWND video_size_preset; // "映像サイズプリセット"のコンボボックスです。
			HWND video_rate_preset; // "映像レートプリセット"のコンボボックスです。
			HWND audio_rate_preset; // "音声レートプリセット"のコンボボックスです。
			HWND cancel; // キャンセルボタンです。
		} retrofit = {};

		//
		// ダイアログをサブクラス化します。
		//
		virtual BOOL subclass(HWND hwnd) override
		{
			// shiftキーが押されている場合は何もしません。
			if (::GetKeyState(VK_SHIFT) < 0) return FALSE;

			//
			// この関数は指定されたウィンドウが対象ではない場合はFALSEを返します。
			//
			const auto is_target = [](HWND hwnd)
			{
				auto window_name = my::get_window_text(hwnd);

				if (match(window_name, hive.dialog_title.new_project)) return TRUE;
				if (match(window_name, hive.dialog_title.new_scene)) return TRUE;
				if (match(window_name, hive.dialog_title.set_scene)) return TRUE;

				return FALSE;
			};

			// 指定されたウィンドウが対象ではない場合は失敗します。
			if (!is_target(hwnd)) return FALSE;

			// ダイアログをサブクラス化します。
			return __super::subclass(hwnd);
		}

		//
		// コントロール配列を初期化します。
		//
		BOOL init_controls(HWND hwnd)
		{
			MY_TRACE_FUNC("{/hex}", hwnd);

			//
			// この関数は指定された条件の既存のコントロールを返します。
			//
			constexpr auto find_window = [](HWND parent, HWND after, LPCWSTR class_name, LPCWSTR window_name)
			{
				return readymade_t::control_t { parent, ::FindWindowExW(parent, after, class_name, tr(L"Dialog", window_name)) };
			};

			//
			// この関数は指定された条件の既存のコントロールを返します。
			//
			constexpr auto get_window = [](HWND parent, HWND hwnd, UINT cmd)
			{
				return readymade_t::control_t { parent, ::GetWindow(hwnd, cmd) };
			};

			// 「名前」関連のコントロールを取得します。
			readymade.name_stc = find_window(hwnd, nullptr, WC_STATICW, L"名前");
			readymade.name = get_window(hwnd, readymade.name_stc, GW_HWNDNEXT);

			// 「解像度」関連のコントロールを取得します。
			readymade.video_size_stc = find_window(hwnd, nullptr, WC_STATICW, L"解像度");
			readymade.video_width = get_window(hwnd, readymade.video_size_stc, GW_HWNDNEXT);
			readymade.video_height = get_window(hwnd, readymade.video_width, GW_HWNDNEXT);

			// 「フレームレート」関連のコントロールを取得します。
			readymade.video_rate_stc = find_window(hwnd, nullptr, WC_STATICW, L"フレームレート");
			readymade.video_rate = get_window(hwnd, readymade.video_rate_stc, GW_HWNDNEXT);

			// 「サンプリングレート」関連のコントロールを取得します。
			readymade.audio_rate_stc = find_window(hwnd, nullptr, WC_STATICW, L"サンプリングレート");
			readymade.audio_rate = get_window(hwnd, readymade.audio_rate_stc, GW_HWNDNEXT);

			// 「出力リサイズ」関連のコントロールを取得します。
			readymade.output_size_stc = find_window(hwnd, nullptr, WC_STATICW, L"出力リサイズ");
			readymade.output_width = get_window(hwnd, readymade.output_size_stc, GW_HWNDNEXT);
			readymade.output_height = get_window(hwnd, readymade.output_width, GW_HWNDNEXT);

			// 「OK」ボタンを取得します。
			readymade.ok = find_window(hwnd, nullptr, WC_BUTTONW, L"OK");

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
				my::get_width(readymade.video_rate.rc),
				my::get_height(readymade.video_rate.rc),
			};

			// 余白サイズを取得します。
			auto space = SIZE {
				readymade.video_height.rc.left - readymade.video_width.rc.right,
				readymade.video_rate.rc.top - readymade.video_width.rc.bottom,
			};

			// 移動予定のオフセットサイズを取得します。
			auto offset = SIZE {
				base.cx + space.cx,
				base.cy + space.cy,
			};

			// ダイアログのサイズを変更します。
			{
				WINDOWPLACEMENT wp = { sizeof(wp) };
				::GetWindowPlacement(hwnd, &wp);
				wp.rcNormalPosition.right += offset.cx;
				wp.rcNormalPosition.bottom += offset.cy;
				::SetWindowPlacement(hwnd, &wp);
			}

			// 既存のコントロールの位置を変更します。
			{
				// コントロールの位置を一括変更するために使用します。
				my::DeferWindowPos dwp;

				//
				// この関数は既存のコントロールの位置を変更します。
				//
				const auto func = [&](HWND child) -> BOOL
				{
					MY_TRACE_HWND(child);

					// 直接の子ウィンドウではない場合は除外します。
					if (::GetParent(child) != *this) return TRUE;

					// コントロールのウィンドウ矩形を取得します。
					auto rc = my::get_window_rect(child);

					// 親ウィンドウ(ダイアログ)の座標系に変換します。
					my::map_window_points(nullptr, *this, &rc);

					// 「OK」ボタンの場合は
					if (child == readymade.ok)
					{
						auto w = my::get_width(rc);
						auto h = my::get_height(rc);

						rc.left = client_rc.right + offset.cx - (w + space.cx * 2) * 2;
						rc.top = client_rc.bottom + offset.cy - (h + space.cy * 2);
						rc.right = rc.left + w;
						rc.bottom = rc.top + h;
					}
					// それ以外のコントロールの場合は
					else
					{
						// オフセットの分だけずらします。
						::OffsetRect(&rc, 0, offset.cy);
					}

					// コントロールのウィンドウ位置を変更します。
					dwp.set_window_pos(child, nullptr, &rc, SWP_NOZORDER);

					// 列挙を続けます。
					return TRUE;
				};

				// 既存のコントロールを列挙します。
				::EnumChildWindows(hwnd, [](HWND child, LPARAM l_param) -> BOOL
				{
					// 関数を取得します。
					auto p = (decltype(&func))l_param;

					// 関数を実行します。
					return (*p)(child);
				},
				(LPARAM)&func);
			}

			// 追加のコントロールを作成します。
			{
				// 既存のコントロールのフォントを取得します。
				auto font = (HFONT)::SendMessage(readymade.ok, WM_GETFONT, 0, 0);

				// 追加コントロールの基準X座標です。
				auto x = readymade.video_height.rc.right + space.cx;

				{
					// Y座標の基準となるコントロール(一番上のコントロール)です。
					auto base_control = readymade.name_stc ? readymade.name_stc : readymade.video_size_stc;

					// 追加コントロールの基準Y座標です。
					auto y = base_control.rc.top;

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

					retrofit.preset_stc = create_control(
						WC_STATICW, tr(L"プリセット"), SS_CENTERIMAGE, readymade.video_size_stc.rc.left, y,
						my::get_width(readymade.video_size_stc.rc), my::get_height(readymade.video_size_stc.rc));
					retrofit.preset = create_combobox(readymade.video_width.rc.left, y, base.cx, base.cy);
					retrofit.swap_video_size = create_control(
						WC_BUTTONW, tr(L"縦横反転"), BS_AUTOCHECKBOX, x, y, base.cx, base.cy);
					if (readymade.name_stc)
						retrofit.name_preset = create_combobox(x, readymade.name_stc.rc.top + offset.cy, base.cx, base.cy);
					retrofit.video_size_preset = create_combobox(x, readymade.video_size_stc.rc.top + offset.cy, base.cx, base.cy);
					retrofit.video_rate_preset = create_combobox(x, readymade.video_rate_stc.rc.top + offset.cy, base.cx, base.cy);
					retrofit.audio_rate_preset = create_combobox(x, readymade.audio_rate_stc.rc.top + offset.cy, base.cx, base.cy);

					{
						auto w = my::get_width(readymade.ok.rc);
						auto h = my::get_height(readymade.ok.rc);
						auto x = client_rc.right + offset.cx - (w + space.cx * 2);
						auto y = client_rc.bottom + offset.cy - (h + space.cy * 2);

						retrofit.cancel = create_control(WC_BUTTONW, tr(L"Dialog", L"キャンセル"), BS_PUSHBUTTON, x, y, w, h);
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
						// (全体の)プリセットのコンボボックスを初期化します。
						auto combobox = retrofit.preset;
						customize_combobox(combobox);
						for (const auto& preset : table::project.nodes)
						{
							if (preset.display_name.empty())
							{
								if (preset.scene_name.length())
								{
									my::combobox::add_text(combobox,
										my::format(L"{/}, {/} x {/} px, {/} fps, {/} Hz",
											preset.scene_name,
											preset.video_width, preset.video_height,
											preset.video_rate, preset.audio_rate).c_str());
								}
								else
								{
									my::combobox::add_text(combobox,
										my::format(L"{/} x {/} px, {/} fps, {/} Hz",
											preset.video_width, preset.video_height,
											preset.video_rate, preset.audio_rate).c_str());
								}
							}
							else
							{
								my::combobox::add_text(combobox, preset.display_name.c_str());
							}
						}
					}

					{
						// 名前プリセットのコンボボックスを初期化します。
						auto combobox = retrofit.name_preset;
						customize_combobox(combobox);
						for (const auto& preset : table::scene_name.nodes)
							my::combobox::add_text(combobox, preset.scene_name.c_str());
					}

					{
						// 映像サイズプリセットのコンボボックスを初期化します。
						auto combobox = retrofit.video_size_preset;
						customize_combobox(combobox);
						for (const auto& preset : table::video_size.nodes)
						{
							if (preset.display_name.empty())
							{
								my::combobox::add_text(combobox,
									my::format(L"{/} x {/}", preset.video_width, preset.video_height).c_str());
							}
							else
							{
								my::combobox::add_text(combobox, preset.display_name.c_str());
							}
						}
					}

					{
						// 映像レートプリセットのコンボボックスを初期化します。
						auto combobox = retrofit.video_rate_preset;
						customize_combobox(combobox);
						for (const auto& preset : table::video_rate.nodes)
						{
							if (preset.display_name.empty())
							{
								my::combobox::add_text(combobox,
									my::format(L"{/}fps", preset.video_rate).c_str());
							}
							else
							{
								my::combobox::add_text(combobox, preset.display_name.c_str());
							}
						}
					}

					{
						// 音声レートのコンボボックスを初期化します。
						auto combobox = retrofit.audio_rate_preset;
						customize_combobox(combobox);
						for (const auto& preset : table::audio_rate.nodes)
						{
							if (preset.display_name.empty())
							{
								my::combobox::add_text(combobox,
									my::format(L"{/}Hz", preset.audio_rate).c_str());
							}
							else
							{
								my::combobox::add_text(combobox, preset.display_name.c_str());
							}
						}
					}
				}
			}

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
						my::locker_t locker(this);

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
					const auto set_control_text = [this](HWND control, const std::wstring& text)
					{
						// コントロールとテキストがどちらも有効の場合は
						if (::IsWindowEnabled(control) && text.length())
						{
							// コントロールのテキストを変更します。
							::SetWindowTextW(control, text.c_str());
						}
					};

					//
					// この関数は映像サイズのコントロールを返します。
					//
					const auto get_video_size_controls = [this]()
					{
						// 映像サイズのコントロールを取得します。
						auto* video_width = &readymade.video_width;
						auto* video_height = &readymade.video_height;

						// 映像サイズのコントロールが無効状態の場合は
						if (!::IsWindowEnabled(*video_width) || !::IsWindowEnabled(*video_height))
						{
							// 出力サイズのコントロールを取得します。
							video_width = &readymade.output_width;
							video_height = &readymade.output_height;
						}

						// 縦横反転にチェックが入っている場合はコントロールを入れ替えます。
						return (::SendMessage(retrofit.swap_video_size, BM_GETCHECK, 0, 0) == BST_CHECKED) ?
							std::make_pair(video_height, video_width) : std::make_pair(video_width, video_height);
					};

					// ロックされている場合は何もしません。
					if (is_locked()) break;

					my::locker_t locker(this);

//					auto control_id = LOWORD(w_param);
					auto code = HIWORD(w_param);
					auto control = (HWND)l_param;

					// コントロールが無効の場合は何もしません。
					if (!control) break;

					if (control == retrofit.preset)
					{
						if (code != CBN_SELCHANGE) break;

						// コンボボックスから選択されているプリセットのインデックスを取得します。
						auto index = (size_t)my::combobox::get_cur_sel(control);
						if (index >= table::video_size.nodes.size()) break;

						// テーブルからプロジェクトのプリセットを取得します。
						const auto& preset = table::project.nodes[index];

						// プロジェクトのプリセットを適用します。
						{
							auto video_size = get_video_size_controls();

							set_control_text(*video_size.first, preset.video_width);
							set_control_text(*video_size.second, preset.video_height);

							set_control_text(readymade.video_rate, preset.video_rate);
							set_control_text(readymade.audio_rate, preset.audio_rate);

							if (readymade.name)
								set_control_text(readymade.name, preset.scene_name);
						}
					}
					else if (control == retrofit.name_preset)
					{
						if (code != CBN_SELCHANGE) break;

						// コンボボックスから選択されているプリセットのインデックスを取得します。
						auto index = (size_t)my::combobox::get_cur_sel(control);
						if (index >= table::scene_name.nodes.size()) break;

						// テーブルからシーン名のプリセットを取得します。
						const auto& preset = table::scene_name.nodes[index];

						// シーン名のプリセットを適用します。
						{
							if (readymade.name)
								set_control_text(readymade.name, preset.scene_name);
						}
					}
					else if (control == retrofit.video_size_preset)
					{
						if (code != CBN_SELCHANGE) break;

						// コンボボックスから選択されているプリセットのインデックスを取得します。
						auto index = (size_t)my::combobox::get_cur_sel(control);
						if (index >= table::video_size.nodes.size()) break;

						// テーブルから映像サイズのプリセットを取得します。
						const auto& preset = table::video_size.nodes[index];

						// 映像サイズのプリセットを適用します。
						{
							auto video_size = get_video_size_controls();

							set_control_text(*video_size.first, preset.video_width);
							set_control_text(*video_size.second, preset.video_height);
						}
					}
					else if (control == retrofit.video_rate_preset)
					{
						if (code != CBN_SELCHANGE) break;

						// コンボボックスから選択されているプリセットのインデックスを取得します。
						auto index = (size_t)my::combobox::get_cur_sel(control);
						if (index >= table::video_rate.nodes.size()) break;

						// テーブルから映像レートのプリセットを取得します。
						const auto& preset = table::video_rate.nodes[index];

						// 映像レートのプリセットを適用します。
						{
							set_control_text(readymade.video_rate, preset.video_rate);
						}
					}
					else if (control == retrofit.audio_rate_preset)
					{
						if (code != CBN_SELCHANGE) break;

						// コンボボックスから選択されているプリセットのインデックスを取得します。
						auto index = (size_t)my::combobox::get_cur_sel(control);
						if (index >= table::audio_rate.nodes.size()) break;

						// テーブルから音声レートのプリセットを取得します。
						const auto& preset = table::audio_rate.nodes[index];

						// 音声レートのプリセットを適用します。
						{
							set_control_text(readymade.audio_rate, preset.audio_rate);
						}
					}
					else if (control == retrofit.swap_video_size)
					{
						if (code != BN_CLICKED) break;

						// 映像サイズの縦横を入れ替えます。
						{
							auto video_size = get_video_size_controls();

							auto first = my::get_window_text(*video_size.first);
							auto second = my::get_window_text(*video_size.second);

							::SetWindowTextW(*video_size.first, second.c_str());
							::SetWindowTextW(*video_size.second, first.c_str());
						}
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
