#include"renderer/renderer.h"
#include<iostream>
#include<vector>
using namespace YeahooQAQ;

int main(int argc, char* argv[]){
    Renderer renderer(1000, 1000, Vec3f(0.0f, 0.0f, 0.0f));
    vector<PointLight> lights{
        {Vec3f(0, 3, 0),Vec3f(1.0f, 1.0f, 1.0f)},
        {Vec3f(0, 3, -5),Vec3f(1.0f, 1.0f, 1.0f)},
        {Vec3f(0, -3, 0),Vec3f(1.0f, 1.0f, 1.0f)},      
        {Vec3f(-2, 0, 0),Vec3f(1.0f, 0.0f, 0.0f)}, 
        {Vec3f(0, 2, 0),Vec3f(0.0f, 1.0f, 0.0f)},     
        {Vec3f(0, 0, -2),Vec3f(0.0f, 0.0f, 1.0f)},  
        {Vec3f(-2, -2, 2),Vec3f(1.0f, 1.0f, 0.0f)}, 
        {Vec3f(2, -2, -2),Vec3f(0.0f, 1.0f, 1.0f)},
        {Vec3f(-2, 2, -2),Vec3f(1.0f, 0.0f, 1.0f)}
    };
    IShader* Shader_ptr = new TextureShader;
    renderer.SetShader(Shader_ptr);    
    renderer.LoadModel("../test_model/cow/cow.obj", "../test_model/cow/cow.png");
    renderer.LoadPointLights(lights);
    renderer.RenderModel(true);
    Vec3f eye_pos(0.0f, 0.0f, -6.0f);
    float theta_per_second = 2.0f;
    int count = 0;
    char key = '0';
    renderer.ShowProcessing(false);
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
        renderer.SetModelMatrix(25.0, count * theta_per_second, 0.0f);
        renderer.SetViewMatrix(eye_pos);
        renderer.SetProjectionMatrix(45.0f, 1.0f, 0.1, 50.0f);   

        renderer.MvpTransforme();

        renderer.Rendering();

        renderer.GetTimeCost();
        renderer.ShowImage("Rendering", 20);
        renderer.ClearTimeCounter();
        count++;
    }

    renderer.SaveImage("../output0.jpg");
    return 0;
}