#pragma once

#include "main/scene_base/base.hpp"

#ifdef SCENE_INTERPOLATION_POSITION

// Store a vec3 (p) + time (t)
struct vec3t{
    vcl::vec3 p; // position
    float t;     // time
};

struct gui_scene_structure{
    bool display_keyframe = true;
    bool display_polygon  = true;
};

struct scene_model : scene_base
{

    void setup_data(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui);
    void frame_draw(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui);

    void set_gui();

    // Called every time the mouse is clicked
    void mouse_click(scene_structure& scene, GLFWwindow* window, int button, int action, int mods);
    // Called every time the mouse is moved
    void mouse_move(scene_structure& scene, GLFWwindow* window);

    // Data (p_i,t_i)
    vcl::buffer<vec3t> keyframes; // Given (position,time)

    vcl::mesh_drawable point_visual;                       // moving point
    vcl::mesh_drawable keyframe_visual;                    // keyframe samples
    vcl::mesh_drawable keyframe_picked;                    // showing the picked sample
    vcl::segment_drawable_immediate_mode segment_drawer;   // used to draw segments between keyframe samples
    vcl::curve_dynamic_drawable trajectory;                // Draw the trajectory of the moving point as a curve

    // Store the index of a selected sphere
    int picked_object;

    gui_scene_structure gui_scene;
    vcl::timer_interval timer;

};

#endif


