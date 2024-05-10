#ifndef BOID_H_
#define BOID_H_

#include <raylib.h>
#include <memory>
#include <unordered_set>
#include "lib.hpp"

using std::shared_ptr;
using std::unordered_set;

class Boid {
    float m_size;
    shared_ptr<Texture2D> m_image;
    Rectangle source_rec;
    Rectangle dest_rec;
    Vec origin;

    unordered_set<shared_ptr<Boid>> m_others;

    public:

    Vec position;
    Vec acceleration;
    Vec velocity;

    float max_speed;
    float max_steer;
    float sight_dist;

    float sep_weight;
    float align_weight;
    float cohes_weight;

    void draw();
    void flock();
    void calc_others(unordered_set<shared_ptr<Boid>> others);
    Vec separation();
    Vec alignment(Vec average_other_vel);
    Vec cohesion(Vec avg_others);
    Vec apply_steering(Vec wishpos);

    Vec avoid_edges();
    void loop_edges();

    void update(unordered_set<shared_ptr<Boid>> others);

    Boid(Texture2D* image, float size);
};

#endif // BOID_H_
