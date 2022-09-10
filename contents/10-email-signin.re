= メール/パスワードでのサインイン

//abstract{
  新規アカウントが作成できるようになったので、メール/パスワードでサインインするメソッドを実装します。

  また、前章で新規登録画面からSNSサインインのボタンを削除したため、新たにログイン方法選択画面を作成します。
  サインイン成功時にページ推移するプロフィール画面には、サインアウトボタンを作成します。
//}

//makechaptitlepage[toc=on]
== メール/パスワードでサインインできるようになるまで

メール/パスワードでサインインするためには、

 * ログイン画面
 * ログイン成功時に表示するページ
 * パスワード・リセットの要求ページ
 * パスワード・リセット要求完了ページ

//blankline
が必要になります。

//blankline
幸い、元プロジェクトには必要なページが含まれていますので修正して使います。

//blankline
また、サンプルアプリケーションとしての拡張を考え、SNS認証の種類を増やせるように
ログイン方法選択画面を追加します。

== サインイン選択画面を作成
今回のアプリケーションは、SNS認証を含め4つのサインイン方法を提供しています。

//blankline
メール/パスワード認証は入力画面が必要ですが、
SNS認証はボタンのみ実装できます。仮に、SNS実装が増えてもボタンをひとつ増やし、認証コントローラーにログイン・メソッドを実装するだけになります。


//blankline
Firebase認証は、

今回実装する、「Twitter」、「Google」、「Apple」だけでなく「Facebook」、「GitHub」、「Microsoft」、「米Yahoo!」などの
SNSログインに対応しています。


//blankline
将来的に、ログイン方法を増やすことが容易になるよう新しく「ログイン方法選択画面」を作成します。
//image[03_test01-min][作成する画面][scale=0.4, pos=H]
//blankline
「lib/pages」フォルダに「select_signin_page.dart」ファイルを作成します。

//list[][select_signin_page.dart]{
import 'package:flutter/material.dart';
import 'package:font_awesome_flutter/font_awesome_flutter.dart';
import 'package:get/get.dart';

import '../common/theme_helper.dart';
import 'widgets/header_widget.dart';


class SelectSignInPage extends StatelessWidget{
  const LoginPage({Key? key}): super(key:key);

  
  final double _headerHeight = 250;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.white,
      body: SingleChildScrollView(
        child: Column(
          children: [
            SizedBox(
              height: _headerHeight,
              child: HeaderWidget(_headerHeight, true, Icons.storefront), //let's create a common header widget
            ),
            SafeArea(
              child: Container(
                  padding: const EdgeInsets.fromLTRB(20, 0, 20, 0),
                  margin: const EdgeInsets.fromLTRB(20, 0, 20, 0),// This will be the login form
                  child: Column(
                    children: [
                      const SizedBox(height: 20.0,),
                      const Text(
                        '以下の方法でログインできます。',
                        style: TextStyle(color: Colors.grey),
                      ),
                      const SizedBox(height: 20.0,),
                      Container(
                        decoration: ThemeHelper().buttonBoxDecoration(context),
                        child: ElevatedButton(
                          style: ThemeHelper().buttonStyle(),
                          child: Row(
                              children: const <Widget>[
                                FaIcon(FontAwesomeIcons.envelope, size: 23),
                                Padding(
                                  padding: EdgeInsets.fromLTRB(30, 10, 0, 10),
                                  child: Text('Emailとパスワード', style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold, color: Colors.white),),
                                ),
                              ]
                          ),
                          onPressed: (){
                            Get.toNamed('/login');
                          },
                        ),
                      ),
                      const SizedBox(height: 20.0,),
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
                          },
                        ),
                      ),
                      const SizedBox(height: 20.0,),
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
                          },
                        ),
                      ),
                      const SizedBox(height: 20.0,),
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
                          },
                        ),
                      ),
                      const SizedBox(height: 20.0,),
                      Container(
                        decoration: ThemeHelper().buttonBoxDecoration(context),
                        child: ElevatedButton(
                          style: ThemeHelper().buttonStyle(),
                          child: Row(
                              children: const [
                                FaIcon(FontAwesomeIcons.userPlus, size: 23,),
                                Padding(
                                  padding: EdgeInsets.fromLTRB(30, 10, 40, 10),
                                  child: Text('新規作成', style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold, color: Colors.white),),
                                ),
                              ]
                          ),
                          onPressed: (){
                            Get.toNamed('/registration');
                          },
                        ),
                      ),
                    ],
                  )
              ),
            ),
          ],
        ),
      ),
    );

  }
}
//}

//blankline
Routeに、「SelectSignInPage」を加え、スプラッシュスクリーンから「SelectSignInPage」へ推移するよう変更します。
また、「LoginPage」、「ForgotPasswordPage」、「ForgotPasswordVerificationPage」もRouteへ追加します。

//list[][Route]{
class AppRoutes {
  AppRoutes._();

  static final routes = [
    GetPage(name: '/', page: () => SplashScreen(title: "")),
    GetPage(name: '/select-signin', page: () => SelectSignInPage()),
    GetPage(name: '/login', page: () => LoginPage()),
    GetPage(name: '/forgotpassword', page: () => ForgotPasswordPage()),
    GetPage(
        name: '/forgotpassword-verify',
        page: () => const ForgotPasswordVerificationPage()),
    GetPage(name: '/registration', page: () => RegistrationPage()),
    GetPage(name: '/profile', page: () => ProfilePage()),
  ];
}
//}

//blankline

//list[][スプラッシュスクリーンの移動先の変更]{
class _SplashScreenState extends State<SplashScreen> {
  bool _isVisible = false;

  AuthController authController = Get.put(AuthController());
  _SplashScreenState(){

    new Timer(const Duration(milliseconds: 2000), (){
      setState(() {
        Get.toNamed('/select-signin');　@<balloon>{ログイン方法選択画面へ}
      });
    });
//}


== LoginPageの修正
ログインページの修正を行います。

 * StatelessWidgetへの変更
 * 入力フィールドと認証コントローラーのTextEditingControllerの結びつけ
 * 日本語化
 * パスワード忘れのページ推移

=== StatelessWigdetへの変更
LoginPage（lib/pages/login_page.dart）を開き、赤ワク部分を削除します。「extends」後の継承元を
「StatefulWidget」から「StatelessWidget」へ変更します。

//image[01_login01][][scale=0.7, pos=H]

=== 入力フィールドと認証コントローラーの結びつけ
認証コントローラーをLoginPageにバインドします。

//list[][LoginPageへ認証コントローラーをバインド]{
class LoginPage extends StatelessWidget {
  LoginPage({Key? key}) : super(key: key);

  double _headerHeight = 250;

  final AuthController authController = AuthController.to;
//}


メールアドレス、パスワード入力欄の「TextFieldのcontroller」プロパティに認証コントローラーのTextEditingControllerを指定します。
日本語化も同時に行います。

//image[01_login02][変更前][scale=0.7, pos=H]

//image[01_login03][変更後][scale=0.7, pos=H]

=== パスワード忘れへのページ推移
ページのナビゲーションをGetXに変更します。Routeは既に追加してあります。

//list[][ナビゲーションの変更]{
  Container(
    margin: EdgeInsets.fromLTRB(10, 0, 10, 20),
    alignment: Alignment.topRight,
    child: GestureDetector(
      onTap: () {
        Get.toNamed('/forgotpassword');
      },
      child: Text("パスワードを忘れましたか?",
        style: TextStyle(color: Colors.grey,),
      ),
    ),
  ),
//}


== ForgotPasswordPageの修正
パスワード・リセット要求のページを修正します。

 * StatelessWidgetへ変更
 * 認証コントローラーのバインドし、メールアドレス欄にコントローラーをセット
 * 日本語化
 * ログインページ戻るナビゲーションをGetXに
 * 送信ボタンに認証コントローラーのパスワードリセットをバインド
 * メールアドレス欄の入力検証

=== StatelessWidgetへ変更

赤ワク内を削除し、「StatefulWidget」を「StatelessWidget」へ変更します。
//image[02_forgotpass01][StatelessWidgetへ][scale=0.7, pos=H]

=== 認証コントローラーのバンドル

//list[][認証コントローラーのバンドル]{
class ForgotPasswordPage extends StatelessWidget {
  ForgotPasswordPage({Key? key}) : super(key: key);

  final AuthController authController = AuthController.to;

  @override
  Widget build(BuildContext context) {
    double _headerHeight = 300;
    return Scaffold(
        backgroundColor: Colors.white,
        body: SingleChildScrollView(
//}


メールアドレス欄に認証コントローラーのTextEditingControllerをバインド。
//image[02_forgotpass02][][scale=0.7, pos=H]

=== LoginPageへ戻るナビゲーション

戻るリンクのナビゲーションをGetXにします。Routeには既にあります。

//list[][ナビゲーションリンク]{
  Text.rich(
    TextSpan(
      children: [
        TextSpan(text: "思い出しましたか? "),
        TextSpan(
          text: 'サインインへ',
          recognizer: TapGestureRecognizer()
            ..onTap = () {
              Get.toNamed('/login');
            },
          style: TextStyle(
              fontWeight: FontWeight.bold
          ),
        ),
      ],
    ),
  ),
//}

=== 送信ボタンへパスワードリセットメソッドをバインド

メールアドレス欄に入力された値を検証し、問題なければ認証コントローラーの「パスワードリセット」メソッドを実行します。

//list[][入力欄の検証とメソッド実行]{

 /// 送信ボタンクリック時にメールアドレス・フィールドをチェック
  /// エラーの場合は、SnackBarを表示する。
  bool _validate() {
    String val = authController.emailController.text.trim();
    if (val.isEmpty || !GetUtils.isEmail(val)) {
      Utility.customSnackBar('入力確認', '有効なメールアドレスを入力してください。', 'warn');
      return false;
    }
    return true;
  }

  /// 入力値を検証し送信
  void _submit() {
    if (_validate()) {
      authController.passwordReset();
    }
  }

//}

//blankline
送信ボタンへメソッドの割当をします。
//blankline

//list[][パスワード・リセット要求メソッドの割当]{
    Container(
      decoration: ThemeHelper().buttonBoxDecoration(context),
      child: ElevatedButton(
        style: ThemeHelper().buttonStyle(),
        child: Padding(
          padding: const EdgeInsets.fromLTRB(
              40, 10, 40, 10),
          child: Text(
            "送信",
            style: TextStyle(
              fontSize: 20,
              fontWeight: FontWeight.bold,
              color: Colors.white,
            ),
          ),
        ),
        onPressed: () {
            _submit();
        },
      ),
    ),
//}



== サインアウトの実装
サインインが出来ると当然ですがサインアウトの機能も必要です。

次の号でドロワーを実装し、ドロワーにサインアウトできる機能を置く予定です。
ログイン後にアクセスする全ページにドロワーがありますので、どのページからもサインアウトができるようになります。

//blankline
それまでは、サインイン後にページ推移するプロフィールページにサインアウトボタンを置きます。

サインアウト・メソッドは、認証コントローラーが持っていますので、バインドします。

//list[][認証コントローラーのバインド]{
class _ProfilePageState extends State<ProfilePage>{

  AuthController authController = AuthController.to;
  double  _drawerIconSize = 24;
  double _drawerFontSize = 17;

//}

プロフィールページ（profile_page.dart）へサインアウトボタンを追加し、サインアウト・メソッドの呼び出しを行います。

//list[label][desc]{
  // 
  Container(
    decoration:
    ThemeHelper().buttonBoxDecoration(context),
    child: ElevatedButton(
        style: ThemeHelper().buttonStyle(),
        child: const Padding(
          padding: EdgeInsets.fromLTRB(40, 10, 40, 10),
          child: Text(
            "サインアウト",
            style: TextStyle(
              fontSize: 20,
              fontWeight: FontWeight.bold,
              color: Colors.white,
            ),
          ),
        ),
        onPressed: () {
          authController.singOut();
        }),
  ),
//}


== パスワード・リセット要求完了ページ

Firebase認証で使うメール/パスワードでのサインインでのパスワード・リセットは、

 1. パスワード・リセットの要求。
 2. Firebaseから登録メールアドレスへリセット用リンクをメールで送信。
 3. リンクをクリックし表示されるページで新パスワードの登録。

となります。

//blankline
パスワード・リセット要求ページは出来ましたので、要求成功時に表示されるページを用意します。
//blankline
元プロジェクトには、「forgot_password_valification_page.dart」がありますので、
これを利用します。

//blankline
以下が、「forgot_password_valification_page.dart」の変更後になります。

//list[][パスワード・リセット要求完了ページ]{
import 'package:flutter/gestures.dart';
import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'package:otp_text_field/otp_field.dart';
import 'package:otp_text_field/style.dart';

import 'profile_page.dart';
import 'widgets/header_widget.dart';
import '../../common/theme_helper.dart';

class ForgotPasswordVerificationPage extends StatelessWidget {
  const ForgotPasswordVerificationPage({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    double _headerHeight = 300;

    return Scaffold(
        backgroundColor: Colors.white,
        body: SingleChildScrollView(
          child: Column(
            children: [
              Container(
                height: _headerHeight,
                child: HeaderWidget(
                    _headerHeight, true, Icons.privacy_tip_outlined),
              ),
              SafeArea(
                child: Container(
                  margin: EdgeInsets.fromLTRB(25, 10, 25, 10),
                  padding: EdgeInsets.fromLTRB(10, 0, 10, 0),
                  child: Column(
                    children: [
                      Container(
                        alignment: Alignment.topLeft,
                        margin: EdgeInsets.fromLTRB(20, 0, 20, 0),
                        child: Column(
                          mainAxisAlignment: MainAxisAlignment.start,
                          crossAxisAlignment: CrossAxisAlignment.start,
                          children: [
                            Text(
                              'パスワードリセット',
                              style: TextStyle(
                                  fontSize: 28,
                                  fontWeight: FontWeight.bold,
                                  color: Colors.black54),
                              // textAlign: TextAlign.center,
                            ),
                            SizedBox(
                              height: 10,
                            ),
                            Text(
                              '入力したメールアドレス宛にパスワードリセットリンクを送りました。',
                              style: TextStyle(
                                  // fontSize: 20,
                                  fontWeight: FontWeight.bold,
                                  color: Colors.black54),
                              // textAlign: TextAlign.center,
                            ),
                          ],
                        ),
                      ),
                      SizedBox(height: 40.0),
                      Column(
                        children: <Widget>[
                          SizedBox(height: 50.0),
                          SizedBox(height: 40.0),
                          Container(
                            decoration: ThemeHelper().buttonBoxDecoration(
                                context, "#AAAAAA", "#757575"),
                            child: ElevatedButton(
                                style: ThemeHelper().buttonStyle(),
                                child: Padding(
                                  padding:
                                      const EdgeInsets.fromLTRB(40, 10, 40, 10),
                                  child: Text(
                                    "戻る",
                                    style: TextStyle(
                                      fontSize: 20,
                                      fontWeight: FontWeight.bold,
                                      color: Colors.white,
                                    ),
                                  ),
                                ),
                                onPressed: () {
                                  Get.toNamed('/select-signin');
                                }),
                          ),
                        ],
                      ),
                    ],
                  ),
                ),
              )
            ],
          ),
        ));
  }
}
//}


== 認証コントローラーにメソッドの実装
上記の修正で必要になりましたメソッドを、認証コントローラーに、

 * メール/パスワードでのサインイン・メソッド
 * サインアウト・メソッド
 * パスワードリセット・メソッド

実装します。

=== メール/パスワードサインイン・メソッド
認証コントローラーに、メール/パスワードでサインインするメソッドを追加します。

//list[][サインイン・メソッド]{
  /// Email, passwordでサインイン
  Future<void> signIn() async {
    try {
      await _auth.signInWithEmailAndPassword(
          email: emailController.text, password: passwordController.text);
      firebaseUser.value = _auth.currentUser;
    } on FirebaseException catch (e) {
      if (e.code == 'firebase_auth/user-not-found') {
        Utility.customSnackBar('エラー', 'このEmailではユーザ登録されていません。');
      } else {
        Utility.customSnackBar('エラー', e.message ?? 'サインイン時に特定できないエラーが発生しました。');
      }
    } catch (e) {
      Utility.customSnackBar('エラー', e.toString());
    }
  }
//}

=== サインアウト・メソッド

認証コントローラーに、サインインアウトするメソッドを追加します。

//list[][サインアウト・メソッド]{
 /// サインアウト
  void singOut() async {
    await _auth.signOut();
    firebaseUser.value = _auth.currentUser;
  }
//}

=== パスワードリセット・メソッド

認証コントローラーに、パスワードリセットメソッドを追加します。

//list[][パスワードリセット・メソッド]{
  ///パスワードリセット
  Future<void> passwordReset() async {
    try {
      await _auth.sendPasswordResetEmail(email: emailController.text);
      Get.offAll('./select-signin');
    } catch (error) {
      setAuthErrorMessage('パスワードリセットでエラーが発生しました。');
    }
  }
//}


== 動作確認
実装が完了しましたので、動作確認を行います。

=== Route
リンクが正常に機能しているか？

//image[route][ナビゲーションテスト][scale=0.7, pos=H]

=== メール/パスワードでのサインイン

Firebaseに登録されていないメールアドレスでエラーは表示されるか？

//image[03_test05-min][登録メールアドレスなしテスト][scale=0.4, pos=H]

正常にログインできるか？

//image[test_login][ログインテスト][scale=0.7, pos=H]

=== サインアウト
「サインアウト」ボタンで、サインアウトし「ログイン選択画面」へ戻るか？

//image[signout][サインアウトテスト][scale=0.7, pos=H]


=== パスワード・リセット
パスワード・リセットの動作確認です。問題無く動作しています。

//image[passreset][パスワード・リセット][scale=0.7, pos=H]

メールも届きます。
//image[resetmail][パスワード・リセット用メール][scale=0.7, pos=H]