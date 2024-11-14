#include "user.h"

user::user(QString name, QString username, int age, QString emplid, QString password, QString email, int weight, int user_height[], gender user_gender, activity user_activity) : person(name, username){

    this->emplid = emplid;
    this->password = password;
    this->email = email;
    this->age = age;
    this->weight= weight;
    this->user_height.set_height(user_height[0], user_height[1]);
    this->user_gender = user_gender;
    this->user_activity = user_activity;
}

int user::get_age(){
    return age;
}
void user::set_age(int age){
    this->age = age;
}

QString user::get_emplid(){
    return emplid;
}
void user::set_emplid(QString emplid){
    this->emplid = emplid;
}

QString user::get_password(){
    return password;
}
void user::set_password(QString password){
    this->password = password;
}

QString user::get_email(){
    return email;
}
void user::set_email(QString email){
    this->email = email;
}

int user::get_weight(){
    return weight;
}
void user::set_weight(int weight){
    this->weight = weight;
}

heightnamespace::height user::get_height(){
    return user_height;
}

void user::set_height(int height_array[]){
    user_height.set_height(height_array[0], height_array[1]);
}

gender user::get_gender(){
    return user_gender;
}
void user::set_gender(gender user_gender){
    this->user_gender = user_gender;
}

activity user::get_activity(){
    return user_activity;
}
void user::set_activity(activity user_activity){
    this->user_activity = user_activity;
}


int user::get_recommended_calories(){
    int recommended_calories;
    int bmr;
    if (user_gender == M){
        bmr = (66.47 + (6.24 * weight) + (12.7 * this->user_height.get_height_in_inches()) - (6.75 * age));
    }
    else if (user_gender == F){
        bmr = (65.51 + (4.35 * weight) + (4.7 * this->user_height.get_height_in_inches()) - (4.7 * age));
    }
    switch(user_activity){
    case Sedentary:
        recommended_calories = bmr * 1.2;
        break;
    case Light:
        recommended_calories = bmr * 1.375;
        break;
    case Moderate:
        recommended_calories = bmr * 1.55;
        break;
    case Very:
        recommended_calories = bmr * 1.725;
        break;
    case Extra:
        recommended_calories = bmr * 1.9;
        break;
    }
    return recommended_calories;


}














