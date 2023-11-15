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