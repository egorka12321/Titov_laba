#pragma once
#include <iostream>
template <typename T>
T GetCorrectData(T min, T max) {
    T x{};
    while ((cin >> x).fail() || cin.peek() != '\n' || x < min || x > max) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Try again (" << min << " - " << max << ")" << endl;
    }
    return x;
}
template <typename T>
void Log(const T& message,int n) {
    ofstream logFile("log.txt", ios::app);
    if (logFile.is_open()) {
        logFile << message << endl;
        logFile.close();
    }
    if (n==1)
        cout << message << endl;
    else if (n==2)
        cout << message;
}

template <typename T>
void Log_cin(const T& message) {
    ofstream logFile("log.txt", ios::app);
    if (logFile.is_open())  {
        logFile << message << endl;
        logFile.close();
    }
}