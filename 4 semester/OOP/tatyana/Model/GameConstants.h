#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

class GameConstants {
public:
    static constexpr int TILES_PER_ROADSIDE_LANE = 10;
    static constexpr int LANES_COUNT_ON_FIELD    = 12;

    static constexpr double MINIMAL_VEHICLE_SPEED = 0.05;
    static constexpr double MAXIMAL_VEHICLE_SPEED = 0.2;

    static constexpr double PLAYER_WIDTH = 1.0 / TILES_PER_ROADSIDE_LANE;
    static constexpr double COIN_WIDTH   = PLAYER_WIDTH;

    static constexpr double MINIMAL_VEHICLE_LENGTH = PLAYER_WIDTH * 2;
    static constexpr double MAXIMAL_VEHICLE_LENGTH = PLAYER_WIDTH * 4;

    static constexpr double PLAYER_SPEED = 0.1;

    static constexpr int GAME_THREAD_SLEEP_MS = 100;  // перенесено сюда
};

#endif