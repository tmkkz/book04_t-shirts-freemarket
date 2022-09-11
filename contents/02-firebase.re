= Firebaseとは？

//abstract{
  もともとは、オンラインチャット機能をWebサイトに統合するAPIを提供していたスタートアップEnvolveが、
  ユーザーがチャットではなくゲームデータをリアルタイムに交換しているのをみて、
  別会社Firebaseを設立しiOS、Android、Webでアプリケーションデータを同期する「Firebase Realtime Database」を発表する。

//blankline
この製品を中心とし、「Firebase Hosting」、「Firbase Authentication」を合わせモバイル・バックエンドサービスを提供していた。

//blankline
ネットの世界では、スタートアップはツブされるか買収されるかの2択ですので、結局Googleに買収されてしまう。

//blankline
Googleは、さらにサービスを追加しモバイル・バックエンド・サービス、サーバレス・アーキテクチャの勝者となります。
//}

//makechaptitlepage[toc=on]

== Firebaeを使ってみる

Firebaseは、個別にたくさんのサービスを提供しています。いきなりFirebaseを使うと言っても、どのサービスを使ってよいものかもわかりません。

//blankline
使い方は、

 * プロジェクトを開始し、
 * その都度、必要なサービスを追加

 します。

//blankline
Googleアカウントがあれば、スグに使い始めることができますし、ある程度の使用量は無償です。

//image[firebase00][][scale=0.7 ,pos=H]

料金については、

Firebase Authentication（認証）では、以下のようにアクティブユーザーが月間5万人まで無料です。

//image[firebase00-1][][scale=0.7 ,pos=H]

Realtime Databaseでは、保存するデータが1GBまで無料です。ただし、ダウンロードされるデータは10GBまです。

//blankline
実際に作成してデータをみていただくと、Reatime Databaseに保存されるデータは、巨大なJSONファイルですので
文字列で1GBとなると、相当量です。

//image[firebase00-2][][scale=0.7 ,pos=H]

無料から有料へは、いつでも切り替えることができますし、使用量が減れば無料プランへ戻ることもできます。

=== Firebaseコンソールへ

「コンソールへ移動」をクリックすると、Firebaseコンソールトップへ移動します。ここで「+プロジェクトを追加」をクリックして新規プロジェクトを作成します。

//image[03_firebase02][][scale=0.7 ,pos=H]
#@# textlint-disable
最初にプロジェクトの名前を付けます。使える文字は半角英数、スペース、-!'"の記号4つです。[続行]ボタンをクリックします。
#@# textlint-enable

//image[03_firebase03][][scale=0.7 ,pos=H]

Googleアナリティクスの画面になります。使う場合にはAndorid向けSDKのバージョンが19となります。

//image[03_firebase04][][scale=0.7 ,pos=H]

アナリティクスのアカウントを選択するか、作成します。[プロジェクトを作成]ボタンをクリックすると作成開始します。
//image[03_firebase05][][scale=0.7 ,pos=H]

作成中です。
//image[03_firebase06][][scale=0.7 ,pos=H]

プロジェクトができあがりました。
//image[03_firebase07][][scale=0.7 ,pos=H]

サイドバーにある[構築]ドロップダウンを開くと、追加できるサービスが表示されます。
//image[03_firebase08][][scale=0.7 ,pos=H]

最初に、「Authentication」をクリックし認証サービスを追加します。
//image[03_firebase09][][scale=0.7 ,pos=H]

認証サービスのトップ画面に移動します。[始める]ボタンをクリックします。
//image[03_firebase10][][scale=0.7 ,pos=H]

ログイン方法（ログインプロバイダ）の選択画面になります。最初は、「メール/パスワード」を選択します。
//image[03_firebase11][][scale=0.7 ,pos=H]

「メール/パスワード」を有効にし[保存]ボタンをクリックします。
//image[03_firebase12][][scale=0.7 ,pos=H]

「新しいプロバイダ追加」ボタンをクリックします。
//image[03_firebase13][][scale=0.7 ,pos=H]

以上で「メール/パスワード」での認証が可能になりました。


=== Firebase認証とは？

作成したプロジェクトに対して、

 * メール/パスワードでのアカウント新規作成・ログイン
 * Googleアカウントでのログイン
 * Twitter、AppleID、GitHubなどのSNSサービスでのログイン

ができます。

ログイン状態になると、そのプロジェクトに追加したサービスの細かなアクセス制限ができます。

//blankline
通常のアプリケーションで認証サービスを実現しようとすると、セキュリティが問題になりますが
Firebase Authenticationで解放されます。

//blankline
また、クライアントプログラムも各言語用のライブラリが提供されています。

次の章からは、オンライン・フリーマーケットの認証部分を作成していきます。
