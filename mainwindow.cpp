#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/images/images/bmcc_logo.png");
    ui->bmcc_logo_label->setPixmap(pix.scaled(500, 500, Qt::KeepAspectRatio));
    load_foods();
    load_users();
    load_nutrifacts();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load_foods(){
    QFile food_in("food_db.txt");
    food_in.open(QIODevice::ReadOnly);
    QTextStream food_text_stream(&food_in);

    QString name, location, address, calories_string, price_string, image_url;
    int calories;
    double price;
    food *food_ptr;

    while(!food_text_stream.atEnd()){
        name = food_text_stream.readLine();
        calories_string = food_text_stream.readLine();
        calories = calories_string.toInt();
        price_string = food_text_stream.readLine();
        price = price_string.toDouble();
        location = food_text_stream.readLine();
        address = food_text_stream.readLine();
        image_url = food_text_stream.readLine();
        food_ptr = new food(name, calories, price, location, address, image_url);
        all_foods.push_back(*food_ptr);
        delete food_ptr;
        food_ptr = nullptr;

    }
    food_in.close();
}
void MainWindow::load_users(){
    all_users.clear();

    QFile users_in("/Users/user/honor01/users_db.txt");
    users_in.open(QIODevice::ReadOnly);
    QTextStream user_text_stream(&users_in);

    QString name, username, emplid, password, email, age_string, weight_string, height_feet_string, height_inches_string, gender_string, activity_string;
    int age, weight, height_feet, height_inches, height_array[2];
    gender user_gender;
    activity user_activity;
    user *user_ptr;

    while(!user_text_stream.atEnd()){
        name = user_text_stream.readLine();
        username = user_text_stream.readLine();
        age_string = user_text_stream.readLine();
        age = age_string.toInt();
        emplid = user_text_stream.readLine();
        password = user_text_stream.readLine();
        email = user_text_stream.readLine();
        weight_string = user_text_stream.readLine();
        weight = weight_string.toInt();
        height_feet_string = user_text_stream.readLine();
        height_inches_string = user_text_stream.readLine();
        gender_string = user_text_stream.readLine();
        activity_string = user_text_stream.readLine();
        if (activity_string == "Sedentary"){
            user_activity = Sedentary;
        }
        else if (activity_string == "Light"){
            user_activity = Light;
        }
        else if (activity_string == "Moderate"){
            user_activity = Moderate;
        }
        else if (activity_string == "Very"){
            user_activity = Very;
        }
        else if (activity_string == "Extra"){
            user_activity = Extra;
        }
        if (gender_string == "M"){
            user_gender = M;
        }
        else{
            user_gender = F;
        }
        height_array[0] = height_feet_string.toInt();
        height_array[1] = height_inches_string.toInt();
        user_ptr = new user(name, username, age, emplid, password, email, weight, height_array, user_gender, user_activity);
        all_users.push_back(*user_ptr);
        delete user_ptr;
        user_ptr = nullptr;
    }
    users_in.close();
}

void MainWindow::load_nutrifacts(){


    QFile nutrifacts_in("/Users/user/honor01/nutrifacts.txt");
    nutrifacts_in.open(QIODevice::ReadOnly);
    QTextStream nutrifacts_stream(&nutrifacts_in);
    QString fact;
    while(!nutrifacts_stream.atEnd()){
        fact = nutrifacts_stream.readLine();
        all_nutrifacts.push_back(fact);
    }
    nutrifacts_in.close();
}

void MainWindow::on_loginp_submit_login_btn_clicked()
{
    QString username = ui->loginp_username_line_edit->text();
    QString password = ui->loginp_password_line_edit->text();


    for (int i = 0; i < all_users.size(); i++){
        if (all_users[i].get_username() == username && all_users[i].get_password() == password){
            current_user = &all_users[i];
            ui->userpp_name_display_label->setText(current_user->get_name());
            ui->userpp_age_display_label->setText(QString::number(current_user->get_age()));
            ui->userpp_weight_display_label->setText(QString::number(current_user->get_weight()) + " lbs");
            heightnamespace::height user_height =  current_user->get_height();
            ui->userpp_height_display_label->setText(user_height.get_height_formatted());

            if (current_user->get_gender() == M){
                ui->userpp_gender_display_label->setText("M");
            }
            else{
                ui->userpp_gender_display_label->setText("F");
            }

            QString user_activity;
            switch(current_user->get_activity()){
            case Sedentary:
                user_activity = "Sedentary";
                break;
            case Light:
                user_activity = "Light";
                break;
            case Moderate:
                user_activity = "Moderate";
                break;
            case Very:
                user_activity = "Very";
                break;
            case Extra:
                user_activity = "Extra";
                break;
            }
            ui->userpp_physical_activity_display_label->setText(user_activity);
            ui->userpp_recommended_calorie_display_label->setText(QString::number(current_user->get_recommended_calories()));
            srand(time(NULL));
            ui->userpp_nutrifact_text_browser->setText(all_nutrifacts[(rand() % 52)]);
            ui->page_stack->setCurrentIndex(3);
            break;

        }
        if (i == (all_users.size() - 1)){
            QMessageBox::warning(this, "Failed Login", "The Username and Password you Entered Does Not Exist.");
        }
    }

}


void MainWindow::on_userpp_get_coached_btn_clicked()
{
    ui->page_stack->setCurrentIndex(5);
    ui->page_stack->setCurrentIndex(4);
}


void MainWindow::on_userpp_new_fact_btn_clicked()
{
    srand(time(NULL));
    ui->userpp_nutrifact_text_browser->setText(all_nutrifacts[(rand() % 52)]);
}


void MainWindow::on_register_btn_clicked()
{
    ui->page_stack->setCurrentIndex(1);
}


void MainWindow::on_submit_calories_coach_clicked()
{
    int calories_consumed_today = ui->daily_intakep_consumed_calorie_line_edit->text().toInt();
    int food_budget = ui->daily_intakep_amt_to_spend_slider->value();
    int desired_calories = ui->daily_intakep_desired_calories_line_edit->text().toInt();
    if (calories_consumed_today >= current_user->get_recommended_calories()){
        QMessageBox::warning(this, "Exceeded Recommended Intake", "You have had enough calories for the day.");
    }
    else{
        int remaining_calories_to_eat = current_user->get_recommended_calories() - calories_consumed_today;
        vector<food> compliant_meals;
        for (int i = 0; i < all_foods.size(); i++){
            if ((all_foods[i].get_calories() + 50) < remaining_calories_to_eat && static_cast<double>(food_budget) >= all_foods[i].get_price()
                && all_foods[i].get_calories() <= desired_calories){
                compliant_meals.push_back(all_foods[i]);
            }
        }

        for (int i = 0; i < compliant_meals.size(); i++){

        QPixmap pix(compliant_meals[i].get_image_url());

        QHBoxLayout *dphorizontalLayout = new QHBoxLayout();

        QVBoxLayout *dpverticalLayout = new QVBoxLayout();

        //for the vertical layout that contains only the food image //<-
        QLabel *image_label = new QLabel("image_label", ui->display_foodp_scroll_area);
        //image_label->setMinimumHeight(200);
        image_label->setPixmap(pix.scaled(275, 175, Qt::KeepAspectRatio));
        QVBoxLayout *verticalLayout_0 = new QVBoxLayout();
        verticalLayout_0->insertWidget(0, image_label); //<-

        QLabel *name_label = new QLabel("Name: ", ui->display_foodp_scroll_area);
        QLabel *name_display_label = new QLabel(compliant_meals[i].get_name(), ui->display_foodp_scroll_area);
        QHBoxLayout *name_h_layout = new QHBoxLayout();
        name_h_layout->insertWidget(0, name_label);
        name_h_layout->insertWidget(1, name_display_label);

        QLabel *calories_label = new QLabel("Calories: ", ui->display_foodp_scroll_area);
        QLabel *calories_display_label = new QLabel(QString::number(compliant_meals[i].get_calories()), ui->display_foodp_scroll_area);
        QHBoxLayout *calories_h_layout = new QHBoxLayout();
        calories_h_layout->insertWidget(0, calories_label);
        calories_h_layout->insertWidget(1, calories_display_label);

        QLabel *price_label = new QLabel("Price: ", ui->display_foodp_scroll_area);
        QLabel *price_display_label = new QLabel(("$" + QString::number(compliant_meals[i].get_price())), ui->display_foodp_scroll_area);
        QHBoxLayout *price_h_layout = new QHBoxLayout();
        price_h_layout->insertWidget(0, price_label);
        price_h_layout->insertWidget(1, price_display_label);


        QLabel *location_label = new QLabel("Location: ", ui->display_foodp_scroll_area);
        QLabel *location_display_label = new QLabel(compliant_meals[i].get_location(), ui->display_foodp_scroll_area);
        QHBoxLayout *location_h_layout = new QHBoxLayout();
        location_h_layout->insertWidget(0, location_label);
        location_h_layout->insertWidget(1, location_display_label);

        QLabel *address_label = new QLabel("Address: ", ui->display_foodp_scroll_area);
        QLabel *address_display_label = new QLabel(compliant_meals[i].get_address(), ui->display_foodp_scroll_area);
        QHBoxLayout *address_h_layout = new QHBoxLayout();
        address_h_layout->insertWidget(0, address_label);
        address_h_layout->insertWidget(1, address_display_label);

        dpverticalLayout->insertLayout(0, name_h_layout);
        dpverticalLayout->insertLayout(1, calories_h_layout);
        dpverticalLayout->insertLayout(2, price_h_layout);
        dpverticalLayout->insertLayout(3, location_h_layout);
        dpverticalLayout->insertLayout(4, address_h_layout);


        dphorizontalLayout->insertLayout(0, verticalLayout_0);
        dphorizontalLayout->insertLayout(1, dpverticalLayout);

        ui->display_foodp_verticalLayout->insertLayout(i, dphorizontalLayout);
        }
        ui->page_stack->setCurrentIndex(5);


    }

}


void MainWindow::on_login_btn_clicked()
{
    ui->page_stack->setCurrentIndex(2);
}


void MainWindow::on_daily_intakep_amt_to_spend_slider_sliderMoved(int position)
{
    ui->label_display_amt_spend->setText("  $" + QString::number(position) + "      ");
}


void MainWindow::on_daily_intakep_back_btn_clicked()
{
    ui->page_stack->setCurrentIndex(3);
}


void MainWindow::on_loginp_back_btn_clicked()
{
    ui->page_stack->setCurrentIndex(0);
}


void MainWindow::on_registerp_back_btn_clicked()
{
    ui->page_stack->setCurrentIndex(0);
}

void MainWindow::on_display_foodp_back_btn_clicked()
{
    ui->page_stack->setCurrentIndex(4);
}


void MainWindow::on_userpp_logout_btn_clicked()
{
    ui->loginp_username_line_edit->setText("");
    ui->loginp_password_line_edit->setText("");
    current_user = nullptr;
    ui->page_stack->setCurrentIndex(2);
    QMessageBox::information(this, "Logged Out", "You have been logged out successfully!");
}


void MainWindow::on_registerp_submit_button_clicked()
{
    QString username = ui->loginp_username_line_edit->text();
    bool containsOnlyDigits = true;

    for (int i = 0; i < username.length(); ++i) {
        if (!username[i].isDigit()) {
        containsOnlyDigits = false;
        break;
        }
    }

    try{
        if(containsOnlyDigits){
        throw QString ("You cannot use only numbers as your username. ");
        }
    }
        catch (QString &exceptString){
        QMessageBox::warning(this, "Invalid Username - Cannot be only digits.", exceptString);
    }



    if (ui->registerp_name_line_edit->text() == "" ||
        ui->registerp_username_line_edit->text() == "" ||
        ui->registerp_email_line_edit->text() == ""||
        ui->registerp_password_line_edit->text() == "" ||
        ui->registerp_confirm_passwor_line_edit->text() == "" ||
        ui->registerp_weight_line_edit->text() == "" ||
        ui->registerp_age_drop_down->currentText() == "" ||
        ui->registerp_gender_drop_down->currentText() == "" ||
        ui->registerp_height_inches_drop_down->currentText() == "" ||
        ui->registerp_physical_activity_drop_down->currentText() == "" ||
        ui->registerp_height_feet_drop_down->currentText() == ""
        ){
        QMessageBox::warning(this, "Empty Field", "Please fill all feilds in!");
    }
    else if (ui->registerp_password_line_edit->text() != ui->registerp_confirm_passwor_line_edit->text()){
        QMessageBox::warning(this, "Not Matched", "The Passwords You entered did not match!");
    }
    else{

        QString name, username, age, emplid, password, email, weight, height_feet, height_inches, gender, activeness;
        name = ui->registerp_name_line_edit->text();
        username = ui->registerp_username_line_edit->text();
        age = ui->registerp_age_drop_down->currentText();
        emplid = "11111111";
        password = ui->registerp_password_line_edit->text();
        email = ui->registerp_email_line_edit->text();
        weight = ui->registerp_weight_line_edit->text();
        height_feet = ui->registerp_height_feet_drop_down->currentText();
        height_inches = ui->registerp_height_inches_drop_down->currentText();
        gender = ui->registerp_gender_drop_down->currentText();
        activeness = ui->registerp_physical_activity_drop_down->currentText();

        QFile file_out("users_db.txt");
        file_out.open(QIODevice::Append);
        QTextStream user_db_stream(&file_out);
        user_db_stream << name << "\n" << username << "\n" << age << "\n" << emplid << "\n" << password << "\n" << email << "\n";
        user_db_stream << weight <<  "\n" << height_feet << "\n" << height_inches << "\n" << gender << "\n" << activeness << "\n";


        ui->registerp_name_line_edit->setText("");
        ui->registerp_username_line_edit->setText("");
        ui->registerp_age_drop_down->setCurrentText("");
        ui->registerp_password_line_edit->setText("");
        ui->registerp_email_line_edit->setText("");
        ui->registerp_weight_line_edit->setText("");
        ui->registerp_height_feet_drop_down->setCurrentText("");
        ui->registerp_height_inches_drop_down->setCurrentText("");
        ui->registerp_gender_drop_down->setCurrentText("");
        ui->registerp_physical_activity_drop_down->setCurrentText("");
        ui->page_stack->setCurrentIndex(2);
        QMessageBox::information(this, "Status", "Registration Successful!");
        file_out.close();
        load_users();
    }

}

