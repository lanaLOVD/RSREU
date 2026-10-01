#pragma once
#include "GameObject.h"

/**
 * @brief Класс игрока.
 */
class Player : public GameObject {
private:
    double m_velocityX = 0;
    double m_velocityY = 0;
    double m_gravity = 0.5;
    bool m_isJumping = true;
    int m_lives = 3;
    int m_coins = 0;
    bool m_isInvulnerable = false;
    float m_invulnerabilityTimer = 0.0f;

public:
    Player(double x, double y);

    void jump();
    void accelerateLeft(bool isRunning);
    void accelerateRight(bool isRunning);
    void applyFriction();

    void takeDamage();
    void respawn();
    void setLives(int lives);
    void stopJump();
    void update() override;
    void reset();

    int getLives() const;
    int getCoins() const;
    void addCoin();
    bool getIsInvulnerable() const;
    void setInvulnerable(bool invuln, float duration = 3.0f);
    double getVelocityY() const;
    double getVelocityX() const;
};