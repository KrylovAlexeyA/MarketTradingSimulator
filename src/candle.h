#ifndef CANDLE_H
#define CANDLE_H

#include "trade.h"
#include <vector>

// Структура для свечи (OLHC Candle)
struct Candle {
    double open;
    double close;
    double low;
    double high;
    double avgBuyPrice;
    double avgSellPrice;
    double buyVolume;
    double sellVolume;

    Candle(double initialPrice);

    // Обновление свечи на основе трейда
    void update(const Trade& trade);

    // Печать информации о свече
    void print() const;
};

// Функция для генерации свечей
std::vector<Candle> generateCandles(const std::vector<Trade>& trades, std::chrono::milliseconds windowSize);

#endif // CANDLE_H