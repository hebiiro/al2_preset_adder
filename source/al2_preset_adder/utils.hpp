#pragma once

namespace apn::preset_adder
{
	//
	// 指定されたダイアログのタイトルがマッチする場合はTRUEを返します。
	//
	inline BOOL match(const std::wstring& window_name, const std::wstring& raw_title)
	{
		// ダイアログのタイトルを翻訳します。
		auto title = tr(L"Dialog", raw_title);

		// タイトルの比較結果を返します。
		return window_name == title;
	};

	//
	// 文字列をトリムします。
	// https://www.paveway.info/entry/2019/09/29/cpp_trim
	//
	inline static std::wstring trim(const std::wstring& src, const std::wstring& trim_characters = L"\xfeff\r\n \t")
	{
		// trimするとき削除する文字以外の最初の文字の位置を取得します。
		size_t start = src.find_first_not_of(trim_characters);
		if (start == std::wstring::npos) return L"";

		// trimするとき削除する文字以外の最後の文字の位置を取得します。
		size_t end = src.find_last_not_of(trim_characters);
		if (end == std::wstring::npos) return L"";

		// trimするとき削除する文字以外の文字列を切り出します。
		return src.substr(start, end - start + 1);
	}

	//
	// 文字列を分割して配列にして返します。
	//
	inline std::vector<std::wstring> split(const std::wstring& str, wchar_t delimiter)
	{
		std::vector<std::wstring> vec;
		std::wstringstream ss(str);
		std::wstring buffer;
		while (std::getline(ss, buffer, delimiter)) vec.emplace_back(buffer);
		return vec;
	}
}
