
#include "interpolation_position.hpp"


#ifdef SCENE_INTERPOLATION_POSITION


using namespace vcl;


/** Function returning the index i such that t \in [vt[i],vt[i+1]] */
static size_t index_at_value(float t, const std::vector<float>& vt);

static vec3 linear_interpolation(float t, float t1, float t2, const vec3& p1, const vec3& p2);


void scene_model::setup_data(std::map<std::string,GLuint>& shaders, scene_structure& , gui_structure& )
{
    // Initial Keyframe data
    keyframe_position = {{0,0,0}, {1,0,0}, {1,1,0}, {2,1,0}, {3,1,0}, {3,0,0}, {4,0,0}, {4,-1,0}, {0,-1,0}, {0,0,0}, {1,0,0}, {1,1,0}};
    keyframe_time = {0,1,2,3,4,5,6,7,8,9,10,11};



    // Set timer bounds
    //  To ease spline interpolation of a closed curve time \in [t_1,t_{N-2}]
    timer.t_min = keyframe_time[1];
    timer.t_max = keyframe_time[keyframe_time.size()-2];
    timer.t = timer.t_min;

    // Prepare the visual elements
    surface = mesh_primitive_sphere();
    surface.shader = shaders["mesh"];
    surface.uniform.color   = {0,0,1};
    surface.uniform.transform.scaling = 0.08f;

    sphere = mesh_primitive_sphere();
    sphere.shader = shaders["mesh"];
    sphere.uniform.color = {1,1,1};
    sphere.uniform.transform.scaling = 0.05f;

    segment_drawer.init();

    trajectory = curve_dynamic_drawable(100); // number of steps stroed in the trajectory
    trajectory.uniform.color = {0,0,1};

    picked_object=-1;

}




void scene_model::frame_draw(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& )
{
    timer.update();
    const float t = timer.t;
    set_gui();



    // ********************************************* //
    // Compute interpolated position at time t
    // ********************************************* //
    const size_t idx = index_at_value(t, keyframe_time);

    // Assume a closed curve trajectory
    const size_t N = keyframe_time.size();



    // Linear interpolation
    const float t1 = keyframe_time[idx];
    const float t2 = keyframe_time[idx+1];

    const vec3& p1 = keyframe_position[idx];
    const vec3& p2 = keyframe_position[idx+1];


    const vec3 p = linear_interpolation(t,t1,t2,p1,p2);
    trajectory.add_point(p);


    // Draw current position
    surface.uniform.transform.translation = p;
    draw(surface, scene.camera);


    // Draw sphere at each keyframe position
    for(size_t k=0; k<N; ++k)
    {
        const vec3& p_keyframe = keyframe_position[k];
        sphere.uniform.transform.translation = p_keyframe;
        draw(sphere, scene.camera);
    }


    // Draw segments between each keyframe
    for(size_t k=0; k<keyframe_position.size()-1; ++k)
    {
        const vec3& pa = keyframe_position[k];
        const vec3& pb = keyframe_position[k+1];

        segment_drawer.uniform_parameter.p1 = pa;
        segment_drawer.uniform_parameter.p2 = pb;
        segment_drawer.draw(shaders["segment_im"], scene.camera);
    }

    // Draw moving point trajectory
    trajectory.draw(shaders["curve"], scene.camera);

    // Draw selected sphere in red
    if( picked_object!=-1 )
    {
        const vec3& p_keyframe = keyframe_position[picked_object];
        sphere.uniform.color = vec3(1,0,0);
        sphere.uniform.transform.scaling = 0.06f;
        sphere.uniform.transform.translation = p_keyframe;
        draw(sphere, scene.camera);
        sphere.uniform.color = vec3(1,1,1);
        sphere.uniform.transform.scaling = 0.05f;
    }

}


void scene_model::mouse_click(scene_structure& scene, GLFWwindow* window, int , int action, int )
{
    // Mouse click is used to select a position of the control polygon
    // ******************************************************************** //

    // Window size
    int w=0;
    int h=0;
    glfwGetWindowSize(window, &w, &h);

    // Current cursor position
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    // Convert pixel coordinates to relative screen coordinates between [-1,1]
    const float x = 2*float(xpos)/float(w)-1;
    const float y = 1-2*float(ypos)/float(h);

    // Check if shift key is pressed
    const bool key_shift = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT));

    if(action==GLFW_PRESS && key_shift)
    {
        // Create the 3D ray passing by the selected point on the screen
        const ray r = picking_ray(scene.camera, {x,y});

        // Check if this ray intersects a position (represented by a sphere)
        //  Loop over all positions and get the intersected position (the closest one in case of multiple intersection)
        const size_t N = keyframe_position.size();
        picked_object = -1;
        float distance_min = 0.0f;
        for(size_t k=0; k<N; ++k)
        {
            const vec3 c = keyframe_position[k];
            const picking_info info = ray_intersect_sphere(r, c, 0.1f);

            if( info.picking_valid ) // the ray intersects a sphere
            {
                const float distance = norm(info.intersection-r.p); // get the closest intersection
                if( picked_object==-1 || distance<distance_min ){
                    picked_object = k;
                }
            }
        }
    }

}

void scene_model::mouse_move(scene_structure& scene, GLFWwindow* window)
{
    // Mouse move is used to translate a position once selected
    // ******************************************************************** //

    // Window size
    int w=0;
    int h=0;
    glfwGetWindowSize(window, &w, &h);

    // Current cursor position
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    // Convert pixel coordinates to relative screen coordinates between [-1,1]
    const float x = 2*float(xpos)/float(w)-1;
    const float y = 1-2*float(ypos)/float(h);

    // Check that the mouse is clicked (drag and drop)
    const bool mouse_click_left  = (glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT )==GLFW_PRESS);
    const bool key_shift = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT));

    const size_t N = keyframe_position.size();
    if(mouse_click_left && key_shift && picked_object!=-1)
    {
        // Translate the selected object to the new pointed mouse position within the camera plane
        // ************************************************************************************** //

        // Get vector orthogonal to camera orientation
        const mat4 M = scene.camera.camera_matrix();
        const vec3 n = {M(0,2),M(1,2),M(2,2)};

        // Compute intersection between current ray and the plane orthogonal to the view direction and passing by the selected object
        const ray r = picking_ray(scene.camera, {x,y});
        vec3& p0 = keyframe_position[picked_object];
        const picking_info info = ray_intersect_plane(r,n,p0);

        // translate the position
        p0 = info.intersection;

        // Make sure that duplicated positions are moved together
        int Ns = N;
        if(picked_object==0 || picked_object==Ns-3){
            keyframe_position[0] = info.intersection;
            keyframe_position[N-3] = info.intersection;
        }
        if(picked_object==1 || picked_object==Ns-2){
            keyframe_position[1] = info.intersection;
            keyframe_position[N-2] = info.intersection;
        }
        if(picked_object==2 || picked_object==Ns-1){
            keyframe_position[2] = info.intersection;
            keyframe_position[N-1] = info.intersection;
        }

    }
}

void scene_model::set_gui()
{
    ImGui::SliderFloat("Time", &timer.t, timer.t_min, timer.t_max);

    const float time_scale_min = 0.1f;
    const float time_scale_max = 3.0f;
    ImGui::SliderFloat("Time scale", &timer.scale, time_scale_min, time_scale_max);

    if( ImGui::Button("Print Keyframe") )
    {
        std::cout<<"keyframe_position={";
        for(size_t k=0; k<keyframe_position.size(); ++k)
        {
            const vec3& p = keyframe_position[k];
            std::cout<< "{"<<p.x<<"f,"<<p.y<<"f,"<<p.z<<"f}";
            if(k<keyframe_position.size()-1)
                std::cout<<", ";
        }
        std::cout<<"}"<<std::endl;
    }

}



static size_t index_at_value(float t, const std::vector<float>& vt)
{
    const size_t N = vt.size();
    assert(vt.size()>=2);
    assert(t>=vt[0]);
    assert(t<vt[N-1]);

    size_t k=0;
    while( vt[k+1]<t )
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

