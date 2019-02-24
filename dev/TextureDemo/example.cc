/** CSci-4611 In-Class Example */

#include "example.h"

#include "config.h"

#include <iostream>
#include <sstream>



Example::Example() : GraphicsApp(1024,768, "MinGfx Example") {
    // Define a search path for finding data files (images and shaders)
    search_path_.push_back(".");
    search_path_.push_back("./data");
    search_path_.push_back(DATA_DIR_INSTALL);
    search_path_.push_back(DATA_DIR_BUILD);
}


Example::~Example() {
}


void Example::UpdateSimulation(double dt)  {
}


void Example::InitOpenGL() {
    // Set up the camera in a good position to see the entire scene
    proj_matrix_ = Matrix4::Perspective(60, aspect_ratio(), 0.01, 100);
    view_matrix_ = Matrix4::LookAt(Point3(2,1,4), Point3(2,1,0), Vector3(0,1,0));
    glClearColor(1,1,1,1);
    
    
    // Load the texture we will use
    texture_.InitFromFile(Platform::FindFile("monalisa.bmp", search_path_));
    
     
    // Create the mesh by setting the vertex and index arrays directly
    std::vector<unsigned int> indices;
    std::vector<Point3> vertices;
    std::vector<Vector3> normals;
    std::vector<Point2> tex_coords;
    
    // four vertices, each requires 3 floats: (x,y,z)
    vertices.push_back(Point3(0,0,0));
    vertices.push_back(Point3(1,0,0));
    vertices.push_back(Point3(1,1,-1));
    vertices.push_back(Point3(0,1,-1));
    
    // four normals, each requires 3 floats: (x,y,z)
    normals.push_back(Vector3(0,1,1).ToUnit());
    normals.push_back(Vector3(0,1,1).ToUnit());
    normals.push_back(Vector3(0,1,1).ToUnit());
    normals.push_back(Vector3(0,1,1).ToUnit());
    
    // TODO: YOU ADD TEXTURE COORDINATES TO THE MESH

    
    
    // indices into the arrays above for the first triangle
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    
    // indices for the second triangle, note some are reused
    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(3);
    
    mesh_.SetVertices(vertices);
    mesh_.SetNormals(normals);
    mesh_.SetIndices(indices);
    
    // TODO: ALSO REMEMBER TO CALL mesh_.SetTexCoords(..) HERE ONCE YOU HAVE THEM DEFINED.
    // USE TEXTURE UNIT = 0 SINCE WE HAVE ONLY ONE TEXTURE APPLIED TO THE MESH.
    
    mesh_.UpdateGPUMemory();
    
}


void Example::DrawUsingOpenGL() {
    // draws a set of axes at the world origin, since we are passing the identity
    // matrix for the "model" matrix.
    Matrix4 identity;
    quick_shapes_.DrawAxes(identity, view_matrix_, proj_matrix_);
    
    
    // We're already learned about how to use transformation matrices to move
    // an individual model around within the scene.
    Matrix4 model_matrix = Matrix4::Scale(Vector3(4,4,4));

    
    // Since we want to texture the mesh we will define a custom material for the
    // mesh.  The material property we are interested in is called "surface_texture".
    // We'll set that to point to the Texture2D that we loaded earlier.  You can
    // also set other properties of the material to define how it reflects light.
    DefaultShader::MaterialProperties mesh_material;
    mesh_material.surface_texture = texture_;
    mesh_material.ambient_reflectance = Color(0.8,0.8,0.8);
    mesh_material.diffuse_reflectance = Color(0.8,0.8,0.8);
    
    
    // Use a shader program to draw the mesh with the given model, view, and projection
    // matrices and with the material properties defined in mesh_material.
    shader_.Draw(model_matrix, view_matrix_, proj_matrix_, &mesh_, mesh_material);
}




