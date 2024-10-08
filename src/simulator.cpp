#include "simulator.h"
#include <iostream>

// Метод для добавления данных о свечах для инструмента
void Simulator::addCandles(const std::string& instrument, const std::vector<Candle>& instrumentCandles) {
    candles[instrument] = instrumentCandles;
}

// Метод для добавления данных BBO для инструмента
void Simulator::addBBOData(const std::string& instrument, const std::vector<BBO>& instrumentBBO) {
    bboData[instrument] = instrumentBBO;
}

// Метод симуляции торгов для всех стратегий
void Simulator::simulate(std::vector<Strategy>& strategies, bool useBBO, bool useAveragePrice) {
    for (auto& strategy : strategies) {
        for (auto& actionPair : strategy.actions) {
            const std::string& instrument = actionPair.first;
            const std::vector<int>& actions = actionPair.second;

            if (candles.find(instrument) == candles.end() || bboData.find(instrument) == bboData.end()) {
                std::cerr << "Данные по свечам или BBO для инструмента " << instrument << " не найдены." << std::endl;
                continue;
            }

            const std::vector<Candle>& instrumentCandles = candles[instrument];
            const std::vector<BBO>& instrumentBBO = bboData[instrument];

            for (size_t i = 0; i < actions.size() && i < instrumentCandles.size() && i < instrumentBBO.size(); ++i) {
                const Candle& candle = instrumentCandles[i];
                const BBO& bbo = instrumentBBO[i];
                int action = actions[i]; // Положительное значение - покупка, отрицательное - продажа

                double tradePrice = 0;

                if (useBBO) {
                    // Использование цен BBO для покупки и продажи
                    if (action > 0) {
                        tradePrice = bbo.askPrice;  // Покупка по цене Ask
                    } else if (action < 0) {
                        tradePrice = bbo.bidPrice;  // Продажа по цене Bid
                    }
                } else {
                    // Использование средней цены или цены закрытия
                    tradePrice = useAveragePrice ? (action > 0 ? candle.avgBuyPrice : candle.avgSellPrice) : candle.close;
                }

                // Рассчитываем PnL для этой сделки
                double tradePnL = action * tradePrice;
                strategy.pnl[instrument] += tradePnL;

                // Увеличиваем проторгованный объём
                strategy.tradedVolume[instrument] += abs(action);

                // Изменение позиции
                int previousPosition = strategy.currentPosition[instrument];
                strategy.currentPosition[instrument] += action;

                // Считаем количество переходов через 0
                if ((previousPosition > 0 && strategy.currentPosition[instrument] < 0) ||
                    (previousPosition < 0 && strategy.currentPosition[instrument] > 0)) {
                    strategy.positionFlips[instrument]++;
                }

                // Время удержания позиции (условно за каждый период)
                if (action != 0) {
                    strategy.holdingTime[instrument] += 1;
                }
            }
        }
    }
}

// Метод подсчёта и вывода статистики
void Simulator::calculateStatistics(const std::vector<Strategy>& strategies) {
    for (const auto& strategy : strategies) {
        std::cout << "Стратегия: " << strategy.name << std::endl;
        for (const auto& pnlPair : strategy.pnl) {
            const std::string& instrument = pnlPair.first;
            std::cout << "Инструмент: " << instrument << std::endl;
            std::cout << "PnL: " << strategy.pnl.at(instrument) << std::endl;
            std::cout << "Проторгованный объём: " << strategy.tradedVolume.at(instrument) << std::endl;
            std::cout << "Количество переходов через 0: " << strategy.positionFlips.at(instrument) << std::endl;
            std::cout << "Среднее время удержания позиции: " << strategy.holdingTime.at(instrument) << std::endl;
        }
        std::cout << std::endl;
    }
}
