#include "Player.h"
#include <algorithm>

Player::Player(double x, double y)
    : GameObject{ x, y, 30, 50 } {}

/**
 * Прыжок
 */
void Player::jump() {
    if (!m_isJumping) {
        m_velocityY = -13.8;
        m_isJumping = true;
    }
}

void Player::accelerateLeft(bool isRunning) {
    double maxSpeed = isRunning ? 11.0 : 6.5;
    double accel = isRunning ? 2.2 : 1.6;
    m_velocityX -= accel;
    if (m_velocityX < -maxSpeed) m_velocityX = -maxSpeed;
}

void Player::accelerateRight(bool isRunning) {
    double maxSpeed = isRunning ? 11.0 : 6.5;
    double accel = isRunning ? 2.2 : 1.6;
    m_velocityX += accel;
    if (m_velocityX > maxSpeed) m_velocityX = maxSpeed;
}

void Player::applyFriction() {
    if (std::abs(m_velocityX) < 0.4) {
        m_velocityX = 0;
    } else {
        m_velocityX *= 0.78;
    }
}



void Player::respawn() {
    setPosition(100, 300);
    m_velocityX = 0;
    m_velocityY = 0;
    m_isJumping = false;
    setInvulnerable(true, 3.0f);
}

void Player::setInvulnerable(bool invuln, float duration) {
    m_isInvulnerable = invuln;
    m_invulnerabilityTimer = invuln ? duration : 0.0f;
}

void Player::update() {
    if (m_isInvulnerable) {
        m_invulnerabilityTimer -= 1.0f / 60.0f;
        if (m_invulnerabilityTimer <= 0.0f) {
            setInvulnerable(false);
        }
    }

    m_velocityY += m_gravity;
    setPosition(getX() + m_velocityX, getY() + m_velocityY);

    if (m_velocityY > 15) m_velocityY = 15;

    if (getY() > 700) {
        takeDamage();
    }
}

void Player::reset() {
    setPosition(100, 300);
    m_velocityX = 0;
    m_velocityY = 0;
    m_isJumping = false;
    m_lives = 5;        // 5 жизней
    m_coins = 0;
    setInvulnerable(true, 3.0f);
    setActive(true);
}

void Player::takeDamage() {
    if (m_isInvulnerable) return;

    m_lives--;
    setInvulnerable(true, 3.0f);

    if (m_lives > 0) {
        respawn();           // Возрождение
    } else {
        setActive(false);    // Последняя смерть
    }
}

int Player::getLives() const { return m_lives; }
int Player::getCoins() const { return m_coins; }
void Player::addCoin() { m_coins++; }
bool Player::getIsInvulnerable() const { return m_isInvulnerable; }
double Player::getVelocityY() const { return m_velocityY; }
double Player::getVelocityX() const { return m_velocityX; }
void Player::setLives(int lives) { m_lives = lives; }
void Player::stopJump() {
    if (m_velocityY < 0) m_velocityY = 0;
    m_isJumping = false;
}