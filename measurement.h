#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <string>
#include <chrono>

// Struct för att representera ett enskilt mätvärde
// Jag valde struct eftersom detta är en enkel databehållare
struct Measurement {
    double value;  // Mätvärdet (t.ex. temperatur)
    std::chrono::system_clock::time_point timestamp;  // När mätningen gjordes
    
    // Funktion för att få en läsbar tidssträng
    std::string getTimeString() const;
    
    // Funktion för att få en formaterad sträng för filspar
    std::string toFileString() const;
};

#endif // MEASUREMENT_H
