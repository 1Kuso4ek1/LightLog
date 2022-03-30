#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <memory>

struct Color
{
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

    static void Init(std::string filename, bool silent);
    static void Write(std::string data, Type type);

private:
    Log();

    static std::string normal, red, green,
                       yellow, blue, magenta,
                       cyan, white;

    static std::ofstream output;

    static bool silent;
};
