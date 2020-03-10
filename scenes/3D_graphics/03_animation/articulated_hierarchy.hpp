#pragma once

#include "main/scene_base/base.hpp"

#ifdef SCENE_ARTICULATED_HIERARCHY


struct gui_scene_structure
{
    bool wireframe   = false;
};

struct scene_model : scene_base
{

    void setup_data(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui);
    void frame_draw(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui);

    void set_gui();

    vcl::hierarchy_mesh_drawable hierarchy;


    vcl::mesh_drawable ground;

    gui_scene_structure gui_scene;
    vcl::timer_interval timer;
};

#endif


