#include "food.h"


food::food(QString name, int calories, double price, QString location, QString address, QString image_url){
    this->name = name;
    this->calories = calories;
    this->price = price;
    this->location = location;
    this->address = address;
    this->image_url = image_url;
}

QString food::get_name(){
    return name;
}

int food::get_calories(){
    return calories;
}

double food::get_price(){
    return price;
}

QString food::get_location(){
    return location;
}

QString food::get_address(){
    return address;
}

QString food::get_image_url(){
    return image_url;
}
