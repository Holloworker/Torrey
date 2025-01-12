#include "hw1.h"
#include "hw1_scenes.h"
#include "Camera.h"
#include "Renderer.h"

using namespace hw1;

CameraParameters cameraParameters = 
{
    Vector3(0., 0.,  -1.),
    Vector3(0., 0., 0.),
    Vector3 (0., 1., 0.),
    1.,
    90.,
    1.,
	640,
    480
};

Image3 hw_1_1(const std::vector<std::string> &/*params*/) {
    // Homework 1.1: generate camera rays and output the ray directions
    // The camera is positioned at (0, 0, 0), facing towards (0, 0, -1),
    // with an up vector (0, 1, 0) and a vertical field of view of 90 degree.
    std::shared_ptr<Image3> img;
    cameraParameters.width = 640;
    cameraParameters.height = 480;
    Variables vars;
    Renderer render;
    ParsedScene scene;

    CameraUnion cam = GenerateCameraByType(cameraParameters, PERSPECTIVE_CAM);
    //CameraUnion cam = GenerateCameraByType(cameraParameters, ENVIRONMENT_CAM);
    render.Render(cam, vars, scene, Miss_hw_1_1, Illumination_hw_1_1);
    img = render.GetImage();

    return *img;
}

Image3 hw_1_2(const std::vector<std::string> &/*params*/) {
    // Homework 1.2: intersect the rays generated from hw_1_1
    // with a unit sphere located at (0, 0, -2)

    std::shared_ptr<Image3> img;
    cameraParameters.width = 640;
    cameraParameters.height = 480;
    Variables vars;
    Renderer render;
    ParsedScene scene;
    ParsedSphere sphere;
    sphere.position = Vector3(0., 0., -2.);
    sphere.radius = 1.;
    ParsedShape shape{ sphere };
    scene.shapes.push_back(shape);

    CameraUnion cam = GenerateCameraByType(cameraParameters, PERSPECTIVE_CAM);
    render.Render(cam, vars, scene, Miss_hw_1_2, Illumination_hw_1_2);
    img = render.GetImage();

    return *img;
}

Image3 hw_1_3(const std::vector<std::string> &params) {
    // Homework 1.3: add camera control to hw_1_2. 
    // We will use a look at transform:
    // The inputs are "lookfrom" (camera position),
    //                "lookat" (target),
    //                and the up vector
    // and the vertical field of view (in degrees).
    // If the user did not specify, fall back to the default
    // values below.
    // If you use the default values, it should render
    // the same image as hw_1_2.

    Vector3 lookfrom = Vector3{0, 0,  0};
    Vector3 lookat   = Vector3{0, 0, -2};
    Vector3 up       = Vector3{0, 1,  0};
    Real    vfov     = 90;
    for (int i = 0; i < (int)params.size(); i++) {
        if (params[i] == "-lookfrom") {
            Real x = std::stof(params[++i]);
            Real y = std::stof(params[++i]);
            Real z = std::stof(params[++i]);
            lookfrom = Vector3{x, y, z};
        } else if (params[i] == "-lookat") {
            Real x = std::stof(params[++i]);
            Real y = std::stof(params[++i]);
            Real z = std::stof(params[++i]);
            lookat = Vector3{x, y, z};
        } else if (params[i] == "-up") {
            Real x = std::stof(params[++i]);
            Real y = std::stof(params[++i]);
            Real z = std::stof(params[++i]);
            up = Vector3{x, y, z};
        } else if (params[i] == "-vfov") {
            vfov = std::stof(params[++i]);
        }
    }

    // avoid unused warnings
    UNUSED(lookfrom);
    UNUSED(lookat);
    UNUSED(up);
    UNUSED(vfov);

    std::shared_ptr<Image3> img;
    cameraParameters.width = 640;
    cameraParameters.height = 480;
    Variables vars;
    Renderer render;
    ParsedScene scene;
    ParsedSphere sphere;
    sphere.position = Vector3(0., 0., -2.);
    sphere.radius = 1.;
    ParsedShape shape{ sphere };
    scene.shapes.push_back(shape);
    //lookfrom
    //    lookat
    //    up
    //    vfov
    cameraParameters.eye = lookfrom;
    cameraParameters.center = lookat;
    cameraParameters.upvec = up;
    cameraParameters.fovy = vfov;

    CameraUnion cam = GenerateCameraByType(cameraParameters, PERSPECTIVE_CAM);
    render.Render(cam, vars, scene, Miss_hw_1_3, Illumination_hw_1_3);
    img = render.GetImage();

    return *img;
}

Image3 hw_1_4(const std::vector<std::string> &params) {
    // Homework 1.4: render the scenes defined in hw1_scenes.h
    // output their diffuse color directly.
    if (params.size() == 0) {
        return Image3(0, 0);
    }

    int scene_id = std::stoi(params[0]);
    UNUSED(scene_id); // avoid unused warning
    // Your scene is hw1_scenes[scene_id]
    Scene& scene = hw1_scenes[scene_id];

    std::shared_ptr<Image3> img;
    Variables vars;
    Renderer render;
    ParsedScene parsed_scene = SceneToParsedScene(scene);

    cameraParameters.width = 640;
    cameraParameters.height = 480;
    cameraParameters.eye = parsed_scene.camera.lookfrom;
    cameraParameters.center = parsed_scene.camera.lookat;
    cameraParameters.upvec = parsed_scene.camera.up;
    cameraParameters.fovy = parsed_scene.camera.vfov;

    CameraUnion cam = GenerateCameraByType(cameraParameters, PERSPECTIVE_CAM);
    render.Render(cam, vars, parsed_scene, Miss_hw_1_4, Illumination_hw_1_4);
    img = render.GetImage();

    return *img;
}

Image3 hw_1_5(const std::vector<std::string> &params) {
    // Homework 1.5: render the scenes defined in hw1_scenes.h,
    // light them using the point lights in the scene.
    if (params.size() == 0) {
        return Image3(0, 0);
    }

    int scene_id = std::stoi(params[0]);
    UNUSED(scene_id); // avoid unused warning
    // Your scene is hw1_scenes[scene_id]
    Scene& scene = hw1_scenes[scene_id];

    std::shared_ptr<Image3> img;
    Variables vars;
    Renderer render;
    ParsedScene parsed_scene = SceneToParsedScene(scene);

    cameraParameters.width = 640;
    cameraParameters.height = 480;
    cameraParameters.eye = parsed_scene.camera.lookfrom;
    cameraParameters.center = parsed_scene.camera.lookat;
    cameraParameters.upvec = parsed_scene.camera.up;
    cameraParameters.fovy = parsed_scene.camera.vfov;

    CameraUnion cam = GenerateCameraByType(cameraParameters, PERSPECTIVE_CAM);
    render.Render(cam, vars, parsed_scene, Miss_hw_1_5, Illumination_hw_1_5);
    img = render.GetImage();

    return *img;
}

Image3 hw_1_6(const std::vector<std::string> &params) {
    // Homework 1.6: add antialiasing to homework 1.5
    if (params.size() == 0) {
        return Image3(0, 0);
    }

    int scene_id = 0;
    int spp = 64;
    for (int i = 0; i < (int)params.size(); i++) {
        if (params[i] == "-spp") {
            spp = std::stoi(params[++i]);
        } else {
            scene_id = std::stoi(params[i]);
        }
    }

    UNUSED(scene_id); // avoid unused warning
    UNUSED(spp); // avoid unused warning
    // Your scene is hw1_scenes[scene_id]

    Scene& scene = hw1_scenes[scene_id];

    std::shared_ptr<Image3> img;
    Variables vars;
    Renderer render;
    ParsedScene parsed_scene = SceneToParsedScene(scene);

    cameraParameters.width = 160;
    cameraParameters.height = 120;
    cameraParameters.eye = parsed_scene.camera.lookfrom;
    cameraParameters.center = parsed_scene.camera.lookat;
    cameraParameters.upvec = parsed_scene.camera.up;
    cameraParameters.fovy = parsed_scene.camera.vfov;
    cameraParameters.samples_per_pixel = spp;

    CameraUnion cam = GenerateCameraByType(cameraParameters, PERSPECTIVE_CAM);
    render.Render(cam, vars, parsed_scene, Miss_hw_1_6, Illumination_hw_1_6);
    img = render.GetImage();

    return *img;
}

Image3 hw_1_7(const std::vector<std::string> &params) {
    // Homework 1.7: add mirror materials to homework 1.6
    if (params.size() == 0) {
        return Image3(0, 0);
    }

    int scene_id = 0;
    int spp = 64;
    for (int i = 0; i < (int)params.size(); i++) {
        if (params[i] == "-spp") {
            spp = std::stoi(params[++i]);
        }
        else {
            scene_id = std::stoi(params[i]);
        }
    }

    UNUSED(scene_id); // avoid unused warning
    UNUSED(spp); // avoid unused warning
    // Your scene is hw1_scenes[scene_id]

    Scene& scene = hw1_scenes[scene_id];

    std::shared_ptr<Image3> img;
    Variables vars;

    vars.max_depth = 10; // tracing depth

    Renderer render;
    ParsedScene parsed_scene = SceneToParsedScene(scene);

    cameraParameters.width = 640;
    cameraParameters.height = 480;
    cameraParameters.eye = parsed_scene.camera.lookfrom;
    cameraParameters.center = parsed_scene.camera.lookat;
    cameraParameters.upvec = parsed_scene.camera.up;
    cameraParameters.fovy = parsed_scene.camera.vfov;
    cameraParameters.samples_per_pixel = spp;

    CameraUnion cam = GenerateCameraByType(cameraParameters, PERSPECTIVE_CAM);
    render.Render(cam, vars, parsed_scene, Miss_hw_1_7, Illumination_hw_1_7);
    img = render.GetImage();

    return *img;
}

Image3 hw_1_8(const std::vector<std::string> &params) {
    // Homework 1.8: parallelize HW 1.7
    if (params.size() == 0) {
        return Image3(0, 0);
    }

    int scene_id = 0;
    int spp = 64;
    for (int i = 0; i < (int)params.size(); i++) {
        if (params[i] == "-spp") {
            spp = std::stoi(params[++i]);
        }
        else {
            scene_id = std::stoi(params[i]);
        }
    }

    UNUSED(scene_id); // avoid unused warning
    UNUSED(spp); // avoid unused warning
    // Your scene is hw1_scenes[scene_id]

    Scene& scene = hw1_scenes[scene_id];

    std::shared_ptr<Image3> img;
    Variables vars;

    vars.max_depth = 10; // tracing depth

    Renderer render;
    ParsedScene parsed_scene = SceneToParsedScene(scene);

    cameraParameters.width = 1280;
    cameraParameters.height = 960;
    cameraParameters.eye = parsed_scene.camera.lookfrom;
    cameraParameters.center = parsed_scene.camera.lookat;
    cameraParameters.upvec = parsed_scene.camera.up;
    cameraParameters.fovy = parsed_scene.camera.vfov;
    cameraParameters.samples_per_pixel = spp;

    CameraUnion cam = GenerateCameraByType(cameraParameters, PERSPECTIVE_CAM);
    render.Render(cam, vars, parsed_scene, Miss_hw_1_8, Illumination_hw_1_8);
    img = render.GetImage();

    return *img;
}

Image3 hw_1_10(const std::vector<std::string>& params) {
    // Homework 1.10: Rendering glasses
    if (params.size() == 0) {
        return Image3(0, 0);
    }

    int scene_id = 0;
    int spp = 64;
    for (int i = 0; i < (int)params.size(); i++) {
        if (params[i] == "-spp") {
            spp = std::stoi(params[++i]);
        }
        else {
            scene_id = std::stoi(params[i]);
        }
    }

    UNUSED(scene_id); // avoid unused warning
    UNUSED(spp); // avoid unused warning
    // Your scene is hw1_scenes[scene_id]

    Scene& scene = hw1_scenes[scene_id];

    std::shared_ptr<Image3> img;
    Variables vars;

    vars.max_depth = 5; // tracing depth

    Renderer render;
    ParsedScene parsed_scene = SceneToParsedScene(scene);

    cameraParameters.width = 1280;
    cameraParameters.height = 960;
    cameraParameters.eye = parsed_scene.camera.lookfrom;
    cameraParameters.center = parsed_scene.camera.lookat;
    cameraParameters.upvec = parsed_scene.camera.up;
    cameraParameters.fovy = parsed_scene.camera.vfov;
    cameraParameters.samples_per_pixel = spp;

    CameraUnion cam = GenerateCameraByType(cameraParameters, PERSPECTIVE_CAM);
    render.Render(cam, vars, parsed_scene, Miss_hw_1_10, Illumination_hw_1_10);
    img = render.GetImage();

    return *img;    
}
Image3 hw_1_9(const std::vector<std::string>& params)
{
    // Homework 1.11: defocus blur
    if (params.size() == 0) {
        return Image3(0, 0);
    }

    int scene_id = 0;
    int spp = 64;
    for (int i = 0; i < (int)params.size(); i++) {
        if (params[i] == "-spp") {
            spp = std::stoi(params[++i]);
        }
        else {
            scene_id = std::stoi(params[i]);
        }
    }

    UNUSED(scene_id); // avoid unused warning
    UNUSED(spp); // avoid unused warning
    // Your scene is hw1_scenes[scene_id]

    Scene& scene = hw1_scenes[scene_id];

    std::shared_ptr<Image3> img;
    Variables vars;

    vars.max_depth = 5; // tracing depth

    Renderer render;
    ParsedScene parsed_scene = SceneToParsedScene(scene);

    cameraParameters.width = 1280;
    cameraParameters.height = 960;
    cameraParameters.eye = parsed_scene.camera.lookfrom;
    cameraParameters.center = parsed_scene.camera.lookat;
    cameraParameters.upvec = parsed_scene.camera.up;
    cameraParameters.fovy = parsed_scene.camera.vfov;
    cameraParameters.samples_per_pixel = spp;
    //cameraParameters.aperture = 0.03;

    CameraUnion cam = GenerateCameraByType(cameraParameters, PERSPECTIVE_CAM);
    render.Render(cam, vars, parsed_scene, Miss_hw_1_9, Illumination_hw_1_9);
    img = render.GetImage();

    return *img;
};
Image3 hw_1_11(const std::vector<std::string>& params)
{
    // Homework 1.11: defocus blur
    if (params.size() == 0) {
        return Image3(0, 0);
    }

    int scene_id = 0;
    int spp = 64;
    for (int i = 0; i < (int)params.size(); i++) {
        if (params[i] == "-spp") {
            spp = std::stoi(params[++i]);
        }
        else {
            scene_id = std::stoi(params[i]);
        }
    }

    UNUSED(scene_id); // avoid unused warning
    UNUSED(spp); // avoid unused warning
    // Your scene is hw1_scenes[scene_id]

    Scene& scene = hw1_scenes[scene_id];

    std::shared_ptr<Image3> img;
    Variables vars;

    vars.max_depth = 10; // tracing depth

    Renderer render;
    ParsedScene parsed_scene = SceneToParsedScene(scene);

    cameraParameters.width = 1280;
    cameraParameters.height = 960;
    cameraParameters.eye = parsed_scene.camera.lookfrom;
    cameraParameters.center = parsed_scene.camera.lookat;
    cameraParameters.upvec = parsed_scene.camera.up;
    cameraParameters.fovy = parsed_scene.camera.vfov;
    cameraParameters.samples_per_pixel = spp;
    cameraParameters.aperture = 0.04;

    CameraUnion cam = GenerateCameraByType(cameraParameters, PERSPECTIVE_CAM);
    render.Render(cam, vars, parsed_scene, Miss_hw_1_11, Illumination_hw_1_11);
    img = render.GetImage();

    return *img;
};
