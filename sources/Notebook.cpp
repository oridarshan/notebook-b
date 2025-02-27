#include <iostream>
#include <string>
#include "Notebook.hpp"
using ariel::Direction;
using namespace std;

const int MIN_CHAR = 32;
const unsigned long LINE_WIDTH = 100;
const int MAX_CHAR = 125;
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
    if((direction == Direction::Horizontal && column + length > LINE_WIDTH) 
        || (column < 0 || page < 0 || row < 0 || length < 0)){
        throw("Out of boundaries");
    }
}

void valid_write(string const &data){
    for (int i = 0; i < data.length(); i++)
    {
        char c = data[(unsigned long)i];
        if(c < MIN_CHAR || c > MAX_CHAR){
            throw("unsupported char");
        }
    }
}

std::vector<char> new_line (LINE_WIDTH, '_');

void ariel::Notebook::write(int page, int row, int column, Direction direction, const string &data){
    // אפשר לממש בעזרת ריד, קודם נקרא את המקום אליו נרצה לכתוב ונוודא שהוא פנוי ותקין
    int length = data.length();
    string curr_str = read(page, row, column, direction, length);
    if(curr_str != std::string (data.length(),'_')){
        throw ("Cannot rewrite with pen!");
    }
    valid_write(data);
    if(direction == Direction::Horizontal){
        //create string representing the line
        string index_string = std::to_string(page )+ "-" + std::to_string(row);
        
        for (int i = 0; i < length; i++)
        {
            if(data[(unsigned long)i] == '~'){throw ("can't write ~");}
            paper[index_string].at((unsigned int)(column+i)) = data[(unsigned long)i];
        }
    }
    else{
        for (int i = 0; i < length; i++)
        {
            string index_string = std::to_string(page )+ "-" + std::to_string(row+i);
            paper[index_string].at((unsigned int)(column)) = data[(unsigned long)i];
        }
    }
}
string ariel::Notebook::read(int page, int row, int column, Direction direction, int length)
{
    check_params(page, row, column, direction, length);
    string res;
    if(direction == Direction::Horizontal){
        //create string representing the line
        string index_string = std::to_string(page )+ "-" + std::to_string(row);
        if (paper[index_string].empty())
        {
            paper[index_string] = new_line;
        }    
        for (int i = 0; i < length; i++)
        {
            res += paper[index_string].at((unsigned int)(column+i));
        }
    }
    else{
        for (int i = 0; i < length; i++)
        {
            string index_string = std::to_string(page )+ "-" + std::to_string(row+i);
            if (paper[index_string].empty())
            {
                paper[index_string] = new_line;
            }
            res += paper[index_string].at((unsigned int)(column));
        }
    }
    return res;
}
void ariel::Notebook::erase(int page, int row, int column, Direction direction, int length){
    string curr_str = read(page, row, column, direction, length);
    if(direction == Direction::Horizontal){
        //create string representing the line
        string index_string = std::to_string(page )+ "-" + std::to_string(row);
        
        for (int i = 0; i < length; i++)
        {
            paper[index_string].at((unsigned int)(column+i)) = '~';
        }
    }
    else{
        for (int i = 0; i < length; i++)
        {
            string index_string = std::to_string(page )+ "-" + std::to_string(row+i);
            paper[index_string].at((unsigned int)(column)) = '~';
        }
    }
}
string ariel::Notebook::show(int page){
    if( page < 0){
        throw("Out of boundaries");
    }
    string res;
    for (int i = 0; i < LINE_WIDTH; i++)
    {
        res += read(page, i, 0, Direction::Horizontal, LINE_WIDTH);
    }
    return res;
    }
