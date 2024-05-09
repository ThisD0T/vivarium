#include "lib.hpp"
#include "raymath.h"
#include <iostream>
#include <raylib.h>
#include <string>

float WIDTH() {
    return GetMonitorWidth(GetCurrentMonitor());
}

float HEIGHT() {
    return GetMonitorHeight(GetCurrentMonitor());
}

void init_window() {
    InitWindow(0, 0, "Vivarium");
    int display = GetCurrentMonitor();
    SetTargetFPS(GetMonitorRefreshRate(display));
    ToggleFullscreen();
}


void print_vector(Vec vec, const char* name) {
    std::cout << name << ": {" << vec.x << ", " << vec.y << "}" << "\n";
}

Vec random_position() {
    return (Vec){float(GetRandomValue(0, WIDTH())), float(GetRandomValue(0, HEIGHT()))};
}

Vec random_vector(float min_mag, float max_mag) {
    // trigenometry!
    float magnitude = GetRandomValue(min_mag, max_mag);
    float angle = GetRandomValue(0, 360);
    return (Vec){sin(angle) * magnitude, cos(angle) * magnitude};
}

float to_degrees(float radians) {
    return radians * (180/pi);
}

// returns an angle from 0-360 degrees
float get_angle(Vec vec) {
    float degrees = to_degrees(asin(vec.x / vec.mag()));
    degrees = abs(degrees);

    // accounting for the fact the above formula will only ever give a 0-90 value
    if (vec.y > 0 && vec.x > 0) {
        degrees = (180 - degrees);
    }
    else if (vec.y > 0 && vec.x < 0) {
        degrees += 180;
    }
    else if (vec.y < 0 && vec.x < 0) {
        degrees = 360 - degrees;
    }

    return degrees;
}

float hyperbola(float input) {
    return input / input * input;
}


Vec::Vec() {
    x = 0;
    y = 0;
}

Vec::Vec(float x, float y) {
    this->x = x;
    this->y = y;
}

void Vec::Subtract(Vec other) {
    this->x -= other.x;
    this->y -= other.y;
}

void Vec::Add(Vec other) {
    this->x += other.x;
    this->y += other.y;
}

void Vec::Scale(float num) {
    this->x *= num;
    this->y *= num;
}

Vec Vec::scaled(float num) {
    return (Vec){this->x * num, this->y * num};
}

void Vec::Div(float num) {
    this->x /= num;
    this->y /= num;
}

float Vec::mag() {
    return sqrt(pow(x, 2) + pow(y, 2));
}

void Vec::Normalize() {
    if (x == 0 && y == 0)
        return;
    this->x /= this->mag();
    this->y /= this->mag();
}

Vec Vec::normalized() {
    return (Vec){this->x / this->mag(), this->y / this->mag()};
}

void Vec::set_mag(float new_mag) {
    this->Normalize();
    this->Scale(new_mag);
}

void Vec::Limit(float max_mag) {
    if (mag() > max_mag) {
        set_mag(max_mag);
    }
}

void Vec::operator+=(Vec const& other) {
    this->x += other.x;
    this->y += other.y;
}

Vec Vec::operator-(Vec const& other) {
    return (Vec){this->x - other.x, this->y - other.y};
}

void Vec::operator*=(Vec const& other) {
    this->x *= other.x;
    this->y *= other.y;
}

void Vec::operator/=(Vec const& other) {
    this->x /= other.x;
    this->y /= other.y;
}

void Vec::operator/=(float const& num) {
    this->x /= num;
    this->y /= num;
}

bool Vec::operator==(Vec const& other) {
    if (x == other.x && y == other.y) return true;
    else return false;
}

Vector2 vec2vec(Vec vec) {
    return (Vector2){vec.x, vec.y};
}


float distance(Vec vec1, Vec vec2) {
    Vec vec = vec1 - vec2;
    return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
}
