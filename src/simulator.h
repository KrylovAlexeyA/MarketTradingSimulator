#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "candle.h"
#include "strategy.h"
#include <vector>
#include <string>
#include <unordered_map>

class Simulator {
public:
    // Хранение данных о свечах для каждого инструмента
    std::unordered_map<std::string, std::vector<Candle>> candles;

    // Метод для добавления данных о свечах для инструмента
    void addCandles(const std::string& instrument, const std::vector<Candle>& instrumentCandles);

    // Метод симуляции торгов для всех стратегий
    void simulate(std::vector<Strategy>& strategies, bool useAveragePrice = true);

    // Метод подсчёта и вывода статистики
    void calculateStatistics(const std::vector<Strategy>& strategies);
};

#endif // SIMULATOR_H
