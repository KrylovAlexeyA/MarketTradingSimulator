#include "strategy.h"

// Конструктор, инициализирующий стратегию по имени
Strategy::Strategy(const std::string& name) : name(name) {}

// Метод добавления действий для инструмента
void Strategy::addActions(const std::string& instrument, const std::vector<int>& instrumentActions) {
    actions[instrument] = instrumentActions;
    pnl[instrument] = 0;
    tradedVolume[instrument] = 0;
    positionFlips[instrument] = 0;
    holdingTime[instrument] = 0;
    currentPosition[instrument] = 0;
}
