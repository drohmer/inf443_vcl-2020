
#include "articulated_hierarchy.hpp"


#ifdef SCENE_ARTICULATED_HIERARCHY


using namespace vcl;



void scene_model::setup_data(std::map<std::string,GLuint>& shaders, scene_structure& , gui_structure& )
{
    const float r_body = 0.25f;
    const float r_cylinder = 0.05f;
    const float l_arm = 0.2f;
    mesh_drawable body = mesh_primitive_sphere(r_body,{0,0,0},40,40);
    body.shader = shaders["mesh"];

    mesh_drawable eye = mesh_drawable(mesh_primitive_sphere(0.05f,{0,0,0},20,20), shaders["mesh"]);
    eye.uniform.color = {0,0,0};

    mesh arm_top_left = mesh_primitive_cylinder(r_cylinder, {0,0,0}, {-l_arm,0,0});
    mesh arm_bottom_left = mesh_primitive_cylinder(r_cylinder, {0,0,0}, {-l_arm/1.5f,-l_arm/1.0f,0});
    mesh arm_top_right = mesh_primitive_cylinder(r_cylinder, {0,0,0}, {l_arm,0,0});
    mesh arm_bottom_right = mesh_primitive_cylinder(r_cylinder, {0,0,0}, {l_arm/1.5f,-l_arm/1.0f,0});

    mesh shoulder = mesh_primitive_sphere(0.055f);

    hierarchy.add(body, "body");
    hierarchy.add(eye, "eye_left", "body", {r_body/3,r_body/2,r_body/1.5f});
    hierarchy.add(eye, "eye_right", "body", {-r_body/3,r_body/2,r_body/1.5f});

    hierarchy.add(arm_top_left, "arm_top_left", "body", {-r_body+0.05f,0,0});
    hierarchy.add(arm_bottom_left, "arm_bottom_left", "arm_top_left", {-l_arm,0,0});

    hierarchy.add(arm_top_right, "arm_top_right", "body", {r_body-0.05f,0,0});
    hierarchy.add(arm_bottom_right, "arm_bottom_right", "arm_top_right", {l_arm,0,0});

    hierarchy.add(shoulder, "shoulder_left", "arm_bottom_left");
    hierarchy.add(shoulder, "shoulder_right", "arm_bottom_right");

    hierarchy.set_shader_for_all_elements(shaders["mesh"]);
    timer.scale = 0.5f;

}




void scene_model::frame_draw(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& )
{
    timer.update();
    set_gui();

    const float t = timer.t;

    hierarchy["body"].transform.translation = {0,0,0.2f*(1+std::sin(2*3.14f*t))};

    hierarchy["arm_top_left"].transform.rotation = rotation_from_axis_angle_mat3({0,1,0}, std::sin(2*3.14f*(t-0.4f)) );
    hierarchy["arm_bottom_left"].transform.rotation = rotation_from_axis_angle_mat3({0,1,0}, std::sin(2*3.14f*(t-0.6f)) );

    hierarchy["arm_top_right"].transform.rotation = rotation_from_axis_angle_mat3({0,-1,0}, std::sin(2*3.14f*(t-0.4f)) );
    hierarchy["arm_bottom_right"].transform.rotation = rotation_from_axis_angle_mat3({0,-1,0}, std::sin(2*3.14f*(t-0.6f)) );

    hierarchy.update_local_to_global_coordinates();
    draw(hierarchy, scene.camera);

}




void scene_model::set_gui()
{
    ImGui::SliderFloat("Time", &timer.t, timer.t_min, timer.t_max);

    const float time_scale_min = 0.1f;
    const float time_scale_max = 3.0f;
    ImGui::SliderFloat("Time scale", &timer.scale, time_scale_min, time_scale_max);
    ImGui::Checkbox("Wireframe", &gui_scene.wireframe);
}



#endif

