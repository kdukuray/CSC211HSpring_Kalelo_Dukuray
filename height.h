#ifndef HEIGHT_H
#define HEIGHT_H
#include <QString>
using namespace std;


namespace heightnamespace{
class height{
private:
    int feet;
    int inches;

public:
    int get_feet();
    void set_feet(int feet);
    int get_inches();
    void set_inches(int inches);
    void set_height(int feet, int inches);
    QString get_height_formatted();
    int get_height_in_inches();
};
}

#endif
