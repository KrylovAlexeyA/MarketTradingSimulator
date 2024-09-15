#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "candle.h"
#include "bbo.h"
#include "strategy.h"
#include <vector>
#include <string>
#include <unordered_map>

class Simulator {
public:
    // Данные о свечах и BBO для каждого инструмента
    std::unordered_map<std::string, std::vector<Candle>> candles;
    std::unordered_map<std::string, std::vector<BBO>> bboData;  // Данные BBO для каждого инструмента

    // Метод для добавления данных о свечах и BBO для инструмента
    void addCandles(const std::string& instrument, const std::vector<Candle>& instrumentCandles);
    void addBBOData(const std::string& instrument, const std::vector<BBO>& instrumentBBO);

    // Метод симуляции торгов для всех стратегий
    void simulate(std::vector<Strategy>& strategies, bool useBBO = false, bool useAveragePrice = true);

    // Метод подсчёта и вывода статистики
    void calculateStatistics(const std::vector<Strategy>& strategies);
};

#endif // SIMULATOR_H
