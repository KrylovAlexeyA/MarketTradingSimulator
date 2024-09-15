#include "trade.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

// Функция для загрузки трейдов из CSV
std::vector<Trade> loadTrades(const std::string& filename) {
    std::vector<Trade> trades;
    std::ifstream file(filename);
    std::string line;

    if (file.is_open()) {
        std::getline(file, line); // Пропускаем заголовок
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            Trade trade;
            std::string timestamp, side, price, amount;

            std::getline(ss, timestamp, ',');
            std::getline(ss, side, ',');
            std::getline(ss, price, ',');
            std::getline(ss, amount, ',');

            trade.timestamp = std::chrono::microseconds(std::stoll(timestamp));
            trade.side = side;
            trade.price = std::stod(price);
            trade.amount = std::stod(amount);

            trades.push_back(trade);
        }
    }
    return trades;
}