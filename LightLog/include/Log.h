#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <memory>

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
