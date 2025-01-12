#include "hw4.h"
#include "parse_scene.h"
#include "Renderer.h"
#include "timer.h"
#include "Variables.h"

Image3 hw_4_1(const std::vector<std::string>& params) {
    // Homework 4.1: diffuse interreflection
    if (params.size() < 1) {
        return Image3(0, 0);
    }

    int max_depth = 50;
    std::string filename;
    for (int i = 0; i < (int)params.size(); i++) {
        if (params[i] == "-max_depth") {
            max_depth = std::stoi(params[++i]);
        }
        else if (filename.empty()) {
            filename = params[i];
        }
    }

    int spp = 16;
    Timer timer;
    tick(timer);
    ParsedScene scene = parse_scene(params[0]);
    std::cout << "Scene parsing done. Took " << tick(timer) << " seconds." << std::endl;
    UNUSED(scene);

    UNUSED(spp);
    std::shared_ptr<Image3> img;
    Variables vars;

    vars.max_depth = max_depth; // tracing depth

    Renderer render;

    vars.cameraParameters.width = scene.camera.width;
    vars.cameraParameters.height = scene.camera.height;
    vars.cameraParameters.eye = scene.camera.lookfrom;
    vars.cameraParameters.center = scene.camera.lookat;
    vars.cameraParameters.upvec = scene.camera.up;
    vars.cameraParameters.fovy = scene.camera.vfov;
    vars.cameraParameters.samples_per_pixel = scene.samples_per_pixel;
    //vars.cameraParameters.samples_per_pixel = 4;

    //larger the file, larger the parallel_counts for bvh
    vars.parallel_counts_bvh = 16;
    // enable shading_normal
    vars.shading_normal = true;
    // enable multiple sampling on area lights, must be square
    //vars.area_light_samples = 4 * 4;

    CameraUnion cam = GenerateCameraByType(vars.cameraParameters, PERSPECTIVE_CAM);
    Scene s = ParsedSceneToScene(scene);
    render.Render_BVH_Path(cam, vars, s, &Renderer::Miss_hw_4_1, &Renderer::Illumination_hw_4_1);
    img = render.GetImage();

    return *img;
}

Image3 hw_4_2(const std::vector<std::string>& params) {
    // Homework 4.2: adding more materials
    if (params.size() < 1) {
        return Image3(0, 0);
    }

    int max_depth = 50;
    std::string filename;
    for (int i = 0; i < (int)params.size(); i++) {
        if (params[i] == "-max_depth") {
            max_depth = std::stoi(params[++i]);
        }
        else if (filename.empty()) {
            filename = params[i];
        }
    }

    int spp = 16;
    Timer timer;
    tick(timer);
    ParsedScene scene = parse_scene(params[0]);
    std::cout << "Scene parsing done. Took " << tick(timer) << " seconds." << std::endl;
    UNUSED(scene);

    UNUSED(spp);
    std::shared_ptr<Image3> img;
    Variables vars;

    vars.max_depth = max_depth; // tracing depth

    Renderer render;

    vars.cameraParameters.width = scene.camera.width;
    vars.cameraParameters.height = scene.camera.height;
    vars.cameraParameters.eye = scene.camera.lookfrom;
    vars.cameraParameters.center = scene.camera.lookat;
    vars.cameraParameters.upvec = scene.camera.up;
    vars.cameraParameters.fovy = scene.camera.vfov;
    vars.cameraParameters.samples_per_pixel = scene.samples_per_pixel;
    //vars.cameraParameters.samples_per_pixel = 128;

    //larger the file, larger the parallel_counts for bvh
    vars.parallel_counts_bvh = 16;
    // enable shading_normal
    vars.shading_normal = true;
    // enable multiple sampling on area lights, must be square
    //vars.area_light_samples = 4 * 4;

    CameraUnion cam = GenerateCameraByType(vars.cameraParameters, PERSPECTIVE_CAM);
    Scene s = ParsedSceneToScene(scene);
    render.Render_BVH_Path(cam, vars, s, &Renderer::Miss_hw_4_2, &Renderer::Illumination_hw_4_2);
    img = render.GetImage();

    return *img;
}

Image3 hw_4_3(const std::vector<std::string>& params) {
    // Homework 4.3: multiple importance sampling
    if (params.size() < 1) {
        return Image3(0, 0);
    }

    int max_depth = 50;
    std::string filename;
    for (int i = 0; i < (int)params.size(); i++) {
        if (params[i] == "-max_depth") {
            max_depth = std::stoi(params[++i]);
        }
        else if (filename.empty()) {
            filename = params[i];
        }
    }

    int spp = 16;
    Timer timer;
    tick(timer);
    ParsedScene scene = parse_scene(params[0]);
    std::cout << "Scene parsing done. Took " << tick(timer) << " seconds." << std::endl;
    UNUSED(scene);

    UNUSED(spp);
    std::shared_ptr<Image3> img;
    Variables vars;

    vars.max_depth = max_depth; // tracing depth

    Renderer render;

    vars.cameraParameters.width = scene.camera.width;
    vars.cameraParameters.height = scene.camera.height;
    vars.cameraParameters.eye = scene.camera.lookfrom;
    vars.cameraParameters.center = scene.camera.lookat;
    vars.cameraParameters.upvec = scene.camera.up;
    vars.cameraParameters.fovy = scene.camera.vfov;
    vars.cameraParameters.samples_per_pixel = scene.samples_per_pixel;
    //vars.cameraParameters.samples_per_pixel = 32;

    //larger the file, larger the parallel_counts for bvh
    vars.parallel_counts_bvh = 16;
    // enable shading_normal
    vars.shading_normal = true;
    // enable multiple sampling on area lights, must be square
    //vars.area_light_samples = 4 * 4;

    CameraUnion cam = GenerateCameraByType(vars.cameraParameters, PERSPECTIVE_CAM);
    Scene s = ParsedSceneToScene(scene);
    render.Render_BVH_Path_One_Sample(cam, vars, s, &Renderer::Miss_hw_4_3, &Renderer::Illumination_hw_4_3);
    img = render.GetImage();

    return *img;
}

Image3 hw_4_4(const std::vector<std::string>& params) {
    // Homework 4.3: multiple importance sampling
    if (params.size() < 1) {
        return Image3(0, 0);
    }

    int max_depth = 50;
    std::string filename;
    for (int i = 0; i < (int)params.size(); i++) {
        if (params[i] == "-max_depth") {
            max_depth = std::stoi(params[++i]);
        }
        else if (filename.empty()) {
            filename = params[i];
        }
    }

    int spp = 16;
    Timer timer;
    tick(timer);
    ParsedScene scene = parse_scene(params[0]);
    std::cout << "Scene parsing done. Took " << tick(timer) << " seconds." << std::endl;
    UNUSED(scene);

    UNUSED(spp);
    std::shared_ptr<Image3> img;
    Variables vars;

    vars.max_depth = max_depth; // tracing depth

    Renderer render;

    vars.cameraParameters.width = scene.camera.width;
    vars.cameraParameters.height = scene.camera.height;
    vars.cameraParameters.eye = scene.camera.lookfrom;
    vars.cameraParameters.center = scene.camera.lookat;
    vars.cameraParameters.upvec = scene.camera.up;
    vars.cameraParameters.fovy = scene.camera.vfov;
    vars.cameraParameters.samples_per_pixel = scene.samples_per_pixel;
    //vars.cameraParameters.samples_per_pixel = 32;

    //larger the file, larger the parallel_counts for bvh
    vars.parallel_counts_bvh = 16;
    // enable shading_normal
    vars.shading_normal = true;
    // enable multiple sampling on area lights, must be square
    //vars.area_light_samples = 4 * 4;

    CameraUnion cam = GenerateCameraByType(vars.cameraParameters, PERSPECTIVE_CAM);
    Scene s = ParsedSceneToScene(scene);
    render.Render_BVH_Path_One_Sample(cam, vars, s, &Renderer::Miss_hw_4_3, &Renderer::Illumination_hw_4_3);
    img = render.GetImage();

    return *img;
}


Image3 hw_4_8(const std::vector<std::string>& params) {
    // Homework 4.8: deterministic multiple importance sampling
    if (params.size() < 1) {
        return Image3(0, 0);
    }

    int max_depth = 50;
    std::string filename;
    for (int i = 0; i < (int)params.size(); i++) {
        if (params[i] == "-max_depth") {
            max_depth = std::stoi(params[++i]);
        }
        else if (filename.empty()) {
            filename = params[i];
        }
    }

    int spp = 16;
    Timer timer;
    tick(timer);
    ParsedScene scene = parse_scene(params[0]);
    std::cout << "Scene parsing done. Took " << tick(timer) << " seconds." << std::endl;
    UNUSED(scene);

    UNUSED(spp);
    std::shared_ptr<Image3> img;
    Variables vars;

    vars.max_depth = max_depth; // tracing depth

    Renderer render;

    vars.cameraParameters.width = scene.camera.width;
    vars.cameraParameters.height = scene.camera.height;
    vars.cameraParameters.eye = scene.camera.lookfrom;
    vars.cameraParameters.center = scene.camera.lookat;
    vars.cameraParameters.upvec = scene.camera.up;
    vars.cameraParameters.fovy = scene.camera.vfov;
    vars.cameraParameters.samples_per_pixel = scene.samples_per_pixel;
    //vars.cameraParameters.samples_per_pixel = 32;

    //larger the file, larger the parallel_counts for bvh
    vars.parallel_counts_bvh = 16;
    // enable shading_normal
    vars.shading_normal = true;
    // enable multiple sampling on area lights, must be square
    //vars.area_light_samples = 4 * 4;

    //enable multiple-sampling MIS 
    vars.multi_sample = true;

    CameraUnion cam = GenerateCameraByType(vars.cameraParameters, PERSPECTIVE_CAM);
    Scene s = ParsedSceneToScene(scene);
    render.Render_BVH_Path_One_Sample(cam, vars, s, &Renderer::Miss_hw_4_3, &Renderer::Illumination_hw_4_3);
    img = render.GetImage();

    return *img;
}
