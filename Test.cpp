/**
 *
 * AUTHORS: Ori Darshan
 *
 * Date: 2021-03
 */

#include "doctest.h"
#include "Notebook.hpp"
#include "Direction.hpp"
using namespace ariel;

#include <string>
#include <algorithm>
using namespace std;


Notebook notebook1;
Notebook notebook2;

string s =  "0123456789"
            "0123456789"
            "0123456789"
            "0123456789"
            "0123456789"
            "0123456789"
            "0123456789"
            "0123456789"
            "0123456789"
            "0123456789";// 100 characters string


TEST_CASE("Good Input")
{
    //#1 write to the notebook:
    CHECK_NOTHROW(notebook1.write(0,0,0,Direction::Horizontal,"Hello!"));
    //#1.1 unlimited page count
    CHECK_NOTHROW(notebook1.write(10000,0,0,Direction::Horizontal,"World"));
    //#1.2 unlimited line count
    CHECK_NOTHROW(notebook1.write(0,10000,0,Direction::Horizontal,"place holder"));
    //#1.3 100 characters per line
    CHECK_NOTHROW(notebook1.write(0,1,0,Direction::Horizontal,s));
    //#1.4 15 characters from column 85 (85-99)
    CHECK_NOTHROW(notebook1.write(0,2,85,Direction::Horizontal,"123456789012345"));
    //#1.5 10 character from 75 at the same line
    CHECK_NOTHROW(notebook1.write(0,2,75,Direction::Horizontal,"1234567890"));
    //#1.6 can write all relevant chars
    for (int i = 38; i < 126; i++)
    {
        char c = (char)i;
        CHECK_NOTHROW(notebook1.write(0, i, 0, Direction::Horizontal, std::string(1, c)));
    }
    //#1.7 write vertically
    CHECK_NOTHROW(notebook2.write(0,0,0,Direction::Vertical,"Hello!"));
    //#1.8 write more than 100 character vertically
    CHECK_NOTHROW(notebook2.write(0,0,1,Direction::Vertical,s+"0"));
    //#1.9 write '_'
    CHECK_NOTHROW(notebook1.write(100, 0 , 0, Direction::Horizontal, "___"));
    //#1.10 write over written '_'
    CHECK_NOTHROW(notebook1.write(100, 0 , 0, Direction::Horizontal, "Hi"));
    //#1.10 cross writing using '_'
    CHECK_NOTHROW(notebook1.write(101, 1 , 0, Direction::Horizontal, "A_C"));
    CHECK_NOTHROW(notebook1.write(101, 0 , 1, Direction::Vertical, "ABC"));
    /* this will look like:
    _A___
    ABC__
    _C___
    */

    //#2 erase from the notebook
    CHECK_NOTHROW(notebook1.erase(10000, 0, 0, Direction::Horizontal, 5));
    //#2.1 reerase
    CHECK_NOTHROW(notebook1.erase(10000, 0, 0, Direction::Horizontal, 5));
    //#2.2 erase blank lines 
    CHECK_NOTHROW(notebook1.erase(11, 0, 0, Direction::Horizontal, 5));
    //#2.3 erase 100 characters in a line
    CHECK_NOTHROW(notebook1.erase(11, 0, 0, Direction::Horizontal, 100));
    //#2.4 erase 15 characters from column 85 in a line
    CHECK_NOTHROW(notebook1.erase(11, 0, 85, Direction::Horizontal, 15));
    //#2.5 erase more than 100 characters vertically
    CHECK_NOTHROW(notebook1.erase(11, 0, 0, Direction::Vertical, 105));


    //#3 read from the notebook
    CHECK(notebook1.read(0,0,0,Direction::Horizontal,6) == "Hello!");
    //#3.1 read empty parts
    CHECK(notebook1.read(0, 0, 55, Direction::Horizontal, 4) == "____");
    //#3.2 read erased parts
    CHECK(notebook1.read(10000, 0, 0, Direction::Horizontal, 4) == "~~~~");
    //#3.3 read vertically
    CHECK(notebook1.read(101, 0 , 1, Direction::Vertical, 3) == "ABC");
    //#3.4 read 100 characters from a line
    CHECK_NOTHROW(notebook1.read(1, 0, 0, Direction::Horizontal, 100));
    //#3.5 read 100+ characters vertically
    CHECK(notebook2.read(0,0,1,Direction::Vertical,101) == s+"0");
    //#3.6 reading unopened pages
    CHECK_NOTHROW(notebook2.read(1000, 0, 0, Direction::Horizontal, 3));
}

TEST_CASE("Bad Input"){
    //#1 rewriting
    CHECK_THROWS(notebook1.write(0, 0, 0, Direction::Horizontal, "*"));
    //#1.1-1.4 writing outside boundaries
    CHECK_THROWS(notebook1.write(-124, 22, 0, Direction::Horizontal, "*"));
    CHECK_THROWS(notebook1.write(22, -23, 0, Direction::Horizontal, "*"));
    CHECK_THROWS(notebook1.write(22, 22, -1, Direction::Horizontal, "*"));
    CHECK_THROWS(notebook1.write(22, 22, 101, Direction::Horizontal, "*"));
    //#1.5-1.6 writing more than 100 characters a line
    CHECK_THROWS(notebook1.write(3, 0, 0, Direction::Horizontal, s+"0"));
    CHECK_THROWS(notebook1.write(3, 1, 98, Direction::Horizontal, "012"));
    //#1.7 faulty cross-writing
    CHECK_NOTHROW(notebook1.write(70, 1 , 0, Direction::Horizontal, "ABC"));// should run
    CHECK_THROWS(notebook1.write(70, 0 , 1, Direction::Vertical, "ABC"));
    //#1.8 illegal characters
    for (int i = 0; i < 36; i++)
    {
        char c = i;
        CHECK_THROWS(notebook1.write(71,0,0,Direction::Horizontal, string(1,c)));
    }
    CHECK_THROWS(notebook1.write(71,0,0,Direction::Horizontal, string(1,126)));
    CHECK_THROWS(notebook1.write(71,0,0,Direction::Horizontal, string(1,127)));
    
    
    //#2.1-2.6 reading outside baudraries
    CHECK_THROWS(notebook1.read(-124, 22, 0, Direction::Horizontal, 1));
    CHECK_THROWS(notebook1.read(22, -23, 0, Direction::Horizontal, 1));
    CHECK_THROWS(notebook1.read(22, 22, -1, Direction::Horizontal, 1));
    CHECK_THROWS(notebook1.read(22, 22, 101, Direction::Horizontal, 1)); 
    CHECK_THROWS(notebook1.read(22, 22, 70, Direction::Horizontal, 31)); 
    CHECK_THROWS(notebook1.read(22, 22, 0, Direction::Horizontal, 101));

    //#3.1-3.6 erasing outside baudraries
    CHECK_THROWS(notebook1.erase(-124, 22, 0, Direction::Horizontal, 1));
    CHECK_THROWS(notebook1.erase(22, -23, 0, Direction::Horizontal, 1));
    CHECK_THROWS(notebook1.erase(22, 22, -1, Direction::Horizontal, 1));
    CHECK_THROWS(notebook1.erase(22, 22, 101, Direction::Horizontal, 1)); 
    CHECK_THROWS(notebook1.erase(22, 22, 70, Direction::Horizontal, 31)); 
    CHECK_THROWS(notebook1.erase(22, 22, 0, Direction::Horizontal, 101)); 
}