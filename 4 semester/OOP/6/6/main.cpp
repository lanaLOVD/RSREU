#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <numeric>

class Movie
{
public:
    // Вложенное перечисление жанров
    enum class Genre { ACTION, COMEDY, DRAMA, HORROR, SCIFI };

private:
    static inline int s_counter{ 0 };   // счётчик созданных объектов

    int         m_id;
    std::string m_title;
    Genre       m_genre;
    int         m_durationMin;          // продолжительность в минутах

public:
    // Конструктор с параметрами
    Movie(const std::string& title, Genre genre, int durationMin)
        : m_id{ ++s_counter }
        , m_title{ title }
        , m_genre{ genre }
        , m_durationMin{ durationMin }
    {}

    // Конструктор по умолчанию (делегирующий)
    Movie()
        : Movie{ "Неизвестно", Genre::DRAMA, 0 }
    {}

    // Конструктор копирования (явный, с диагностикой)
    Movie(const Movie& other)
        : m_id{ other.m_id }
        , m_title{ other.m_title }
        , m_genre{ other.m_genre }
        , m_durationMin{ other.m_durationMin }
    {}

    ~Movie()
    {
        // деструктор (логирование закомментировано, чтобы не засорять вывод)
        // std::cout << "[~Movie] '" << m_title << "' уничтожен\n";
    }

    // Геттеры
    int                getID()          const { return m_id; }
    const std::string& getTitle()       const { return m_title; }
    Genre              getGenre()       const { return m_genre; }
    int                getDuration()    const { return m_durationMin; }

    // Статический метод — сколько фильмов создано
    static int getCount() { return s_counter; }

    // Вспомогательный: жанр в строку
    static std::string genreToString(Genre g)
    {
        switch (g)
        {
            case Genre::ACTION:  return "Боевик";
            case Genre::COMEDY:  return "Комедия";
            case Genre::DRAMA:   return "Драма";
            case Genre::HORROR:  return "Ужасы";
            case Genre::SCIFI:   return "Фантастика";
            default:             return "Другое";
        }
    }
};

class Session
{
private:
    static inline int s_counter{ 0 };

    int         m_id;
    Movie       m_movie;        // фильм (хранится по значению)
    std::string m_time;         // время начала, например "14:30"
    int         m_hall;         // номер зала

public:
    Session(const Movie& movie, const std::string& time, int hall)
        : m_id{ ++s_counter }
        , m_movie{ movie }
        , m_time{ time }
        , m_hall{ hall }
    {}

    // Геттеры
    int                getID()       const { return m_id; }
    const Movie&       getMovie()    const { return m_movie; }
    const std::string& getTime()     const { return m_time; }
    int                getHall()     const { return m_hall; }

    static int getCount() { return s_counter; }
};


class Ticket
{
private:
    static inline int s_counter{ 0 };

    int    m_id;
    int    m_sessionID;   // id сеанса (ссылка по id, чтобы не хранить копию Session)
    int    m_movieID;     // id фильма (для быстрого поиска)
    int    m_seat;        // номер места
    double m_price;

public:
    Ticket(const Session& session, int seat, double price)
        : m_id{ ++s_counter }
        , m_sessionID{ session.getID() }
        , m_movieID{ session.getMovie().getID() }
        , m_seat{ seat }
        , m_price{ price }
    {}

    // Геттеры
    int    getID()        const { return m_id; }
    int    getSessionID() const { return m_sessionID; }
    int    getMovieID()   const { return m_movieID; }
    int    getSeat()      const { return m_seat; }
    double getPrice()     const { return m_price; }

    static int getCount() { return s_counter; }
};

// Вспомогательные функции вывода

void printSeparator(int width = 60)
{
    std::cout << std::string(width, '-') << '\n';
}

void printHeader(const std::string& title)
{
    printSeparator();
    std::cout << "  " << title << '\n';
    printSeparator();
}

// Подсчёт выручки конкретного фильма по всем билетам
double calcRevenue(int movieID, const std::vector<Ticket>& tickets)
{
    double total{ 0.0 };
    for (const auto& t : tickets)
        if (t.getMovieID() == movieID)
            total += t.getPrice();
    return total;
}

// main
int main()
{
    // ---- 1. Создаём фильмы ----
    std::vector<Movie> movies
    {
        Movie{ "Интерстеллар",   Movie::Genre::SCIFI,   169 },
        Movie{ "Джокер",         Movie::Genre::DRAMA,   122 },
        Movie{ "Мстители",       Movie::Genre::ACTION,  181 },
        Movie{ "Оно",            Movie::Genre::HORROR,  135 },
        Movie{ "Побег из тюрьмы",Movie::Genre::DRAMA,   142 },
    };

    // ---- 2. Создаём сеансы ----
    std::vector<Session> sessions
    {
        Session{ movies[0], "10:00", 1 },
        Session{ movies[0], "14:30", 2 },
        Session{ movies[1], "12:00", 1 },
        Session{ movies[1], "17:00", 3 },
        Session{ movies[2], "11:00", 2 },
        Session{ movies[2], "15:30", 1 },
        Session{ movies[2], "20:00", 3 },
        Session{ movies[3], "21:00", 2 },
        Session{ movies[4], "13:00", 1 },
    };

    // ---- 3. Создаём билеты ----
    std::vector<Ticket> tickets
    {
        // Интерстеллар — сеанс 1 (id=1)
        Ticket{ sessions[0], 1,  450.0 },
        Ticket{ sessions[0], 2,  450.0 },
        Ticket{ sessions[0], 5,  500.0 },
        // Интерстеллар — сеанс 2 (id=2)
        Ticket{ sessions[1], 3,  400.0 },
        Ticket{ sessions[1], 7,  400.0 },

        // Джокер — сеанс 3 (id=3)
        Ticket{ sessions[2], 1,  350.0 },
        Ticket{ sessions[2], 2,  350.0 },
        Ticket{ sessions[2], 10, 350.0 },
        // Джокер — сеанс 4 (id=4)
        Ticket{ sessions[3], 4,  370.0 },

        // Мстители — сеанс 5 (id=5)
        Ticket{ sessions[4], 1,  600.0 },
        Ticket{ sessions[4], 2,  600.0 },
        Ticket{ sessions[4], 3,  600.0 },
        Ticket{ sessions[4], 8,  550.0 },
        // Мстители — сеанс 6 (id=6)
        Ticket{ sessions[5], 5,  580.0 },
        Ticket{ sessions[5], 6,  580.0 },
        // Мстители — сеанс 7 (id=7)
        Ticket{ sessions[6], 2,  620.0 },
        Ticket{ sessions[6], 9,  620.0 },
        Ticket{ sessions[6], 11, 600.0 },

        // Оно — сеанс 8 (id=8)
        Ticket{ sessions[7], 3,  300.0 },
        Ticket{ sessions[7], 4,  300.0 },

        // Побег из тюрьмы — сеанс 9 (id=9)
        Ticket{ sessions[8], 1,  280.0 },
        Ticket{ sessions[8], 2,  280.0 },
        Ticket{ sessions[8], 3,  280.0 },
    };

    // ---- 4. Вывод всех фильмов ----
    printHeader("Список фильмов");
    std::cout << std::left
              << std::setw(4)  << "ID"
              << std::setw(22) << "Название"
              << std::setw(14) << "Жанр"
              << std::setw(8)  << "Мин."
              << '\n';
    printSeparator();
    for (const auto& m : movies)
    {
        std::cout << std::left
                  << std::setw(4)  << m.getID()
                  << std::setw(22) << m.getTitle()
                  << std::setw(14) << Movie::genreToString(m.getGenre())
                  << std::setw(8)  << m.getDuration()
                  << '\n';
    }

    // ---- 5. Вывод сеансов ----
    printHeader("Список сеансов");
    std::cout << std::left
              << std::setw(5)  << "Сеанс"
              << std::setw(22) << "Фильм"
              << std::setw(8)  << "Время"
              << std::setw(6)  << "Зал"
              << '\n';
    printSeparator();
    for (const auto& s : sessions)
    {
        std::cout << std::left
                  << std::setw(5)  << s.getID()
                  << std::setw(22) << s.getMovie().getTitle()
                  << std::setw(8)  << s.getTime()
                  << std::setw(6)  << s.getHall()
                  << '\n';
    }

    // ---- 6. Подсчёт выручки по каждому фильму ----
    // Структура для хранения результата
    struct MovieRevenue
    {
        std::string title;
        int         movieID;
        double      revenue;
    };

    std::vector<MovieRevenue> revenues;
    revenues.reserve(movies.size());

    for (const auto& m : movies)
    {
        double rev{ calcRevenue(m.getID(), tickets) };
        revenues.push_back({ m.getTitle(), m.getID(), rev });
    }

    // ---- 7. Вычисление средней выручки ----
    double totalRevenue{ 0.0 };
    for (const auto& r : revenues)
        totalRevenue += r.revenue;

    double avgRevenue{ totalRevenue / static_cast<double>(revenues.size()) };

    // ---- 8. Вывод выручки по каждому фильму ----
    printHeader("Выручка по фильмам");
    std::cout << std::left
              << std::setw(22) << "Фильм"
              << std::right
              << std::setw(14) << "Выручка (руб.)"
              << '\n';
    printSeparator();
    for (const auto& r : revenues)
    {
        std::cout << std::left  << std::setw(22) << r.title
                  << std::right << std::setw(14)
                  << std::fixed << std::setprecision(2) << r.revenue
                  << '\n';
    }
    printSeparator();
    std::cout << std::left  << std::setw(22) << "Средняя выручка:"
              << std::right << std::setw(14)
              << std::fixed << std::setprecision(2) << avgRevenue
              << '\n';

    // ---- 9. Фильмы с выручкой выше средней ----
    printHeader("Фильмы с выручкой ВЫШЕ средней");
    std::cout << std::left
              << std::setw(22) << "Фильм"
              << std::right
              << std::setw(14) << "Выручка (руб.)"
              << '\n';
    printSeparator();

    bool anyFound{ false };
    for (const auto& r : revenues)
    {
        if (r.revenue > avgRevenue)
        {
            std::cout << std::left  << std::setw(22) << r.title
                      << std::right << std::setw(14)
                      << std::fixed << std::setprecision(2) << r.revenue
                      << '\n';
            anyFound = true;
        }
    }
    if (!anyFound)
        std::cout << "  (нет фильмов с выручкой выше средней)\n";

    // ---- 10. Статистика ----
    printHeader("Статистика объектов");
    std::cout << "Создано фильмов:  " << Movie::getCount()   << '\n';
    std::cout << "Создано сеансов:  " << Session::getCount() << '\n';
    std::cout << "Продано билетов:  " << Ticket::getCount()  << '\n';
    printSeparator();

    return 0;
}
