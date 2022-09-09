= 認証関連画面の作成

//abstract{
Flutterで作成するUI部分は、すべてWidgetと呼ばれる部品を組み合わせて作成します。

//blankline
HTMLでは、<div>タグの中に複数のHTMLタグを入れてUIを組み立てます。入れ子になったHTMLタグもあります。

//blankline
Flutterも同じようにWidgetを組合せてUIを構築します。

//}

//makechaptitlepage[toc=on]

== UIについて
本書では、一画面に表示されるもの全体を指してページと呼びます。

//blankline
概要でも少し説明していますが、ページはWidgetと呼ぶ部品を組み合わせて作成します。Flutterの公式（SDKに含まれている）Widgetもありますし、
世界中の開発者が作成したもが集めてあるサイトもあります。

//blankline
もちろん自分で作成することもできます。

//blankline
色、形、ドロップシャドウなどのデザインに関するものは、ThemeData（HTMLで言えば、全体に適用されるCSS）が適用され、
個別のWidgetでもスタイルを適用できます。

//blankline
下記のサイト「
@<href>{https://flutterawesome.com/, Flutter Awesome}」では、UIやアプリが沢山公開されており、そのほどんどはGitHubなどでソースコードを入手できます。
実際に手元で動かし、変更を加えてみればWidgetの使い方も理解が進みます。
//image[flutterawesome][][scale=0.7, pos=H]


== ログインプログラム
今回使用するのは、上記FlutterAwesomeで見つけたログイン関連のアプリ
@<href>{https://flutterawesome.com/flutter-login-ui-with-splash-screen-and-multiple-color-support/, Flutter Login UI} です。

//image[flutterawesome02][][scale=0.7, pos=H]

このサイトは、Videoチュートリアルのリンクもあり、クリックするとYoutubeで作成過程を見ることができます。
YoutubeのVideoチュートリアルの詳細には、同じデザインですが別のGitHubへのリンクがありました。

//blankline
今回は、
@<href>{https://github.com/FlutterTutorialNet/flutter_login_ui, こちら}を使うことにします。


=== 元プロジェクトの確認
//blankline
クローンして魔改造しても良いのですが、勉強も兼ねて写経することにします。Android Studioでコードを書くと、
linterがエラー（インストールされていないパッケージのWidgetなど）がでます。そのため、元プロジェクトの「pubspec.yaml」を開き
インストールされているパッケージを確認します。

//list[][pubspec.yaml]{
dependencies:
  flutter:
    sdk: flutter


  # The following adds the Cupertino Icons font to your application.
  # Use with the CupertinoIcons class for iOS style icons.
  cupertino_icons: ^1.0.2
  hexcolor: ^2.0.4
  font_awesome_flutter: ^9.1.0
  otp_text_field: ^1.1.1
//}

//blankline
使用されているプラグインは、

 * hexcolor -- https://pub.dev/packages/hexcolor
 * font_awesome_flutter -- https://pub.dev/packages/font_awesome_flutter
 * otp_text_field -- https://pub.dev/packages/otp_text_field

の3つです。

=== プロジェクトへ適用

それでは、元プロジェクトをパクっていきましょう。

//blankline
最初にプラグインをインストールします。

//terminal[][プラグインのインストール]{
 > flutter pub add hexcolor font_awesome_flutter otp_text_field
Resolving dependencies...
+ flutter_web_plugins 0.0.0 from sdk flutter
+ font_awesome_flutter 10.2.1
+ hexcolor 2.0.7
+ js 0.6.4
  material_color_utilities 0.1.5 (0.2.0 available)
+ otp_text_field 1.1.3
  source_span 1.9.0 (1.9.1 available)
  test_api 0.4.12 (0.4.13 available)
  vector_math 2.1.2 (2.1.3 available)
Downloading font_awesome_flutter 10.2.1...
Changed 5 dependencies!

//}

後は、写経するか、コピペするかでファイルを作成します。フォルダ、ファイルの位置は後々変更することとし、今は元プロジェクトと同じにしておきます。

//image[project_files][][scale=0.5, pos=H]


//blankline
lintでWarningが沢山出ていますが、コントローラーを追加した後すべてのページを、

 * StatefulWidgetからStatelessWidgetへ変更
 * タイトル、入力フィールドなどの文字を日本語化

//blankline
しましので、そのときに修正します。

//blankline
エミュレータで確認すると、以下のように取り入れることが出来ました。
//image[base_project][desc][scale=0.8, pos=H]

//blankline
ここまでのコードは、以下から取得できます。

//note[ここまでのソースコード]{
//terminal[][GitHub]{
　>git clone -b 01_login_screens_import https://github.com/risingforce9zz/tfreemarket.git
//}
//}