#include <LightLog/Log.h>

Log::Log(std::string filename, bool silent) :
         output(filename), silent(silent),
         normal("\x1B[0m"), red("\x1B[31m"),
         green("\x1B[32m"), yellow("\x1B[33m"),
         blue("\x1B[34m"), magenta("\x1B[35m"),
         cyan("\x1B[36m"), white("\x1B[37m") {}

Log::Log() : output("Last_log.txt"), silent(false),
             normal("\x1B[0m"), red("\x1B[31m"),
             green("\x1B[32m"), yellow("\x1B[33m"),
             blue("\x1B[34m"), magenta("\x1B[35m"),
             cyan("\x1B[36m"), white("\x1B[37m") {}

void Log::Write(std::string data, Type type)
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
