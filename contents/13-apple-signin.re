= AppleIDでサインイン

//abstract{
  AppleIDを使ってアプリケーションにサインインします。
//}

//makechaptitlepage[toc=on]

=== Firebaseコンソールでログインプロバイダを追加
Firebaseコンソールを開きます。Authenticationを選択し、「新しいプロバイダを追加」ボタンをクリックします。
//image[apple_signin2][][scale=0.7, pos=H, border=on]

ダイアログが表示されます。追加のプロバイダから「Apple」を選択します。
//image[apple_signin3][][scale=0.7, pos=H, border=on]

表示されたダイアログで、Appleを有効にします。サービスIDなどは後で登録します。ここでは「保存」ボタンをクリックします。
//image[apple_signin4][][scale=0.7, pos=H, border=on]

ログインプロバイダにAppleが追加されているのを確認します。
//image[apple_signin5][][scale=0.7, pos=H, border=on]

== Apple Developerサイトで「Appleでサインイン」を有効に
=== アプリケーションのIDを取得します。
アプリケーションのIDを取得します。Firebaseプロジェクト作成時に「Organaization」欄に入力したものがアプリケーションIDです。
既に登録されている場合は、アプリケーションIDをクリックします。

//blankline
Apple Developerサイトにログインします。「Certificates, Identifiers & Profiles」をクリックします。
//image[apple_signin47][][scale=0.7, pos=H, border=on]

左サイドメニューの「Identifiers」を選択し、「+」をクリックします。
//image[apple_signin48][][scale=0.7, pos=H, border=on]
#@# //image[apple_signin6][][scale=0.7, pos=H, border=on]

「App IDs」を選択し、「Continue」をクリックします。
//image[apple_signin7][][scale=0.7, pos=H, border=on]

「App」を選択し「Continue」をクリックします。
//image[apple_signin8][][scale=0.7, pos=H, border=on]

「Description」欄に備考を入力し、「Bundle ID」欄にアプリケーションIDを入力します。
//image[apple_signin9][][scale=0.7, pos=H, border=on]

下へスクロールすると、「Sign in with Apple」がありますので、チェックをONにします。

//image[apple_signin10][][scale=0.7, pos=H, border=on]
「Edit」をクリックすると、「App ID Configuration」が開きますが、「Save」で閉じます。
//blankline
上にスクロールするし、「Continue」ボタンをクリックします。
//image[apple_signin11][][scale=0.7, pos=H, border=on]

以上でアプリケーションIDの取得が完了しました。

=== XCodeでAppleでサインインを有効にする
プロジェクトフォルダ内のiosフォルダをXCodeで開きます。

//blankline
「Target」-「Signing & Capabilites」で「＋」をクリックします。
//image[apple_signin49][][scale=0.7, pos=H, border=on]

「Sign in with Apple」をダブル・クリックします。
//image[apple_signin12][][scale=0.7, pos=H, border=on]
アプリケーションに「Sign in with Apple」が追加されました。
//image[apple_signin13][][scale=0.7, pos=H, border=on]

=== Appleの匿名E-mailサービスの設定
Apple IDでサインインするときに、「メールを非公開」を選択するとサービス提供者には、
「anonymous@privaterelay.appleid.com（anonymous部分がランダムな文字列になる）」のアドレスが渡されます。

//blankline
サービス提供者がユーザにメールを送ると、AppleはAppleIDのメールアドレスへ転送してくれます。その場合、登録してある差出人からのメールのみ転送します。
ここで、差出人からのメールアドレスを登録します。

//blankline
再度、Apple Developerサイトへログインします。左サイドメニューからサービスを選択し、
「Sign in with Apple for Email Communication」の「configure」ボタンをクリックします。
//image[apple_signin14][][scale=0.7, pos=H, border=on]

「Email Sources」の「+」をクリックします。
//image[apple_signin15][][scale=0.7, pos=H, border=on]

差出人のメールアドレスの「ドメイン」、「サブドメイン」、「メールアドレス」を登録し、「Next」ボタンをクリックします。
//image[apple_signin16][][scale=0.7, pos=H, border=on]

確認ダイアログが表示されますので、「Register」ボタンをクリックします。
//image[apple_signin17][][scale=0.7, pos=H, border=on]

登録完了のダイアログが表示されます。
//image[apple_signin18][][scale=0.7, pos=H, border=on]

差出人メールアドレスが登録されました。
//image[apple_signin19][][scale=0.7, pos=H, border=on]

=== Android用のサービスID、キーIDを取得する

==== サービスIDの取得
AndroidからAppleでサインインするために、サービスID、キーIDを取得します。Apple Developerサイトにログインし,
「Certificates, Identifiers & Profiles」をクリックします。
#@# //image[apple_signin24][][scale=0.7, pos=H, border=on]
//image[apple_signin25][][scale=0.7, pos=H, border=on]

左サイドメニューから「Itentifiers」をクリックします。
//image[apple_signin26][][scale=0.7, pos=H, border=on]

「Service IDｓ」をクリックし、「Continue」ボタンをクリックします。
//image[apple_signin27][][scale=0.7, pos=H, border=on]

「Description」欄と「Identifier」欄に入力します。「Identifier」欄に入力するものは、他で使っていないユニークなものになります。
「Continue」ボタンをクリックします。
//image[apple_signin28][][scale=0.7, pos=H, border=on]

確認ダイアログが表示されますので、「Register」ボタンをクリックします。
//image[apple_signin29][][scale=0.7, pos=H, border=on]

ServiceIDが登録されました。登録された「NAME」がリンクになっていますので、クリックします。
//image[apple_signin30][][scale=0.7, pos=H, border=on]

「Sign in with Apple」のチェックボックスをONにし、「Configure」ボタンをクリックします。
//image[apple_signin31][][scale=0.7, pos=H, border=on]

ダイアログが表示されますので、登録したアプリケーションIDを選択し、Return URLsに
Firebase AuthenticationでAppleを追加したログインプロバイダ登録時の認証コールバックURLを追加します。
//image[apple_signin32][][scale=0.7, pos=H, border=on]

Firebase AuthenticationでApple追加時に表示されています。
//image[apple_signin51][][scale=0.7, pos=H, border=on]

確認ダイアログが表示されますので、「Done」をクリックします。
//image[apple_signin33][][scale=0.7, pos=H, border=on]

ダイアログが消えますので、「Continue」ボタンをクリックします。
//image[apple_signin34][][scale=0.7, pos=H, border=on]

確認が表示あｓれますので、「Save」ボタンをクリックします。
//image[apple_signin35][][scale=0.7, pos=H, border=on]

サービスIDの取得が完了しました。
//image[apple_signin36][][scale=0.7, pos=H, border=on]

==== キーの取得
左サイドメニューから「Keys」を選択し、「+」をクリックします。
//image[apple_signin37][][scale=0.7, pos=H, border=on]

「Register a New Key」の画面で、「Key Name」にユニークなものを入力し、「Sign in with Apple」のチェックボックスをONにし、「Configure」ボタンをクリックします。
//image[apple_signin38][][scale=0.7, pos=H, border=on]

紐付けるアプリケーションIDを選択し、「Save」ボタンをクリックします。
//image[apple_signin39][][scale=0.7, pos=H, border=on]

確認画面になりますので、「Register」ボタンをクリックします。
//image[apple_signin40][][scale=0.7, pos=H, border=on]

キーIDを控え、「Download」ボタンをクリックします。一度しかダウンロードできません。
//image[apple_signin41][][scale=0.7, pos=H, border=on]

=== Firebaseへキーを登録
FirebaseコンソールのAuthenticationを選択し、「Sign-in method」でAppleの編集ボタンをクリックします。
//image[apple_signin42][][scale=0.7, pos=H, border=on]

「サービスID」、「AppleチームID」、「キーID」、ダウンロードしたファイルをテキストエディタで開き、秘密鍵をコピペします。
//image[apple_signin43][][scale=0.7, pos=H, border=on]

以上で準備は完了です。

== アプリケーションにAppleサインイン・メソッドの実装

@<href>{https://firebase.google.com/docs/auth/flutter/federated-auth?hl=ja&authuser=0#apple, Firebaseのサイト}にあるコードそのままです。

//image[apple_signin52][Firebaseドキュメント][scale=0.7, pos=H]

//list[][認証コントローラーへメソッド追加]{
  /// AppleIDでサインイン
  signInWithApple() async {
    final appleProvider = AppleAuthProvider();
    if (kIsWeb) {
      await _auth.signInWithPopup(appleProvider);
    } else {
      await _auth.signInWithAuthProvider(appleProvider);
    }
  }
//}

ログイン選択画面の「Appleアカウント」にメソッドを割り当てます。

//list[][ログイン選択画面のAppleアカウント]{
    Container(
      decoration: ThemeHelper().buttonBoxDecoration(context),
      child: ElevatedButton(
        style: ThemeHelper().buttonStyle(),
        child: Row(
            children: const [
              FaIcon(FontAwesomeIcons.apple, size: 23),
              Padding(
                padding: EdgeInsets.fromLTRB(30, 10, 0, 10),
                child: Text('Appleアカウント', style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold, color: Colors.white),),
              ),
            ]
        ),
        onPressed: (){
          authController.signInWithApple();
        },
      ),
    ),
//}

以上で完了です。

== 動作確認
==== iPhoneで確認
iPhoneシミュレータで動作確認しましたが、AppleIDでサインインは実機でないと動作しないとのことです。
実機を繋いでデバッグしましたところ動作しました。

//image[iPhoneResult][iPhoneシミュレータで確認][scale=0.7, pos=H]

==== Androidで確認
//image[androidResult2][Androidエミュレータで確認][scale=0.7, pos=H]

==== Firebaseで登録確認
Firebaseコンソールでも確認

//image[apple_signin59][Firebaseコンソール][scale=0.7, pos=H]