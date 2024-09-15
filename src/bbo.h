#ifndef BBO_H
#define BBO_H

#include <chrono>
#include <vector>
#include <string>

// Структура для BBO (Best Bid/Offer)
struct BBO {
    std::chrono::microseconds timestamp;
    double askAmount;
    double askPrice;
    double bidPrice;
    double bidAmount;
};

// Функция для загрузки данных BBO из CSV
std::vector<BBO> loadBBO(const std::string& filename);

#endif // BBO_H
