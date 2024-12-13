#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>

class CountryCityManager {
private:
    std::map<std::string, std::vector<std::string>> countryCityMap;

    void loadFromFile(const std::string& filename) {
        std::ifstream inputFile(filename);
        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream ss(line);
            std::string country, city;
            std::getline(ss, country, ',');
            while (std::getline(ss, city, ',')) {
                countryCityMap[country].push_back(city);
            }
        }
        inputFile.close();
    }

    void saveToFile(const std::string& filename) {
        std::ofstream outputFile(filename);
        for (const auto& pair : countryCityMap) {
            outputFile << pair.first;
            for (const auto& city : pair.second) {
                outputFile << "," << city;
            }
            outputFile << "\n";
        }
        outputFile.close();
    }

public:
    CountryCityManager(const std::string& filename) {
        loadFromFile(filename);
    }

    void displayCountries() const {
        for (const auto& pair : countryCityMap) {
            std::cout << pair.first << std::endl;
        }
    }

    void displayCities(const std::string& country) const {
        auto it = countryCityMap.find(country);
        if (it != countryCityMap.end()) {
            for (const auto& city : it->second) {
                std::cout << city << std::endl;
            }
        } else {
            std::cout << "Country not found!" << std::endl;
        }
    }

    void addCountry(const std::string& country) {
        if (countryCityMap.find(country) == countryCityMap.end()) {
            countryCityMap[country] = {};
        } else {
            std::cout << "Country already exists!" << std::endl;
        }
    }

    void removeCountry(const std::string& country) {
        countryCityMap.erase(country);
    }

    void addCity(const std::string& country, const std::string& city) {
        countryCityMap[country].push_back(city);
    }

    void removeCity(const std::string& country, const std::string& city) {
        auto& cities = countryCityMap[country];
        cities.erase(std::remove(cities.begin(), cities.end(), city), cities.end());
    }

    void replaceCity(const std::string& country, const std::string& oldCity, const std::string& newCity) {
        auto& cities = countryCityMap[country];
        auto it = std::find(cities.begin(), cities.end(), oldCity);
        if (it != cities.end()) {
            *it = newCity;
        } else {
            std::cout << "City not found!" << std::endl;
        }
    }

    void countCities(const std::string& country) const {
        auto it = countryCityMap.find(country);
        if (it != countryCityMap.end()) {
            std::cout << "Number of cities in " << country << ": " << it->second.size() << std::endl;
        } else {
            std::cout << "Country not found!" << std::endl;
        }
    }

    void searchCityInCountry(const std::string& country, const std::string& city) const {
        auto it = countryCityMap.find(country);
        if (it != countryCityMap.end()) {
            auto cityIt = std::find(it->second.begin(), it->second.end(), city);
            if (cityIt != it->second.end()) {
                std::cout << "City " << city << " found in " << country << std::endl;
            } else {
                std::cout << "City " << city << " not found in " << country << std::endl;
            }
        } else {
            std::cout << "Country not found!" << std::endl;
        }
    }

    void saveChanges(const std::string& filename) {
        saveToFile(filename);
    }
};

int main() {
    CountryCityManager manager("countries_cities.txt");

    manager.displayCountries();
    manager.displayCities("USA");

    manager.addCountry("Germany");
    manager.addCity("Germany", "Berlin");
    manager.addCity("Germany", "Munich");

    manager.removeCity("Germany", "Munich");
    manager.replaceCity("Germany", "Berlin", "Hamburg");

    manager.searchCityInCountry("Germany", "Hamburg");

    manager.countCities("Germany");

    manager.removeCountry("Germany");

    manager.saveChanges("countries_cities_updated.txt");

    return 0;
}
