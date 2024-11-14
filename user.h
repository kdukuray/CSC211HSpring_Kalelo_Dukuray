#ifndef USER_H
#define USER_H
#include <QString>
#include "height.h"
#include "person.h"
using namespace std;
enum gender {M, F};
enum activity {Sedentary, Light, Moderate, Very, Extra};

class user : public person{
private:
    int age;
    QString emplid;
    QString password;
    QString email;
    int weight;
    heightnamespace::height user_height;
    gender user_gender;
    activity user_activity;

public:
    user(QString name, QString username, int age, QString emplid, QString password, QString email, int weight, int user_height[], gender user_gender, activity user_activity);
    int get_age();
    void set_age(int age);
    QString get_emplid();
    void set_emplid(QString emplid);
    QString get_password();
    void set_password(QString password);
    QString get_email();
    void set_email(QString email);
    int get_weight();
    void set_weight(int weight);
    heightnamespace::height get_height();
    void set_height(int height_array[]);
    gender get_gender();
    void set_gender(gender user_gender);
    activity get_activity();
    int get_recommended_calories();
    void set_activity(activity user_activity);
};

#endif // USER_H
