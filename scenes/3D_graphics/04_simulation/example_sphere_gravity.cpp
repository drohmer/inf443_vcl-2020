
#include "example_sphere_gravity.hpp"

#include <random>

#ifdef SCENE_SPHERE_GRAVITY_FLOOR

using namespace vcl;

// Generator for uniform random number
std::default_random_engine generator;
std::uniform_real_distribution<float> distrib(0.0,1.0);


static void set_gui(timer_event& timer);


void scene_model::setup_data(std::map<std::string,GLuint>& , scene_structure& scene, gui_structure& gui)
{
    // Default camera settings
    scene.camera.camera_type = camera_control_spherical_coordinates;
    scene.camera.scale = 5.0f;
    scene.camera.apply_rotation(0,0, -2.0f,1.2f);

    // Default gui display
    gui.show_frame_worldspace = true;
    gui.show_frame_camera = false;

    // Create mesh for particles represented as spheres
    const float r = 0.05f; // radius of spheres
    sphere = mesh_primitive_sphere(r);
    sphere.uniform.color = {0.6f, 0.6f, 1.0f};

    // Create mesh for the ground displayed as a disc
    ground = mesh_primitive_disc(2.0f, {0,0,-r}, {0,0,1}, 80);
    ground.uniform.color = {1,1,1};

    // Delay between emission of a new particles
    timer.periodic_event_time_step = 0.2f;
}


void scene_model::frame_draw(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& )
{
    const float dt = timer.update(); // dt: Elapsed time between last frame
    set_gui(timer);


    // Emission of new particle if needed
    const bool is_new_particle = timer.event;
    if( is_new_particle )
    {
        particle_structure new_particle;
        const vec3 p0 = {0,0,0};

        // Initial speed is random. (x,z) components are uniformly distributed along a circle.
        const float theta     = 2*3.14f*distrib(generator);
        const vec3 v0 = vec3( std::cos(theta), std::sin(theta), 5.0f);

        particles.push_back({p0,v0});
    }


    // Evolve position of particles
    const vec3 g = {0.0f,0.0f,-9.81f};
    for(particle_structure& particle : particles)
    {
        const float m = 0.01f; // particle mass

        vec3& p = particle.p;
        vec3& v = particle.v;

        const vec3 F = m*g;

        // Numerical integration
        v = v + dt*F/m;
        p = p + dt*v;
    }


    // Remove particles that are too low
    for(auto it = particles.begin(); it!=particles.end(); ++it)
        if( it->p.z < -3)
            it = particles.erase(it);


    // Display particles
    for(particle_structure& particle : particles)
    {
        sphere.uniform.transform.translation = particle.p;
        draw(sphere, scene.camera, shaders["mesh"]);
    }

    // Display ground
    draw(ground, scene.camera, shaders["mesh"]);
}



static void set_gui(timer_event& timer)
{
    // Can set the speed of the animation
    float scale_min = 0.05f;
    float scale_max = 2.0f;
    ImGui::SliderScalar("Time scale", ImGuiDataType_Float, &timer.scale, &scale_min, &scale_max, "%.2f s");

    // Start and stop animation
    if (ImGui::Button("Stop"))
        timer.stop();
    if (ImGui::Button("Start"))
        timer.start();
}


#endif
