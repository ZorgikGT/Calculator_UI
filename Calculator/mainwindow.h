#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void digits_numbers();
    void on_pushButton_point_clicked();
    void pushButton_plusMinus();
    void pushButton_percent();
    void math_operations();
    void on_pushButton_equal_clicked();
    void on_pushButton_clear_clicked();
    void on_pushButton_Insert_clicked();
    void on_pushButton_userSelect_clicked();
};

#endif // MAINWINDOW_H
