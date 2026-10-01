#include "GameView.h"

/**
 * @brief Таймер FLTK: перерисовывает окно каждые ~16 мс (60 FPS).
 */
void GameView::timerCallback(void* data) {
    GameView* view = static_cast<GameView*>(data);
    if (view) {
        view->redraw();
        Fl::repeat_timeout(1.0 / 60.0, timerCallback, data);
    }
}

int GameView::handle(int event) {
    switch (event) {
    case FL_KEYDOWN:
        if (m_keyDownCallback) {
            m_keyDownCallback(Fl::event_key());
        }
        return 1;
    case FL_KEYUP:
        if (m_keyUpCallback) {
            m_keyUpCallback(Fl::event_key());
        }
        return 1;
    case FL_FOCUS:
        return 1;
    default:
        return Fl_Double_Window::handle(event);
    }
}

void GameView::draw() {
    Fl_Double_Window::draw();

    drawBackground();

    try {
        m_model.withDataLock([this]() {
            drawPlatforms();
            drawCoins();
            drawEnemies();
            drawPlayer();
        });

        drawUI();
    } catch (const std::exception&) {}
}

void GameView::drawBackground() {
    for (int y = 0; y < h(); ++y) {
        double ratio = static_cast<double>(y) / h();
        int r = 100 + static_cast<int>(ratio * 80);
        int g = 180 + static_cast<int>(ratio * 60);
        int b = 255;
        fl_color(r, g, b);
        fl_line(0, y, w(), y);
    }
    drawClouds();
}

void GameView::drawClouds() {
    fl_color(255, 255, 255);
    double cameraOffset = m_model.getCameraX() * 0.3;

    drawCloud(200 - cameraOffset, 80, 60);
    drawCloud(500 - cameraOffset, 120, 80);
    drawCloud(800 - cameraOffset, 60, 70);
    drawCloud(1200 - cameraOffset, 100, 90);
}

void GameView::drawCloud(double x, double y, double size) {
    if (x + size >= 0 && x - size <= w()) {
        fl_color(255, 255, 255);
        fl_pie(x - size / 2,      y,              size * 0.6,  size * 0.4,  0, 360);
        fl_pie(x - size / 4,      y - size / 6,   size * 0.8,  size * 0.5,  0, 360);
        fl_pie(x + size / 4,      y - size / 8,   size * 0.7,  size * 0.45, 0, 360);
        fl_pie(x,                 y + size / 8,   size * 0.9,  size * 0.3,  0, 360);
    }
}

void GameView::drawPlatforms() {
    auto& platforms = m_model.getPlatforms();
    for (auto& platform : platforms) {
        if (platform && platform->getActive()) {
            double x = platform->getX() - m_model.getCameraX();
            if (x + platform->getWidth() >= 0 && x <= w()) {
                drawPlatform(x, platform->getY(), platform->getWidth(), platform->getHeight());
            }
        }
    }
}

void GameView::drawPlatform(double x, double y, double width, double height) {
    fl_color(139, 90, 43);
    fl_rectf(x, y, width, height);

    fl_color(34, 139, 34);
    fl_rectf(x, y-6, width, 8);

    fl_color(0, 100, 0);
    for (int i = 0; i < width; i += 12) {
        fl_line(x+i, y-6, x+i+4, y-2);
        fl_line(x+i+6, y-5, x+i+9, y-1);
    }

    fl_color(160, 82, 45);
    for (int i = 8; i < width-8; i += 28) {
        for (int j = 8; j < height-8; j += 18) {
            fl_rect(x+i, y+j, 18, 12);
        }
    }
}

void GameView::drawEnemies() {
    auto& enemies = m_model.getEnemies();
    for (auto& enemy : enemies) {
        if (enemy && enemy->getActive()) {
            double screenX = enemy->getX() - m_model.getCameraX();
            double screenY = enemy->getY();
            if (screenX + enemy->getWidth() >= -50 && screenX <= w() + 50) {
                drawEnemy(screenX, screenY, enemy->getWidth(), enemy->getHeight());
            }
        }
    }
}

void GameView::drawEnemy(double x, double y, double width, double height) {
    fl_color(139, 0, 0);
    fl_pie(x + 2, y + height*0.3, width-4, height*0.7, 0, 360);

    fl_color(100, 0, 0);
    fl_pie(x + width*0.1, y + 5, width*0.8, height*0.45, 0, 360);

    fl_color(255, 255, 100);
    fl_pie(x + width*0.25, y + height*0.22, width*0.22, height*0.22, 0, 360);
    fl_pie(x + width*0.53, y + height*0.22, width*0.22, height*0.22, 0, 360);

    fl_color(0, 0, 0);
    fl_pie(x + width*0.3, y + height*0.27, width*0.1, height*0.1, 0, 360);
    fl_pie(x + width*0.58, y + height*0.27, width*0.1, height*0.1, 0, 360);

    fl_color(0, 0, 0);
    fl_arc(x + width*0.35, y + height*0.55, width*0.3, height*0.15, 0, 180);
}

void GameView::drawCoins() {
    auto& coins = m_model.getCoins();
    static double coinRotation = 0;
    coinRotation += 3;

    for (auto& coin : coins) {
        if (coin && coin->getActive()) {
            double x = coin->getX() - m_model.getCameraX();
            if (x + coin->getWidth() >= 0 && x <= w()) {
                drawCoin(x, coin->getY(), coin->getWidth(), coin->getHeight(), coinRotation);
            }
        }
    }
}

void GameView::drawCoin(double x, double y, double width, double height, double rotation) {
    double cx = x + width / 2;
    double cy = y + height / 2;

    fl_color(255, 215, 0);
    fl_pie(x, y, width, height, 0, 360);

    fl_color(255, 235, 100);
    fl_pie(x + 4, y + 4, width - 8, height - 8, 0, 360);

    fl_color(255, 255, 255);
    fl_pie(cx - width*0.3, cy - height*0.3, width*0.4, height*0.4, 0, 360);

    fl_color(139, 69, 19);
    fl_font(FL_HELVETICA_BOLD, 12);
    fl_draw("$", cx - 5, cy + 5);
}

void GameView::drawPlayer() {
    try {
        Player* player = m_model.getPlayer();
        if (player && player->getActive()) {
            double x      = player->getX() - m_model.getCameraX();
            double y      = player->getY();
            double width  = player->getWidth();
            double height = player->getHeight();

            drawPlayerCharacter(x, y, width, height);
        }
    } catch (...) {}
}

void GameView::drawPlayerCharacter(double x, double y, double w, double h) {
    bool invuln = m_model.getPlayer()->getIsInvulnerable();
    static int frame = 0; frame++;

    if (invuln && (frame / 8) % 2 == 0) return;

    fl_color(200, 0, 0);
    fl_rectf(x + w*0.2, y + h*0.45, w*0.6, h*0.48);

    fl_color(255, 220, 177);
    fl_pie(x + w*0.25, y + h*0.1, w*0.5, h*0.4, 0, 360);

    fl_color(220, 0, 0);
    fl_pie(x + w*0.18, y, w*0.64, h*0.32, 0, 360);
    fl_rectf(x + w*0.15, y + h*0.15, w*0.7, h*0.1);

    fl_color(0,0,0);
    fl_pie(x + w*0.38, y + h*0.28, w*0.1, h*0.12, 0, 360);
    fl_pie(x + w*0.58, y + h*0.28, w*0.1, h*0.12, 0, 360);

    fl_color(100, 50, 20);
    fl_rectf(x + w*0.35, y + h*0.45, w*0.3, h*0.04);

    fl_color(30, 30, 30);
    fl_rectf(x + w*0.22, y + h*0.88, w*0.25, h*0.12);
    fl_rectf(x + w*0.55, y + h*0.88, w*0.25, h*0.12);
}

void GameView::drawUI() {
    try {
        m_model.withDataLock([this]() {
            Player* player = m_model.getPlayer();
            if (!player) return;

            fl_color(0, 0, 0);
            fl_rectf(10, 10, 300, 120);
            fl_color(255, 255, 255);
            fl_rect(10, 10, 300, 120);

            fl_font(FL_HELVETICA_BOLD, 18);
            fl_color(255, 255, 255);
            fl_draw("Coins:", 20, 35);

            fl_color(255, 215, 0);
            fl_pie(90, 20, 20, 20, 0, 360);

            fl_color(255, 255, 255);
            fl_draw(std::to_string(player->getCoins()).c_str(), 120, 35);
        });

        if (m_model.getGameOver()) {
            fl_font(FL_HELVETICA_BOLD, 32);
            fl_color(FL_RED);
            fl_draw("GAME OVER", w() / 2 - 80, h() / 2);
            fl_font(FL_HELVETICA, 16);
        }
    } catch (...) {}
}