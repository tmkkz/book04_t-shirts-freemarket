= 状態管理コントローラを作る

//abstract{
  認証状態を管理する状態コントローラを作成します。

//blankline
コントローラには、管理するデータとデータを変更するメソッドがあります。
//}

//makechaptitlepage[toc=on]

== GetXコントローラ

公式サイト
https://pub.dev/packages/get

GitHub
https://github.com/jonataslaw/getx

==== インストール
ターミナルに「flutter pub add get」と入力しエンターキーを押します。

//terminal[][GetXのインストール]{
 ❯ flutter pub add get
 Resolving dependencies...
 + get 4.6.5
   material_color_utilities 0.1.5 (0.2.0 available)
   source_span 1.9.0 (1.9.1 available)
   test_api 0.4.12 (0.4.13 available)
   vector_math 2.1.2 (2.1.3 available)
 Changed 1 dependency!

//}


GetXは、状態管理以外にもできることが多くあります。その機能が必要になった時点で個別に説明しますが、

 * State management 状態管理
 * dependency_anagement 依存管理
 * route management ルート管理

が、大きな機能です。

//blankline
そのほかにも、国際化対応、検証（validation）などがあります。

GetXの特徴は、下図のように、

 * コントローラは、データとデータ更新用メソッドをもつ。
 * 表示は、GetXのWidgetにコントローラのデータを表示させる。
 * ボタンなど操作部は、コントローラのメソッドを呼び出す。

 と配置され、

 1. 操作部からコントローラのメソッドが呼ばれる。
 2. コントローラ内でメソッドが実行され、データ更新。
 3. GetXのしくみで表示用Widgetにデータ変更の通知。
 4. 表示用Widgetが再描画。

 と、流れます。

//image[getx_flow][][scale=0.5, pos=H]

== 認証コントローラの作成

認証コントローラ（authController）は、以下のようなフローで動作します。

 * 画面のテキストフィールドは、コントローラがもつ。
 * サインインなどのメソッドもコントローラがもつ。
 * コントローラは、Firebase Userデータをもつ。
 * Firebase Userデータは、認証状態が変わると通知を受ける。
 * GetXには、イベント発生時にコールバックを呼び出すWorkerがある。
 * コールバックで表示ページを切り替える。

//image[auth_controller01][][scale=0.7, pos=H]

=== GetXControllerについて
GetXController作成前に、もう少しGetXControllerについて知っておくことがあります。

//blankline
==== GetXコントローラはライフサイクルがある。
GetXコントローラには、ライフサイクルがあり以下のイベント発生時にメソッド呼び出しができます。

 * onInit 初期化されたとき
 * onReady 準備完了したとき
 * onClose 終了するとき

//blankline
 GetXコントローラには、Workerと呼ばれるしくみがあり、監視対象が変更されるとコールバックを呼び出せる。

 * ever（監視対象, コールバック）　監視対象が更新されるたびにコールバックされる。
 * once（(監視対象, コールバック）　監視対象が更新と一度だけコールバックされる。
 * debounce（監視対象, コールバック, time:時間の長さ）　監視対象が更新され、経過時間後にコールバックされる。
 * interval（監視対象, コールバック, time:時間の長さ）　指定した時間内の監視対象が更新は無視する。

//blankline
GetXコントローラがもつデータは、監視対象（更新されると通知する）と通常の変数がある。

//list[][監視対象]{

  // 監視対象のデータに「.obs」を付ける。
  var checkBoxVal = false.obs;

  // Rx、Rxnと型で作り初期化する。
  final userName = Rx<String>('');
//}

では、いよいよ認証コントローラの作成に入ります。

=== AuthControllerの作成
コントローラは今後もアプリ内で増えていきますので、lib/controllersフォルダを作成し、
「auth_controller.dart」ファイルを作成します。

//blankline
コード内容は、

 * 新規登録・メール/パスワードサインイン画面のテキストフィールドコントロールを定義
 * 監視対象データ「firebaseUser」を定義し、nullで初期化
 * コントローラの初期化イベントでテキストフィールドコントロールをインスタンス化
 * onReadyイベントで、firebaseUserの状態に更新があれば「hundleAuthChanged」呼び出しWorker作成
 * onReadyイベントで、firebaseUserをFirebaseから通知を受けるよう設定。
 * onCloseイベントでテキストフィールドコントロールを削除
 * handleAuthChangedが呼ばれると、firebaseUserが「null」であれば「/login」へ

//blankline
現時点では、アプリを起動してもAuthControllerはどこからも参照されていないので何も起こりません。


//list[][lib/auth_controller.dart]{
import 'package:firebase_auth/firebase_auth.dart';
import 'package:flutter/material.dart';
import 'package:get/get.dart';

enum TextEditingControllerStatus { init, clear, dispose }

class AuthController extends GetxController {
  static AuthController get to => Get.find();

  /// 新規作成画面、サインイン画面で使用するTextEditingController
  late TextEditingController nameController;
  late TextEditingController displayNameController;
  late TextEditingController emailController;
  late TextEditingController passwordController;
  late TextEditingController phoneNumberController;
  late TextEditingController profilePicController;
  late TextEditingController storeDescriptionController;

  final FirebaseAuth _auth = FirebaseAuth.instance;

  /// firebaseのユーザ firebase_authで定義されている。
  Rxn<User> firebaseUser = Rxn<User>();

  @override
  void onInit() {
    nameController = TextEditingController();
    displayNameController = TextEditingController();
    emailController = TextEditingController();
    passwordController = TextEditingController();
    phoneNumberController = TextEditingController();
    profilePicController = TextEditingController();
    storeDescriptionController = TextEditingController();
    super.onInit();
  }

  @override
  void onReady() {
    /// getXのworker、監視対象(引数1)に変化があった場合、引数2のコールバックを呼び出す。
    /// everは毎回。
    ever(firebaseUser, handleAuthChanged);
    firebaseUser.bindStream(_auth.authStateChanges());
    super.onReady();
  }

  @override
  void onClose() {
    handleTextEditingControllers(TextEditingControllerStatus.dispose);
    super.onClose();
  }

  /// textEditingControllerの初期化、終了処理
  void handleTextEditingControllers(TextEditingControllerStatus status) {
    List<TextEditingController> textEditingControllers = [
      nameController,
      displayNameController,
      emailController,
      passwordController,
      phoneNumberController,
      profilePicController,
      storeDescriptionController,
    ];

    switch (status) {
      case TextEditingControllerStatus.clear:
        for (var controller in textEditingControllers) {
          controller.clear();
        }
        break;
      case TextEditingControllerStatus.dispose:
        for (var controller in textEditingControllers) {
          controller.dispose();
        }
        break;
      default:
        break;
    }
  }

  /// firebaseUserの状態が変化したときに呼ばれる
  handleAuthChanged(_firebaseUser) async {
    if (_firebaseUser == null) {
      handleTextEditingControllers(TextEditingControllerStatus.clear);
      if (Get.currentRoute != '/login') {
        Get.toNamed('/login');
      }
    } else {
      if (Get.currentRoute != '/profile') {
        Get.toNamed('/profile');
      }
    }
  }
}

//}


以上で、認証コントローラの根本ができました。次の章からユーザー新規登録ができるようにします。

#@# textlint-disable
//blankline
//note[ここまでのソースコード]{
//terminal[][GitHub]{
　>git clone -b 04_auth_controller https://github.com/risingforce9zz/tfreemarket.git
//}
//}
#@# textlint-enable
