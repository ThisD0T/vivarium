#include "lib.hpp"
#include "raymath.h"
#include "boid.hpp"

#include <iostream>
#include <raylib.h>
#include <string>

Boid::Boid(Texture2D* image, float size) {
    position = random_position();
    m_size = size;
    m_image = shared_ptr<Texture2D>(image);
    int frame_width = m_image->width;
    int frame_height = m_image->height;

    sight_dist = 300;
    max_steer = 3.9;
    max_speed = 2.4;

    cohes_mag = max_steer * .7;
    sep_mag = max_steer * .9;
    align_mag = max_steer * .6;

    velocity = random_vector(1, 3);
    acceleration = Vec();
    position = random_position();
    print_vector(position, "position");
}

void Boid::draw() {
    DrawTextureEx(*m_image, vec2vec(position), get_angle(velocity), m_size, WHITE);
}

void Boid::update(unordered_set<shared_ptr<Boid>> other_boids) {
    calc_others(other_boids);
    velocity.Add(acceleration);
    position.Add(velocity);
    velocity.Limit(max_speed);
    loop_edges();
}

void Boid::flock() {

    if (m_others.size() < 1) return;

    Vec avg_others;
    Vec avg_other_vel;

    for (shared_ptr<Boid> other : m_others) {
        avg_other_vel += other->velocity;
        avg_others += other->position;
    }
    avg_other_vel /= (float)m_others.size();
    avg_others /= (float)m_others.size();

    Vec acceleration = (Vec){0, 0};

    //acceleration += avoid_edges().scaled(GetFrameTime());
    acceleration += alignment(avg_other_vel).scaled(GetFrameTime());
    acceleration += separation(avg_others).scaled(GetFrameTime());
    acceleration += cohesion(avg_others).scaled(GetFrameTime());

    velocity.Add(acceleration);
}

void Boid::calc_others(unordered_set<shared_ptr<Boid>> other_boids) {
    m_others.clear();
    for (shared_ptr<Boid> other : other_boids) {
        if (other->position == position) continue;
        else if (distance(position, other->position) < this->sight_dist) {
            m_others.insert(other);
        }
    }
}

Vec Boid::apply_steering(Vec wishpos) {
    wishpos.Subtract(velocity);
    wishpos.Limit(max_steer);

    return wishpos;
}

void Boid::loop_edges() {
    if (position.x < 0) {
        position.x = WIDTH();
    } else if (position.x > WIDTH()) {
        position.x = 0;
    }

    if (position.y < 0) {
        position.y = HEIGHT();
    } else if (position.y > HEIGHT()) {
        position.y = 0;
    }
}

Vec Boid::avoid_edges() {
    Vec avoid_vec = (Vec){0, 0};
    float min_dist = 300;

    if (position.x < min_dist) {
        avoid_vec.x += max_speed * ((min_dist - position.x) / min_dist);
    } else if (position.x > WIDTH() - min_dist) {
        avoid_vec.x -= max_speed * (abs(WIDTH() - min_dist - position.x) / min_dist);
    }

    if (position.y < min_dist) {
        avoid_vec.y += max_speed * ((min_dist - position.y) / min_dist);
    } else if (position.y > HEIGHT() - min_dist) {
        avoid_vec.y -= max_speed * (abs(HEIGHT() - min_dist - position.y) / min_dist);
    }
    avoid_vec.Scale(2);

    return avoid_vec;
}

Vec Boid::alignment(Vec avg) {
    apply_steering(avg);
    avg.set_mag(align_mag);
    return avg;
}

Vec Boid::separation(Vec avg_others) {
    Vec separation = avg_others.scaled(-1);
    separation = separation - this->position;
    separation /= pow(separation.mag(), 2);
    separation.set_mag(sep_mag);
    return apply_steering(separation);
}

Vec Boid::cohesion(Vec avg_others) {
    Vec cohesion = avg_others;
    cohesion = cohesion - this->position;
    cohesion.set_mag(cohes_mag);
    return apply_steering(cohesion);
}
