= はじめに

このたびは、「0円で、モバイルアプリ作るお〜！」を手にしていただき、誠にありがとうございます。

//image[yaruo_pre0001][][scale=0.4, pos=H]

//blankline
今回も、tkg様の開発された「AAスレ作成アプリAAストーリーボード」を使わせていただいます。
tkg様始めたくさんのAAを投稿されている皆様へ感謝しています。

//image[r401][][scale=0.4,pos=H]

//blankline
今回紹介させていただいている「Flutter」ですが、驚くほど簡単にモバイルアプリを作成できます。
「Flutter」がどんなものかをサクッと知りたい方は、以下の@<href>{https://youtu.be/5fH6__PAi6A, Youtube動画}がお勧めです。10分ほどの動画ですが
「Flutter」の概要が分かります。

//image[flutter_youtube][][scale=0.5,pos=H]

実は、私は「React、Redux、Electron」を使いMac、Windows用のデスクトップアプリを開発していました。
その縁で「ReactNative」に乗り換えようとしたのですが、開発環境の作成で挫折しました。

//blankline
いえ、別に「ReactNative」をディスるつもりはありません。

//blankline
誰でもが簡単にモバイルアプリを作成できるようになり、おもしろいアプリが世の中に溢れるとよいですね。

//blankline
本書は、

 * Flutter -- 開発環境
 * Firebase -- 認証、データベース、クラウドストレージ、メッセージング
 * GetX -- 状態管理（ReactでのRedux、Recoil、Jotaiのようなもの）

 を使いオンライン・フリーマーケットを作成します。

//image[yaruo_pre0002][][scale=0.5, pos=H]

//blankline
E-mail、Twitterアカウント、Googleアカウント、AppleIDでの自分のオンラインショップを作成し、
商品の登録、管理、販売ができます。サンプルアプリですので決済までは含んでいません。

//blankline
構成は、

 1. （本書 Vol.1）アカウント作成と認証。
 2. （次号 Vol.2）ストア情報の管理、商品登録・管理
 3. （Vol.3） 商品管理、販売カート
 4. （Vol.4） 販売・在庫切れなどの通知

と、なります。

//blankline
とても難しそうですが、FlutterはGoogleがオープンソースで公開している開発フレームワークです。そのため
世界中の開発者が、

 * GitHubなどでアプリのソース公開
 * YouTubeでの解説
 * Qiita.com、zenn.devなどでの情報

//blankline
を発信していますので、助けになるものが多くあります。日本語情報も増えていますが、英語でも動画やGitHubでのコードだと何とか理解できます。
ちょっとだけ頑張れば、あなたもモバイルアプリ作れます。

//blankline
本書で扱うオンライン・フリーマーケットもゼロからの開発ではなく、GitHubなどで公開されているアプリを魔改造していきます。
出典元や情報サイトなども提示していますので参考にしてください。

//blankline
本書のソースコードはGitHubにあります。章毎にブランチを分けていますので、どの章からでも始めていただけます。
できる限り図解していますのでページ数も膨大になりますが、ご容赦ください。

//blankline
また、Flutter開発環境の作成については本書では扱っていません。別途、無償配布しています「Flutter開発環境の作成Mac編」、
「Flutter開発環境の作成Windows編」を参照してください。

//blankline
最後になりますが、本書での「間違い」、「認識不足」、「誤字脱字」、「参照元のリンク切れ」などありましたら、
@<href>{https://github.com/risingforce9zz/book04_t-shirts-freemarket/blob/main/README.md, 本書サポートサイト}にて
issueを発行していただけませんでしょうか？

//blankline
よろしくお願します。
最後まで楽しんでいただけることを願っています。

//image[freeSoftware][][scale=0.6, pos=H]