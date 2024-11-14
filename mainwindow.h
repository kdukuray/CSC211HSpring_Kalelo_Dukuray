#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <Qpixmap>
#include <vector>
#include "food.h"
#include <fstream>
#include "user.h"
#include "height.h"
#include <stdlib.h>
#include <time.h>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <cctype>
#include <string>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void on_register_btn_clicked();

    //void on_login_btn_clicked();

    //void on_submit_login_btn_clicked();

   // void on_get_coached_btn_clicked();

    //void on_submit_calories_coach_clicked();

    void load_foods();

    void load_users();
    void load_nutrifacts();

    //void on_pushButton_3_clicked();


    void on_loginp_submit_login_btn_clicked();

    void on_userpp_get_coached_btn_clicked();

    void on_userpp_new_fact_btn_clicked();

    void on_register_btn_clicked();

    void on_submit_calories_coach_clicked();

    void on_login_btn_clicked();

    void on_daily_intakep_amt_to_spend_slider_sliderMoved(int position);

    void on_daily_intakep_back_btn_clicked();

    void on_loginp_back_btn_clicked();

    void on_registerp_back_btn_clicked();


    void on_display_foodp_back_btn_clicked();

    void on_userpp_logout_btn_clicked();

    void on_registerp_submit_button_clicked();

private:
    Ui::MainWindow *ui;
    vector<food> all_foods;
    vector<user> all_users;
    QVector<QString> all_nutrifacts;
    int current_user_index;
    user *current_user;


};
#endif // MAINWINDOW_H
