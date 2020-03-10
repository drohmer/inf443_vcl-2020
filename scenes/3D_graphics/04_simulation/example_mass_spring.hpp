#pragma once

#include "main/scene_base/base.hpp"

#ifdef SCENE_MASS_SPRING_1D

struct particle_element
{
    vcl::vec3 p; // Position
    vcl::vec3 v; // Speed
};

struct scene_model : scene_base
{

    void setup_data(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui);
    void frame_draw(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui);


    particle_element pA;
    particle_element pB;
    float L0;


    vcl::mesh_drawable sphere;      // Visual display of particles
    vcl::segments_drawable borders; // Visual display of borders
    vcl::segment_drawable_immediate_mode segment_drawer;

    vcl::timer_event timer;
};






#endif
