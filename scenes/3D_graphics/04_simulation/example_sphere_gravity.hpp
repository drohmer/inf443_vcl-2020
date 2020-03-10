#pragma once

#include "main/scene_base/base.hpp"

#ifdef SCENE_SPHERE_GRAVITY_FLOOR

// Structure of a particle
struct particle_structure
{
    vcl::vec3 p; // Position
    vcl::vec3 v; // Speed
};

struct scene_model : scene_base
{

    void setup_data(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui);
    void frame_draw(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui);


    std::list<particle_structure> particles; // Storage of all currently active particles

    vcl::mesh_drawable sphere; // Visual representation of a particle - a sphere
    vcl::mesh_drawable ground; // Visual representation of the ground - a disc
    vcl::timer_event timer;    // Timer allowing to indicate periodic events

};

#endif
