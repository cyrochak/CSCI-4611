/** CSci-4611 In-Class Example */

#ifndef SNOWMAN_H_
#define SNOWMAN_H_

#include <mingfx.h>

#include <string>
#include <vector>

class Example : public GraphicsApp {
public:
  
    // Creates the App
    Example();
    
    // Cleans up when the App shuts down
    virtual ~Example();
    
    // Note a Run() function is inherited from GraphicsApp, that's what
    // actually starts up the App.
    
    // This is a callback, a function that gets called when the user presses
    // the Pause button in the GUI.
    void OnPauseBtnPressed();
    
    // This gets called once each frame.  Note that dt (a.k.a., "delta time") is
    // the amount of time (in seconds) that has passed since the last frame.
    void UpdateSimulation(double dt);
    
    // This is where we initialize any OpenGL data, like textures or meshes that
    // need to be loaded from files and setup in OpenGL.  It gets called once
    // when the program starts up.
    void InitOpenGL();
    
    // This gets called once each frame, and this is where you draw the latest
    // version of your 3D graphics scene.
    void DrawUsingOpenGL();
    
    
private:

    // Texture loaded from a file
    Texture2D texture_;
    
    // Triangle mesh data structure
    Mesh mesh_;

    // A shader is required to draw meshes, MinGfx provides a default shader
    // that does some simple lighting.
    DefaultShader shader_;
    
    // Sets up the computer graphics camera
    Matrix4 view_matrix_;
    Matrix4 proj_matrix_;
    
    // A helper class for drawing some simple shapes (cubes, spheres, 3D arrows)
    QuickShapes quick_shapes_;
    
    // Paths to search for data files, like images
    std::vector<std::string> search_path_;
};

#endif