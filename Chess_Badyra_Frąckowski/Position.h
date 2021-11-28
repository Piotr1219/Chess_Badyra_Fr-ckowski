#pragma once
#include <string>
struct Position
{
    char SrcPosition;
    char DstPosition;
    int Score;
    //internal bool TopSort;
    std::string Move;
public:
    std::string ToString();
};