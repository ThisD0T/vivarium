#ifndef SPATIAL_HASH_H_
#define SPATIAL_HASH_H_

#include <map>
#include <unordered_set>
#include <raylib.h>
#include <memory>
#include <vector>

using std::vector;
using std::shared_ptr;
using std::unordered_set;

class Boid {
    Vector2 pos;
    Vector2 velocity;
    Vector2 acceleration;
    int hash_id;// boids might not need to know what box they are in but I will keep it like this for now.

    void flock(unordered_set<shared_ptr<Boid>> others);// combine steering behaviours.
    void separation(unordered_set<shared_ptr<Boid>> others);
    void alignment(unordered_set<shared_ptr<Boid>> others);
    void cohesion(vector<Boid> others);
    void wrap();// make sure the boid is not going off screen
};


class Hash {
    std::map<int, unordered_set<shared_ptr<Boid>>> hash;
    void get_id(Vector2 pos);

    int box_size;

    // places a boid into the hash_map
    int assign_id(Boid *boid);
};

#endif // SPATIAL_HASH_H_
