#include <Log.h>

int main()
{
    Log::Init("log.txt", false);
    
    Log::Write("Hello world!", Log::Type::Info);
    Log::Write("Hello warning!", Log::Type::Warning);
    Log::Write("Hello error!", Log::Type::Error);
    Log::Write("Hello critical!", Log::Type::Critical);
}