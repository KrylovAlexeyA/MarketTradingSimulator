#include "candle.h"
#include <iostream>
#include <algorithm>

// Конструктор для свечи
Candle::Candle(double initialPrice)
    : open(initialPrice), close(initialPrice), low(initialPrice), high(initialPrice),
      avgBuyPrice(0), avgSellPrice(0), buyVolume(0), sellVolume(0) {}

// Обновление свечи на основе трейда
void Candle::update(const Trade& trade) {
    close = trade.price;
    low = std::min(low, trade.price);
    high = std::max(high, trade.price);

    if (trade.side == "buy") {
        avgBuyPrice = (avgBuyPrice * buyVolume + trade.price * trade.amount) / (buyVolume + trade.amount);
        buyVolume += trade.amount;
    } else {
        avgSellPrice = (avgSellPrice * sellVolume + trade.price * trade.amount) / (sellVolume + trade.amount);
        sellVolume += trade.amount;
    }
}

// Печать информации о свече
void Candle::print() const {
    std::cout << "Open: " << open << ", Close: " << close
              << ", Low: " << low << ", High: " << high
              << ", AvgBuyPrice: " << avgBuyPrice
              << ", AvgSellPrice: " << avgSellPrice
              << ", BuyVolume: " << buyVolume
              << ", SellVolume: " << sellVolume << std::endl;
}

// Функция для генерации свечей
std::vector<Candle> generateCandles(const std::vector<Trade>& trades, std::chrono::milliseconds windowSize) {
    std::vector<Candle> candles;

    if (trades.empty()) return candles;

    std::chrono::microseconds startTime = trades[0].timestamp;
    Candle currentCandle(trades[0].price);

    for (const auto& trade : trades) {
        if (trade.timestamp - startTime >= windowSize) {
            candles.push_back(currentCandle);  // Завершаем текущую свечу
            startTime = trade.timestamp;       // Начинаем новую свечу
            currentCandle = Candle(trade.price);
        }
        currentCandle.update(trade);           // Обновляем текущую свечу на основе сделки
    }

    candles.push_back(currentCandle);          // Добавляем последнюю свечу
    return candles;
}
