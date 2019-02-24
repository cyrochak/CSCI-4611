#ifndef GFX_TEST_H_
#define GFX_TEST_H_

#include <mingfx.h>

#include <string>
#include <vector>

class GfxTest : public GraphicsApp {
public:
  
    GfxTest();
    virtual ~GfxTest();
    
    void OnPauseBtnPressed();
    
    void UpdateSimulation(double dt);
    
    void InitOpenGL();
    
    void DrawUsingOpenGL();
      
private:    
    
    // Sets up the computer graphics camera
    Matrix4 rotMatrix_;
    Matrix4 viewMatrix_;
    Matrix4 projMatrix_;
    
    Mesh teapotMesh_;
    ShaderProgram phongShader_;

    // Gui elements
    nanogui::Button  *pauseBtn_;
    bool playing_;
};

#endif