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
    std::cout << pepeTrades.size() << " pepe trades строк извлечено" << std::endl;
    std::vector<Candle> pepeCandles = generateCandles(pepeTrades, std::chrono::milliseconds(1000));
    std::cout << pepeCandles.size() << " pepe свечек создано" << std::endl;
    std::vector<BBO> pepeBBO = loadBBO("/Users/krylovalexey/CLionProjects/MarketTradingSimulator/data/bbo_1000pepeusdt.csv");
    std::cout << pepeBBO.size() << " pepe bbo строк извлечено" << std::endl;

    std::vector<Trade> dogeTrades = loadTrades("/Users/krylovalexey/CLionProjects/MarketTradingSimulator/data/trades_dogeusdt.csv");
    std::cout << dogeTrades.size() << " dodge trades строк извлечено" << std::endl;
    std::vector<Candle> dogeCandles = generateCandles(dogeTrades, std::chrono::milliseconds(1000));
    std::cout << dogeCandles.size() << " dodge свечек создано" << std::endl;
    std::vector<BBO> dogeBBO = loadBBO("/Users/krylovalexey/CLionProjects/MarketTradingSimulator/data/bbo_dogeusdt.csv");
    std::cout << dogeBBO.size() << " doge bbo строк извлечено" << std::endl;

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
    simulator.addBBOData("PEPEUSDT", pepeBBO);

    simulator.addCandles("DOGEUSDT", dogeCandles);
    simulator.addBBOData("DOGEUSDT", dogeBBO);

    // Симулируем стратегии
    std::vector<Strategy> strategies = {strategy1, strategy2};

    // Запускаем симуляцию с использованием цен BBO
    simulator.simulate(strategies, true, false);

    // Выводим статистику
    simulator.calculateStatistics(strategies);

    return 0;
}
