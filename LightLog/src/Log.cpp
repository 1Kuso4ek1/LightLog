#include <Log.h>

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
std::vector<std::pair<std::string, Log::Type>> Log::messages = {};
std::function<void()> Log::crashHandle = std::function<void()>([]() {});

void Log::Init(std::string filename, bool isSilent, bool storeMessages)
{
	signal(SIGSEGV, SigSegv);
    Log::output.open(filename);
    Log::silent = isSilent;
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
        messages.push_back({ "Error: " + data, Log::Type::Error });
        output << std::ctime(&t) << '\t' << "Error: " << data << "\n";
        cont << white << std::ctime(&t) << normal << '\t' << red << "Error: " << data << normal << "\n";
        break;
    case Log::Type::Warning:
        messages.push_back({ "Warning: " + data, Log::Type::Warning });
        output << std::ctime(&t) << '\t' << "Warning: " << data << "\n";
        cont << white << std::ctime(&t) << normal << '\t' << yellow << "Warning: " << data << normal << "\n";
        break;
    case Log::Type::Info:
        messages.push_back({ "Info: " + data, Log::Type::Info });
        output << std::ctime(&t) << '\t' << "Info: " << data << "\n";
        cont << white << std::ctime(&t) << normal << '\t' << cyan << "Info: " << data << normal << "\n";
        break;
    }
    if(!silent || type == Log::Type::Critical)
        std::cout << cont.str();

    if(type == Log::Type::Critical)
    {
        output.close();
        crashHandle();
        exit(EXIT_FAILURE);
    }
}

void Log::SetCrashHandle(std::function<void()> handle)
{
	crashHandle = handle;
}

void Log::ClearMessagesList()
{
    messages.clear();
}

std::vector<std::pair<std::string, Log::Type>> Log::GetMessages()
{
    return messages;
}

void Log::SigSegv(int sig)
{
	auto current_time = std::chrono::system_clock::now();
	std::time_t t = std::chrono::system_clock::to_time_t(current_time);
	output << std::ctime(&t) << '\t' << "SIGSEGV received" << "\n";
	output.close();
    std::cout << white << std::ctime(&t) << normal << '\t' << red << "SIGSEGV received" << normal << "\n";
	crashHandle();
	signal(sig, SIG_DFL);
	exit(EXIT_FAILURE);
}
