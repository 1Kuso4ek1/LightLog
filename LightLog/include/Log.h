#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <memory>
#include <vector>
#include <signal.h>
#include <functional>
#include <string_view>

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
    static void SetCrashHandle(std::function<void()> handle);

    static void ClearMessagesList();

    using StringLogType = std::pair<std::string, Log::Type>;

    static std::vector<StringLogType> GetMessages();

private:
    Log();

    static void SigSegv(int sig);

    static std::string normal, red, green,
                       yellow, blue, magenta,
                       cyan, white;
                       
    static std::function<void()> crashHandle;

    static std::ofstream output;

    static std::vector<StringLogType> messages;

    static bool silent;
};
