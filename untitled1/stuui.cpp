﻿#include "stuui.h"
#include "ui_stuui.h"

StuUi::StuUi(QString user,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StuUi),user(user)
{
    ui->setupUi(this);
    connect(ui->queryBtn,&QPushButton::clicked,this,&StuUi::queryScoreSignal);
    showMessage();
}

StuUi::~StuUi()
{
    delete ui;
}

void StuUi::showMessage()
{
    QSqlQuery sql;

    QString str = "SELECT StuId, name, sex, college, major, classId FROM userstu WHERE StuId = ?";
    sql.prepare(str);  // 准备查询
    sql.addBindValue(user.toInt());  // 绑定参数

    if (!sql.exec()) {  // 执行查询并检查错误
        qDebug() << "Query execution failed:" << sql.lastError().text();
        return;
    }

    if (sql.next()) {  // 检查是否有结果
        // 赋值到 UI 控件
        ui->StuIdEdit->setText(sql.value(0).toString());
        ui->nameEdit->setText(sql.value(1).toString());
        ui->sexEdit->setText(sql.value(2).toString());
        ui->collageEdit->setText(sql.value(3).toString());
        ui->majorEdit->setText(sql.value(4).toString());
        ui->classIdEdit->setText(sql.value(5).toString());
    } else {
        qDebug() << "No results found.";  // 打印没有找到结果的信息
    }


}
