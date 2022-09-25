#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <memory>
#include <vector>

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

    static void Init(std::string filename, bool silent, bool storeMessages = false);
    static void Write(std::string data, Type type);

    static void ClearMessagesList();

    static std::vector<std::pair<std::string, Log::Type>> GetMessages();

private:
    Log();

    static std::string normal, red, green,
                       yellow, blue, magenta,
                       cyan, white;

    static std::ofstream output;

    static std::vector<std::pair<std::string, Log::Type>> messages;

    static bool silent;
};
