= 状態管理とは？
#@# イラスト
//abstract{
#@# textlint-disable
  今回、状態管理で使用するのはGetX（状態管理だけではないですが・・）です。

  では、「状態管理」とはいったい何を指していて、なぜ必要なのでしょうか？
#@# textlint-enable
//}


//makechaptitlepage[toc=on]

== 状態管理とは？

IT業界での状態管理（英語では-State Management-）の「状態（State）」は、
アプリケーションの一部で、たとえば、

 * データベースで管理しているデータ
 * ブラウザで発生するイベント、表示している色、形

です。それらは、バックエンド、データベース、フロントエンドのコンポーネントなど、アプリケーションのどこにでもあります。

たとえば、スマートフォンで表示しているボタンの色や形状などです。

//blankline
それでは、状態を管理する「状態管理」とは何なのでしょうか？

//blankline
「State-Management」とは、デザインパターンによる実装で、
アプリケーションのあちこちに散らばる状態をすべてのコンポーネントで状態を同期させ、
「サービスの実装」や「データベースからのデータの取扱」を楽にすること。

//blankline
だ、そうです。

//blankline
上記の例ですと、ボタンの形を変えるためにAモジュールへアクセスし、色を変えるためBモジュールへアクセスするような実装ではなく
ボタンの状態を管理するモジュールがあれば、そこへアクセスするだけで良いとする実装を指します。

== 状態管理ライブラリ

Reactでも同様ですが状態を管理するライブラリは、たいていの場合、戦国時代の武将のように
湧いてきて、戦いの後は、「ひとりの絶大な勝者」と「2〜3人ほどの生き残り」となります。
その後時間が経過すると、この状況に不満をもつ新興勢力が台頭してきます。

//blankline
Flutterの世界も同様で、現在は戦いの終盤戦に近付いているのではないでしょうか？

//blankline
Flutterの公式サイトでも
@<href>{https://docs.flutter.dev/development/data-and-backend/state-mgmt/options, 状態管理のライブラリ}
を公開しています。しかし、公式サイトですので、どれが良いなどとは口が裂けてもいえない状況にあります。

//blankline
コードを書く人は、たいていの場合どのライブラリが良いかを議論しません。過去の経験から「宗教戦争」になると心得ているからです。しかし、内心では、
「状態管理といえば、XXX一択！」と思っています。

//blankline
本書では、GetXを使いますが、Riverpod推しやProvider推しの方はお許しください。


== GetXを使っての状態管理の解説

それでは、Flutterのスタートアッププロジェクトを使って説明します。

=== スタートアッププロジェクト
//blankline
下図は、Android Studioで新規プロジェクトを作成しエミュレータでデバッグしているところです。


//image[ch01_01_state_management][][scale=0.7 ,pos=H]

お馴染みのスタートアッププロジェクトが作成されており、FAB（フローティング・アクション・ボタン）をクリックすると表示されているカウンタが増えていきます。

//blankline
コードを見ると、

 * 状態を保持するStateを継承した状態管理setStateを使用
 * データ保持用変数「_counter」を持っている
 * データを操作する「_incrementCounter」ビジネスロジックを持っている。
 * データを表示する「Text Widget」を持っている。

つまり、表示用コード、データ、ビジネスロジックが同居しています。別なページから、このデータにアクセスするためにはどのようにするのでしょうか？

=== GetXを導入

GetX（あくまで本書では）を導入し状態管理を。

//blankline
ご覧のように、データ、ビジネスロジックとも外部に移動しています。

//image[ch01_02_state_management][][scale=0.7 ,pos=H]

データ表示部にエラーが出ているのは、表示部分に状態管理を適用していないためです。


//image[ch01_03_state_management][][scale=0.7 ,pos=H]

表示部に状態管理「GetBuilder」を適用するとデータが表示されています。実は、GetBuilder自体は、StatefulWidgetを継承していて
GetBuilder自体が状態を保持しています。

//list[][GetBuilderの正体]{
  class GetBuilder<T extends GetxController> extends StatefulWidget {
  final GetControllerBuilder<T> builder;
  final bool global;
  final Object? id;
  final String? tag;
  final bool autoRemove;
  final bool assignId;
  final Object Function(T value)? filter;
  final void Function(GetBuilderState<T> state)? initState,
      dispose,
      didChangeDependencies;
  final void Function(GetBuilder oldWidget, GetBuilderState<T> state)?
      didUpdateWidget;
  final T? init;

  const GetBuilder({
    Key? key,
    this.init,
    this.global = true,
    required this.builder,
    this.autoRemove = true,
    this.assignId = false,
    this.initState,
    this.filter,
    this.tag,
    this.dispose,
    this.id,
    this.didChangeDependencies,
    this.didUpdateWidget,
  }) : super(key: key);
//}

//blankline

==== 状態管理をしているコントローラ

状態管理をしているコントローラは、こんな風になっています。

//image[ch01_04_state_management][][scale=0.7 ,pos=H]

コントローラは、「GetXコントローラ」を継承し、データとビジネスロジックを持っています。
ビジネスロジック「increment」に「update()」が含まれているのは、「GetBuilder」に、
//blankline
　　状態が変化したので表示を書き換えてね。お願いっ！
//blankline
と通知するためです。

//blankline
状態が変化すると、自動で再描画する「GetX<>」、「Obx()」のような優秀なのもいます。
しかし、優秀なのは、それなりにメモリを使う・CPUを使うなどリソースを使います。

//blankline
==== 何がうれしいのか？

では、状態管理コントローラを導入したメリットは何でしょうか？

 1. データとビジネスロジックを一ヵ所にまとめたので、変更があっても一ヵ所。
 2. 状態管理コントローラを増やしても、表示部のコード変更は最小です。
 2. 別なページにデータを簡単に渡せる。
 3. データと表示ページには関連がないので、ページを再表示してもデータ再取得がない。

と、たくさんのメリットがあります。

//blankline
===== 表示を増やしてみた

表示部を2つ、それぞれを操作するボタンを2つにしましたが、状態管理コントローラをひとつ増やしただけです。
こちらには、優秀な「GetX<コントローラ型>」を使って表示しています。
//image[ch01_05_state_management][][scale=0.7 ,pos=H]

//blankline
==== 状態管理コントローラの別インスタンス

同じデータ型、同じビジネスロジックをもつのなら、状態管理コントローラの別インスタンスで管理できます。
インスタンスが別ですので、それぞれの操作で、それぞれのデータを管理できます。

//image[ch01_06_state_management][][scale=0.7 ,pos=H]

//blankline
==== 別ページでも同じ状態管理コントローラへアクセス

ページ移動しても、アプリケーション全体で状態管理コントローラは動作していますので、
状態管理コントローラへアクセスすれば、先ほどまでのデータを取得できます。

//image[ch01_07_state_management][][scale=0.7 ,pos=H]


//image[ch01_09_state_management_second_page][][scale=0.7 ,pos=H]

ここでデータを操作し変化させます。

//image[ch01_10_state_management_second_page][][scale=0.7 ,pos=H]

元ページに戻っても、アクセスしている状態管理コントローラのデータを取得しますので、データは最新です。

//image[ch01_11_state_management_back_page][][scale=0.7 ,pos=H]

==== FABはひとつ。

Flutterで推奨されているMaterial Designでは、FABが複数あることを推奨していません。今回は、状態管理の解説のため簡易的にです。

//image[ch01_08_state_management_fab_error][][scale=0.7 ,pos=H]
