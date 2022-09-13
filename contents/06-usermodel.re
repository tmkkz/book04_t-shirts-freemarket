= アプリで認証するユーザーのデータ型を作成する。

//abstract{
  アプリで使うストア情報（Firebaseを使用するユーザーとは別）のデータ型を作成します。

//blankline
 Firebaseの認証後、受け取った情報を元に認証コントローラーでフリーマーケット出店者として登録します。

//image[0601][][scale=0.7, pos=H]
//}

//makechaptitlepage[toc=on]

== ユーザーモデルの作成

アプリで認証するユーザー（今回は、オンライン・フリーマーケットの出店者で、なおかつ購入者）の必要な情報を
検討しデータ型を作成します。

libフォルダ内に「models」フォルダを作成し、「user_model.dart」ファイルを作成します。内容は以下となります。

//list[][ユーザーモデル型]{
class UserModel {

  String id ='';
  String name = '';
  String displayName = '';
  String email = '';
  String phoneNumber = '';
  String profilePic = '';
  String storeDescription = '';

  UserModel({
    required this.id,
    required this.name,
    required this.displayName,
    required this.email,
    required this.phoneNumber,
    required this.profilePic,
    required this.storeDescription,
  });

  Map<String, dynamic> toMap() {
    return {
      'id': id,
      'name': name,
      'displayName': displayName,
      'email': email,
      'phoneNumber': phoneNumber,
      'profilePic': profilePic,
      'storeDescription': storeDescription,
    };
  }

  UserModel.fromMap(Map<dynamic, dynamic>? map) {
    if (map == null) {
      return;
    }
    id = map["id"];
    name = map['name'];
    displayName = map['displayName'];
    email = map['email'];
    phoneNumber = map['phoneNumber'];
    profilePic = map['profilePic'];
    storeDescription = map['storeDescription'];
  }

  UserModel copyWith({
    String? id,
    String? name,
    String? displayName,
    String? email,
    String? phoneNumber,
    String? profilePic,
    String? storeDescription,
  }) {
    return UserModel(
      id: id ?? this.id,
      name: name ?? this.name,
      displayName: displayName ?? this.displayName,
      email: email ?? this.email,
      phoneNumber: phoneNumber ?? this.phoneNumber,
      profilePic: profilePic ?? this.profilePic,
      storeDescription: storeDescription ?? this.storeDescription,
    );
  }
}
//}

#@# textlint-disable
//note[ここまでのソースコード]{
//terminal[][GitHub]{
　>git clone -b 02_login_screens_import https://github.com/risingforce9zz/tfreemarket.git
//}
//}
#@# textlint-enable
