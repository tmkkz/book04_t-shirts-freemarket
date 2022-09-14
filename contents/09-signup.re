= 新規アカウント登録

//abstract{
  Firebase認証の新規アカウント作成ができるようにします。

　ストア情報コントローラができれば、Firebase認証に新規登録と同時にストア登録も行います。

なぜ、アカウントを別々に管理するのかといえば、Firebase Authのユーザー管理では指定された項目しか管理できないこと
Firebase Authユーザー情報にアクセスするには、Admin権限が必要になるためです。

//image[0901][][scale=0.7, pos=H]
//}

//makechaptitlepage[toc=on]

== 新規登録ができるようにする

手順は、

 1. 新規登録画面の修正と入力データの検証部分の作成
 2. スプラッシュスクリーンで認証コントローラを初期化
 3. 新規登録メソッドの実装
 4. ページ推移のためのRoute作成
 5. 動作確認

です。

本章からはGetXの機能をつかいますので、アプリケーションがGetXアプリケーションとして動作するように変更を加えます。具体的には、
「main.dart」ファイルにある「MaterialApp」を「GetMaterialApp」に変更します。

//list[][変更前]{
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Login UI',
      theme: ThemeData(
        primaryColor: _primaryColor,
        accentColor: _accentColor,
        scaffoldBackgroundColor: Colors.grey.shade100,
        primarySwatch: Colors.grey,
      ),
      home: SplashScreen(title: 'Flutter Login UI'),
    );
  }
//}

//list[][変更後]{
  @override
  Widget build(BuildContext context) {
    return GetMaterialApp(
      title: 'Flutter Login UI',
      theme: ThemeData(
        primaryColor: _primaryColor,
        accentColor: _accentColor,
        scaffoldBackgroundColor: Colors.grey.shade100,
        primarySwatch: Colors.grey,
      ),
      home: SplashScreen(title: 'Flutter Login UI'),
    );
  }
//}



== 新規登録画面の修正

編集対象は、「RegistrationPage（registration_page.dart）」です。

=== 新規登録画面の修正
新規登録画面の修正部分は、

//desclist{
//desc[1. ページをStatefulWidgetからStatelessWidgetへ変更]{
  コントローラーがデータを保持するため、画面では不要になります。
//}
//desc[2. 各フィールドを日本語化]{
  フィールド名、プレースホルダーを日本語化します。
//}
//desc[3. 登録ボタンからコントローラのメソッドを実行]{
  登録ボタンにコントローラーの新規登録メソッドを割り当てます。
//}
//desc[4. 入力データの検証]{
  登録ボタンクリック後、コントローラーのメソッドを呼ぶ前に各フィールドの入力値を検証します。
//}
//}

//blankline
それでは、始めましょう。

//image[0902][][scale=0.7, pos=H]

//clearpage

==== 1. StatefulWidgetからStatelessWidgetへ
まずは、ページ全体に対し、「StatefuleWidget」から「StatelessWidget」へ変更します。
//blankline
下図のように、

 * extends の後ろにある「StatefulWidget」を「StatelessWidget」へ変更。
 * 赤ワク部分を削除。

//image[to_stateless][][scale=1.0, pos=H]

//blankline
#@# textlint-disable
これを行うと、_formKey、setState（(）{})部分がエラーになるので削除します。
#@# textlint-enable
//image[to_stateless001][][scale=1.0, pos=H]

Android Studio上でlintの出すエラーがなくなれば、動作確認を行います。新規登録画面を開くことができれば問題ありません。

//blankline

===== 各フィールドとコントローラのTextEditingControllerの対応
アカウントの新規登録の際に入力する項目は、

 * 表示名 -- displayName
 * 氏名　-- name
 * メールアドレス　-- email
 * 携帯電話番号　-- phoneNumber
 * パスワード -- password

です。

//blankline
認証コントローラ側のTextEditingControllerには、上記のフィールド名+Controllerで命名してあります。
これらコントローラと画面上のTextFieldを結び付け、登録ボタンには新規登録メソッドを割り当てます。

//blankline
新規登録ページ（RegistrationPage）に、認証コントローラ（AuthController）をバインドします。ファイル「auth_controller.dart」を
インポートし、インスタンスを結び付けます。

//blankline
AuthControllerのインスタンス化は、のちほどスプラッシュスクリーンの起動で行うようにします。

//list[][AuthControllerをバインド]{
import '../controllers/auth_controller.dart';
import 'profile_page.dart';
import '../../common/theme_helper.dart';
import './widgets/header_widget.dart';

class RegistrationPage extends StatelessWidget {
  bool checkboxValue = false;
  final AuthController authController = AuthController.to;
//}

//blankline
テキストフィールドを「TextFormField」から「TextField」へ変更し、「controller:」プロパティへ
それぞれのコントローラをバインドします。フィールド名、ヒントを日本語にします。

//image[text_field01][変更前][scale=1.0, pos=H]
//image[text_field02][変更後][scale=1.0, pos=H]

//blankline
残りのフィールドにも同じ作業をします。

//clearpage
メールアドレス入力欄、電話番号の入力欄、パスワードの入力欄には、入力時のエラーチェック「validator」プロパティがありますが、
入力値検証は一ヵ所にまとめるため削除します。

//image[text_field03][][scale=1.0, pos=H]

//image[0903][][scale=0.7, pos=H]
//blankline
登録ボタンの後ろへソーシャルログインボタンがありますが、Row Widgetごと削除します。

//image[text_field04][desc][scale=0.7, pos=H]

//blankline
続いて、新規登録メソッドが実行される前に、入力されたデータが有効なのかをチェックする関数を作成します。

===== エラー表示用のSnackBarを作成
登録ボタンがクリックされコントローラの新規登録メソッド前に、入力値の検証をし
エラーが出た場合は、SnackBarを使って表示します。@<br>{}GetXは、SnackBarを簡単に出すことができます。

//blankline
エラー表示用のSnackBarを出す便利クラスを作成します。「lib/helper」フォルダを作成し
「utility.dart」ファイルを作成します。

//list[][lib/helper/utility.dart]{
import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'package:hexcolor/hexcolor.dart';

class Utility {
  static customSnackBar(String title,
      String message, [
        String? status,
      ]) {
    if (status != null) {
      late Icon icon;
      Color backgroundColor = HexColor('#FEEBFC');
      Color textColor = HexColor('#86468B');
      Color iconColor = HexColor('#FBC425');
      switch (status) {
        case 'success':
          backgroundColor = HexColor('#28a745');
          icon = Icon(Icons.task_alt, size: 24.0, color: textColor);
          break;
        case 'info':
          backgroundColor = HexColor('#007bff');
          icon = Icon(Icons.info_outline_rounded,
              size: 24.0, color: textColor);
          break;
        case 'warn':
          icon = Icon(Icons.warning_amber, size: 24.0, color: iconColor);
          break;
        case 'error':
          backgroundColor = HexColor('#dc3545');
          icon = Icon(Icons.error_outline, size: 24.0, color: textColor);
          break;
        default:
          break;
      }
      Get.snackbar(title, message,
          backgroundColor: backgroundColor,
          colorText: textColor,
          snackPosition: SnackPosition.BOTTOM,
          icon: icon,
          borderRadius: 5.0,
          borderColor: HexColor('#6c757d'),
          borderWidth: 2
      );
    } else {
      Get.snackbar(title, message,
          backgroundColor: Colors.white, snackPosition: SnackPosition.BOTTOM);
    }
  }
}
//}

//clearpage
@<B>{入力値検証}

新規登録ページ（registration_page.dart）へ以下のバリデーション・コードを追加します。

//blankline
GetXには、データのValidation機能もあります。


//list[][入力値検証]{
  /// 送信ボタンクリック時に各入力フィールドをチェック
  /// エラーの場合は、SnackBarを表示する。
  bool _validate() {
    // 表示名
    if (authController.displayNameController.text.isEmpty) {
      Utility.customSnackBar('入力確認', '表示名を入力してください。', 'warn');
      return false;
    }
    // 氏名
    if (authController.nameController.text.isEmpty) {
      Utility.customSnackBar('入力確認', '氏名を入力してください。', 'warn');
      return false;
    }
    // 表示名
    String val = authController.emailController.text.trim();
    if (val.isEmpty || !GetUtils.isEmail(val)) {
      Utility.customSnackBar('入力確認', '有効なメールアドレスを入力してください。', 'warn');
      return false;
    }
    // 携帯電話番号
    val = authController.phoneNumberController.text;
    if (!RegExp(r"^0[5789]0-[0-9]{4}-[0-9]{4}$").hasMatch(val)) {
      Utility.customSnackBar('入力確認', 'xxx-xxxx-xxxxで入力してください。。', 'warn');
      return false;
    }

    // パスワード
    RegExp passValid = RegExp(r"(?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=.*\W)");
    val = authController.passwordController.text.trim();
    if (!passValid.hasMatch(val) || val.length < 8) {
      Utility.customSnackBar('入力確認', '8文字a
      で新規登録画面の修正は完了です。、半角で英数大文字・小文字・数字・記号が各1文字以上', 'warn');
      return false;
    }
    // 利用規約同意
    if (!checkboxValue.value) {
      Utility.customSnackBar("入力確認", '利用規約同意が必要です。', 'warn');
      return false;
    }
    return true;
  }

//}

==== ページ上のデータ変更に伴う再描画
利用規約同意のチェックボックスの値が更新されたときは、チェックボックの値をもつ変数「checkboxValue」に格納されます。
しかし、変数の値が更新されても再描画はされません。

//blankline
元は、ページがStatefulWidgetでしたので変数の値の変更を「setState関数」で行い、「setState関数」がStatefulWidgetに
再描画を指示していました。

//blankline
現在は、StatelessWidgetへ変更しましたので、チェックボックスの値の「checkboxValue」をGetXを使って監視対象にします。

//blankline
//noindent
「bool checkboxValue = false;」
#@# textlint-disable
@<br>{}　　　　　↓@<br>{}
#@# textlint-enable
「final Rx<bool> checkboxValue = false.obs;」

に変更します。

//blankline
「obs」は、GetXの提供するオブザーバです。表示部分をGetXのWidgetで囲うことで
値の変化があれば、再描画の通知がされます。

//blankline
「obs」、「Rx<T>」などのGetXのオブザーバに変更しますと、checkboxValueの値は、「checkboxValue.value」でアクセスします。lintがエラーを出している部分を修正します。

//blankline
チェックボックスの値が変更されたときに再描画されるように、GetXのWidgetで「Checkbox」を囲みます。

//image[chckbox][][scale=1.0, pos=H]

@<B>{GetXのValidator}

GetXのUtilityクラスでは、

 * isNull
 * isNullOrBlank
 * isBlank
 * isNum
 * isNumericOnly
 * isAlphabetOnly
 * hasCapitalletter
 * isBool
 * isVideo
 * isImage

//blankline
など、たくさんのValidationがありますが厳密に検査していないものあります。
使うか使わないかは
@<href>{https://github.com/jonataslaw/getx/blob/master/lib/get_utils/src/get_utils/get_utils.dart, ソースコード}
を見て決めてください。

//blankline
@<b>{登録ボタン}

入力値検証後、認証コントローラの新規登録メソッドを呼ぶようにします。認証コントローラの「signup」メソッドは未作成ですので、現時点ではエラーになります。

//list[][認証後、新規登録メソッドを呼ぶ]{
  void _submit() {
    if (_validate()) {
      authController.signUp();
    }
  }
//}

//blankline
最後に、ボタンに上記関数を呼ぶように変更します。

//image[submit][][scale=1.0, pos=H]


以上で新規登録画面の修正は完了です。

//clearpage

=== スプラッシュスクリーンで認証コントローラを初期化
アプリケーション起動時に表示されるページの「スプラッシュスクリーン」へ認証コントローラ（AuthController）のインスタンス化を行うようコードを追加します。

//blankline
認証コントローラは、アプリケーションが起動した後、どのページへ推移するかを決めるため、Firebaseを初期化したようにアプリケーションの最初でもかまいません。

//blankline
GetXのパッケージ、auth_controller.dartのインポートを行い、
//blankline
#@# textlint-disable
　　　AuthController authController = Get.put（Authcontroller());
#@# textlint-enable
//blankline
で、インスタンス化を行います。一度インスタンス化を行うと、ほかのページからは「to」に指定した「Get.find()」でインスタンスにアクセスできます。

//image[0904][][scale=0.7, pos=H]

//image[authcontroller_instance][][scale=1.0, pos=H]


//clearpage
スプラッシュスクリーンでは、「accentColor」に取り消し線がついています。これは、近い将来のバージョンで消えるプロパティを意味します。

//image[accentColor][accentcolorに取り消し線][scale=1.0, pos=H]


@<href>{https://docs.flutter.dev/release/breaking-changes/theme-data-accent-properties, 公式サイト}に対処法があります。

「main.dart」を以下のように修正します。

//list[][修正前]{
      theme: ThemeData(
        primaryColor: _primaryColor,
        accentColor: _accentColor,
        scaffoldBackgroundColor: Colors.grey.shade100,
        primarySwatch: Colors.grey,
      ),
//}

//list[][修正後]{
      theme: ThemeData(
        primaryColor: _primaryColor,
        colorScheme: ColorScheme.fromSwatch().copyWith(secondary: _accentColor),
        scaffoldBackgroundColor: Colors.grey.shade100,
        primarySwatch: Colors.grey,
      ),
//}


スプラッシュスクリーン側は、
//blankline
#@# textlint-disable
//noindent
　　　colors:[Theme.of（context）.accentColor, Theme.of（context）.primaryColor],@<br>{}
  　　　　　　　　↓@<br>{}
    　　　colors:[Theme.of（context）.colorScheme.secondary, Theme.of（context）.primaryColor],
#@# textlint-enable
//blankline
に変更します。そのほかのファイルにも「accentColor」が使われていますので同じく修正してください。

=== 新規登録メソッドの実装
最後に、認証コントローラに新規登録メソッドを作成します。

Firebase認証でのメール/パスワードでログインを行うためには、新規ユーザー作成メソッドとして
「createUserWithEmailAndPassword()」が提供されています。

//blankline
詳細は、
@<href>{https://firebase.google.com/docs/auth/flutter/password-auth?hl=ja&authuser=0, 公式サイト}を確認してください。

公式サイトにあるコードをそのままですが、以下のように「singup()」メソッドを実装します。
//image[singup][Firebaseのドキュメント][scale=1.0, pos=H]

認証コントローラ（auth_controller.dart）へ以下のコードを追加します。

//list[][signupメソッド]{
  /// Error発生時にログイン状態を変更しSnackBarを表示
  void setAuthErrorMessage(String message) {
    Utility.customSnackBar('エラー', message);
  }

  /// アカウント新規作成
  Future<void> signUp() async {
    try {
      await _auth.createUserWithEmailAndPassword(
          email: emailController.text, password: passwordController.text);
      firebaseUser.value = _auth.currentUser;
    } on FirebaseAuthException catch(e) {
      if (e.code == 'email-already-in-use' {
        setAuthErrorMessage('このメールアドレスはすでに使用されています。');
      });
    } catch (error) {
      setAuthErrorMessage(error.toString());
    }
  }
//}

「singup()」メソッドを実装しましたので、「RegistrationPage」のエラーも解消されています。

=== ページ推移のためのRoute作成
ページの移動もGetXで管理できます。

//blankline
「lib/route」フォルダを作成し「app_route.dart」ファイルを作成します。

//list[][app_route.dart]{
import 'package:get/get.dart';

import '../pages/profile_page.dart';
import '../pages/splash_screen.dart';

class AppRoutes {
  AppRoutes._();
  static final routes = [
    GetPage(name: '/', page: () => SplashScreen(title: "")),
    GetPage(name: '/profile', page: () => ProfilePage()),
  ];
}
//}




//blankline
ここで作成したRoutesをGetMaterialAppに登録します。

//clearpage

//list[][main.dart]{
    @override
  Widget build(BuildContext context) {
    return GetMaterialApp(
      title: 'Flutter Login UI',
      theme: ThemeData(
        primaryColor: _primaryColor,
        colorScheme: ColorScheme.fromSwatch().copyWith(secondary: _accentColor),
        scaffoldBackgroundColor: Colors.grey.shade100,
        primarySwatch: Colors.grey,
      ),
      initialRoute: '/',
      getPages: AppRoutes.routes,
    );
  }
//}

スプラッシュスクリーンは、タイマーでログインページに移動するよう設定されていますが、GetXのRouteを使うように変更します。

//list[][SplashPage変更前]{
class _SplashScreenState extends State<SplashScreen> {
  bool _isVisible = false;

  AuthController authController = Get.put(AuthController());
  _SplashScreenState(){

    new Timer(const Duration(milliseconds: 2000), (){
      setState(() {
        Navigator.of(context).pushAndRemoveUntil(
        MaterialPageRoute(builder: (context) => LoginPage()), (route) => false);
      });
    });
//}

//list[][変更後]{
class _SplashScreenState extends State<SplashScreen> {
  bool _isVisible = false;

  AuthController authController = Get.put(AuthController());
  _SplashScreenState(){

    new Timer(const Duration(milliseconds: 2000), (){
      setState(() {
        Get.toNamed('/login');
      });
    });
//}

//clearpage
ログインページをRouteへ登録します。


//list[][lib/route/app_route.dart]{
class AppRoutes {
  AppRoutes._();
  static final routes = [
    GetPage(name: '/', page: () => SplashScreen(title: "")),
    GetPage(name: '/login', page: () => const LoginPage()),
    GetPage(name: '/profile', page: () => ProfilePage()),
  ];
}
//}

//image[0905][][scale=0.7, pos=H]
//clearpage
=== 動作確認

実装が完了しましたので、動作確認を行います。メールアドレスは確認されませんので、テスト目的ならメールアドレスの書式さえ合っていれば
「example@example.com」でもユーザー登録できます。

以下のように、新規登録ができました。入力エラー、登録エラーも表示されています。

//image[testresult][動作確認][scale=0.7, pos=H]

//blankline
Firebase側も登録されています。

//blankline
//image[firebase_auth01][Firebase認証][scale=0.7, pos=H]

//blankline
//blankline
#@# textlint-disable
//note[ここまでのソースコード]{
//terminal[][GitHub]{
　>git clone -b 05_signup https://github.com/risingforce9zz/tfreemarket.git
//}
//}
#@# textlint-enable
