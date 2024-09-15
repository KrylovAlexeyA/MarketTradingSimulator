#ifndef TRADE_H
#define TRADE_H

#include <chrono>
#include <string>

// Структура для трейда
struct Trade {
    std::chrono::microseconds timestamp;  // Время сделки
    std::string side;                     // Покупка или продажа
    double price;                         // Цена сделки
    double amount;                        // Количество контрактов
};

// Функция для загрузки трейдов из CSV
std::vector<Trade> loadTrades(const std::string& filename);

#endif // TRADE_H