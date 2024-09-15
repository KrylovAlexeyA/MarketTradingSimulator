#include "trade.h"
#include "bbo.h"
#include "candle.h"
#include "strategy.h"
#include "simulator.h"
#include <iostream>
#include <chrono>

int main() {
    // Загружаем данные
    std::vector<Trade> pepeTrades = loadTrades("/Users/krylovalexey/CLionProjects/MarketTradingSimulator/data/trades_1000pepeusdt.csv");
    std::vector<Candle> pepeCandles = generateCandles(pepeTrades, std::chrono::milliseconds(1000));

    std::vector<Trade> dogeTrades = loadTrades("/Users/krylovalexey/CLionProjects/MarketTradingSimulator/data/trades_1000pepeusdt.csv");
    std::vector<Candle> dogeCandles = generateCandles(dogeTrades, std::chrono::milliseconds(1000));

    // Инициализируем стратегии
    Strategy strategy1("Strategy 1");
    Strategy strategy2("Strategy 2");

    // Добавляем действия для каждой стратегии
    strategy1.addActions("PEPEUSDT", {5, -3, 0, 2, -1});
    strategy1.addActions("DOGEUSDT", {-10, 5, 0, 5, -5});

    strategy2.addActions("PEPEUSDT", {1, 0, 1, -1, 2});
    strategy2.addActions("DOGEUSDT", {3, 0, -3, 2, 0});

    // Инициализируем симулятор
    Simulator simulator;
    simulator.addCandles("PEPEUSDT", pepeCandles);
    simulator.addCandles("DOGEUSDT", dogeCandles);

    // Симулируем стратегии
    std::vector<Strategy> strategies = {strategy1, strategy2};

    // Запускаем симуляцию для режима использования средней цены
    simulator.simulate(strategies, true);

    // Выводим статистику
    simulator.calculateStatistics(strategies);

    return 0;
}
