cmake_minimum_required(VERSION 3.29)
project(MarketTradingSimulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(MarketTradingSimulator src/main.cpp
        src/trade.h
        src/trade.cpp
        src/bbo.h
        src/bbo.cpp
        src/candle.h
        src/candle.cpp
        src/strategy.h
        src/strategy.cpp
        src/simulator.h
        src/simulator.cpp
)
