#include "trade.h"
#include "bbo.h"
#include "candle.h"
#include <chrono>
#include <iostream>
#include <ostream>

int main() {
    // Загружаем данные
    std::vector<Trade> trades = loadTrades("/Users/krylovalexey/CLionProjects/MarketTradingSimulator/data/trades_1000pepeusdt.csv");
    std::cout << trades.size() << "trades data extracted" << std::endl;
    std::vector<BBO> bboData = loadBBO( "/Users/krylovalexey/CLionProjects/MarketTradingSimulator/data/bbo_1000pepeusdt.csv");
    std::cout << bboData.size() << "bbo data extracted" << std::endl;

    // Временное окно в миллисекундах (например, 1 секунда = 1000 миллисекунд)
    std::chrono::milliseconds windowSize(1000);

    // Генерация свечей
    std::vector<Candle> candles = generateCandles(trades, windowSize);

    // Выводим данные о свечах
    for (const auto& candle : candles) {
        candle.print();
    }

    return 0;
}
