#include "bbo.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Функция для загрузки данных BBO из CSV
std::vector<BBO> loadBBO(const std::string &filename) {
    std::vector<BBO> bboData;
    std::ifstream file(filename);
    std::string line;

    if (file.is_open()) {
        std::getline(file, line); // Пропускаем заголовок
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            BBO bbo;
            std::string timestamp, askAmount, askPrice, bidPrice, bidAmount;

            std::getline(ss, timestamp, ',');
            std::getline(ss, askAmount, ',');
            std::getline(ss, askPrice, ',');
            std::getline(ss, bidPrice, ',');
            std::getline(ss, bidAmount, ',');

            bbo.timestamp = std::chrono::microseconds(std::stoll(timestamp));
            bbo.askAmount = std::stod(askAmount);
            bbo.askPrice = std::stod(askPrice);
            bbo.bidPrice = std::stod(bidPrice);
            bbo.bidAmount = std::stod(bidAmount);

            bboData.push_back(bbo);
        }
        return bboData;
    }
}
