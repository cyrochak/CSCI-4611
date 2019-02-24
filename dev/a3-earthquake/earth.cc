/** CSci-4611 Assignment 3:  Earthquake
 */

#include "earth.h"
#include "config.h"

#include <vector>

// for M_PI constant
#define _USE_MATH_DEFINES
#include <math.h>


Earth::Earth() {
}

Earth::~Earth() {
}

void Earth::Init(const std::vector<std::string> &search_path) {
    // init shader program
    shader_.Init();
    
    // init texture: you can change to a lower-res texture here if needed
    earth_tex_.InitFromFile(Platform::FindFile("earth-2k.png", search_path));

    // init geometry
    const int nslices = 10;
    const int nstacks = 10;

    // TODO: This is where you need to set the vertices and indiceds for earth_mesh_.
    
    // As a demo, we'll add a square with 2 triangles.
    std::vector<unsigned int> indices;
    std::vector<Point3> vertices;
    std::vector<Point3> normals;
    std::vector<Point2> texCoords;
    
    float x_ = 360.0 / nslices;
    float y_ = 180.0 / nstacks;
    
    for (float y = 90; y >= -90; y -= y_) {
        for (float x = -180; x <= 180; x += x_) {
            vertices.push_back(LatLongToPlane(y, x));
            normals.push_back(LatLongToNormal(y, x));
            texCoords.push_back(Point2(x/360.0 +0.5,-1.0*(y/180)+0.5));
        }
    }
    int top = 0;
    int bot = 0;

    for (int y = 0; y < nstacks; y++) { 
        for (int x = 0; x < nslices ; x++) {
            top = y*(nslices + 1) + x;
            bot = (y+1)*(nslices + 1) + x;


            indices.push_back(top);
            indices.push_back(bot);
            indices.push_back(bot + 1);

            indices.push_back(top);
            indices.push_back(bot + 1);
            indices.push_back(top + 1);
            
        }
    }

    earth_mesh_.SetVertices(vertices);
   // earth_mesh_.SetNormals(normals);
    earth_mesh_.SetIndices(indices);
    earth_mesh_.SetTexCoords(0, texCoords);
    earth_mesh_.UpdateGPUMemory();
}



void Earth::Draw(const Matrix4 &model_matrix, const Matrix4 &view_matrix, const Matrix4 &proj_matrix) {
    // Define a really bright white light.  Lighting is a property of the "shader"
    DefaultShader::LightProperties light;
    light.position = Point3(10,10,10);
    light.ambient_intensity = Color(1,1,1);
    light.diffuse_intensity = Color(1,1,1);
    light.specular_intensity = Color(1,1,1);
    shader_.SetLight(0, light);

    // Adust the material properties, material is a property of the thing
    // (e.g., a mesh) that we draw with the shader.  The reflectance properties
    // affect the lighting.  The surface texture is the key for getting the
    // image of the earth to show up.
    DefaultShader::MaterialProperties mat;
    mat.ambient_reflectance = Color(0.5, 0.5, 0.5);
    mat.diffuse_reflectance = Color(0.75, 0.75, 0.75);
    mat.specular_reflectance = Color(0.75, 0.75, 0.75);
    mat.surface_texture = earth_tex_;

    // Draw the earth mesh using these settings
    if (earth_mesh_.num_triangles() > 0) {
        shader_.Draw(model_matrix, view_matrix, proj_matrix, &earth_mesh_, mat);
    }
}


Point3 Earth::LatLongToSphere(double latitude, double longitude) const {
    // TODO: We recommend filling in this function to put all your
    // lat,long --> sphere calculations in one place.
    Point3 SphPos(0,0,0);
    float lat = latitude / 180 * M_PI;
    float lon = longitude / 180 * M_PI;
    SphPos = Point3(cos(lat)*sin(lon), sin(lat),cos(lat)* cos(lon));
    return SphPos;
}

Point3 Earth::LatLongToPlane(double latitude, double longitude) const {
    // TODO: We recommend filling in this function to put all your
    // lat,long --> plane calculations in one place.
    Point3 RecPos(0,0,0);
    RecPos = Point3(longitude / 180 * M_PI, latitude /180 * M_PI, 0);
    return RecPos;
}
bool spherical = false;

float isSphere() { return spherical;}

Point3 Earth::LatLongToNormal( double latitude, double longitude) const {
    Point3 recNorm(0,0,0), SphNorm(0,0,0);
    recNorm[2] = 1;
    SphNorm = LatLongToSphere(latitude, longitude) - Vector3(0, 0, 0);
    double temp = sqrt(pow(SphNorm[0],2) + pow(SphNorm[1],2) + pow(SphNorm[2],2));
    SphNorm[0] = SphNorm[0]/temp;
    SphNorm[1] = SphNorm[1]/temp;
    SphNorm[2] = SphNorm[2]/temp;
    if ( spherical == true){
        return SphNorm;
    } else {
        return recNorm;
    }
}


void Earth::DrawDebugInfo(const Matrix4 &model_matrix, const Matrix4 &view_matrix, const Matrix4 &proj_matrix) {
    // This draws a cylinder for each line segment on each edge of each triangle in your mesh.
    // So it will be very slow if you have a large mesh, but it's quite useful when you are
    // debugging your mesh code, especially if you start with a small mesh.
    for (int t=0; t<earth_mesh_.num_triangles(); t++) {
        std::vector<unsigned int> indices = earth_mesh_.triangle_vertices(t);
        std::vector<Point3> loop;
        loop.push_back(earth_mesh_.vertex(indices[0]));
        loop.push_back(earth_mesh_.vertex(indices[1]));
        loop.push_back(earth_mesh_.vertex(indices[2]));
        quick_shapes_.DrawLines(model_matrix, view_matrix, proj_matrix,
            Color(1,1,0), loop, QuickShapes::LinesType::LINE_LOOP, 0.005);
    }
}

