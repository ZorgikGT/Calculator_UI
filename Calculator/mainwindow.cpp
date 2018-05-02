#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtSql>
#include <iostream>
#include <QCoreApplication>
#include <QMessageBox>

double first_number;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_plusMinus,SIGNAL(clicked()),this,SLOT(pushButton_plusMinus()));
    connect(ui->pushButton_percent,SIGNAL(clicked()),this,SLOT(pushButton_percent()));
    connect(ui->pushButton_plus,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_minus,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_multiply,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->pushButton_divide,SIGNAL(clicked()),this,SLOT(math_operations()));

    ui->pushButton_divide->setCheckable(true);
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers()
{
    QPushButton *button = (QPushButton *)sender();
    QString new_label;
    double all_number;

    all_number = (ui->label->text() + button->text()).toDouble();
    new_label = QString::number(all_number, 'g', 15);
    ui->label->setText(new_label);
}

void MainWindow::on_pushButton_point_clicked()
{
    if(!(ui->label->text().contains('.'))) {
    ui->label->setText(ui->label->text() + ".");
    }
}

void MainWindow::pushButton_plusMinus()
{
    QPushButton *button = (QPushButton *)sender();
    QString new_label;
    double all_number;
    qDebug() << "Работат";

    if(button->text() == "+/-")
    {
        all_number = ui->label->text().toDouble();
        all_number = all_number * -1;
        new_label = QString::number(all_number, 'g', 15);
        ui->label->setText(new_label);
    }
}

void MainWindow::pushButton_percent()
{
    QPushButton *button = (QPushButton *)sender();
    QString new_label;
    double all_number;
    if(button->text() == "%") {
            all_number = (ui->label->text()).toDouble();
            all_number = all_number * 0.01;
            new_label = QString::number(all_number, 'g', 15);
            ui->label->setText(new_label);
        }
}

void MainWindow::math_operations()
{
    QPushButton *button = (QPushButton*) sender();
    first_number = ui->label->text().toDouble();
    button->setChecked(true);
    ui->label->setText("");
}



void MainWindow::on_pushButton_equal_clicked()
{
    double label_number, num_second;
    QString new_label;

    num_second = ui->label->text().toDouble();

    if(ui->pushButton_plus->isChecked()) {
        label_number = first_number + num_second;
        new_label = QString::number(label_number, 'g', 15);
        ui->label->setText(new_label);
        ui->pushButton_plus->setChecked(false);
    }

    if(ui->pushButton_minus->isChecked()) {
        label_number = first_number - num_second;
        new_label = QString::number(label_number, 'g', 15);
        ui->label->setText(new_label);
        ui->pushButton_minus->setChecked(false);
    }

    if(ui->pushButton_divide->isChecked()) {
        label_number = first_number / num_second;
        new_label = QString::number(label_number, 'g', 15);
        ui->label->setText(new_label);
        ui->pushButton_divide->setChecked(false);
    }

    if(ui->pushButton_multiply->isChecked()) {
        label_number = first_number * num_second;
        new_label = QString::number(label_number, 'g', 15);
        ui->label->setText(new_label);
        ui->pushButton_multiply->setChecked(false);
    }
}

void MainWindow::on_pushButton_clear_clicked()
{
    QString new_label = " ";
    ui->label->setText(new_label);
}

void MainWindow::on_pushButton_Insert_clicked()
{
    QString userComment, result;
    QString fullRequest;
    userComment = ui->UserComment->text();

    result = ui->label->text();

    QSqlQuery a_query;

    fullRequest = "INSERT INTO CalcResults (Comment, Results) VALUES ('" + userComment + "', '" + result + "') ";

    if (!a_query.exec(fullRequest)) {
        QMessageBox::about(this, "ОЙ, ой, ой!", "Попробуйте ввести еще раз без скобок, кавычек и т.д.");
    }

    QMessageBox::about(this, "Insert complete", "Все удачно записалось!");

}

void MainWindow::on_pushButton_userSelect_clicked()
{
    QString userComment, new_userSelect;
    QString fullRequest = "SELECT Comment, Results FROM CalcResults";
    userComment = ui->userSelect->text();

    QSqlQuery a_query;

    fullRequest = "SELECT Comment, Results FROM CalcResults WHERE Comment = '" + userComment + "' ";

    if (!a_query.exec(fullRequest)) {
        QMessageBox::about(this, "ОЙ, ой, ой!", "Мы не можем подключиться. Попробуйте позже.");
    }

    QSqlRecord rec = a_query.record();
    int result;
    QString comment;

    if (!a_query.next()) {
        QMessageBox::about(this, "ОЙ, ой, ой!", "Такого комментария не существует.");
    }

    while (a_query.next()) {
        comment = a_query.value(rec.indexOf("Comment")).toString();
        result = a_query.value(rec.indexOf("Results")).toInt();
        new_userSelect = QString::number(result);
        ui->userSelect->setText(comment + " : " + new_userSelect);

    }
}
