#include "measurement.h"
#include <iomanip>
#include <sstream>
#include <ctime>

// Implementering av Measurement-structens metoder
std::string Measurement::getTimeString() const {
    // Konvertera time_point till time_t för att kunna formatera
    std::time_t time = std::chrono::system_clock::to_time_t(timestamp);
    std::tm* local_time = std::localtime(&time);
    
    // Skapa en formaterad tidssträng
    std::ostringstream oss;
    oss << std::put_time(local_time, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string Measurement::toFileString() const {
    // Formatera för filspar: datum,tid,värde
    std::time_t time = std::chrono::system_clock::to_time_t(timestamp);
    std::tm* local_time = std::localtime(&time);
    
    std::ostringstream oss;
    oss << std::put_time(local_time, "%Y-%m-%d %H:%M:%S") << ","
        << std::fixed << std::setprecision(2) << value;
    return oss.str();
}
