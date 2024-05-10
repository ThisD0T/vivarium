#ifndef LIB_H
#define LIB_H

#include <raylib.h>

const float pi = 3.14159265;

float WIDTH();
float HEIGHT();


void init_window();

// making vectors object oriented because I don't like the way Raylib does things
class Vec {
    public:
    float x, y;

    Vec();
    Vec(float x, float y);

    void Subtract(Vec other);
    void Add(Vec other);
    void Scale(float num);
    Vec scaled(float num);
    void Div(float num);

    void Normalize();
    Vec normalized();
    void Limit(float max_mag);
    void set_mag(float new_mag);

    void operator+=(Vec const& other);
    Vec operator-(Vec const & other);
    Vec operator+(Vec const & other);
    void operator*=(Vec const& other);
    Vec operator*(float num);
    void operator/=(Vec const& other);
    void operator/=(float const& other);

    bool operator==(Vec const& other);

    float mag();
};

Vector2 vec2vec(Vec vec);

void print_vector(Vec vec, const char* name);
Vec random_position();
Vec random_vector(float min_mag, float max_mag);

float to_degrees(float radians);
float get_angle(Vec vec);

float hyperbola(float input);
float distance(Vec pos1, Vec pos2);


#endif // LIB_H
