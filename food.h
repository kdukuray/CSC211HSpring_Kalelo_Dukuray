#ifndef FOOD_H
#define FOOD_H
#include <QString>
using namespace std;
class food{
private:
    QString name;
    int calories;
    double price;
    QString location;
    QString address;
    QString image_url;

public:

    food(QString name, int calories, double price, QString location, QString address, QString image_url);
    QString get_name();
    int get_calories();
    double get_price();
    QString get_location();
    QString get_address();
    QString get_image_url();
    // void operator>(int num);
    // void operator<(int num);
    // void operator>=(int num);
    // void operator<=(int num);

};

#endif
