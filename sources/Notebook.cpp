#include <string>
#include "Notebook.hpp"

using ariel::Direction;
using namespace std;

/**
 * @brief checks if the param violte the notebook structure
 * 
 * @param page 
 * @param row 
 * @param column 
 * @param direction 
 * @param length 
 */
void check_params(int page, int row, int column, Direction direction, int length){
    if((direction == Direction::Horizontal && column + length > 100) 
        || (column < 0 || page < 0 || row < 0 || length < 0)){
        throw("Out of boundaries");
    }
}

void ariel::Notebook::write(int page, int row, int column, Direction direction, const string &data){
    // אפשר לממש בעזרת ריד, קודם נקרא את המקום אליו נרצה לכתוב ונוודא שהוא פנוי ותקין
    check_params(page, row, column, direction, data.length()); 
}
string ariel::Notebook::read(int page, int row, int column, Direction direction, int length)
{
    check_params(page, row, column, direction, length);    
    return "";
}
void ariel::Notebook::erase(int page, int row, int column, Direction direction, int length){
    check_params(page, row, column, direction, length); 
}
string ariel::Notebook::show(int page){
    if( page < 0){
        throw("Out of boundaries");
    }
    return "";
    }
