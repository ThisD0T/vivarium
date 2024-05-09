#include <raylib.h>
#include "boid.hpp"
#include <iostream>

using std::make_shared;


auto main(int argc, char *argv[]) -> int {
    init_window();
    Texture2D* boid_texture = new Texture2D(LoadTexture("res/triangle_sprite.png"));

    std::cout << "w and h of screen: " << GetMonitorWidth(GetCurrentMonitor()) << ", " << HEIGHT() << "\n";

    unordered_set<shared_ptr<Boid>> boids;

    for (int i = 0; i < 15; i++) {
        shared_ptr<Boid> new_boid = make_shared<Boid>(boid_texture, 0.6);
        boids.insert(new_boid);
    }

    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(ColorFromHSV(188, 0.9, 0.75));

        for (shared_ptr<Boid> boid : boids) {
            boid->draw();
        }

        EndDrawing();

        for (shared_ptr<Boid> boid : boids) {
            boid->update(boids);
            boid->flock();
        }
    }

    delete boid_texture;
    return 0;
}
