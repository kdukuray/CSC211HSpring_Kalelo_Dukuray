#include "height.h"

int heightnamespace::height::get_feet(){
    return feet;
}

void heightnamespace::height::set_feet(int feet){
    this->feet = feet;
}

int heightnamespace::height::get_inches(){
    return inches;
}

void heightnamespace::height::set_inches(int inches){
    this->inches = inches;
}

void heightnamespace::height::set_height(int feet, int inches){
    this->feet = feet;
    this->inches = inches;
}

QString heightnamespace::height::get_height_formatted(){
    QString height = "";
    height += QString::number(feet) + "\"" + QString::number(inches);
    return height;
}

int heightnamespace::height::get_height_in_inches(){
    return ((feet * 12) + inches);
}
