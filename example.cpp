#include <LightLog/Log.h>

int main()
{
    Log log("log.txt", false);
    
    log.Write("Hello world!", Log::Type::Info);
    log.Write("Hello warning!", Log::Type::Warning);
    log.Write("Hello error!", Log::Type::Error);
    log.Write("Hello critical!", Log::Type::Critical);
}