#include "data_manager.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <limits>

using namespace std;

// Funktion för att visa huvudmenyn
void displayMenu() {
    cout << "\n=== IoT DATA ANALYZER ===" << endl;
    cout << "1. Add manual measurements" << endl;
    cout << "2. Simulate sensor data" << endl;
    cout << "3. Show statistics" << endl;
    cout << "4. Search for value" << endl;
    cout << "5. Sort measurements" << endl;
    cout << "6. Threshold analysis" << endl;
    cout << "7. Moving average" << endl;
    cout << "8. Display histogram" << endl;
    cout << "9. Show all measurements" << endl;
    cout << "10. Clear all measurements" << endl;
    cout << "11. Save to file" << endl;
    cout << "12. Load from file" << endl;
    cout << "0. Exit program" << endl;
    cout << "Choice: ";
}

// Funktion för att visa statistik
void displayStatistics(const DataManager::Statistics& stats, const DataManager& dm) {
    if (stats.count == 0) {
        cout << "No measurements available for analysis." << endl;
        return;
    }
    
    auto measurements = dm.getAllMeasurements();
    
    cout << "\n=== STATISTICAL ANALYSIS ===" << endl;
    cout << "Count: " << stats.count << endl;
    cout << "Sum: " << fixed << setprecision(2) << stats.sum << endl;
    cout << "Mean: " << fixed << setprecision(2) << stats.mean << endl;
    cout << "Minimum: " << stats.min << " (Measurement #" << (stats.minIndex + 1);
    if (stats.minIndex >= 0 && stats.minIndex < measurements.size()) {
        cout << " at " << measurements[stats.minIndex].getTimeString();
    }
    cout << ")" << endl;
    
    cout << "Maximum: " << stats.max << " (Measurement #" << (stats.maxIndex + 1);
    if (stats.maxIndex >= 0 && stats.maxIndex < measurements.size()) {
        cout << " at " << measurements[stats.maxIndex].getTimeString();
    }
    cout << ")" << endl;
    
    cout << "Variance: " << fixed << setprecision(4) << stats.variance << endl;
    cout << "Standard Deviation: " << fixed << setprecision(4) << stats.standardDeviation << endl;
}

// Funktion för att visa histogram
void displayHistogram(const DataManager& dm) {
    auto histogram = dm.generateHistogram();
    
    if (histogram.empty()) {
        cout << "No measurements available for visualization." << endl;
        return;
    }
    
    // Hitta maxfrekvens för skalning
    int maxFreq = 0;
    for (const auto& pair : histogram) {
        if (pair.second > maxFreq) {
            maxFreq = pair.second;
        }
    }
    
    const int maxWidth = 50;
    
    cout << "\n=== TEMPERATURE HISTOGRAM ===" << endl;
    cout << "Value Distribution:" << endl;
    
    for (const auto& pair : histogram) {
        cout << setw(3) << pair.first << "°C | ";
        int barWidth = (pair.second * maxWidth) / maxFreq;
        cout << string(barWidth, '*') << " (" << pair.second << ")" << endl;
    }
}

// Huvudfunktion
int main() {
    DataManager dataManager;
    int choice;
    
    cout << "=== IoT MEASUREMENT ANALYZER ===" << endl;
    cout << "Advanced data analysis tool for sensor measurements" << endl;
    
    // Automatisk laddning från fil vid start (valfritt)
    /*
    cout << "Attempting to load previous measurements from 'measurements.csv'..." << endl;
    if (dataManager.loadFromFile("measurements.csv")) {
        cout << "Previous measurements loaded successfully!" << endl;
    }
    */
    
    do {
        displayMenu();
        
        while (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        switch (choice) {
            case 1: {
                // Lägg till manuella mätvärden
                cout << "\n=== ADD MANUAL MEASUREMENTS ===" << endl;
                cout << "Enter values (decimal numbers). Type 'done' when finished:" << endl;
                
                string input;
                while (true) {
                    cout << "Value: ";
                    cin >> input;
                    
                    if (input == "done" || input == "Done") {
                        break;
                    }
                    
                    try {
                        double value = stod(input);
                        dataManager.addMeasurement(value);
                        cout << "Added: " << value << endl;
                    } catch (const exception& e) {
                        cout << "Invalid value! Please enter a numeric value." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                break;
            }
            
            case 2: {
                // Simulera sensordata
                cout << "\n=== SENSOR SIMULATION ===" << endl;
                cout << "Enter number of measurements to simulate (20-30°C): ";
                
                int count;
                while (!(cin >> count) || count <= 0) {
                    cout << "Invalid number! Enter a positive integer: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                
                dataManager.simulateSensorData(count);
                cout << "Simulated " << count << " measurements." << endl;
                break;
            }
            
            case 3: {
                // Visa statistik
                auto stats = dataManager.calculateStatistics();
                displayStatistics(stats, dataManager);
                break;
            }
            
            case 4: {
                // Sök värde
                cout << "\n=== SEARCH VALUE ===" << endl;
                cout << "Enter value to search for: ";
                
                double target;
                while (!(cin >> target)) {
                    cout << "Invalid value! Enter a numeric value: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                
                auto indices = dataManager.findValue(target);
                if (indices.empty()) {
                    cout << "No matching values found for " << target << endl;
                } else {
                    cout << "Found " << target << " at " << indices.size() << " position(s): ";
                    for (size_t i = 0; i < indices.size(); ++i) {
                        cout << "Measurement #" << (indices[i] + 1);
                        if (i < indices.size() - 1) cout << ", ";
                    }
                    cout << endl;
                }
                break;
            }
            
            case 5: {
                // Sortera mätvärden
                cout << "\n=== SORT MEASUREMENTS ===" << endl;
                cout << "Choose sorting order:" << endl;
                cout << "1. Ascending (lowest first)" << endl;
                cout << "2. Descending (highest first)" << endl;
                cout << "Choice: ";
                
                int sortChoice;
                while (!(cin >> sortChoice) || (sortChoice != 1 && sortChoice != 2)) {
                    cout << "Invalid choice! Choose 1 or 2: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                
                if (sortChoice == 1) {
                    dataManager.sortMeasurementsAscending();
                    cout << "Measurements sorted in ascending order." << endl;
                } else {
                    dataManager.sortMeasurementsDescending();
                    cout << "Measurements sorted in descending order." << endl;
                }
                break;
            }
            
            case 6: {
                // Tröskelvärdesanalys
                cout << "\n=== THRESHOLD ANALYSIS ===" << endl;
                cout << "Enter critical threshold (e.g., 25.0): ";
                
                double threshold;
                while (!(cin >> threshold)) {
                    cout << "Invalid value! Enter a numeric value: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                
                auto above = dataManager.findAboveThreshold(threshold);
                auto below = dataManager.findBelowThreshold(threshold);
                auto stats = dataManager.calculateStatistics();
                
                cout << "\nThreshold: " << threshold << endl;
                cout << "Values above threshold: " << above.size() << " (" 
                     << fixed << setprecision(1) 
                     << (static_cast<double>(above.size()) / stats.count * 100) << "%)" << endl;
                cout << "Values below threshold: " << below.size() << " (" 
                     << fixed << setprecision(1) 
                     << (static_cast<double>(below.size()) / stats.count * 100) << "%)" << endl;
                
                if (!above.empty()) {
                    cout << "WARNING: " << above.size() << " measurements exceed critical threshold!" << endl;
                }
                break;
            }
            
            case 7: {
                // Glidande medelvärde
                cout << "\n=== MOVING AVERAGE ===" << endl;
                cout << "Choose window size (3 or 5): ";
                
                int window;
                while (!(cin >> window) || (window != 3 && window != 5)) {
                    cout << "Invalid choice! Choose 3 or 5: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                
                auto movingAvgs = dataManager.calculateMovingAverage(window);
                auto stats = dataManager.calculateStatistics();
                
                if (movingAvgs.empty()) {
                    cout << "Not enough measurements for moving average with window " << window << endl;
                } else {
                    cout << "\nMoving averages (window: " << window << "):" << endl;
                    cout << "Total mean: " << fixed << setprecision(2) << stats.mean << endl;
                    
                    for (size_t i = 0; i < movingAvgs.size(); ++i) {
                        cout << "Window " << (i + 1) << ": " << fixed << setprecision(2) << movingAvgs[i];
                        double diff = movingAvgs[i] - stats.mean;
                        if (abs(diff) > 0.1) {
                            cout << " (" << (diff > 0 ? "+" : "") << fixed << setprecision(2) << diff 
                                 << " from total mean)" << endl;
                        } else {
                            cout << " (close to total mean)" << endl;
                        }
                    }
                }
                break;
            }
            
            case 8: {
                // Visa histogram
                displayHistogram(dataManager);
                break;
            }
            
            case 9: {
                // Visa alla mätvärden
                auto measurements = dataManager.getAllMeasurements();
                
                if (measurements.empty()) {
                    cout << "No measurements available." << endl;
                } else {
                    cout << "\n=== ALL MEASUREMENTS ===" << endl;
                    cout << "Total: " << measurements.size() << " measurements" << endl;
                    
                    for (size_t i = 0; i < measurements.size(); ++i) {
                        cout << "Measurement #" << (i + 1) << ": " 
                             << fixed << setprecision(2) << measurements[i].value
                             << " - " << measurements[i].getTimeString() << endl;
                    }
                }
                break;
            }
            
            case 10: {
                // Rensa alla mätvärden
                dataManager.clearAllMeasurements();
                cout << "All measurements have been cleared." << endl;
                break;
            }
            
            case 11: {
                // Spara till fil
                cout << "\n=== SAVE TO FILE ===" << endl;
                cout << "Enter filename (or press Enter for 'measurements.csv'): ";
                
                string filename;
                cin.ignore();
                getline(cin, filename);
                
                if (filename.empty()) {
                    filename = "measurements.csv";
                }
                
                if (dataManager.saveToFile(filename)) {
                    cout << "Measurements saved to " << filename << " successfully!" << endl;
                } else {
                    cout << "Failed to save measurements." << endl;
                }
                break;
            }
            
            case 12: {
                // Ladda från fil
                cout << "\n=== LOAD FROM FILE ===" << endl;
                cout << "Enter filename (or press Enter for 'measurements.csv'): ";
                
                string filename;
                cin.ignore();
                getline(cin, filename);
                
                if (filename.empty()) {
                    filename = "measurements.csv";
                }
                
                if (dataManager.loadFromFile(filename)) {
                    cout << "Measurements loaded from " << filename << " successfully!" << endl;
                } else {
                    cout << "Failed to load measurements. File may not exist or is empty." << endl;
                }
                break;
            }
            
            case 0: {
                // Automatisk sparfil vid avslut
                cout << "\nSaving measurements to 'measurements_auto_save.csv'..." << endl;
                dataManager.saveToFile("measurements_auto_save.csv");
                
                cout << "Exiting program. Thank you for using the IoT Analyzer!" << endl;
                break;
            }
            
            default: {
                cout << "Invalid choice! Please choose an option between 0-12." << endl;
                break;
            }
        }
        
    } while (choice != 0);
    
    return 0;
}
