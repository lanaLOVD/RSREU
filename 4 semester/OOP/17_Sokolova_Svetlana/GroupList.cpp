#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <io.h>


#if defined(__APPLE__) || defined(__MACH__)
    #define MACOS
#elif defined(_WIN32) || defined(_WIN64)
    #define WINDOWS
#endif


using namespace std;

struct People
{
    int id {};
    wstring name;
    int height;
};


People createTeacherInfo()
{
    People teacher;

    teacher.id = 0;
    teacher.name = L"Столчнев Вячеслав";
    teacher.height = 184;

    return teacher;
}
People create01Vavilova()
{
    People student;

    student.id = 1;
    student.name = L"Вавилова Полина";
    student.height = 170;

    return student;
}
// <<< Вместо данного комментария необходимо добавить функции создания структур с информацией о студенте
People create03Gricuta()
{
People student;
student.id = 3;
student.name = L"Грицюта Александра";
student.height = 151;
return student;
}
People create04DanshovInfo()
{
    People student;

    student.id = 04;
    student.name = L"Даньшов Никита";
    student.height = 178;

    return student;
}

People create06Ivanova()
{
    People student;

    student.id = 6;
    student.name = L"Иванова Татьяна";
    student.height = 160;

    return student;
}

People create07MarfinInfo()
{
    People student;

    student.id = 7;
    student.name = L"Марфин Дмитрий";
    student.height = 181;

    return student;
}

People create08MaslovInfo()
{
    People student;

    student.id = 8;
    student.name = L"Maslov Paul";
    student.height = 181;

    return student;
}

People create09Mikhailov()
{
    People student;

    student.id = 9;
    student.name = L"Михайлов Иван";
    student.height = 173;

    return student;
}
People create010NikolaevInfo()
{
    People student;

    student.id = 10;
    student.name = L"Nikolaev_Egor";
    student.height = 167;

    return student;
}

People create12PovarovInfo()
{
    People student;

    student.id = 12;
    student.name = L"Поваров Владимир";
    student.height = 178;

    return student;
}

People create13PopovInfo()
{
    People student;

    student.id = 13;
    student.name = L"Попов Алексей";
    student.height = 180;

    return student;
}
People create14SamogaevInfo()
{
    People student;

    student.id = 14;
    student.name = L"Алексей";
    student.height = 180;

    return student;
}

People create15SergachevInfo()
{
    People student;

    student.id = 15;
    student.name = L"Сергачев Семён";
    student.height = 176;

    return student;
}


People create17SokolovaInfo()
{
    People student;

    student.id = 17;
    student.name = L"Соколова Светлана";
    student.height = 165;

    return student;
}

People create18SoldatovaInfo()
{
    People student;

    student.id = 18;
    student.name = L"Солдатова Злата";
    student.height = 157;

    return student;
}

People create20TokarevInfo()
{
    People student;

    student.id = 20;
    student.name = L"Максим";
    student.height = 176;

    return student;
}

People create21ShevtsovInfo()
{
    People student;
    student.id = 21;
    student.name = L"Шевцов Михаил";
    student.height = 185;

    return student;
}

People create22YakovlevInfo()
{
    People student;

    student.id = 22;
    student.name = L"Евгений";
    student.height = 177;

    return student;
}


#ifdef WINDOWS
void showPeoples(const vector<People>& listOfPeoples)
{
    const int columnNumLength = 4;
    const int columnNameLenght = 50;
    const int columnHeightLength = 5;

    wstringstream buffer;
    buffer << L"+=====+" << setw(columnNameLenght + 2) << setfill(L'=') << L"+" << setw(columnHeightLength + 2) << L"+";
    wstring headerLine = buffer.str();
    buffer.str(L"");

    buffer << L"+-----+" << setw(columnNameLenght + 2) << setfill(L'-') << L"+" << setw(columnHeightLength + 2) << L"+";
    wstring line = buffer.str();
    buffer.str(L"");

    wstring nameTitle = L"ФИО";
    buffer << L"|" << L"  №  " << L"| " << nameTitle << setw(columnNameLenght - nameTitle.length()) << setfill(L' ') << L" " << L"|" << setw(columnHeightLength) << L" Рост " << L"|";
    wstring title = buffer.str();
    buffer.str(L"");

    wcout << headerLine << endl;
    wcout << title << endl;
    wcout << headerLine << endl;

    for(const auto& p: listOfPeoples)
    {
        buffer << L"|" << setw(columnNumLength) << p.id << L" | " << p.name << setw(columnNameLenght - p.name.length()) << setfill(L' ') << L" " << L"|" << setw(columnHeightLength) << p.height << L" |";
        wcout << buffer.str() << endl;
        buffer.str(L"");
        wcout << line << endl;
    }
}
#endif

// Функция для macOS (использует обычный cout с преобразованием в UTF-8)
#ifdef MACOS
#include <codecvt>
#include <locale>

// Вспомогательная функция для конвертации wstring в UTF-8 строку
string wstringToUTF8(const wstring& wstr)
{
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

void showPeoples(const vector<People>& listOfPeoples)
{
    const int columnNumLength = 4;
    const int columnNameLenght = 50;
    const int columnHeightLength = 5;

    stringstream buffer;

    // Создаем заголовок таблицы
    buffer << "+=====+" << setw(columnNameLenght + 2) << setfill('=') << "+" << setw(columnHeightLength + 2) << "+";
    string headerLine = buffer.str();
    buffer.str("");

    buffer << "+-----+" << setw(columnNameLenght + 2) << setfill('-') << "+" << setw(columnHeightLength + 2) << "+";
    string line = buffer.str();
    buffer.str("");

    string nameTitle = wstringToUTF8(L"ФИО");
    buffer << "|" << "  №  " << "| " << nameTitle << setw(columnNameLenght - nameTitle.length() + 3) << setfill(' ') << " " << "|" << setw(columnHeightLength) << " Рост " << "|";
    string title = buffer.str();
    buffer.str("");

    cout << headerLine << endl;
    cout << title << endl;
    cout << headerLine << endl;

    for(const auto& p: listOfPeoples)
    {
        string utf8Name = wstringToUTF8(p.name);
        buffer << "|" << setw(columnNumLength) << p.id << " | " << utf8Name
               << setw(columnNameLenght - p.name.length()) << setfill(' ') << " "
               << "|" << setw(columnHeightLength) << p.height << " |";
        cout << buffer.str() << endl;
        buffer.str("");
        cout << line << endl;
    }
}
#endif

int main()
{
    #ifdef WINDOWS
    _setmode(_fileno(stdout), _O_U8TEXT);
    #endif
    vector<People> listOfPeoples;

    listOfPeoples.push_back(createTeacherInfo());
    // <<< Вместо данного комментария добавить вызов функций создания структур с информацией о студентах
    // (необходимо соблюдать порядок по возрастанию идентификаторов - порядоковому номеру в журнале)
    // listOfPeoples.push_back(ваша функция);
    listOfPeoples.push_back(create01Vavilova());
    listOfPeoples.push_back(create03Gricuta());
    listOfPeoples.push_back(create04DanshovInfo());
    listOfPeoples.push_back(create06Ivanova());
    listOfPeoples.push_back(create07MarfinInfo());
    listOfPeoples.push_back(create08MaslovInfo());
    listOfPeoples.push_back(create09Mikhailov());
    listOfPeoples.push_back(create010NikolaevInfo());
    listOfPeoples.push_back(create12PovarovInfo());
    listOfPeoples.push_back(create13PopovInfo());
    listOfPeoples.push_back(create14SamogaevInfo());
    listOfPeoples.push_back(create15SergachevInfo());
    listOfPeoples.push_back(create18SoldatovaInfo());
    listOfPeoples.push_back(create20TokarevInfo());
    listOfPeoples.push_back(create21ShevtsovInfo());
    listOfPeoples.push_back(create22YakovlevInfo());
    showPeoples(listOfPeoples);
}