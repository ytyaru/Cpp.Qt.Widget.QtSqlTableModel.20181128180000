#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlField>
#include <QDir>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase _db = QSqlDatabase::addDatabase("QSQLITE", "Memo");
    QString dbPath = QDir(QApplication::applicationDirPath()).filePath("Memo.sqlite3");
    _db.setDatabaseName(dbPath);
    qDebug() << dbPath;

    QSqlDatabase db = QSqlDatabase::database("Memo");
    QSqlQuery query(db);
//    query.exec(tr("create table Memo(id INTEGER PRIMARY KEY AUTOINCREMENT, Memo TEXT, Created TEXT)"));
//    query.exec(tr("insert into Memo(Memo,Created) values('メモ内容だよ', '1999-12-31 23:59:59')"));
    query.exec(tr("select * from Memo"));
    while (query.next()) {
        qDebug() << query.value(0) << "|" << query.value(1) << "|" << query.value(2);
    }

    QSqlTableModel model(nullptr, db);
    qDebug() << model.tableName();
    model.setTable("Memo");
//    model.select();
    qDebug() << model.tableName();
    qDebug() << "columnCount: " << model.columnCount();

    QSqlRecord record;
    QSqlField fMemo("Memo");
    fMemo.setValue("追記したメモ");
    QSqlField fCreated("Created");
    fCreated.setValue("1999-12-31 23:59:59");
    record.append(fMemo);
    record.append(fCreated);
    model.insertRecord(0, record);
    model.submitAll();

    db.close();
    QSqlDatabase::removeDatabase("Memo");
}

MainWindow::~MainWindow()
{
    delete ui;
}
