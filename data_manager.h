#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "measurement.h"
#include <vector>
#include <string>
#include <map>

// Klass för att hantera alla mätvärden och deras analys
// Jag valde klass för att kapsla in komplex logik och datamanipulation
class DataManager {
private:
    std::vector<Measurement> measurements;  // Alla sparade mätvärden
    
    // Privata hjälpmetoder
    double calculateMean() const;
    double calculateVariance(double mean) const;
    
public:
    // Konstruktor och destruktor
    DataManager();
    ~DataManager() = default;
    
    // Grundläggande operationer
    void addMeasurement(double value);
    void clearAllMeasurements();
    size_t getMeasurementCount() const;
    
    // Filhantering - ny funktionalitet för inlämning 2
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
    
    // Avancerade funktioner från inlämning 1
    void simulateSensorData(int count);
    std::vector<double> getAllValues() const;
    std::vector<Measurement> getAllMeasurements() const;
    
    // Statistikberäkningar
    struct Statistics {
        size_t count;
        double sum;
        double mean;
        double min;
        double max;
        double variance;
        double standardDeviation;
        int minIndex;
        int maxIndex;
        
        // Konstruktor för att initiera värden
        Statistics() : count(0), sum(0), mean(0), min(0), max(0), 
                      variance(0), standardDeviation(0), minIndex(-1), maxIndex(-1) {}
    };
    
    Statistics calculateStatistics() const;
    
    // Sök- och filterfunktioner
    std::vector<int> findValue(double target, double tolerance = 0.001) const;
    std::vector<Measurement> findAboveThreshold(double threshold) const;
    std::vector<Measurement> findBelowThreshold(double threshold) const;
    
    // Sorteringsfunktioner
    void sortMeasurementsAscending();
    void sortMeasurementsDescending();
    
    // Glidande medelvärde
    std::vector<double> calculateMovingAverage(int windowSize) const;
    
    // Histogramgenerering
    std::map<int, int> generateHistogram() const;
};

#endif // DATA_MANAGER_H
