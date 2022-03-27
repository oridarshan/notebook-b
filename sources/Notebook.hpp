#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "Direction.hpp"

using ariel::Direction;
using namespace std;
namespace ariel{
    class Notebook{
        private:
            std::unordered_map<std::string, std::vector<char>> paper;

        public:
            void write(int page, int row, int column, Direction direction, const string &data);
            string read(int page, int row, int column, Direction direction, int length);
            void erase(int page, int row, int column, Direction direction, int length);
            string show(int page);
    };
}
// class ariel::Notebook{
//     public void write(int page, int row, int column, Direction direction, string data);
//     public void read(int page, int row, int column, Direction direction, int length);
//     public void erase(int page, int row, int column, Direction direction, int length);
//     public void show(int page);
// };