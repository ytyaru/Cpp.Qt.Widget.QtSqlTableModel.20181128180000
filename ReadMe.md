# このソフトウェアについて

　Qt5学習。QtでSQLite3を使う。QSqlTableModelを使ってみた。

* 最初にcreate tableしておく必要がある
* QSqlRecordを渡してinsertできた

## 前回まで

* https://github.com/ytyaru/Cpp.Qt.Widget.QtSqliteDb.20181128160000
* https://github.com/ytyaru/Cpp.Qt.Widget.QtSqliteDb.20181128120000
* https://github.com/ytyaru/Cpp.Qt.Widget.QSql.SQLite3.Transaction.20181128070000
* https://github.com/ytyaru/Cpp.Qt.Widget.QSql.SQLite3.Class.20181127180000
* https://github.com/ytyaru/Cpp.Qt.Widget.QSql.SQLite3.Class.20181127170000
* https://github.com/ytyaru/Cpp.Qt.Widget.QSql.SQLite3.Class.20181127160000
* https://github.com/ytyaru/Cpp.Qt.Widget.QSql.SQLite3.Class.20181127130000

## コード抜粋

1. DB作成
1. テーブル作成
1. モデル作成
1. モデルからinsert

### 1. DB作成

```cpp
QSqlDatabase _db = QSqlDatabase::addDatabase("QSQLITE", "Memo");
QString dbPath = QDir(QApplication::applicationDirPath()).filePath("Memo.sqlite3");
_db.setDatabaseName(dbPath);
```
### 2. テーブル作成

```cpp
QSqlDatabase db = QSqlDatabase::database("Memo");
QSqlQuery query(db);
query.exec(tr("create table Memo(id INTEGER PRIMARY KEY AUTOINCREMENT, Memo TEXT, Created TEXT)"));
query.exec(tr("insert into Memo(Memo,Created) values('メモ内容だよ', '1999-12-31 23:59:59')"));
query.exec(tr("select * from Memo"));
while (query.next()) {
    qDebug() << query.value(0) << "|" << query.value(1) << "|" << query.value(2);
}
```

### 3. モデル作成

```cpp
QSqlTableModel model(nullptr, db);
qDebug() << model.tableName();
qDebug() << "columnCount: " << model.columnCount();
```

### 4. モデルからinsert

```cpp
QSqlField fMemo("Memo");
fMemo.setValue("追記したメモ");

QSqlField fCreated("Created");
fCreated.setValue("1999-12-31 23:59:59");

QSqlRecord record;
record.append(fMemo);
record.append(fCreated);

model.insertRecord(0, record);
model.submitAll();
```

　Fieldに関してはテーブル定義がすでにあるはずなので、情報を取得できそうだが。

## Qt要素

* http://doc.qt.io/qt-5/qsql.html
    * http://doc.qt.io/qt-5/qsqldatabase.html
    * http://doc.qt.io/qt-5/qsqlquery.html
    * http://doc.qt.io/qt-5/qsqlerror.html
    * http://doc.qt.io/qt-5/qsqltablemodel.html
    * http://doc.qt.io/qt-5/qsqlrecord.html
    * http://doc.qt.io/qt-5/qsqlfield.html

# 開発環境

* [Raspberry Pi](https://ja.wikipedia.org/wiki/Raspberry_Pi) 3 Model B+
    * [Raspbian](https://www.raspberrypi.org/downloads/raspbian/) GNU/Linux 9.0 (stretch) 2018-06-27
        * Qt 5.7.1

## 環境構築

* [Raspbian stretch で Qt5.7 インストールしたもの一覧](http://ytyaru.hatenablog.com/entry/2019/12/17/000000)

# ライセンス

　このソフトウェアはCC0ライセンスである。

[![CC0](http://i.creativecommons.org/p/zero/1.0/88x31.png "CC0")](http://creativecommons.org/publicdomain/zero/1.0/deed.ja)

## 利用ライブラリ

ライブラリ|ライセンス|ソースコード
----------|----------|------------
[Qt](http://doc.qt.io/)|[LGPL](http://doc.qt.io/qt-5/licensing.html)|[GitHub](https://github.com/qt)

* [参考1](https://www3.sra.co.jp/qt/licence/index.html)
* [参考2](http://kou-lowenergy.hatenablog.com/entry/2017/02/17/154720)
* [参考3](https://qiita.com/ynuma/items/e8749233677821a81fcc)
