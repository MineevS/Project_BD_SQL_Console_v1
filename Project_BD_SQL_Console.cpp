// Project_BD_SQL_Console.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string> // string, getline;

#include <sstream>
#include <algorithm>
#include <iterator>

#include <stdio.h>
#include <windows.h>

#include <fstream>

#include <clocale>

#include "SWITH_CASE_STR.h"

bool FLAG = false;

template<class Container>
void Split(const std::string str, Container& cont)
{
    std::istringstream iss(str);
    std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(cont));
}

bool ISALNUM(std::string str) {

    bool alph = false;
    bool num = false;

    for(char c: str) {

        isalpha(c) ? alph = true : (isdigit(c) ? num = true : num = false);
    }

    return (alph && num);
}

void Delete_(std::vector<std::string>& vector) {

    for (auto &con : vector) {

        if (con.find(';') != std::string::npos) {

            auto it = std::find(vector.begin(), vector.end(), con);

            if (it != vector.end()) {

                *it = con.erase(con.find(';'), 1);

                ///////////////////////////////////////////////////////////////////////

                HWND hWnd = GetConsoleWindow();
                RECT rc;
                GetClientRect(hWnd, &rc);
                int w = rc.right; // ширина рабочей области

                //std::cout << w << std::endl;
                int r = 0;

                
                while (w / 8 != r) {

                    std::cout << "\x1b[32m/\x1b[0m";
                    ++r;
                }
                std::cout << std::endl;
                r = 0;

                std::cout << "Был встречен символ \"" << "\x1b[0;35;40m;\x1b[0m" <<"\". " <<" Для дальнейшей работы:\n"
                             "- либо введите" << " \"" << "\x1b[0;36;40m\\n\x1b[0m" << "\"" <<" для обработки SQL - запроса и ожидания нового введения SQL-запроса.\n"
                             "- Либо продолжите вводить новый блок.\n"
                             "- либо нажмите " << "\x1b[0;33;40mENTER\x1b[0m" <<" или введите " << "\"" << "\x1b[0;36;40m\\q\x1b[0m" << "\"" << " или " << "\"" << "\x1b[0;36;40m\\quit\x1b[0m" << "\"" << " - для обработки введеного блока информации и завершения работы программы." << std::endl;

                while (w / 8 != r) {

                    std::cout << "\x1b[32m/\x1b[0m";
                    ++r;
                }
                std::cout << std::endl;
                r = 0;

                for (auto &con: vector) {
                
                    if ((con.find('=') != std::string::npos) && !(ISALNUM(con))) {
                    
                        auto it = std::find(vector.begin(), vector.end(), con);
                        vector.erase(it);
                    }
                    else if ((con.find('=') != std::string::npos) && (ISALNUM(con))) {
                    
                        std::string parsed;
                        std::stringstream input_stringstream(con);
                        int x = 0;

                        while (getline(input_stringstream, parsed, '='))
                        {
                            auto it = std::find(vector.begin(), vector.end(), con);

                            if (x == 0) {

                                *it = parsed;
                                ++x;
                            }
                            else {

                                vector.push_back(parsed);
                                ++x;
                            }
                        }
                    }

                }

                //////////////////////////////////////////////////////////////////////
            }

            Delete_(vector);
            
        }
        else if ((con.find('=') != std::string::npos) && (ISALNUM(con))) {

            std::string parsed;
            std::stringstream input_stringstream(con);
            int x = 0;

            while(getline(input_stringstream, parsed, '='))
            {
                auto it = std::find(vector.begin(), vector.end(), con);

                if (x == 0) {
                
                    *it = parsed;
                    ++x;
                }
                else {
                
                    vector.push_back(parsed);
                    ++x;
                }
            }

            x = 0;
        }
        else if (con.find(',') != std::string::npos) {

            con.erase(con.find(','), 1);

            //vector.push_back(",");
        }
        else {


        }

        
        
    }
}

void func(std::string str, std::vector<std::string>& vector) {

    //std::cout << str << std::endl;

    Split(str, vector);

    Delete_(vector); // Delete ";"

}

void ftr(int w) {

    int tq = 0;
    while (w / 39 != tq) {

        std::cout << "\x1b[32m \x1b[0m";
        ++tq;
    }

}


void HELP() {

    HWND hWnd = GetConsoleWindow();
    RECT rc;
    GetClientRect(hWnd, &rc);
    int w = rc.right; // ширина рабочей области

    //std::cout << w << std::endl;
    int r = 0;
    while (w / 22 != r) {
        std::cout << "\x1b[32m/\x1b[0m";
        ++r;
    }
    std::cout << "Справочная информация по данной программе";
    int t = 0;
    while (w / 22 != t) {

        std::cout << "\x1b[32m/\x1b[0m";
        ++t;
    } 
    
    std::cout << std::endl << std::endl << std::endl;
    
    ftr(w - 500);

    std::cout << "Программа содержит по умолчанию слудующие команды: " << std::endl << std::endl;

    
    ftr(w + 500);
    std::cout << "• " << "\x1b[32m\\help\x1b[0m" << "   - Вывод справочной информации. " << std::endl;
    ftr(w + 500);
    std::cout << "• " << "\x1b[32m\\cls\x1b[0m " << " или "<< "\x1b[32m\\clouse\x1b[0m   - Очистка экрана. " << std::endl;
    ftr(w + 500);
    std::cout << "• " << "\x1b[32m\\q\x1b[0m" << " или " << "\x1b[32m\\quit\x1b[0m  - Выход из программы. " << std::endl;
    ftr(w + 500);
    std::cout << "• " << "\x1b[32m\\n\x1b[0m " << " - Шаг выполнения SQL - запроса. " << std::endl;

    std::cout << std::endl;

    ftr(w - 940);
    std::cout << " Для получения более подробной информации, предлагаем вам посетить: ";
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10);
    std::cout << "https://github.com/MineevS/Project_BD_SQL_Console.git" << std::endl;
    SetConsoleTextAttribute(hConsole, 7);
    
    

    //std::cout << "Справочная информация по данной программе." << std::endl;

}

void write(std::vector<std::string>& vector) 
{
    std::string str;

    do {

        std::cout << "\x1b[31m>>>\x1b[0m ";
        
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        setlocale(LC_ALL, "RUSSIAN");

        getline(std::cin, str);

        if (( (str.find("\\q") != std::string::npos) | (str.find("\\quit") != std::string::npos) ) && (vector.size() == 0)) // Обработчик если в начале пользователь решил сразу завершить программу.
        {
            exit(0);
        }
        else if (str.find("\\n") != std::string::npos) {
        
            FLAG = true;
            return;
        }
        else if (str.empty() | (str.find("\\q") != std::string::npos) | (str.find("\\quit") != std::string::npos)) {
        
            FLAG = false;
            return;
        
        }
        else if ((str.find("\\cls") != std::string::npos) | (str.find("\\clouse") != std::string::npos)) {
        
            system("cls");
            //return;
        }
        else if ((str.find("\\help") != std::string::npos)) {
        
            HELP();
            //return;
        }

        func(str, vector);

    } while ( (!str.empty()) && (str.find("\\q") == std::string::npos) && (str.find("\\quit") == std::string::npos) && (str.find("\\n") == std::string::npos));

    if (str.find("\\n") == std::string::npos) {
    
        FLAG = true;
    }
}

//////////////////////////////////////////////////////////

std::vector<std::vector<std::string>> Write_File(std::string namefile) {

    //std::cout << namefile << std::endl;

    std::ifstream file(namefile);

    if (!file.is_open()) {
    
        // RU:
        std::cout << "Ошибка! : Файл ";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 10);
            std::cout << namefile;
            SetConsoleTextAttribute(hConsole, 7);
            std::cout << " не найден!" << std::endl;

        /*
        // EN:
        std::cout << "ERROR: file ";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 10);
            std::cout << namefile;
            SetConsoleTextAttribute(hConsole, 7);
            std::cout << " not find!" << std::endl;
        */
    }
    else if (file.eof()) {
    
        std::cout << "Ошибка! : Файл ";
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 10);
            std::cout << namefile;
            SetConsoleTextAttribute(hConsole, 7);
            std::cout << " пуст !" << std::endl;
    
    }
    else if (!file.eof()) {

        std::vector<std::vector<std::string>>  mas;

        while (!file.eof())
        {
            std::string temp, word;

            while (file >> temp)
            {
                if ((*(--temp.end()) != ';')) {

                    temp += ";";
                }

                std::stringstream s(temp);

                std::vector<std::string> line;

                while (!getline(s, word, ';').eof())
                {
                    line.push_back(word);
                }

                mas.push_back(line);
            }

            /*
            for (auto m1: mas) {

                for (auto m2: m1) {
                
                    std::cout << m2 << " ";
                }

                std::cout << std::endl;
            }
            */

            
        }

        return mas;
    
    }

    return std::vector<std::vector<std::string>>();
}

void Parsing(std::vector<std::vector<std::string>> file, std::vector<std::string>::iterator it_from, std::vector<std::string> vector) {

    /*
    for (auto m1 : file) {

        for (auto m2 : m1) {

            std::cout << m2 << "  ";
        }

        std::cout << std::endl;
    }
    */

    ///////////////////////////////////

    std::vector<std::string>::iterator it_start; // Указатель на результат вывода SQL Запроса.
    for (int i = 0; *(it_from - i) != "SELECT"; i++) 
    {
        it_start = (it_from - i);
    }

    if (*(--it_start) == "SELECT") {

        int j = 1;

        while (*(it_from + j) != *(--(vector.end())) && *(it_from + j) != "SELECT" && *(it_from + j) != "WHERE") {
        
            j++;
        }

        if (*(it_from + j) == "WHERE") {

            std::vector<std::string>::iterator it_WHERE; // Указатель на условия запроса.
            for (int i = 0; *(it_from + i) != "WHERE"; i++) {
                it_WHERE = ++(it_from + i);
            }

            std::vector<std::string>::iterator it_sinc;

            it_sinc = ++it_WHERE;

            if (*it_sinc == "") {
            
                return;
            }
            else {
                
                // Проверяем записи на условия и выводим те записи,которые удовлетворяют всем условиям запроса.
                auto fiS = file[0]; // Получаем заголовок таблицы;
                int id_column = 0;
                std::vector<std::vector<std::string>>  mas_temp;

                std::vector<std::string>::iterator it_sinc_znach;

                for (auto fis: fiS) {
                
                    if (fis == *it_sinc) {
                    
                        it_sinc_znach = ++it_sinc;

                        // Проходяим по записым и выбираем те, которые содержат данное значение(it_sinc_znach).

                        for (auto fil: file) {
                        
                            if (fil[id_column] == *it_sinc_znach) {
                            
                                mas_temp.push_back(fil);
                            }
                        }
                    }

                    ++id_column;
                }

                if (*(it_sinc_znach) == *(--vector.end())) {
                
                    // Не каких условий больше нет.
                    int r = 0;
                    int w = 0;
                    
                    while ((it_start + r) != it_from) {
                    
                        int d = 0;

                        for (auto fis : fiS) {

                            if (fis == *(it_start + r)) {

                                for (auto mas_t: mas_temp) {
                                
                                    if (w != 0) {

                                        std::cout << ", ";
                                    }
                                    else {
                                    
                                        ++w;
                                    }

                                    std::cout << mas_t[d];

                                } 

                                //std::cout << ", ";
                            }
                            else if (*(it_start + r) == "*") {
                            
                                for (auto mas_t : mas_temp) {

                                    for (auto mas: mas_t) {
                                    
                                        if (w != 0) {

                                            std::cout << ", ";
                                        }
                                        else {

                                            ++w;
                                        }

                                        std::cout << mas;
                                    
                                    }
                                    

                                }

                                std::cout << std::endl;
                                return;
                            
                            }
                          
                            ++d;  
                        }

                        ++r;
                    }

                    std::cout << std::endl;
                }
            }
        }
        else if ( *(it_from + j) == *(--(vector.end())) ) {
        
            int f = 0;

            while ((it_start + f) != it_from) {

                SWITCH(*(it_start + f)) {

                    CASE("*") :

                        for (auto m1 : file) {

                            for (auto m2 : m1) {

                                std::cout << m2 << "  ";
                            }

                            std::cout << std::endl;
                        }

                    break;
                    CASE("") :

                        break;
                default:

                    // Остальные случаи:

                    auto fiS = file[0]; // Получаем заголовок таблицы;
                    int id_col = 0;

                    for (auto fis : fiS) {

                        if (fis == *(it_start + f)) {

                            // Проходяим по записым.

                            for (auto fil : file) {

                                std::cout << fil[id_col] << std::endl;
                                
                            }
                        }

                        ++id_col;
                    }
                    

                    break;
                }

                ++f;
            }
        }
        else if (*(it_from + j) == "SELECT") {
        
        
        }

        ////////////////////////////////// 
    }
}

void Processing(std::vector<std::string>& vector) 
{
    for (auto v : vector) {

        //std::cout << ":" << v << ":" << std::endl;

        SWITCH (v) {

            CASE("FROM") :{

                           std::vector<std::vector<std::string>>  mas = Write_File(*(++(std::find(vector.begin(), vector.end(), v))));

                           /*
                           for (auto m1 : mas) {

                               for (auto m2 : m1) {

                                   std::cout << m2 << "  ";
                               }

                               std::cout << std::endl;
                           }
                           */

                           Parsing( mas, (std::find(vector.begin(), vector.end(), v)) , vector);
                           
                           //Write_File(*(++(std::find(vector.begin(), vector.end(), v))));
                }
                break;
            CASE(" ") :

                break;
            default:
                break;
        }
    }
}

int main(int argc, char argv)
{
    setlocale(LC_ALL, "RUSSIAN");

    std::vector<std::string> vector;

    /////////////////////////////////////////////////

    do {

        write(vector); // Записываем блоки SQL по словам в массив.

        /*
        for (auto v : vector) {

            std::cout << ":" << v << ":" << std::endl;
        }
        */

        Processing(vector); // Обработка  SQL - запроса.

        //////////////////////

            vector.clear();

        /////////////////////
    
    } while(FLAG);
    
    ////////////////////////////////////////////////

    system("pause");
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
