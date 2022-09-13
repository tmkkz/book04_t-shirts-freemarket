= FlutterでFirebaseを使う

//abstract{
  Firebase関連のプラグインの導入と設定をします。

//image[0701][][scale=0.7, pos=H]
//}

//makechaptitlepage[toc=on]

== クライアント側（Flutter）でFirebaseの設定

以前は、モバイルアプリでFirebaseを使うために、

 * Firebaseコンソールにアプリを登録して、
 * Firebase側が自動作成したファイルを、Android用、iOS用にダウンロード・配置をし、
 * Firebaseのサービス毎にプラグインのインストール

が必要でした（プラグインのインストールは今でも必要）。

//blankline
しかし、最近は「Firebase CLI」があります。これは、ターミナルからコマンドで設定が完了する優れもので、
アプリ登録やAndoroid、iOS用設定ファイルのダウンロードも自動化されています。

//blankline
公式サイト
https://firebase.google.com/docs/flutter/setup?platform=ios#available-plugins
//blankline
インストールは、ターミナルを開き、

//terminal[][Firebase CLIのインストール]{
　> curl -sL https://firebase.tools | bash
//}

と、入力しエンターキーを押します。たった、これだけ。続けて、プロジェクトフォルダへ移動し、

//terminal[][Firebaseにログインし設定]{
 > firebase login

 > firebase projects:list
//}

//blankline
これで、Firebaseに登録しているプロジェクトが表示されればOKです。

//blankline
プロジェクトフォルダで作業していることを再度確認し、

//terminal[][flutterfireの有効化]{
 > dart pub global activate flutterfire_cli
//}

これで、プロジェクトへFirebase関連の設定のほとんどをコマンドで行うことができます。

//clearpage
fluttrefireコマンドが有効になりましたので、さっそく使ってみます。

//terminal[][flutterfireコマンド]{
 > flutterfire configure
╔═══════════════════════════════════════════════════╗
║ The Dart tool uses Google Analytics to report feature usage statistics     ║
║ and to send basic crash reports. This data is used to help improve the     ║
║ Dart platform and tools over time.                                         ║
║                                                                            ║
║ To disable reporting of analytics, run:                                    ║
║                                                                            ║
║   dart --disable-analytics                                                 ║
║                                                                            ║
╚═══════════════════════════════════════════════════╝

- ansi_styles 0.3.2+1s... (1.2s)
- args 2.3.1
- async 2.9.0
- characters 1.2.1
 *********** 中略 ************
- uri 1.0.0
- win32 2.7.0 (3.0.0 available)
- xml 5.4.1 (6.1.0 available)
- yaml 3.1.1
Downloading flutterfire_cli 0.2.4...
Downloading pub_updater 0.2.2...
Downloading interact 2.1.1...
Downloading deep_pick 0.10.0...
Downloading cli_util 0.3.5...
 *********** 中略 ************
Downloading async 2.9.0...
Building package executables... (2.1s)
Built flutterfire_cli:flutterfire.
Installed executable flutterfire.
Warning: Pub installs executables into $HOME/.pub-cache/bin, which is not on your path.
You can fix that by adding this to your shell's config file (.bashrc, .bash_profile, etc.):

    export PATH="$PATH":"$HOME/.pub-cache/bin"


Activated flutterfire_cli 0.2.4.
//}

//blankline
最後に、パスを通すように指示されましたので、エディッタで「~/.zshrc」を開き、@<br>{}
#@# textlint-disable
　　　@<strong>{export PATH="$PATH":"$HOME/.pub-cache/bin"}@<br>{}
#@# textlint-enable
を追加して保存してください。

パスの設定が完了しましたら、
//terminal[][pathの設定]{
 > source ~/.zshrc
//}

で、設定を読み込みます。


//blankline
Flutter用のFirebaseコアプラグインをインストールします。ターミナルに「flutter pub add firebase_core」と入力しエンターキーを押します。

 * Firebaseに登録しているプロジェクトが表示されるので、上下矢印キーで選択。
 * 対象のプラットフォームを選択する。デフォルトで全選択になっているのでエンターキー。
 * Andoroidのコンパイル設定ファイルの上書を求められるのでエンターキー。

//terminal[][Firebase coreのインストール]{
❯ flutter pub add firebase_core
Resolving dependencies...

- firebase_core 1.21.1
- firebase_core_platform_interface 4.5.1
- firebase_core_web 1.7.2
material_color_utilities 0.1.5 (0.2.0 available)
- plugin_platform_interface 2.1.2
source_span 1.9.0 (1.9.1 available)
test_api 0.4.12 (0.4.13 available)
vector_math 2.1.2 (2.1.3 available)
Downloading firebase_core 1.21.1...
Downloading firebase_core_web 1.7.2...
Downloading firebase_core_platform_interface 4.5.1...
Changed 4 dependencies!
//}

//blankline
「flutterfireコマンド」で設定します。ターミナルに「flutterfire configure」と入力しエンターキーを押します。

//blankline
コマンドが実行され、

 * Firebaseコンソールに登録されたプロジェクト名が表示されるので、設定先を選択する。

//clearpage

//terminal[][flutterfireコマンド]{
 > flutterfire configure
 i Found 3 Firebase projects.

@<balloon>{ここにプロジェクトが表示されるので、上下矢印キーで選択しエンターキーで決定}

x Select a Firebase project to configure your Flutter application with · プロジェクト名 (プロジェクト名)

x Which platforms should your configuration support (use arrow keys & space to select)? · ios, macos, web, android

@<balloon>{ここに設定するプラットフォームが表示される。チェックマークで選択}

i Firebase android app com.imakita3gyo.frema.t_free_market is not registered on Firebase project tshirtsfreemarket.
i Registered a new Firebase android app on Firebase project tshirtsfreemarket.
i Firebase ios app com.imakita3gyo.frema.tFreeMarket is not registered on Firebase project tshirtsfreemarket.
i Registered a new Firebase ios app on Firebase project tshirtsfreemarket.
i Firebase macos app com.imakita3gyo.frema.tFreeMarket registered.
i Firebase web app t_free_market (web) is not registered on Firebase project tshirtsfreemarket.
i Registered a new Firebase web app on Firebase project tshirtsfreemarket.

@<balloon>{Androidのコンパイル設定ファイルを上書しても良いか、yes選択状態なのでエンターキー}

? The files android/build.gradle & android/app/build.gradle will be updated to apply Firebase configuration and gradle build plugins. Do you want to continue? (y/n) › yes

Firebase configuration file lib/firebase_options.dart generated successfully with the following Firebase apps:

Platform  Firebase App Id
web       1:65147047369:web:d8f9e2c3b9faa316a9ec18
android   1:65147047369:android:6e7f4e03f4305567a9ec18
ios       1:65147047369:ios:024142971626c8b6a9ec18
macos     1:65147047369:ios:024142971626c8b6a9ec18

Learn more about using this file and next steps from the documentation:
//}

これで、

 * アクセス情報の入った「lig/firebase_options.dart」
 * Android用設定ファイル「Android/app/google-services.json」
 * iOS用設定ファイル「ios/Runner/GoogleServie-info.plist」
 * macOS用設定ファイル「macos/firebase_app_id_file.json」

が、ダウンロードされます。

//clearpage
Firebaseサービス用のFlutterプラグインをインストールする度に再設定の必要があるので、Firebase系のプラグインは一度でインストールします。

//image[0702][][scale=0.7, pos=H]
== Firebaseサービス用Flutterプラグインのインストール
続いて、Firebaseの各サービスを使用するために、サービス毎のプラグインをインストールします。

//blankline
//noindent
Flutterで使用できるFirebase関連プラグイン一覧@<br>{}
https://firebase.google.com/docs/flutter/setup?platform=ios#available-plugins


//blankline
プロジェクトで使用すると思われるプラグインは、

 * アナリティクス  firebase_analytics
 * 認証 firebase_auth
 * Cloud Firestore（ドキュメント形式のデータベース） cloud_firestore
 * Cloud Messaging firebaes_messaging
 * Cloud Storege  firebase_storage
 * Realtime Database firebase_database

です。

//blankline
ターミナルに、@<br>{}
 flutter pub add firebase_analytics firebase_auth cloud_firestore
  firebase_messaging firebase_storage firebase_database
//blankline
を入力しエンターキーを押します。

//terminal[][Firebaseサービスプラグインのインストール]{
> flutter pub add firebase_analytics firebase_auth cloud_firestore\
   firebase_messaging firebase_storage firebase_database
...
Changed 22 dependencies!
//}

Firebase関連のプラグインをインストールした場合には、お約束の「flutterfire configure」を行います。ターミナルには前回と同じ表示が出ます。同じように選択しエンターキーを押します。

//blankline
以上で、Firebaseのサービスを使う準備ができました。

//clearpage

最後に、Firebaseアナリティクスを使うためには、AndoroidのSDKの最低バージョンが19以上でないとコンパイルが通りません。
ここで最低のSDKバージョンを29に指定します。

//blankline
また、コンパイルSDKバージョンも最新が要求されます。

//blankline
2022年8月に「33」が正式リリースされました。古いAndoroid OSをサポートすると画面解像度の種類も膨大になるため
4世代前を仕様とします。

//blankline
「Android/app/src/buld.gradle」ファイルの以下の項目の下から4行目にある「minSdkVersion」にバージョン番号を指定してします。
編集は、コメントアウト・新規行の追加を行ます。

//blankline
2行目の「compleSdkVersion」を「33」にします。

//list[][Android/app/src/build.gradle]{
  android {
    compileSdkVersion 33
    ndkVersion flutter.ndkVersion

    compileOptions {
        sourceCompatibility JavaVersion.VERSION_1_8
        targetCompatibility JavaVersion.VERSION_1_8
    }

    kotlinOptions {
        jvmTarget = '1.8'
    }

    sourceSets {
        main.java.srcDirs += 'src/main/kotlin'
    }

    defaultConfig {
        // TODO: Specify your own unique Application ID (https://developer.android.com/studio/build/application-id.html).
        applicationId "com.imakita3gyo.tfreemarket.tfreemarket"
        // You can update the following values to match your application needs.
        // For more information, see: https://docs.flutter.dev/deployment/android#reviewing-the-build-configuration.
        // minSdkVersion flutter.minSdkVersion
        minSdkVersion 29 @<balloon>{この行を追加、上の行をコメントアウト}
        targetSdkVersion flutter.targetSdkVersion
        versionCode flutterVersionCode.toInteger()
        versionName flutterVersionName
    }

//}

== テスト

起動時にFirebaseクライアントを初期化し、アプリが起動するかを確認します。

//blankline
「lib/main.dart」を以下のように変更します。

 * firebase_coreをインポート
 * firebase_optionsをインポート
 * mainをasyncキーワード付けて非同期にし、Firebaseを初期化

//list[][lib/main.dart]{
import 'package:firebase_core/firebase_core.dart';

import 'firebase_options.dart';
import 'pages/splash_screen.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp(
    options: DefaultFirebaseOptions.currentPlatform,
  );
  runApp(LoginUiApp());
}
//}

編集が完了すると、エミュレータでデバッグします。問題なく起動しましたので次に進みます。

#@# textlint-disable
//note[ここまでのソースコード]{
//terminal[][GitHub]{
　>git clone -b 03_flutterfire_setup https://github.com/risingforce9zz/tfreemarket.git
//}
//}
#@# textlint-enable

//image[0703][][scale=0.7, pos=H]