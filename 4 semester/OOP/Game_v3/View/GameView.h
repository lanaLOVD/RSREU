#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <FL/Fl_Widget.H>
#include <FL/Fl.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>

#include <string>
#include <functional>
#include <memory>

#include "../Model/Game.h"
#include "../Model/GameConstants.h"

/**
 * Отображение окна игры
 */
class GameView : public Fl_Double_Window
{
private:
    /**
     * Ссылка на объект, содержащий игровую логику
     */
    Game& m_rGame;

    /**
     * Время в секундах, через которое повторяется обратный вызов таймера
     */
    double m_timeout;

    /**
     * Флаг, указывающий, задан ли интервал повторения обратного вызова
     */
    bool m_hasTimeout;

    /**
     * Функция обратного вызова для выхода в меню
     */
    std::function<void()> m_exitCallback;

    /**
     * Функция обратного вызова для движения игрока влево
     */
    std::function<void()> m_keysMoveLeftCallback;

    /**
     * Функция обратного вызова для движения игрока вправо
     */
    std::function<void()> m_keysMoveRightCallback;

    /**
     * Функция обратного вызова для движения игрока вперёд
     */
    std::function<void()> m_keysMoveForwardCallback;

    /**
     * Указатель на изображение игрового персонажа
     */
    std::unique_ptr<Fl_PNG_Image> m_imgChicken;

    /**
     * Указатель на изображение зелёной машины
     */
    std::unique_ptr<Fl_PNG_Image> m_imgGreenCar;

    /**
     * Указатель на изображение оранжевой машины
     */
    std::unique_ptr<Fl_PNG_Image> m_imgOrangeCar;

    /**
     * Указатель на изображение монеты
     */
    std::unique_ptr<Fl_PNG_Image> m_imgCoin;

    /**
     * Указатель на изображение дорожки с проезжей частью
     */
    std::unique_ptr<Fl_PNG_Image> m_imgRoad;

    /**
     * Указатель на изображение дорожки с обочиной
     */
    std::unique_ptr<Fl_PNG_Image> m_imgRoadside;

    /**
     * Указатель на отмасштабированное  изображение игрового персонажа
     */
    std::unique_ptr<Fl_PNG_Image> m_scaledImageChicken;

    /**
     * Указатель на отмасштабированное изображение зелёной машины
     */
    std::unique_ptr<Fl_PNG_Image> m_scaledImageGreenCar;

    /**
     * Указатель на отмасштабированное изображение оранжевой машины
     */
    std::unique_ptr<Fl_PNG_Image> m_scaledImageOrangeCar;

    /**
     * Указатель на отмасштабированное изображение монеты
     */
    std::unique_ptr<Fl_PNG_Image> m_scaledImageCoin;

    /**
     * Указатель на отмасштабированное изображение дорожки с проезжей частью
     */
    std::unique_ptr<Fl_PNG_Image> m_scaledImageRoad;

    /**
     * Указатель на отмасштабированное изображение дорожки с обочиной
     */
    std::unique_ptr<Fl_PNG_Image> m_scaledImageRoadside;

    /**
     * Заголовок окна
     */
    static const std::string WINDOW_NAME;

    /**
     * Путь к изображению игрового персонажа
     */
    static const std::string IMG_PATH_CHICKEN;

    /**
     * Путь к изображению зелёной машины
     */
    static const std::string IMG_PATH_GREEN_CAR;

    /**
     * Путь к изображению оранжевой машины
     */
    static const std::string IMG_PATH_ORANGE_CAR;

    /**
     * Путь к изображению монеты
     */
    static const std::string IMG_PATH_COIN;

    /**
     * Путь к изображению дорожки с проезжей частью
     */
    static const std::string IMG_PATH_ROAD;

    /**
     * Путь к изображению дорожки с обочиной
     */
    static const std::string IMG_PATH_ROADSIDE;

    /**
     * Текст интерфейса, используемый для отображения счёта игрока
     */
    static const std::string TEXT_HUD_SCORE;

    /**
     * Текст, выводимый при поражении
     */
    static const std::string TEXT_GAME_OVER;

    /**
     * Текст-подсказка, с описанием действий для выхода в меню
     */
    static const std::string TEXT_HUD_ESCAPE;

    /**
     * Минимальная ширина текстуры объекта
     */
    static const int MINIMAL_OBJECT_LENGTH{ 4 };

    /**
     * Размер шрифта текста, отображающего счёт
     */
    static const int HUD_FONT_SIZE_SCORE{ 22 };

    /**
     * Размер шрифта текста-подсказки
     */
    static const int HUD_FONT_SIZE_ESCAPE{ 14 };

    /**
     * Размер шрифта текста, выводимого при поражении
     */
    static const int HUD_FONT_SIZE_GAME_OVER{ 36 };

    /**
     * Горизонтальный отступ для надписи со счётом
     */
    static const int HUD_LABEL_SCORE_X_IDENT{ 10 };

    /**
     * Вертикальный отступ для надписи со счётом
     */
    static const int HUD_LABEL_SCORE_Y_IDENT{ 30 };

    /**
     * Горизонтальный отступ для текста-подсказки
     */
    static const int HUD_LABEL_ESCAPE_X_IDENT{ 10 };

    /**
     * Вертикальный отступ для текста-подсказки
     */
    static const int HUD_LABEL_ESCAPE_Y_IDENT{ 10 };

    /**
     * Горизонтальный отступ для текста, выводимого при поражении
     */
    static const int HUD_GAME_OVER_X_IDENT{ 20 };

    /**
     * Горизонтальный отступ для надписи со счётом при поражении
     */
    static const int HUD_GAME_OVER_SCORE_X_IDENT{ 60 };

    /**
     * Вертикальный отступ для надписи со счётом при поражении
     */
    static const int HUD_GAME_OVER_SCORE_Y_IDENT{ 30 };

    /**
     * Красная компонента цвета фона
     */
    static const int BACKGROUD_COLOR_RED{ 50 };

    /**
     * Зеленая компонента цвета фона
     */
    static const int BACKGROUD_COLOR_GREEN{ 50 };

    /**
     * Синяя компонента цвета фона
     */
    static const int BACKGROUD_COLOR_BLUE{ 50 };

    /**
     * Красная компонента цвета проезжей части, если не удалось загрузить текстуру
     */    
    static const int LANE_ROAD_NO_TEXTURE_BACKGROUND_RED{ 80 };

    /**
     * Зеленая компонента цвета проезжей части, если не удалось загрузить текстуру
     */    
    static const int LANE_ROAD_NO_TEXTURE_BACKGROUND_GREEN{ 80 };

    /**
     * Синяя компонента цвета проезжей части, если не удалось загрузить текстуру
     */    
    static const int LANE_ROAD_NO_TEXTURE_BACKGROUND_BLUE{ 80 };

    /**
     * Красная компонента цвета обочины, если не удалось загрузить текстуру
     */   
    static const int LANE_ROADSIDE_NO_TEXTURE_BACKGROUND_RED{ 34 };

    /**
     * Зеленая компонента цвета обочины, если не удалось загрузить текстуру
     */    
    static const int LANE_ROADSIDE_NO_TEXTURE_BACKGROUND_GREEN{ 120 };

    /**
     * Синяя компонента цвета обочины, если не удалось загрузить текстуру
     */    
    static const int LANE_ROADSIDE_NO_TEXTURE_BACKGROUND_BLUE{ 15 };

    /**
     * Красная компонента границы между дорожками
     */
    static const int LANE_BORDER_RED{ 60 };

    /**
     * Зеленая компонента границы между дорожками
     */
    static const int LANE_BORDER_GREEN{ 60 };

    /**
     * Синяя компонента границы между дорожками
     */
    static const int LANE_BORDER_BLUE{ 60 };

    /**
     * Размер дуги для рисования круга
     */
    static const int CIRCLE_NO_TEXTURE_ARC_DEGREES{ 360 };

    /**
     * Обратный вызов таймера
     */
    static void timerCallback(void* data);

    /**
     * Рисование фона
     */
    void drawBackground() const;

    /**
     * Рисование дорожек
     */
    void drawLanes() const;

    /**
     * Рисование машин
     */
    void drawVehicles() const;

    /**
     * Рисование монет
     */
    void drawCoins() const;

    /**
     * Рисование игрового персонажа
     */
    void drawPlayer() const;

    /**
     * Рисование интерфейса
    */
    void drawHUD() const;

    /**
     * Вывод надписи при поражении
     */
    void drawGameOver() const;

    /**
     * Загрузка изображения из файла
     * const std::string& rPath - путь к файлу
     * Возвращает указатель на загруженное изображение при успехе, nullptr - при неудаче
     */
    std::unique_ptr<Fl_PNG_Image> loadImage(const std::string& rPath);

    /**
     * Масштабирование изображения
     * Fl_PNG_Image& rImage - ссылка на избражение
     * int width - новая ширина изображения
     * int height - новая высота изображения
     * Возвращает указатель на отмасштабированное изображение
     */
    std::unique_ptr<Fl_PNG_Image> scaleImage(Fl_PNG_Image& rImage, int width, int height);

    /**
     * Вычисление экранной координаты левой стороны игрового объекта
     * double gameX - относительная координата объекта
     * Возвращает экранную координату
     */
    int calculateGameObjectXtoScreen(double gameX) const;

    /**
     * Вычисление экранной координаты верхней части дорожки
     * int laneIndex - индекс дорожки
     * Возвращает экранную координату
     */
    int calculateLaneYtoScreen(int laneIndex) const;

    /**
     * Вычисление высоты объекта в пикселях
     * Возвращает высоту объекта
     */
    int calculateGameObjectHeightPx() const;

    /**
     * Вычисление ширины объекта в пикселях
     * double width - относительная ширина объекта
     * Возвращает ширину объекта в пикселях
     */
    int calculateGameObjectWidthPx(double width) const;

    /**
     * Клавиша для движения вперед
     */
    static const int KEY_W_BIG{ 'W' };

    /**
     * Клавиша для движения вперед
     */
    static const int KEY_W_SMALL{ 'w' };

    /**
     * Клавиша для движения вправо
     */
    static const int KEY_D_BIG{ 'D' };

    /**
     * Клавиша для движения вправо
     */
    static const int KEY_D_SMALL{ 'd' };

    /**
     * Клавиша для движения влево
     */
    static const int KEY_A_BIG{ 'A' };

    /**
     * Клавиша для движения влево
     */
    static const int KET_A_SMALL{'a'};

public:
    /**
     * Конструктор
     * int width - ширина в пикселях
     * int height - высота в пикселях
     */
    GameView(int width, int height);

    /**
     * Деструктор
     */
    ~GameView() override;

    /**
     * ОТображение окна
     */
    void show() override;

    /**
     * Рисование окна
     */
    void draw() override;

    /**
     * Обработка событий
     */
    int  handle(int event) override;

    /**
     * Запуск таймера
     */
    void startTimer();

    /**
     * Запуск таймера
     */
    void stopTimer();

    /**
     * Обновление окна
     */
    void refresh();

    /**
     * Установка обратного вызова для клавиш движения влево
     */
    void setMoveLeftCallback(std::function<void()> cb) { m_keysMoveLeftCallback = cb; };

    /**
     * Установка обратного вызова для клавиш движения вправо
     */
    void setMoveRightCallback(std::function<void()> cb) { m_keysMoveRightCallback = cb; };

    /**
     * Установка обратного вызова для клавиш движения вперед
     */
    void setMoveForwardCallback(std::function<void()> cb) { m_keysMoveForwardCallback = cb; };

    /**
     * Установка обратного вызова для выхода в меню
     */
    void setExitCallback(std::function<void()>   cb) { m_exitCallback = cb; }
};

#endif