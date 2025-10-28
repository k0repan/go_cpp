#ifndef VECTOR2INT_H
#define VECTOR2INT_H

struct Vector2Int {
    int first, second;
    Vector2Int() : first(0), second(0) {}
    Vector2Int(const int first, const int second) : first(first), second(second) {}
    Vector2Int(const float first, const float second) : first(static_cast<int>(first)), second(static_cast<int>(second)) {}
    bool operator==(const Vector2Int&) const = default;
};

#endif //VECTOR2INT_H
