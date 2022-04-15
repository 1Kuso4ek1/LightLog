#include <Log.h>
#define _WIN32

#ifndef _WIN32
    std::string Log::normal = "\x1B[0m";
    std::string Log::red = "\x1B[31m";
    std::string Log::green = "\x1B[32m";
    std::string Log::yellow = "\x1B[33m";
    std::string Log::blue = "\x1B[34m";
    std::string Log::magenta = "\x1B[35m";
    std::string Log::cyan = "\x1B[36m";
    std::string Log::white = "\x1B[37m";
#else
    std::string Log::normal = "";
    std::string Log::red = "";
    std::string Log::green = "";
    std::string Log::yellow = "";
    std::string Log::blue = "";
    std::string Log::magenta = "";
    std::string Log::cyan = "";
    std::string Log::white = "";
#endif

std::ofstream Log::output("");
bool Log::silent = false;

void Log::Init(std::string filename, bool issilent)
{
    Log::output.open(filename); Log::silent = issilent;
}

void Log::Write(std::string data, Log::Type type)
{
    auto current_time = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(current_time);
    std::stringstream cont;
    switch(type)
    {
    case Log::Type::Critical:
        output << std::ctime(&t) << '\t' << "CRITICAL ERROR: " << data << "\n";
        cont << white << std::ctime(&t) << normal << '\t' << red << "CRITICAL ERROR: " << data << normal << "\n";
        break;
    case Log::Type::Error:
        output << std::ctime(&t) << '\t' << "Error: " << data << "\n";
        cont << white << std::ctime(&t) << normal << '\t' << red << "Error: " << data << normal << "\n";
        break;
    case Log::Type::Warning:
        output << std::ctime(&t) << '\t' << "Warning: " << data << "\n";
        cont << white << std::ctime(&t) << normal << '\t' << yellow << "Warning: " << data << normal << "\n";
        break;
    case Log::Type::Info:
        output << std::ctime(&t) << '\t' << "Info: " << data << "\n";
        cont << white << std::ctime(&t) << normal << '\t' << cyan << "Info: " << data << normal << "\n";
        break;
    }
    if(!silent || type == Log::Type::Critical)
        std::cout << cont.str();

    if(type == Log::Type::Critical)
    {
        output.close();
        throw cont.str();
    }
}
