#pragma once

class Stone {
    public:
        int x, y;
        bool isBlack { true };
        bool isStand { false };
        Stone(const bool isB, const int x, const int y): x(x), y(y), isBlack(isB) {}
};
