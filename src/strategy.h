#ifndef STRATEGY_H
#define STRATEGY_H

#include <string>
#include <vector>
#include <unordered_map>

class Strategy {
public:
    std::string name;  // Имя стратегии
    std::unordered_map<std::string, std::vector<int>> actions; // actions[instrument_name][candle_index]
    std::unordered_map<std::string, double> pnl;               // Финансовый результат (PnL)
    std::unordered_map<std::string, double> tradedVolume;      // Проторгованный объём
    std::unordered_map<std::string, int> positionFlips;        // Количество переходов через 0
    std::unordered_map<std::string, double> holdingTime;       // Среднее время удержания позиции
    std::unordered_map<std::string, int> currentPosition;      // Текущая позиция

    // Конструктор с указанием имени стратегии
    Strategy(const std::string& name);

    // Метод для добавления действий для определённого инструмента
    void addActions(const std::string& instrument, const std::vector<int>& instrumentActions);
};

#endif // STRATEGY_H
