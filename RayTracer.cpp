#include"renderer/renderer.h"
#include<iostream>
#include<vector>
using namespace LemonCube;

int main(){
    Renderer renderer(400, 400, Vec3f(0.0f, 0.0f, 0.0f));
    Vec3f eye_pos(0.0f, 2.0f, -16.0f);
    shared_ptr<Material> red = make_shared<Lambertian>(Vec3f(1.0f, 0.0f, 0.0f));
    shared_ptr<Material> green = make_shared<Lambertian>(Vec3f(0.0f, 1.0f, 0.0f));
    shared_ptr<Material> blue = make_shared<Lambertian>(Vec3f(0.0f, 0.0f, 1.0f));
    shared_ptr<Material> white = make_shared<Lambertian>(Vec3f(1.0f, 1.0f, 1.0f));
    vector<shared_ptr<Hitable>> obj_ptr{
        make_shared<Sphere>(Vec3f(0.0f, 3.0f, 0.0f), 3.0f, red),
        make_shared<Sphere>(Vec3f(-4.0f, 1.0f, -4.0f), 1.0f, blue),
        make_shared<Sphere>(Vec3f(2.0f, 5.0f, -7.0f), 1.0f, green),
        make_shared<Sphere>(Vec3f(4.0f, 1.0f, -1.0f), 1.0f, blue),
        make_shared<Sphere>(Vec3f(0.0f, -200.0f, 0.0f), 200.0f, white)
    };
    renderer.LoadObjectPtr(obj_ptr);
    renderer.SetProjectionMatrix(90.0f, 1.0f, 1.0f, 50.0f);
    renderer.MSAA(true, 100);   
    float theta = 0.0f;
    float theta_per_second = 0.03f;
    char key = '0';
    while((key = cv::waitKey(2)) != ' '){
        if(key == 'w'){
            eye_pos.z += 0.2f;
        }
        else if(key == 's'){
            eye_pos.z -= 0.2f;
        }
        else if(key == 'a'){
            eye_pos.x -= 0.2f;
        }
        else if(key == 'd'){
            eye_pos.x += 0.2f;
        }

        renderer.StartClock();

        renderer.ClearCanvas();
        renderer.SetModelMatrix(sin(theta+=theta_per_second)*10.0f, theta, 0.0f);

        renderer.SetViewMatrix(eye_pos);
        renderer.MvpTransforme();
        renderer.RayTracing(50);

        renderer.GetTimeCost();
        renderer.ShowImage("RayTracing", 3);
        renderer.ClearTimeCounter();
    }
    
    renderer.SaveImage("../output0.jpg");
    return 0;
}