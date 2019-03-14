#include <utils.h>

#include <cmath>
#include <exception>
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <SuperimposeMesh/SICAD.h>


int main()
{
    std::string log_ID = "[Test - SICAD]";
    std::cout << log_ID << "This test checks whether the present machine can render properly using OpenGL." << std::endl;
    std::cout << log_ID << "A single mesh will be rendered on 1 viewport." << std::endl;

    SICAD::ModelPathContainer obj;
    obj.emplace("alien", "./Space_Invader.obj");

    const unsigned int cam_width  = 320;
    const unsigned int cam_height = 240;
    const float        cam_fx     = 257.34;
    const float        cam_cx     = 160;
    const float        cam_fy     = 257.34;
    const float        cam_cy     = 120;

    SICAD si_cad(obj,
                 cam_width, cam_height,
                 cam_fx, cam_fy, cam_cx, cam_cy,
                 1,
                 ".");

    Superimpose::ModelPose obj_pose(7);
    obj_pose[0] = 0;
    obj_pose[1] = 0;
    obj_pose[2] = -0.1;
    obj_pose[3] = 0;
    obj_pose[4] = 1.0;
    obj_pose[5] = 0;
    obj_pose[6] = 0;

    Superimpose::ModelPoseContainer objpose_map;
    objpose_map.emplace("alien", obj_pose);

    double cam_x[] = { 0, 0, 0 };
    double cam_o[] = { 1.0, 0, 0, 0 };


    cv::Mat img_rendered_1;

    si_cad.superimpose(objpose_map, cam_x, cam_o, img_rendered_1);

    cv::Mat img_ground_truth_1 = cv::imread("./gt_sicad_alien.png");

    if (!utils::compareImages(img_rendered_1, img_ground_truth_1))
    {
        std::cerr << log_ID << " Rendered and ground truth images are different." << std::endl;

        return EXIT_FAILURE;
    }

    std::cout << log_ID << " Rendered and ground truth images are identical. Saving rendered image for visual inspection." << std::endl;
    cv::imwrite("./test_sicad_alien.png", img_rendered_1);


    cv::Mat img_rendered_2 = cv::imread("./space.png");

    si_cad.setBackgroundOpt(true);
    si_cad.superimpose(objpose_map, cam_x, cam_o, img_rendered_2);

    cv::Mat img_ground_truth_2 = cv::imread("./gt_sicad_alien_space.png");

    if (!utils::compareImages(img_rendered_2, img_ground_truth_2))
    {
        std::cerr << log_ID << " Rendered and ground truth images are different." << std::endl;

        return EXIT_FAILURE;
    }

    std::cout << log_ID << " Rendered and ground truth images are identical. Saving rendered image for visual inspection." << std::endl;

    cv::imwrite("./test_sicad_alien_space.png", img_rendered_2);

    return EXIT_SUCCESS;
}
