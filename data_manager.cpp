#include "data_manager.h"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <random>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

// Konstruktor
DataManager::DataManager() {
    // Initieringslogik om det behövs
}

// Lägg till ett nytt mätvärde
void DataManager::addMeasurement(double value) {
    Measurement m;
    m.value = value;
    m.timestamp = chrono::system_clock::now();
    measurements.push_back(m);
}

// Rensa alla mätvärden
void DataManager::clearAllMeasurements() {
    measurements.clear();
}

// Hämta antal mätvärden
size_t DataManager::getMeasurementCount() const {
    return measurements.size();
}

// Privat hjälpmetod: Beräkna medelvärde
double DataManager::calculateMean() const {
    if (measurements.empty()) return 0.0;
    
    double sum = 0.0;
    for (const auto& m : measurements) {
        sum += m.value;
    }
    return sum / measurements.size();
}

// Privat hjälpmetod: Beräkna varians
double DataManager::calculateVariance(double mean) const {
    if (measurements.size() <= 1) return 0.0;
    
    double variance = 0.0;
    for (const auto& m : measurements) {
        variance += pow(m.value - mean, 2);
    }
    return variance / measurements.size();
}

// Beräkna fullständig statistik
DataManager::Statistics DataManager::calculateStatistics() const {
    Statistics stats;
    
    if (measurements.empty()) {
        return stats;
    }
    
    stats.count = measurements.size();
    
    // Beräkna summa, min och max
    stats.min = measurements[0].value;
    stats.max = measurements[0].value;
    stats.minIndex = 0;
    stats.maxIndex = 0;
    
    for (size_t i = 0; i < measurements.size(); ++i) {
        double value = measurements[i].value;
        stats.sum += value;
        
        if (value < stats.min) {
            stats.min = value;
            stats.minIndex = i;
        }
        if (value > stats.max) {
            stats.max = value;
            stats.maxIndex = i;
        }
    }
    
    // Beräkna övrig statistik
    stats.mean = stats.sum / stats.count;
    stats.variance = calculateVariance(stats.mean);
    stats.standardDeviation = sqrt(stats.variance);
    
    return stats;
}

// Simulera sensordata
void DataManager::simulateSensorData(int count) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(20.0, 30.0);
    
    for (int i = 0; i < count; ++i) {
        addMeasurement(dist(gen));
    }
}

// Hämta alla värden som en vektor
vector<double> DataManager::getAllValues() const {
    vector<double> values;
    for (const auto& m : measurements) {
        values.push_back(m.value);
    }
    return values;
}

// Hämta alla mätvärden
vector<Measurement> DataManager::getAllMeasurements() const {
    return measurements;
}

// Sök efter specifikt värde
vector<int> DataManager::findValue(double target, double tolerance) const {
    vector<int> indices;
    
    for (size_t i = 0; i < measurements.size(); ++i) {
        if (abs(measurements[i].value - target) < tolerance) {
            indices.push_back(i);
        }
    }
    
    return indices;
}

// Hitta mätvärden över tröskel
vector<Measurement> DataManager::findAboveThreshold(double threshold) const {
    vector<Measurement> result;
    
    for (const auto& m : measurements) {
        if (m.value > threshold) {
            result.push_back(m);
        }
    }
    
    return result;
}

// Hitta mätvärden under tröskel
vector<Measurement> DataManager::findBelowThreshold(double threshold) const {
    vector<Measurement> result;
    
    for (const auto& m : measurements) {
        if (m.value <= threshold) {
            result.push_back(m);
        }
    }
    
    return result;
}

// Sortera mätvärden stigande
void DataManager::sortMeasurementsAscending() {
    sort(measurements.begin(), measurements.end(), 
        [](const Measurement& a, const Measurement& b) {
            return a.value < b.value;
        });
}

// Sortera mätvärden fallande
void DataManager::sortMeasurementsDescending() {
    sort(measurements.begin(), measurements.end(), 
        [](const Measurement& a, const Measurement& b) {
            return a.value > b.value;
        });
}

// Beräkna glidande medelvärde
vector<double> DataManager::calculateMovingAverage(int windowSize) const {
    vector<double> movingAverages;
    
    if (measurements.size() < windowSize) {
        return movingAverages;
    }
    
    for (size_t i = windowSize - 1; i < measurements.size(); ++i) {
        double sum = 0.0;
        for (int j = 0; j < windowSize; ++j) {
            sum += measurements[i - j].value;
        }
        movingAverages.push_back(sum / windowSize);
    }
    
    return movingAverages;
}

// Generera histogram
map<int, int> DataManager::generateHistogram() const {
    map<int, int> histogram;
    
    for (const auto& m : measurements) {
        int rounded = static_cast<int>(round(m.value));
        histogram[rounded]++;
    }
    
    return histogram;
}

// NY FUNKTION: Spara till fil
bool DataManager::saveToFile(const string& filename) const {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: Could not open file for writing: " << filename << endl;
        return false;
    }
    
    // Skriv header
    file << "timestamp,value" << endl;
    
    // Skriv alla mätvärden
    for (const auto& m : measurements) {
        file << m.toFileString() << endl;
    }
    
    file.close();
    return true;
}

// NY FUNKTION: Ladda från fil
bool DataManager::loadFromFile(const string& filename) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: Could not open file for reading: " << filename << endl;
        return false;
    }
    
    // Rensa befintliga mätvärden
    measurements.clear();
    
    string line;
    getline(file, line); // Läs bort header
    
    int loadedCount = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string timestampStr, valueStr;
        
        // Försök att läsa kommaseparerade värden
        if (getline(ss, timestampStr, ',') && getline(ss, valueStr)) {
            try {
                // Konvertera sträng till time_point
                tm tm = {};
                stringstream tsStream(timestampStr);
                tsStream >> get_time(&tm, "%Y-%m-%d %H:%M:%S");
                
                if (tsStream.fail()) {
                    // Försök med alternativt format
                    tsStream.clear();
                    tsStream.str(timestampStr);
                    tsStream >> get_time(&tm, "%Y-%m-%d %H:%M");
                }
                
                time_t time = mktime(&tm);
                chrono::system_clock::time_point tp = chrono::system_clock::from_time_t(time);
                
                // Konvertera värde
                double value = stod(valueStr);
                
                // Skapa och lägg till mätvärde
                Measurement m;
                m.value = value;
                m.timestamp = tp;
                measurements.push_back(m);
                loadedCount++;
                
            } catch (const exception& e) {
                cerr << "Warning: Could not parse line: " << line << endl;
                cerr << "Error: " << e.what() << endl;
            }
        }
    }
    
    file.close();
    cout << "Loaded " << loadedCount << " measurements from " << filename << endl;
    return loadedCount > 0;
}
