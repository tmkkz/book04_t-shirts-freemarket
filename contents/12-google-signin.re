= Googleサインイン
//abstract{
  Googleアカウントを使用してアプリケーションにサインインします。


//}

//makechaptitlepage[toc=on]

== GoogleアカウントでFirebase認証
TwitterのアカウントをFirebase認証に使用します。

Firebase、FlutterともにGoogleが開発しているため親和性は抜群です。まずは、
@<href>{https://firebase.google.com/docs/auth/flutter/federated-auth#google, 公式サイト}を確認します。


//image[google-doc][][scale=0.7, pos=H]

//blankline
手順は、

 1. Firebaseに登録したアプリにSHA1フィンガープリントを登録
 2. google_sign_inプラグインのインストール
 3. iOS用の設定
 4. アプリケーションにgoogleサインイン・メソッドの実装

と、なります。

== Firebaseにキーを登録
ターミナルに、以下のコマンドを入力してキーを取得します。

//terminal[][SHA1キーの取得]{
 > keytool -list -v -keystore ~/.android/debug.keystore -alias androiddebugkey -storepass android -keypass android
  Alias name: androiddebugkey
  Creation date: Aug. 17, 2022
  Entry type: PrivateKeyEntry
  Certificate chain length: 1
  Certificate[1]:
  Owner: C=US, O=Android, CN=Android Debug
  Issuer: C=US, O=Android, CN=Android Debug
  Serial number: 1
  Valid from: Wed Aug 17 15:58:43 PDT 2022 until: Fri Aug 09 15:58:43 PDT 2052
  Certificate fingerprints:
          SHA1: AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA
          SHA256: AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA:AA
  Signature algorithm name: SHA1withRSA (weak)
  Subject Public Key Algorithm: 2048-bit RSA key
  Version: 1

Warning:
The certificate uses the SHA1withRSA signature algorithm which is considered a security risk. This algorithm will be disabled in a future update.

//}


=== 表示されたSHA1フィンガープリントをFirebaseに登録

//blankline
Firebaseコンソールを開き、Authenticationを選択します。「Sign-in method」タブを選択し
「新しいプロバイダを追加」ボタンをクリックします。

//image[firebase13][ログインプロバイダの登録][scale=0.7, pos=H]

表示されたダイアログから、「Google」を選択します。
//image[firebase14][Googleを追加][scale=0.7, pos=H]

//clearpage
表示されたダイアログのスイッチを有効化します。プロジェクトのサポートメールを選択し、「保存」ボタンをクリックします。
//image[firebase15][有効化][scale=0.7, pos=H]

以上で、Googleが追加されます。
//image[firebase16][ログインプロバイダの登録][scale=0.7, pos=H]

//clearpage
Firebaseコンソールの「プロジェクトの概要」橫の歯車をクリックし、「プロジェクトの設定」を選択します。
//image[key01][SHA1の登録][scale=0.7, pos=H]

「flutterfire configure」コマンドを使ったときにアプリケーションが登録されていますので、Andoroidのアプリを選択します。
「フィンガープリントを追加」をクリックします。
//image[key02][SHA1の登録][scale=0.7, pos=H]

フィンガープリントの登録ダイアログが表示されますので、先ほど出力したSHA1をコピペします。ついでにSHA256も登録します。
//image[key03][SHA1の登録][scale=0.7, pos=H]
「保存」ボタンをクリックすると登録されます。
//image[key04][SHA1の登録][scale=0.7, pos=H]

以上でFirebase側の設定は完了です。

== google_sign_inプラグインのインストール

@<href>{https://pub.dev/packages/google_sign_in, google_sign_inプラグイン}をインストールします。

//image[plugin01][google_sign_inプラグイン][scale=0.7, pos=H]

ターミナルに「flutter pub add google_sign_in」と入力しエンターキーを押します。

//terminal[][]{
 > flutter pub add google_sign_in
  Resolving dependencies...
  + google_sign_in 5.4.1
  + google_sign_in_android 6.1.0
  + google_sign_in_ios 5.5.0
  + google_sign_in_platform_interface 2.3.0
  + google_sign_in_web 0.10.2
    material_color_utilities 0.1.5 (0.2.0 available)
  + quiver 3.1.0
    source_span 1.9.0 (1.9.1 available)
    test_api 0.4.12 (0.4.13 available)
    vector_math 2.1.2 (2.1.3 available)
  Changed 6 dependencies!

//}

以上でプラグインのインストールは完了です。

== iOS用の設定

iOS用のに以下の設定をします。

「プロジェクトフォルダ/ios/Runner/Info.plist」を開き以下を追加します。
@<br>{}「XXXXXXXXXX」の部分は、「プロジェクトフォルダ/ios/Runner/GoogleService-Info.plist」ファイル内の
「REVERSED_CLIENT_ID」に書き換えます。

//list[][追加するコード]{
<!-- Put me in the [my_project]/ios/Runner/Info.plist file -->
<!-- Google Sign-in Section -->
<key>CFBundleURLTypes</key>
<array>
	<dict>
		<key>CFBundleTypeRole</key>
		<string>Editor</string>
		<key>CFBundleURLSchemes</key>
		<array>
			<!-- TODO Replace this value: -->
			<!-- Copied from GoogleService-Info.plist key REVERSED_CLIENT_ID -->
			<string>XXXXXXXXXX</string>
		</array>
	</dict>
</array>
<!-- End of the Google Sign-in Section -->
//}

以上で、iOS用の設定は完了です。

== アプリにgoogleサインイン・メソッドの実装

アプリケーションの認証コントローラに以下のコードを追加します。

//list[][googleサインイン・メソッドの追加]{
  /// Googleサインイン
  signInWithGoogle() async {
    // 認証フローの開始
    final GoogleSignInAccount? googleUser = await GoogleSignIn(
        clientId: DefaultFirebaseOptions.currentPlatform.iosClientId)
        .signIn();

    // 認証情報詳細を取得
    final GoogleSignInAuthentication? googleAuth =
    await googleUser?.authentication;

    // クレデンシャルの作成
    final credential = GoogleAuthProvider.credential(
      accessToken: googleAuth?.accessToken,
      idToken: googleAuth?.idToken,
    );

    // サインインに成功するとユーザークレデンシャルが返る
    UserCredential userCredential =
    await FirebaseAuth.instance.signInWithCredential(credential);
  }
//}

ログイン選択画面の「Googleアカウント」ボタンにメソッド呼び出しを割り当てます。

//list[][メソッド呼び出し]{
    Container(
      decoration: ThemeHelper().buttonBoxDecoration(context),
      child: ElevatedButton(
        style: ThemeHelper().buttonStyle(),
        child: Row(
            children: const [
              FaIcon(FontAwesomeIcons.google, size: 23),
              Padding(
                padding: EdgeInsets.fromLTRB(30, 10, 0, 10),
                child: Text('Googleアカウント', style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold, color: Colors.white),),
              ),
            ]
        ),
        onPressed: (){
          authController.signInWithGoogle();
        },
      ),
    ),
//}

以上で、Googleアカウントでアプリケーションへのログインができます。

== 動作確認
=== iPhone
iPhoneシミュレータでデバッグしようとするとエラーになりました。
//blankline
「プラットフォームが指定されていないのでiOS 11を割り当てた。」
@<br>{}「CocoaPodsのリポジトリが期限切れ」
//blankline
とのことです。

//terminal[][ビルドエラー]{
Error output from CocoaPods:


    [!] Automatically assigning platform `iOS` with version `11.0` on target `Runner` because no platform was specified. Please specify a platform for this target in your Podfile. See `https://guides.cocoapods.org/syntax/podfile.html#platform`.

Error: CocoaPods's specs repository is too out-of-date to satisfy dependencies.
To update the CocoaPods specs, run:
  pod repo update

Error running pod install
Error launching application on iPhone 12.
//}

Xcodeを開き、iOSの対象を指定します。iOS 16がリリースされるので、2世代前のiOS 14の最新版を仕様とします。

//image[i02][XcodeでiOSのバージョン指定][scale=0.7, pos=H]

ビルドエラーが発生しましたので、環境を再構築します。

//terminal[][desc]{
> flutter clean
Cleaning Xcode workspace...                                         4.7s
Cleaning Xcode workspace...                                      2,860ms
Deleting build...                                                  548ms
Deleting .dart_tool...                                               3ms
Deleting Generated.xcconfig...                                       0ms
Deleting flutter_export_environment.sh...                            0ms
Deleting Flutter.podspec...                                          0ms
Deleting ephemeral...                                                0ms
Deleting .flutter-plugins-dependencies...                            0ms
Deleting .flutter-plugins...                                         0ms
> rm -Rf ios/Pods
> rm -Rf ios/.symlinks
> rm ios/Podfile
> rm ios/Podfile.lock
> cd ios
> pod install
//}

今回は無事にビルドできました。

//image[iPhoneResult][iPhoneの動作確認][scale=0.7, pos=H]

//clearpage
=== Android

さすがにGoogleがすべて関与しているものだと問題なく動作します。

//image[AndroidResult][Androidでの動作確認][scale=0.7, pos=H]

#@# textlint-disable
//note[ここまでのソースコード]{
//terminal[][GitHub]{
　> git clone -b 08_google_signin https://github.com/risingforce9zz/tfreemarket.git
//}
//}
#@# textlint-enable
