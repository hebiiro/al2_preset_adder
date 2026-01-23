# 🎉AviUtl2プリセット追加MOD

* aviutl2の`プロジェクトを新規作成`ダイアログなどにプリセットを追加するMODです。
* aviutl2の汎用プラグインの形式になっていますが、実際には見た目を変えるタイプのMODです。

!["スクリーンショット"](images/r1.png)

## 🚧注意事項

* `データフォルダ`とは`C:\ProgramData\aviutl2`または`aviutl2.exeがあるフォルダ\data`のことです。
* `プラグインフォルダ`とは`データフォルダ\Plugin`のことです。

> [!IMPORTANT]
> * aviutl2のバージョンによってはダイアログのレイアウトが崩れる場合があります。

## 🚀インストール

* `プラグインフォルダ`に以下のファイルを入れてください。
	* `al2_preset_adder.aux2`
	* `al2` (フォルダ)
		* `assets` (フォルダ)
			* `al2_preset_adder` (フォルダ) ✏️ここにプリセットの初期値が入っています。
				* `project.tsv` (プロジェクト)
				* `video_size.tsv` (映像サイズ)
				* `video_rate.tsv` (フレームレート)
				* `audio_rate.tsv` (サンプリングレート)
				* `scene_name.tsv` (シーン名)
				* `layer_name.tsv` (レイヤー名)
	* (上記ファイルはzipファイル内の`Plugin`フォルダに入っています)

## 🔥アンインストール

* `プラグインフォルダ`から以下のファイルを削除してください。
	* `al2_preset_adder.aux2`
	* `al2/config/al2_preset_adder.json`
	* `al2/config/al2_preset_adder` (フォルダ)
	* `al2/assets/al2_preset_adder` (フォルダ)

## 💡使い方

1. aviutl2でプロジェクトを新規作成します。
1. 自動的に`プロジェクトを新規作成`ダイアログが拡張され、プリセットが追加されているはずです。
1. プリセットを選択してダイアログの数値を変更します。
---
* `シーンを作成`・`シーンの設定`・`レイヤー名を変更`ダイアログも同じように操作します。

### 🏷️プリセットをカスタマイズする

1. aviutl2を終了すると`al2/config/al2_preset_adder`内にtsvファイルが作成されます。
1. これをテキストエディタで編集してください。**※文字コードはutf-8です。**

### 🏷️設定を初期化する

1. aviutl2を起動していない状態で以下のファイルを削除してください。
	* `al2/config/al2_preset_adder.json`
	* `al2/config/al2_preset_adder` (フォルダ)

## 🔧設定

* `プリセット追加`ウィンドウで設定します。
---
* `ダイアログ名のパターン`
	* 各ダイアログ名を正規表現のパターンで指定します。
	* aviutl2を翻訳して使用している場合はそれに合わせて変更してください。
	* 特定のダイアログを除外したい場合は、先頭に`x`などを入れて意図的にマッチしないようにしてください。

## 🔖更新履歴

* 🔖r1 #2026年01月23日
	* 🎉初版

## ⚗️動作確認

* AviUtl ExEdit2 beta29 https://spring-fragrance.mints.ne.jp/aviutl/

## 💳クレジット

* AviUtl ExEdit2 Plugin SDK https://spring-fragrance.mints.ne.jp/aviutl/
* Microsoft Research Detours Package https://github.com/microsoft/Detours
* JSON for Modern C++ https://github.com/nlohmann/json

## 👽️作成者情報
 
* 作成者 - 蛇色 (へびいろ)
* GitHub - https://github.com/hebiiro
* X - https://x.com/io_hebiiro

## 🚨免責事項

この作成物および同梱物を使用したことによって生じたすべての障害・損害・不具合等に関しては、私と私の関係者および私の所属するいかなる団体・組織とも、一切の責任を負いません。各自の責任においてご使用ください。
