#include "gfx_test.h"

#include <iostream>
#include <sstream>

GfxTest::GfxTest() : GraphicsApp(1024,768, "GfxTest"), playing_(true) {
    // Setup the GUI window
    nanogui::Window *window = new nanogui::Window(screen(), "Controls");
    window->setPosition(Eigen::Vector2i(10, 10));
    window->setSize(Eigen::Vector2i(400,200));
    window->setLayout(new nanogui::GroupLayout());
    
    pauseBtn_ = new nanogui::Button(window, "Pause");
    pauseBtn_->setCallback(std::bind(&GfxTest::OnPauseBtnPressed, this));
    pauseBtn_->setTooltip("Toggle playback.");
        
    screen()->performLayout();
 }


GfxTest::~GfxTest() {
}


void GfxTest::OnPauseBtnPressed() {
    playing_ = !playing_;
    if (playing_) {
        pauseBtn_->setCaption("Pause");
    }
    else {
        pauseBtn_->setCaption("Play");
    }
}


void GfxTest::UpdateSimulation(double dt)  {
    static const float radiansPerSec = to_radians(25.0);
    if (playing_) {
        rotMatrix_ = rotMatrix_ * Matrix4::rotationY(dt * radiansPerSec);
    }
}


void GfxTest::InitOpenGL() {
    // Set up the camera in a good position to see the entire field
    projMatrix_ = Matrix4::perspective(60, aspect_ratio(), 0.01, 100);
    viewMatrix_ = Matrix4::lookAt(Point3(0,0,4), Point3(0,0,0), Vector3(0,1,0));
    glClearColor(0.0, 0.0, 0.0, 1);
    
    teapotMesh_.LoadFromOBJ(Platform::findMinGfxDataFile("teapot.obj"));
    
    phongShader_.AddVertexShaderFromFile(Platform::findMinGfxShaderFile("phong.vert"));
    phongShader_.AddFragmentShaderFromFile(Platform::findMinGfxShaderFile("phong.frag"));
    phongShader_.LinkProgram();
}


void GfxTest::DrawUsingOpenGL() {
    phongShader_.UseProgram();
    phongShader_.SetUniform("ViewMatrix", viewMatrix_);
    phongShader_.SetUniform("ProjectionMatrix", projMatrix_);
    phongShader_.SetUniform("LightPosition", Point3(10,10,10));
    phongShader_.SetUniform("LightIntensityAmbient", Color(0.2, 0.2, 0.2));
    phongShader_.SetUniform("LightIntensityDiffuse", Color(0.7, 0.7, 0.7));
    phongShader_.SetUniform("LightIntensitySpecular", Color(0.6, 0.6, 0.6));
    phongShader_.SetUniform("MatReflectanceAmbient", Color(0.2, 0.2, 0.2));
    phongShader_.SetUniform("MatReflectanceDiffuse", Color(0.5, 0.5, 0.5));
    phongShader_.SetUniform("MatReflectanceSpecular", Color(0.6, 0.6, 0.6));
    phongShader_.SetUniform("MatReflectanceShininess", 20.0f);

    for (int r=-2; r<3; r++) {
        for (int c=-2; c<3; c++) {
            Matrix4 modelMatrix = Matrix4::translation(Vector3(r,c,0)) * rotMatrix_;
            Matrix4 normalMatrix = (modelMatrix*viewMatrix_).inverse().transpose();
            phongShader_.SetUniform("ModelMatrix", modelMatrix);
            phongShader_.SetUniform("NormalMatrix", normalMatrix);
            teapotMesh_.Draw();
        }
    }

    phongShader_.StopProgram();
}





