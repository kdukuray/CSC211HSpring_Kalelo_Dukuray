#include "person.h"

person::person(QString name, QString username){
    this->name = name;
    this->username = username;
}

QString person::get_name(){
    return name;
}
void person::set_name(QString name){
    this->name = name;
}

QString person::get_username(){
    return username;
}
void person::set_username(QString username){
    this->username = username;
}

