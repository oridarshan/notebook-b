#include <string>
#include "Notebook.hpp"

using ariel::Direction;
using namespace std;

    void ariel::Notebook::write(int page, int row, int column, Direction direction, const string &data){
        // אפשר לממש בעזרת ריד, קודם נקרא את המקום אליו נרצה לכתוב ונוודא שהוא פנוי ותקין
    }
    string ariel::Notebook::read(int page, int row, int column, Direction direction, int length){return "";}
    void ariel::Notebook::erase(int page, int row, int column, Direction direction, int length){}
    string ariel::Notebook::show(int page){return "";}
