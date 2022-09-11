= Twitterアカウントでサインイン

//abstract{
  Twitterのアカウントを使用してFirebaseにサインインします。

  TwiiterのDeveloperアカウントが必要です。
//}
//makechaptitlepage[toc=on]

== TwitterアカウントでFirebase認証
TwitterのアカウントをFirebase認証に使用します。

準備さえ出来れば簡単に実装できます。ユーザのメリットは、アプリケーション提供側へパスワードの登録がなく、
アプリケーション提供側にセキュリティ上の問題が発生してもパスワード漏洩が起こらないことです。

//blankline
手順は、

 1. Twitter Developerサイトでキーを取得
 2. Firebase認証へ取得したキーを登録
 3. アプリケーションでメソッドの追加

と、なります。


== Twitter Developerサイトでキー作成
最初に、
@<href>{https://developer.twitter.com/, Twitter Developerサイト}にアクセスしキーを取得します。

//blankline
Twitter Devloperサイトにログインします。
//image[04_twitterDev01][][scale=0.7, pos=H, border=on]

右上のメニューから「Product」を選択します。
//image[04_twitterDev02][][scale=0.7, pos=H, border=on]

続いて、「Twitter API」を選択します。
//image[04_twitterDev03][][scale=0.7, pos=H, border=on]

下へスクロールすると、「Get Started」ボタンがあります。クリックすると管理ページにアクセスできます。
//image[04_twitterDev05][][scale=0.7, pos=H, border=on]

「Create App」をクリックします。
//image[04_twitterDev06][][scale=0.7, pos=H, border=on]

アプリケーション名を入力し、「Next」ボタンをクリックします。
//image[04_twitterDev07][][scale=0.7, pos=H, border=on]

各種キーが表示されますのでコピーし、テキストファイルで保存します。アプリ登録が完了すれば、何度でも再作成ができます。
//image[04_twitterDev08][][scale=0.7, pos=H, border=on]

アプリの登録が完了しましたら、「User authentication settings」の「Setup」をクリックします。
//image[04_twitterDev09][][scale=0.7, pos=H, border=on]

ここで、

 * アプリケーションのタイプ
 * コールバックURL
 * アプリケーションのWebサイトのURL
を入力し、「Save」ボタンをクリックします。「新しいプロバイダを追加」ボタンをクリックします。

//blankline
コールバックURLは、「適当な英数字://」で構いません。これは、Firebaseコンソールが指定するURLが
後ほどインストールするプラグインで使えないためです。
//image[04_twitterDev10][][scale=0.7, pos=H, border=on]


「Client ID」、「Client Secret」が表示されますので、これもコピーして保存します。「Done」で完了です。
//image[04_twitterDev11][][scale=0.7, pos=H, border=on]

== Firebase認証でTwitter APIキーの登録
続いて、FirebaseコンソールのAuthenticationを開きます。
//image[03_firebase16][desc][scale=0.7, pos=H, border=on]

表示されたダイアログから「Twitter」を選択します。
//image[03_firebase17][desc][scale=0.7, pos=H, border=on]

表示されたダイアログのスイッチを有効にし、先ほど保存した「APIキー」、「APIシークレット」を入力し保存します。
//image[03_firebase18][desc][scale=0.7, pos=H, border=on]

AuthenticationへTwitterが追加されています。
//image[03_firebase19][desc][scale=0.7, pos=H, border=on]


== アプリケーションへメソッド追加

アプリケーションにTwitterアカウントを使用してのFirebaseサインインを実装します。

=== flutter_dotenvのインストール

//blankline
Twitterアカウントでのサインインを実装するときに、
Twitter Developperサイトで取得したキーと登録したコールバックURL、

 * Twitter API Key
 * Twitter API Secret
 * コールバックURL

をコードに書き込むことになります。

//blankline
しかし、コードに直接上記のキーを書込みすると危険です。ソールコードをGitHubなで管理している場合「公開」になっていると
間違いなく悪用されますし、GitHubであれば警告メールがきます。
それを回避するためには、重要な情報は、「.env」ファイルを作成して別途保存し、デバッグ時・リリース時に読み込むようにします。

//blankline
「.env」ファイルは、ローカルPCに保存し「.gitignore」へプッシュされないよう追加します。

//blankline
Flutterで「.env」を読み込むために、「flutter_dotenvパッケージ」をインストールします。

//image[pubdev_env][][scale=0.7, pos=H]

//terminal[][flutter_dotenvのインストール]{
 > flutter pub add flutter_dotenv
  Resolving dependencies...
  + flutter_dotenv 5.0.2
    material_color_utilities 0.1.5 (0.2.0 available)
    source_span 1.9.0 (1.9.1 available)
    test_api 0.4.12 (0.4.13 available)
    vector_math 2.1.2 (2.1.3 available)
  Changed 1 dependency!
//}

「プロジェクトフォルダ/.env」ファイルを作成します。

//list[][プロジェクトフォルダ/.env]{
TWITTER_API_KEY=取得したAPI KEY
TWITTER_API_SECRET_KEY=取得したAPI Secret Key
TWITTER_REDIRECT_URI=設定したコールバックURL
//}

//blankline
忘れないように、今、スグに「.gitignore」を開き「*.env」を追加します。

//blankline
次に、「.env」ファイルが読み込まれるように「pubspec.yaml」ファイルにパスを書き込みます。

//list[][pubspec.yaml]{
flutter:

  # The following line ensures that the Material Icons font is
  # included with your application, so that you can use the icons in
  # the material Icons class.
  uses-material-design: true

  assets:
    - .env @<balloon>{ここです。}
  # To add assets to your application, add an assets section, like this:
  # assets:
  #   - images/a_dot_burr.jpeg
  #   - images/a_dot_ham.jpeg
//}

//blankline
mainメソッド（lib/main.dart）で初期化します。

//list[][main.dart]{
void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp(
    options: DefaultFirebaseOptions.currentPlatform,
  );
  await dotenv.load(fileName: ".env");
  runApp(LoginUiApp());
}
//}


=== 認証コントローラーへメソッドの追加

==== twitter_loginプラグインのインストール・設定
@<href>{https://firebase.google.com/docs/auth/flutter/federated-auth#twitter, FirebaseのFlutterソーシャル}を確認します。

「twitter_login」プラグインが必要とありますので、インストールします。

//image[pubdev_twitterlogin][][scale=0.7, pos=H]

//terminal[][twitter_loginのインストール]{
❯ flutter pub add twitter_login
Resolving dependencies...
+ crypto 3.0.2
  material_color_utilities 0.1.5 (0.2.0 available)
  source_span 1.9.0 (1.9.1 available)
  test_api 0.4.12 (0.4.13 available)
+ twitter_login 4.2.3
  vector_math 2.1.2 (2.1.3 available)
Changed 2 dependencies!

//}

上記のプラグインサイトの指示に従って設定します。

===== Android
プラグインサイトのREADMEに従い、下記のコードを、
//blankline
　　プロジェクトフォルダ/android/app/src/main/AndroidManifest.xml
@<br>{}に追加します。

//blankline
その際に、下から3行目の「example」をTwitterに登録したコールバックURLにします。「://」は不要です。
下から2行目の「gizmos」は削除して「host=""」にします。

//blankline
//list[][Android向け]{
<intent-filter>
  <action android:name="android.intent.action.VIEW" />
  <category android:name="android.intent.category.DEFAULT" />
  <category android:name="android.intent.category.BROWSABLE" />
  <!-- Accepts URIs that begin with "example://gizmos” -->
  <!-- Registered Callback URLs in TwitterApp -->
  <data android:scheme="example"
        android:host="gizmos" /> <!-- host is option -->
</intent-filter>
//}

全体は、以下のようになります。

//list[][AndroidManifest.xml]{
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    package="com.imakita3gyo.tfreemarket.tfreemarket">
   <application
        android:label="tfreemarket"
        android:name="${applicationName}"
        android:icon="@mipmap/ic_launcher">
        <activity
            android:name=".MainActivity"
            android:exported="true"
            android:launchMode="singleTop"
            android:theme="@style/LaunchTheme"
            android:configChanges="orientation|keyboardHidden|keyboard|screenSize|smallestScreenSize|locale|layoutDirection|fontScale|screenLayout|density|uiMode"
            android:hardwareAccelerated="true"
            android:windowSoftInputMode="adjustResize">
            <!-- Specifies an Android theme to apply to this Activity as soon as
                 the Android process has started. This theme is visible to the user
                 while the Flutter UI initializes. After that, this theme continues
                 to determine the Window background behind the Flutter UI. -->
            <meta-data
              android:name="io.flutter.embedding.android.NormalTheme"
              android:resource="@style/NormalTheme"
              />
            <intent-filter>
                <action android:name="android.intent.action.MAIN"/>
                <category android:name="android.intent.category.LAUNCHER"/>
            </intent-filter>
            <intent-filter>
                <action android:name="android.intent.action.VIEW" />
                <category android:name="android.intent.category.DEFAULT" />
                <category android:name="android.intent.category.BROWSABLE" />
                <!-- Accepts URIs that begin with "example://gizmos” -->
                <!-- Registered Callback URLs in TwitterApp -->
                <data android:scheme="manatee"
                    android:host="" /> <!-- host is option -->
            </intent-filter>
        </activity>
        <!-- Don't delete the meta-data below.
             This is used by the Flutter tool to generate GeneratedPluginRegistrant.java -->
        <meta-data
            android:name="flutterEmbedding"
            android:value="2" />
    </application>
</manifest>
//}


===== iOS

iOS用は、
@<br>{}　　プロジェクトフォルダ/ios/Runner/info.plist
@<br>{}に以下のコードを追加します。

//blankline
下から4行目の「<string>example</string>」の「example」部分を先ほどと同じくコールバックURLに書き換えます。

//list[][iOS用設定]{
<key>CFBundleURLTypes</key>
<array>
  <dict>
    <key>CFBundleTypeRole</key>
    <string>Editor</string>
    <key>CFBundleURLName</key>
    <string></string>
    <key>CFBundleURLSchemes</key>
    <array>
      <!-- Registered Callback URLs in TwitterApp -->
      <string>example</string>
    </array>
  </dict>
</array>
//}

全体は、以下のようになります。

//list[][iOS設定ファイル info.plist]{
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
	<key>CFBundleDevelopmentRegion</key>
	<string>$(DEVELOPMENT_LANGUAGE)</string>
	<key>CFBundleDisplayName</key>
	<string>Tfreemarket</string>
	<key>CFBundleExecutable</key>
	<string>$(EXECUTABLE_NAME)</string>
	<key>CFBundleIdentifier</key>
	<string>$(PRODUCT_BUNDLE_IDENTIFIER)</string>
	<key>CFBundleInfoDictionaryVersion</key>
	<string>6.0</string>
	<key>CFBundleName</key>
	<string>tfreemarket</string>
	<key>CFBundlePackageType</key>
	<string>APPL</string>
	<key>CFBundleShortVersionString</key>
	<string>$(FLUTTER_BUILD_NAME)</string>
	<key>CFBundleSignature</key>
	<string>????</string>
	<key>CFBundleVersion</key>
	<string>$(FLUTTER_BUILD_NUMBER)</string>
	<key>LSRequiresIPhoneでのTwitterサインインOS</key>
	<true/>
	<key>UILaunchStoryboardName</key>
	<string>LaunchScreen</string>
	<key>UIMainStoryboardFile</key>
	<string>Main</string>
	<key>UISupportedInterfaceOrientations</key>
	<array>
		<string>UIInterfaceOrientationPortrait</string>
		<string>UIInterfaceOrientationLandscapeLeft</string>
		<string>UIInterfaceOrientationLandscapeRight</string>
	</array>
	<key>UISupportedInterfaceOrientations~ipad</key>
	<array>
		<string>UIInterfaceOrientationPortrait</string>
		<string>UIInterfaceOrientationPortraitUpsideDown</string>
		<string>UIInterfaceOrientationLandscapeLeft</string>
		<string>UIInterfaceOrientationLandscapeRight</string>
	</array>
	<key>UIViewControllerBasedStatusBarAppearance</key>
	<false/>
	<key>CADisableMinimumFrameDurationOnPhone</key>
	<true/>
	<key>UIApplicationSupportsIndirectInputEvents</key>
	<true/>
	<key>CFBundleURLTypes</key>
    <array>
      <dict>
        <key>CFBundleTypeRole</key>
        <string>Editor</string>
        <key>CFBundleURLName</key>
        <string></string>
        <key>CFBundleURLSchemes</key>
        <array>
          <!-- Registered Callback URLs in TwitterApp -->
          <string>manatee</string>
        </array>
      </dict>
    </array>
</dict>
</plist>

//}

以上で準備完了です。

=== Twitterサインイン・メソッドの追加

認証コントローラー（auth_controller.dart）へメソッドを追加します。

//list[][Twitterサインイン]{
  /// Twitterログイン
  signInWithTwitter() async {
    // TwitterLoginのインスタンス化
    final twitterLogin = TwitterLogin(
        apiKey: dotenv.env['TWITTER_API_KEY']!,
        apiSecretKey: dotenv.env['TWITTER_API_SECRET_KEY']!,
        redirectURI: dotenv.env['TWITTER_REDIRECT_URI']!);

    // Twitterサインイン　フロー開始
    final authResult = await twitterLogin.login();
    String accessToken = authResult.authToken!;
    String accessTokenSecret = authResult.authTokenSecret!;
    String screenName = authResult.user!.screenName;
    String twitterThumbnailImage = authResult.user!.thumbnailImage;
    String name = authResult.user!.name;

    // アクセストークンからcredentialを作成
    final twitterAuthCredential = TwitterAuthProvider.credential(
        accessToken: accessToken, secret: accessTokenSecret);

    // firebaseのcredentialを作成
    await _auth.signInWithCredential(twitterAuthCredential);
  }
//}

ログイン選択画面に、認証コントローラーをバインドします。

//list[][select_signin_page.dart]{
  class SelectSignInPage extends StatelessWidget{
    SelectSignInPage({Key? key}): super(key:key);

    final AuthController authController = AuthController.to;
    
    final double _headerHeight = 250;
//}

ボタンに認証コントローラーのメソッド呼び出しを割り当てます。

//list[][Twitterサインイン・メソッド]{
  Container(
    decoration: ThemeHelper().buttonBoxDecoration(context),
    child: ElevatedButton(
      style: ThemeHelper().buttonStyle(),
      child: Row(
          children: const [
            FaIcon(FontAwesomeIcons.twitter, size: 23, color: Colors.blue),
            Padding(
              padding: EdgeInsets.fromLTRB(30, 10, 0, 10),
              child: Text('Twitterアカウント', style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold, color: Colors.white),),
            ),
          ]
      ),
      onPressed: (){
          authController.signInWithTwitter();
      },
    ),
  ),
//}

== 動作確認

動作確認を行います。

=== iOS
iPhoneシミュレータでのサインインです。Twitterアカウントのメール/パスワードでアプリにサインインできました。
//image[ios_twitter][iPhoneでのTwitterサインイン][scale=0.7, pos=H]

=== Android
Androidエミュレータでのサインです。同じくTwitterアカウントのメール/パスワードでサインインできました。

//image[android_twitter][AndroidでTwitterサインイン][scale=0.7, pos=H]

=== Firebaseコンソール

Twitterアカウントがひとつしかないので、iPhoneでサイン後アカウント削除し、Androidでサインインしています。

//image[firebase_twitter][Firebaseコンソール][scale=0.7, pos=H]


#@# textlint-disable
//note[ここまでのソースコード]{
//terminal[][GitHub]{
　>git clone -b 07_twitter_signin https://github.com/risingforce9zz/tfreemarket.git
//}
//}
#@# textlint-enable
