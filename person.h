#ifndef PERSON_H
#define PERSON_H
#include <QString>

class person{
private:
    QString name;
    QString username;




public:
    person(QString name, QString username);
    QString get_name();
    void set_name(QString name);
    QString get_username();
    void set_username(QString username);



};
#endif
