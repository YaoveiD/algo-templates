#pragma once

#include <iostream>

struct StringMsg {
    std::string val;

    void say() const {
        std::cout << "this is string msg, s=" << val << '\n';
    }
};

struct IntMsg {
    int val;

    void say() const {
        std::cout << "this is int msg, v=" << val << '\n';
    }
};

