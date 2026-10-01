#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

/**
 * Константы, необходимые для работы игры
 */
class GameConstants
{
public:
    /**
     * Количество частей, на которые делится дорожка
     */
    static constexpr int TILES_PER_ROADSIDE_LANE{ 10 };

    /**
     * Количество активных дорожек на поле
     */
    static constexpr int LANES_COUNT_ON_FIELD{ 12 };

    /**
     * Минимально возможная относительная скорость машин
     */
    static constexpr double MINIMAL_VEHICLE_SPEED{ 0.008 };

    /**
     * Максимально возможная относительная скорость машин
     */
    static constexpr double MAXIMAL_VEHICLE_SPEED{ 0.01 };

    /**
     * Вероятность того, что новая дорожка окажется проезжей частью
     */
    static constexpr double LANE_ROAD_SPAWN_CHANCE{ 0.5 };

    /**
     * Относительная ширина игрового персонажа
     */
    static constexpr double PLAYER_WIDTH{ 1.0 / TILES_PER_ROADSIDE_LANE };

    /**
     * Относительная ширина монеты
     */
    static constexpr double COIN_WIDTH{ PLAYER_WIDTH };

    /**
     * Относительная ширина машины
     */
    static constexpr double VEHICLE_LENGTH{ PLAYER_WIDTH * 2 };

    /**
     * Относительная скорость игрока
     */
    static constexpr double PLAYER_SPEED{ 0.1 };

    /**
     * Вероятность появления монеты на каждой из частей дорожки
     */
    static constexpr double COIN_SPAWN_CHANCE{ 0.05 };

    /**
     * Шанс того, что машины на дорожке будут двигаться слева направо
     */
    static constexpr double CAR_LEFT_TO_RIGHT_CHANCE{0.5};

    /**
     * Время в миллисекундах, на которое приостанавливается выполнение функции, обрабатывающей игровую логику
     */
    static constexpr int GAME_THREAD_SLEEP_MS{ 50 };
};

#endif