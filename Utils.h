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
    cerr << x << endl;
    return x;
}

class redirect_output_wrapper
{
    std::ostream& stream;
    std::streambuf* const old_buf;
public:
    redirect_output_wrapper(std::ostream& src)
        :old_buf(src.rdbuf()), stream(src)
    {
    }

    ~redirect_output_wrapper() {
        stream.rdbuf(old_buf);
    }
    void redirect(std::ostream& dest)
    {
        stream.rdbuf(dest.rdbuf());
    }
};
