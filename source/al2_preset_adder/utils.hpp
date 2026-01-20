#pragma once

namespace apn::preset_adder
{
	//
	// 指定された文字列が指定された正規表現パターンにマッチする場合はTRUEを返します。
	//
	inline BOOL match(const std::wstring& text, const std::wstring& pattern)
	{
		if (pattern.empty()) return FALSE;

		return std::regex_search(text, std::wregex(pattern));
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
