
#include "interpolation_position.hpp"


#ifdef SCENE_INTERPOLATION_POSITION


using namespace vcl;


/** Function returning the index i such that t \in [v[i].t,v[i+1].t] */
static size_t index_at_value(float t, const vcl::buffer<vec3t> &v);

static vec3 linear_interpolation(float t, float t1, float t2, const vec3& p1, const vec3& p2);


void scene_model::setup_data(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& )
{
    // Initial Keyframe data vector of (position, time)
    keyframes = { { {-1,1,0}   , 0.0f  },
                  { {0,1,0}    , 1.0f  },
                  { {1,1,0}    , 2.0f  },
                  { {1,2,0}    , 2.5f  },
                  { {2,2,0}    , 3.0f  },
                  { {2,2,1}    , 3.5f  },
                  { {2,0,1.5}  , 3.75f  },
                  { {1.5,-1,1} , 4.5f  },
                  { {1.5,-1,0} , 5.0f  },
                  { {1,-1,0}   , 6.0f  },
                  { {0,-0.5,0} , 7.0f },
                  { {-1,-0.5,0}, 8.0f },
                };

    // Set timer bounds
    // You should adapt these extremal values to the type of interpolation
    timer.t_min = keyframes[0].t;                   // first time of the keyframe
    timer.t_max = keyframes[keyframes.size()-1].t;  // last time of the keyframe
    timer.t = timer.t_min;

    // Prepare the visual elements
    point_visual = mesh_primitive_sphere();
    point_visual.shader = shaders["mesh"];
    point_visual.uniform.color   = {0,0,1};
    point_visual.uniform.transform.scaling = 0.04f;

    keyframe_visual = mesh_primitive_sphere();
    keyframe_visual.shader = shaders["mesh"];
    keyframe_visual.uniform.color = {1,1,1};
    keyframe_visual.uniform.transform.scaling = 0.05f;

    keyframe_picked = mesh_primitive_sphere();
    keyframe_picked.shader = shaders["mesh"];
    keyframe_picked.uniform.color = {1,0,0};
    keyframe_picked.uniform.transform.scaling = 0.055f;

    segment_drawer.init();

    trajectory = curve_dynamic_drawable(100); // number of steps stored in the trajectory
    trajectory.uniform.color = {0,0,1};

    picked_object=-1;
    scene.camera.scale = 7.0f;
}




void scene_model::frame_draw(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& )
{
    timer.update();
    const float t = timer.t;

    if( t<timer.t_min+0.1f ) // clear trajectory when the timer restart
        trajectory.clear();

    set_gui();

    // ********************************************* //
    // Compute interpolated position at time t
    // ********************************************* //
    const int idx = index_at_value(t, keyframes);

    // Assume a closed curve trajectory
    const size_t N = keyframes.size();

    // Preparation of data for the linear interpolation
    // Parameters used to compute the linear interpolation
    const float t1 = keyframes[idx  ].t; // = t_i
    const float t2 = keyframes[idx+1].t; // = t_{i+1}

    const vec3& p1 = keyframes[idx  ].p; // = p_i
    const vec3& p2 = keyframes[idx+1].p; // = p_{i+1}



    // Compute the linear interpolation here
    const vec3 p = linear_interpolation(t,t1,t2,p1,p2);

    // Create and call a function cardinal_spline_interpolation(...) instead
    // ...




    // Store current trajectory of point p
    trajectory.add_point(p);


    // Draw current position
    point_visual.uniform.transform.translation = p;
    draw(point_visual, scene.camera);

    // Draw moving point trajectory
    trajectory.draw(shaders["curve"], scene.camera);


    // Draw sphere at each keyframe position
    if(gui_scene.display_keyframe) {
        for(size_t k=0; k<N; ++k)
        {
            const vec3& p_keyframe = keyframes[k].p;
            keyframe_visual.uniform.transform.translation = p_keyframe;
            draw(keyframe_visual, scene.camera);
        }
    }

    // Draw selected sphere in red
    if( picked_object!=-1 )
    {
        const vec3& p_keyframe = keyframes[picked_object].p;
        keyframe_picked.uniform.transform.translation = p_keyframe;
        draw(keyframe_picked, scene.camera);
    }


    // Draw segments between each keyframe
    if(gui_scene.display_polygon) {
        for(size_t k=0; k<keyframes.size()-1; ++k)
        {
            const vec3& pa = keyframes[k].p;
            const vec3& pb = keyframes[k+1].p;

            segment_drawer.uniform_parameter.p1 = pa;
            segment_drawer.uniform_parameter.p2 = pb;
            segment_drawer.draw(shaders["segment_im"], scene.camera);
        }
    }

}



void scene_model::mouse_click(scene_structure& scene, GLFWwindow* window, int , int , int )
{
    // Mouse click is used to select a position of the control polygon
    // ******************************************************************** //

    // Cursor coordinates
    const vec2 cursor = glfw_cursor_coordinates_window(window);

    // Check that the mouse is clicked (drag and drop)
    const bool mouse_click_left  = glfw_mouse_pressed_left(window);
    const bool key_shift = glfw_key_shift_pressed(window);

    // Check if shift key is pressed
    if(mouse_click_left && key_shift)
    {
        // Create the 3D ray passing by the selected point on the screen
        const ray r = picking_ray(scene.camera, cursor);

        // Check if this ray intersects a position (represented by a sphere)
        //  Loop over all positions and get the intersected position (the closest one in case of multiple intersection)
        const size_t N = keyframes.size();
        picked_object = -1;
        float distance_min = 0.0f;
        for(size_t k=0; k<N; ++k)
        {
            const vec3 c = keyframes[k].p;
            const picking_info info = ray_intersect_sphere(r, c, 0.1f);

            if( info.picking_valid ) // the ray intersects a sphere
            {
                const float distance = norm(info.intersection-r.p); // get the closest intersection
                if( picked_object==-1 || distance<distance_min ){
                    distance_min = distance;
                    picked_object = k;
                }
            }
        }
    }

}

void scene_model::mouse_move(scene_structure& scene, GLFWwindow* window)
{

    const bool mouse_click_left  = glfw_mouse_pressed_left(window);
    const bool key_shift = glfw_key_shift_pressed(window);
    if(mouse_click_left && key_shift && picked_object!=-1)
    {
        // Translate the selected object to the new pointed mouse position within the camera plane
        // ************************************************************************************** //

        // Get vector orthogonal to camera orientation
        const mat4 M = scene.camera.camera_matrix();
        const vec3 n = {M(0,2),M(1,2),M(2,2)};

        // Compute intersection between current ray and the plane orthogonal to the view direction and passing by the selected object
        const vec2 cursor = glfw_cursor_coordinates_window(window);
        const ray r = picking_ray(scene.camera, cursor);
        vec3& p0 = keyframes[picked_object].p;
        const picking_info info = ray_intersect_plane(r,n,p0);

        // translate the position
        p0 = info.intersection;

    }
}

void scene_model::set_gui()
{
    ImGui::SliderFloat("Time", &timer.t, timer.t_min, timer.t_max);
    ImGui::SliderFloat("Time scale", &timer.scale, 0.1f, 3.0f);

    ImGui::Text("Display: "); ImGui::SameLine();
    ImGui::Checkbox("keyframe", &gui_scene.display_keyframe); ImGui::SameLine();
    ImGui::Checkbox("polygon", &gui_scene.display_polygon);

    if( ImGui::Button("Print Keyframe") )
    {
        std::cout<<"keyframe_position={";
        for(size_t k=0; k<keyframes.size(); ++k)
        {
            const vec3& p = keyframes[k].p;
            std::cout<< "{"<<p.x<<"f,"<<p.y<<"f,"<<p.z<<"f}";
            if(k<keyframes.size()-1)
                std::cout<<", ";
        }
        std::cout<<"}"<<std::endl;
    }

}



static size_t index_at_value(float t, vcl::buffer<vec3t> const& v)
{
    const size_t N = v.size();
    assert(v.size()>=2);
    assert(t>=v[0].t);
    assert(t<v[N-1].t);

    size_t k=0;
    while( v[k+1].t<t )
        ++k;
    return k;
}


static vec3 linear_interpolation(float t, float t1, float t2, const vec3& p1, const vec3& p2)
{
    const float alpha = (t-t1)/(t2-t1);
    const vec3 p = (1-alpha)*p1 + alpha*p2;

    return p;
}


#endif

