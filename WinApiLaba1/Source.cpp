#include <Windows.h>
#include <math.h>
#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <iostream>
#include <Windows.h>
#include <map>
#include <sstream>
#include <locale>
#include <codecvt>
#include <algorithm>


//define
//Кнопки
#define ID_BUTTON1 1001 
#define ID_BUTTON2 1002
#define ID_BUTTON3 1009
#define ID_BUTTON4 1010
#define ID_BUTTON5 1011
#define ID_BUTTON6 1013
#define ID_BUTTON7 1014

//Текстовые поля
#define ID_TEXTBOX1 1005
#define ID_TEXTBOX2 1006
#define ID_TEXTBOX3 1008
#define ID_TEXTBOX4 1012

//Комбобокс
#define ID_COMBOBOX1 1004


//Глобальные переменные
HANDLE fileHandle;
LPWSTR wszFileName;
std::string fileContent;
BOOLEAN flagWord = false;
std::map<std::string, int> wordCount;
std::map<std::string, int> wordCountSearch; 
std::map<char, int> ;

int PNum;

int step;

std::vector<std::pair<std::string, int>> vec;
std::vector<std::pair<char, int>> vecC;

std::map<char, int> charCount;
std::map<char, int> punctCount;
int inf[5];

double MathExpectation;
double Dispersion;
double StandardDeviation;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MyWindowClass";
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        L"MyWindowClass",
        L"Mathematics",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1000,
        300,
        NULL,
        NULL,
        hInstance,
        NULL);

    //Создание блоков окна
    //Buttons
    HWND hwndButton1 = CreateWindow(
        L"BUTTON",
        L"Open file",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10,
        10,
        100,
        30,
        hwnd,
        (HMENU)ID_BUTTON1,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    HWND hwndButton2 = CreateWindow(
        L"BUTTON",
        L"Action",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        120,
        10,
        100,
        30,
        hwnd,
        (HMENU)ID_BUTTON2,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    HWND hwndButton3 = CreateWindow(
        L"BUTTON",
        L"Search",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        120,
        80,
        100,
        30,
        hwnd,
        (HMENU)ID_BUTTON3,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    HWND hwndButton4 = CreateWindow(
        L"BUTTON",
        L"<",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        680,
        235,
        20,
        20,
        hwnd,
        (HMENU)ID_BUTTON4,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    HWND hwndButton5 = CreateWindow(
        L"BUTTON",
        L">",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        780,
        235,
        20,
        20,
        hwnd,
        (HMENU)ID_BUTTON5,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);


    HWND hwndButton6 = CreateWindow(
        L"BUTTON",
        L"Search page",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        490,
        235,
        100,
        20,
        hwnd,
        (HMENU)ID_BUTTON6,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    HWND hwndButton7 = CreateWindow(
        L"BUTTON",
        L"Data graph",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        120,
        120,
        100,
        30,
        hwnd,
        (HMENU)ID_BUTTON7,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    //ComboBox
    HWND hwndComboBox = CreateWindow(
        L"COMBOBOX",
        NULL,
        CBS_DROPDOWNLIST | WS_VISIBLE | WS_CHILD,
        10,
        50,
        100,
        200,
        hwnd,
        (HMENU)ID_COMBOBOX1,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    //TextBox
    HWND textBox1 = CreateWindow(
        L"EDIT",
        L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE,
        5,
        235,
        475,
        20,
        hwnd,
        (HMENU)ID_TEXTBOX1,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    HWND textBox2 = CreateWindow(
        L"EDIT",
        L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | WS_VSCROLL,
        240,
        10,
        240,
        215,
        hwnd,
        (HMENU)ID_TEXTBOX2,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    HWND textBox3 = CreateWindow(
        L"EDIT",
        L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE,
        120,
        50,
        100,
        20,
        hwnd,
        (HMENU)ID_TEXTBOX3,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    HWND textBox4 = CreateWindow(
        L"EDIT",
        L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE,
        710,
        235,
        60,
        20,
        hwnd,
        (HMENU)ID_TEXTBOX4,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    // Добавление вариантов в панель выбора
    SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)L"Words");
    SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)L"Chars");
    SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)L"Punctuation");
    SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)L"Get stats");

    // Отображение окна
    ShowWindow(hwnd, nCmdShow);

    //Отрисовка стартовых линий графика
    PAINTSTRUCT ps;
    RECT rect;
    HDC hdc = BeginPaint(hwnd, &ps);
    GetClientRect(hwnd, &rect);
    Rectangle(hdc, 490, 5, 970, 230);

    MoveToEx(hdc, 520, 20, NULL);  // Вертикаль
    LineTo(hdc, 520, 220);

    MoveToEx(hdc, 510, 210, NULL);  // Горизанталь
    LineTo(hdc, 950, 210);

    MoveToEx(hdc, 520, 10, NULL);  // Стрелка вертикали
    LineTo(hdc, 515, 20);
    LineTo(hdc, 525, 20);
    LineTo(hdc, 520, 10);

    MoveToEx(hdc, 960, 210, NULL);  // Стрелка горизантали
    LineTo(hdc, 950, 205);
    LineTo(hdc, 950, 215);
    LineTo(hdc, 960, 210);

    EndPaint(hwnd, &ps);
    
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

void information(HWND hwnd)
{
    const int bufferSize = 100000;
    char buffer[bufferSize];
    DWORD bytesRead = 0;

    while (ReadFile(fileHandle, buffer, bufferSize, &bytesRead, NULL) && bytesRead > 0) {
        fileContent.append(buffer, bytesRead);
    }

    inf[0] = 0;
    inf[1] = 0;
    inf[2] = 0;
    inf[3] = 0;
    inf[4] = 0;

    HWND hwndTextBox2 = GetDlgItem(hwnd, ID_TEXTBOX2);

    std::vector<std::string> words;
    wordCount.clear();
    charCount.clear();
    std::string word;
    std::istringstream iss(fileContent);
    std::string resultText;
    int size = 0;
    wchar_t* wstr;
    std::string ch;
    flagWord = false;

    while (iss >> word) {
        for (char& c : word) {
            if (!(c < 0) && !(c > 255)) {
                if (std::isalpha(c))
                {
                    inf[1]++;
                    c = tolower(c);
                    charCount[c]++;
                }
                else if (std::ispunct(c))
                {
                    inf[2]++;
                    punctCount[c]++;
                    c = ' ';
                }
                inf[3]++;
            }
        }
        word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char c) { return std::isspace(c); }), word.end());
        if (!word.empty()) {            
            wordCount[word]++;
        }
        inf[0]++;
    }
    inf[4] = wordCount.size();
 
    double Count = 0;
    for (const auto& pair : wordCount) {
        Count += pair.second;
    }
    MathExpectation = Count / wordCount.size();

    double CountD = 0;
    for (const auto& pair : wordCount) {
        CountD += (pair.second - MathExpectation) * (pair.second - MathExpectation);
    }
    Dispersion = CountD / wordCount.size();
    StandardDeviation = sqrt(Dispersion);

}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    //HWND блоки окна
   
    //Кнопки
    HWND hwndButton1 = GetDlgItem(hwnd, ID_BUTTON1);
    HWND hwndButton2 = GetDlgItem(hwnd, ID_BUTTON2);
    HWND hwndButton3 = GetDlgItem(hwnd, ID_BUTTON3);
    HWND hwndButton4 = GetDlgItem(hwnd, ID_BUTTON4);
    HWND hwndButton5 = GetDlgItem(hwnd, ID_BUTTON5);
    HWND hwndButton6 = GetDlgItem(hwnd, ID_BUTTON6);
    HWND hwndButton7 = GetDlgItem(hwnd, ID_BUTTON7);

    //Текстовые поля
    HWND hwndTextBox1 = GetDlgItem(hwnd, ID_TEXTBOX1);
    HWND hwndTextBox2 = GetDlgItem(hwnd, ID_TEXTBOX2);
    HWND hwndTextBox3 = GetDlgItem(hwnd, ID_TEXTBOX3);
    HWND hwndTextBox4 = GetDlgItem(hwnd, ID_TEXTBOX4);

    //КомбоБокс
    HWND hwndComboBox = GetDlgItem(hwnd, ID_COMBOBOX1);

    PAINTSTRUCT ps;
    HDC hdc;
    RECT rectangle;
    HBRUSH Brush;
    RECT outsideRect;
    switch (uMsg)
    {
    case WM_PAINT:
        //Paint
        hdc = BeginPaint(hwnd, &ps);
        rectangle = {900, 235, 945, 255};
        Brush = CreateSolidBrush(RGB(255, 255, 255)); 
        FillRect(hdc, &rectangle, Brush); 

        rectangle = { 900, 235, 985, 255 };
        FillRect(hdc, &rectangle, Brush);

        Rectangle(hdc, 490, 5, 970, 230);

        MoveToEx(hdc, 520, 20, NULL);  // Вертикаль
        LineTo(hdc, 520, 220);

        MoveToEx(hdc, 510, 210, NULL);  // Горизанталь
        LineTo(hdc, 950, 210);

        MoveToEx(hdc, 520, 10, NULL);  // Стрелка вертикали
        LineTo(hdc, 515, 20);
        LineTo(hdc, 525, 20);
        LineTo(hdc, 520, 10);

        MoveToEx(hdc, 960, 210, NULL);  // Стрелка горизантали
        LineTo(hdc, 950, 205);
        LineTo(hdc, 950, 215);
        LineTo(hdc, 960, 210);

        if (PNum == 1)
        {
            for (int i = 8 * step - 8, j = 0; i < vec.size() && i < step * 8; i++, j++)
            {
                double part = static_cast<double>(vec[i].second) / static_cast<double>(vec[0].second);
                int y = round(20 + (190 * (100 - (part) * 100)) / 100);
                rectangle = { 530 + j * 50,  y, 575 + j * 50, 210 };
                Brush = CreateSolidBrush(RGB(0, 0, 255));
                FillRect(hdc, &rectangle, Brush);
                SetBkMode(hdc, TRANSPARENT);

                outsideRect = { 530 + j * 50, 190, 575 + j * 50, 210 };
                std::wstring text = std::to_wstring(vec[i].second);
                DrawText(hdc, text.c_str(), -1, &outsideRect, DT_SINGLELINE | DT_CENTER | DT_BOTTOM);

                outsideRect = { 530 + j * 50, 210, 575 + j * 50, 230 };
                std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converterW;
                std::wstring wide = converterW.from_bytes(vec[i].first);
                DrawText(hdc, wide.c_str(), -1, &outsideRect, DT_SINGLELINE | DT_TOP);
            }
            outsideRect = {900, 235, 985, 255};
            int MaxP = round(vec.size() / 8 + 1);
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converterPage;
            std::wstring wideP = converterPage.from_bytes(std::to_string(step) + " / " + std::to_string(MaxP));
            DrawText(hdc, wideP.c_str(), -1, &outsideRect, DT_SINGLELINE | DT_CENTER | DT_TOP);
        }
        else if (PNum == 2)
        {
            for (int i = 8 * step - 8, j = 0; i < vecC.size() && i < step * 8; i++, j++)
            {
                double part = static_cast<double>(vecC[i].second) / static_cast<double>(vecC[0].second);
                int y = round(20 + (190 * (100 - (part) * 100)) / 100);
                rectangle = { 530 + j * 50,  y, 575 + j * 50, 210 };
                Brush = CreateSolidBrush(RGB(0, 0, 255));
                FillRect(hdc, &rectangle, Brush);
                SetBkMode(hdc, TRANSPARENT);

                outsideRect = { 530 + j * 50, 190, 575 + j * 50, 210 };
                std::wstring text = std::to_wstring(vecC[i].second);
                DrawText(hdc, text.c_str(), -1, &outsideRect, DT_SINGLELINE | DT_CENTER | DT_BOTTOM);

                outsideRect = { 530 + j * 50, 210, 575 + j * 50, 230 };
                std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converterW;
                std::wstring wide = converterW.from_bytes(vecC[i].first);
                DrawText(hdc, wide.c_str(), -1, &outsideRect, DT_SINGLELINE | DT_TOP);
            }
            outsideRect = { 900, 235, 985, 255 };
            int MaxP = round(vecC.size() / 8 + 1);
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converterPage;
            std::wstring wideP = converterPage.from_bytes(std::to_string(step) + " / " + std::to_string(MaxP));
            DrawText(hdc, wideP.c_str(), -1, &outsideRect, DT_SINGLELINE | DT_CENTER | DT_TOP);
        }
        EndPaint(hwnd, &ps);
        break;
    case WM_COMMAND:
        if (lParam == /*Открытие файла*/(LPARAM)hwndButton1)
        {
            wordCount.clear();
            wordCountSearch.clear();
            charCount.clear();
            punctCount.clear();

            MathExpectation = 0;
            Dispersion = 0;
            StandardDeviation = 0;

            SetWindowText(hwndTextBox1, L"");
            SetWindowText(hwndTextBox2, L"");

            OPENFILENAME ofn;
            char szFileName[MAX_PATH] = "";

            int bufferSize = MultiByteToWideChar(CP_ACP, 0, szFileName, -1, NULL, 0);
            wszFileName = new WCHAR[bufferSize];
            MultiByteToWideChar(CP_ACP, 0, szFileName, -1, wszFileName, bufferSize);

            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hwnd;
            ofn.lpstrFilter = L"All Files (*.*)\0*.*\0";
            ofn.lpstrFile = wszFileName; //Хранит название файла
            ofn.nMaxFile = MAX_PATH;
            ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

            if (fileHandle != INVALID_HANDLE_VALUE)
            {
                CloseHandle(fileHandle);
                fileContent = "";
            }
            
            if (GetOpenFileName(&ofn))
            {
                fileHandle = CreateFile(wszFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);  
                SetWindowText(hwndTextBox1, wszFileName);

                information(hwnd);
            }
        }
        else if (lParam == /*Выбор параметров*/(LPARAM)hwndButton2)
        {
            int selectedIndex = SendMessage(hwndComboBox, CB_GETCURSEL, 0, 0);
            if (fileHandle != INVALID_HANDLE_VALUE)
            {
                const int bufferSize = 100000;
                char buffer[bufferSize];
                DWORD bytesRead = 0;
               
                while (ReadFile(fileHandle, buffer, bufferSize, &bytesRead, NULL) && bytesRead > 0) {
                    fileContent.append(buffer, bytesRead);
                }

                std::vector<std::string> words;
                std::string word;
                std::istringstream iss(fileContent);
                std::string resultText;
                int size = 0;
                wchar_t* wstr;
                std::string ch;
                flagWord = false;

                switch (selectedIndex)
                {
                case 0:
                    if (fileHandle != INVALID_HANDLE_VALUE) {
                        flagWord = true;
                        for (const auto& pair : wordCount) {
                            resultText += pair.first + " -> " + std::to_string(pair.second) + "\r\n";
                        }

                        size = MultiByteToWideChar(CP_UTF8, 0, resultText.c_str(), -1, NULL, 0);
                        wstr = new wchar_t[size];
                        MultiByteToWideChar(CP_UTF8, 0, resultText.c_str(), -1, wstr, size);
                        SetWindowText(hwndTextBox2, wstr);

                    }
                    break;
                case 1:                 
                    for (const auto& pair : charCount) {
                        resultText += std::string(1, pair.first) + " -> " + std::to_string(pair.second) + "\r\n";
                    }

                    size = MultiByteToWideChar(CP_UTF8, 0, resultText.c_str(), -1, NULL, 0);
                    wstr = new wchar_t[size];
                    MultiByteToWideChar(CP_UTF8, 0, resultText.c_str(), -1, wstr, size);
                    SetWindowText(hwndTextBox2, wstr);
                    break;
                case 2:
                    for (const auto& pair : punctCount) {
                        resultText += std::string(1, pair.first) + " -> " + std::to_string(pair.second) + "\r\n";
                    }

                    size = MultiByteToWideChar(CP_UTF8, 0, resultText.c_str(), -1, NULL, 0);
                    wstr = new wchar_t[size];
                    MultiByteToWideChar(CP_UTF8, 0, resultText.c_str(), -1, wstr, size);
                    SetWindowText(hwndTextBox2, wstr);
                    break;
                case 3:
                    resultText += "Number of words: " + std::to_string(inf[0]) + "\r\n";
                    resultText += "Number of unique words: " + std::to_string(inf[4]) + "\r\n";
                    resultText += "Number of all symbols: " + std::to_string(inf[3]) + "\r\n";
                    resultText += "Number of symbols without space: " + std::to_string(inf[1]) + "\r\n";
                    resultText += "Number of punct: " + std::to_string(inf[2]) + "\r\n\r\n";

                    std::string str = std::to_string(MathExpectation);
                    size_t found = str.find(".");
                    if (found != std::string::npos) {
                        str = str.substr(0, found + 4); 
                    }
                    resultText += "MathExpectation: " + str + "\r\n";

                    str = std::to_string(Dispersion);
                    found = str.find(".");
                    if (found != std::string::npos) {
                        str = str.substr(0, found + 4); 
                    }
                    resultText += "Dispersion: " + str + "\r\n";

                    str = std::to_string(StandardDeviation);
                    found = str.find(".");
                    if (found != std::string::npos) {
                        str = str.substr(0, found + 4); 
                    }
                    resultText += "Standard Deviation: " + str + "\r\n";

                    size = MultiByteToWideChar(CP_UTF8, 0, resultText.c_str(), -1, NULL, 0);
                    wstr = new wchar_t[size];
                    MultiByteToWideChar(CP_UTF8, 0, resultText.c_str(), -1, wstr, size);
                    SetWindowText(hwndTextBox2, wstr);
                    break;
                }
                
                
            }           
        }
        else if (lParam == /*Поиск подстроки*/(LPARAM)hwndButton3)
        {
            if (flagWord)
            {
                wchar_t buffer[100]; 
                GetWindowText(hwndTextBox3, buffer, 100);
                std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
                std::string str = converter.to_bytes(buffer);
                if (wcslen(buffer) > 0)
                {
                    std::string resultText;

                    for (const auto& pair : wordCount) {
                        if (pair.first.find(str) != std::string::npos) {
                            resultText += pair.first + " -> " + std::to_string(pair.second) + "\r\n";
                        }
                    }

                    int size = MultiByteToWideChar(CP_UTF8, 0, resultText.c_str(), -1, NULL, 0);
                    wchar_t* wstr = new wchar_t[size];
                    MultiByteToWideChar(CP_UTF8, 0, resultText.c_str(), -1, wstr, size);
                    SetWindowText(hwndTextBox2, wstr);
                }
                else
                {
                    std::string resultText;
                    for (const auto& pair : wordCount) {
                        resultText += pair.first + " -> " + std::to_string(pair.second) + "\r\n";
                    }

                    int size = MultiByteToWideChar(CP_UTF8, 0, resultText.c_str(), -1, NULL, 0);
                    wchar_t* wstr = new wchar_t[size];
                    MultiByteToWideChar(CP_UTF8, 0, resultText.c_str(), -1, wstr, size);
                    SetWindowText(hwndTextBox2, wstr);
                }
             
            }
        }
        else if (lParam == /*Расчёт графика*/(LPARAM)hwndButton7)
        {           
            if (wordCount.size() > 0)
            {
                int selectedIndex = SendMessage(hwndComboBox, CB_GETCURSEL, 0, 0);
                vec.clear();
                vecC.clear();
                
                if (selectedIndex == 0)
                {
                    PNum = 1;
                    wordCountSearch.clear();
                    wchar_t buffer[100];
                    GetWindowText(hwndTextBox3, buffer, 100);
                    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
                    std::string str = converter.to_bytes(buffer);
                    if (wcslen(buffer) > 0)
                    {
                        if (wordCountSearch.size() == 0)
                        {
                            for (const auto& pair : wordCount) {
                                if (pair.first.find(str) != std::string::npos) {
                                    wordCountSearch[pair.first] = pair.second;
                                }
                            }
                        }
                        vec.assign(wordCountSearch.begin(), wordCountSearch.end());

                        std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                            return a.second > b.second;
                            });
                    }
                    else
                    {
                        vec.assign(wordCount.begin(), wordCount.end());

                        std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
                            return a.second > b.second;
                            });
                    }
                }
                else if (selectedIndex == 1)
                {
                    PNum = 2;
                    vecC.assign(charCount.begin(), charCount.end());

                    std::sort(vecC.begin(), vecC.end(), [](const auto& a, const auto& b) {
                        return a.second > b.second;
                        });
                }
                else if (selectedIndex == 2)
                {
                    PNum = 2;
                    vecC.assign(punctCount.begin(), punctCount.end());

                    std::sort(vecC.begin(), vecC.end(), [](const auto& a, const auto& b) {
                        return a.second > b.second;
                        });
                }
                step = 1;
                std::wstring text = std::to_wstring(step);
                SetWindowText(hwndTextBox4, text.c_str());
                RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
            }

        }
        else if (lParam == /*Пагинация влево*/(LPARAM)hwndButton4)
        {
            if (step > 1 && vec.size() > 0)
            {
                step--;
                std::wstring text = std::to_wstring(step);
                SetWindowText(hwndTextBox4, text.c_str());
                RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
            }
            else if (step > 1 && vecC.size() > 0)
            {
                step--;
                std::wstring text = std::to_wstring(step);
                SetWindowText(hwndTextBox4, text.c_str());
                RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
            }
        
        }
        else if (lParam == /*Пагинация вправо*/(LPARAM)hwndButton5)
        {
            if (step < vec.size() / 8 + 1  && vec.size() > 0)
            {
                step++;
                std::wstring text = std::to_wstring(step);
                SetWindowText(hwndTextBox4, text.c_str());
                RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
            }
            else if (step < vecC.size() / 8 + 1 && vecC.size() > 0)
            {
                step++;
                std::wstring text = std::to_wstring(step);
                SetWindowText(hwndTextBox4, text.c_str());
                RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
            }
        }
        else if (lParam == /*Пагинация по номеру*/(LPARAM)hwndButton6)
        {
            int textLength = GetWindowTextLength(hwndTextBox4);
            std::wstring text;
            text.resize(textLength + 1); 
            GetWindowText(hwndTextBox4, &text[0], textLength + 1);
            int intValue;
            try
            {
                intValue = std::stoi(text);
            }
            catch (const std::invalid_argument& e)
            {
                intValue = 1;
            }

            if (vec.size() > 0)
            {
                if (intValue < vec.size() / 8 + 1)
                {
                    step = intValue;
                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
                }
                else
                {
                    step = vec.size() / 8 + 1;
                    std::wstring text = std::to_wstring(step);
                    SetWindowText(hwndTextBox4, text.c_str());
                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
                }
            }
            else if (vecC.size() > 0)
            {
                if (intValue < vecC.size() / 8 + 1)
                {
                    step = intValue;
                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
                }
                else
                {
                    step = vecC.size() / 8 + 1;
                    std::wstring text = std::to_wstring(step);
                    SetWindowText(hwndTextBox4, text.c_str());
                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
                }
            }
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}