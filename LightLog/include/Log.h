#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <sstream>

struct Color
{
    Color(std::string code) : code(code) {}

    std::string code;
};

static std::ostream& operator<<(std::ostream& stream, Color c)
{
    return (stream << c.code);
}

class Log
{
public:
    enum class Type
    {
        Critical,
        Error,
        Warning,
        Info
    };

    Log(std::string filename, bool silent);
    Log();

    void Write(std::string data, Type type);

private:
    bool silent;
    std::ofstream output;

    Color normal, red, green,
          yellow, blue, magenta,
          cyan, white;
};
