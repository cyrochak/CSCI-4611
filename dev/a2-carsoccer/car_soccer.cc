/** CSci-4611 Assignment 2:  Car Soccer
 */

#include "car_soccer.h"
#include "config.h"


CarSoccer::CarSoccer() : GraphicsApp(1024,768, "Car Soccer") {
    // Define a search path for finding data files (images and shaders)
    searchPath_.push_back(".");
    searchPath_.push_back("./data");
    searchPath_.push_back(DATA_DIR_INSTALL);
    searchPath_.push_back(DATA_DIR_BUILD);
}

CarSoccer::~CarSoccer() {
}


Vector2 CarSoccer::joystick_direction() {
    Vector2 dir;
    if (IsKeyDown(GLFW_KEY_LEFT))
        dir[0]--;
    if (IsKeyDown(GLFW_KEY_RIGHT))
        dir[0]++;
    if (IsKeyDown(GLFW_KEY_UP))
        dir[1]++;
    if (IsKeyDown(GLFW_KEY_DOWN))
        dir[1]--;
    return dir;
}


void CarSoccer::OnSpecialKeyDown(int key, int scancode, int modifiers) {
    if (key == GLFW_KEY_SPACE) {
        // Here's where you could call some form of launch_ball();
        ball_.Reset();
    }
}

Vector3 reflectVec( Vector3 v, Vector3 n){
    return ( v - n*(float)(2 * v.Dot(n)));
}
void CarSoccer::UpdateSimulation(double timeStep) {
    // Here's where you shound do your "simulation", updating the positions of the
    // car and ball as needed and checking for collisions.  Filling this routine
    // in is the main part of the assignment.
    Vector2 joy = joystick_direction();
    car_.set_position(car_.position() + 0.1*Vector3(joy[0], 0, -joy[1]));
    
   
    ball_.set_position(ball_.position() + (ball_.speed()* timeStep));
    Vector3 g = Vector3(0, timeStep * 0.0098, 0);
    ball_.set_speed(ball_.speed() - g);
   
//    if ( car_.position()[1] -1 < 0)
//    {
//        car_.position()[1] = 1;
//        car_.vel() = Vector3(0,0,0);
//    } else if ((car_.position()[1] -1 ) == 0)
//    {
//        car_.vel()[1] = 100 * timeStep + car_.vel()[1];
//        car_.position()[1] += car_.vel()[1] * timeStep;
//    } else {
//        car_.vel()[1] = 5* timeStep;
//        car_.position()[1] += car_.vel()[1] * timeStep;
//    }
     Vector3 diff = car_.position() - ball_.position();
    float radius_sum = car_.collision_radius() + ball_.radius();
    Vector3 collNorm, relVel;
     float diffLength = diff.Length();
    if (diffLength <= radius_sum){
        collNorm = (ball_.position() - car_.position())/ diffLength;
        if (diffLength < radius_sum){
            ball_.position()[0] += collNorm[0]* (radius_sum - diffLength);
            ball_.position()[1] += collNorm[1]* (radius_sum - diffLength);
            ball_.position()[2] += collNorm[2]* (radius_sum - diffLength);
        }
        relVel = ball_.speed() - car_.vel();
        relVel = reflectVec(relVel,collNorm);
        ball_.speed() = car_.vel() + relVel;
    }
    
}


void CarSoccer::InitOpenGL() {
    // Set up the camera in a good position to see the entire field
    projMatrix_ = Matrix4::Perspective(60, aspect_ratio(), 1, 1000);
    modelMatrix_ = Matrix4::LookAt(Point3(0,60,70), Point3(0,0,10), Vector3(0,1,0));
 
    // Set a background color for the screen
    glClearColor(0.8,0.8,0.8, 1);
    
    // Load some image files we'll use
    fieldTex_.InitFromFile(Platform::FindFile("pitch.png", searchPath_));
    crowdTex_.InitFromFile(Platform::FindFile("crowd.png", searchPath_));
}


void CarSoccer::DrawUsingOpenGL() {
    // Draw the crowd as a fullscreen background image
    quickShapes_.DrawFullscreenTexture(Color(1,1,1), crowdTex_);
    
    // Draw the field with the field texture on it.
    Color col(16.0/255.0, 46.0/255.0, 9.0/255.0);
    Matrix4 M = Matrix4::Translation(Vector3(0,-0.201,0)) * Matrix4::Scale(Vector3(50, 1, 60));
    quickShapes_.DrawSquare(modelMatrix_ * M, viewMatrix_, projMatrix_, col);
    M = Matrix4::Translation(Vector3(0,-0.2,0)) * Matrix4::Scale(Vector3(40, 1, 50));
    quickShapes_.DrawSquare(modelMatrix_ * M, viewMatrix_, projMatrix_, Color(1,1,1), fieldTex_);
    
    // Draw the car
    Color carcol(0.8, 0.2, 0.2);
    Matrix4 Mcar =
        Matrix4::Translation(car_.position() - Point3(0,0,0)) *
        Matrix4::Scale(car_.size()) *
        Matrix4::Scale(Vector3(0.5,0.5,0.5));
    quickShapes_.DrawCube(modelMatrix_ * Mcar, viewMatrix_, projMatrix_, carcol);
    
    
    // Draw the ball
    Color ballcol(1,1,1);
    Matrix4 Mball =
        Matrix4::Translation(ball_.position() - Point3(0,0,0)) *
        Matrix4::Scale(Vector3(ball_.radius(), ball_.radius(), ball_.radius()));
    quickShapes_.DrawSphere(modelMatrix_ * Mball, viewMatrix_, projMatrix_, ballcol);
    
    
    // Draw the ball's shadow -- this is a bit of a hack, scaling Y by zero
    // flattens the sphere into a pancake, which we then draw just a bit
    // above the ground plane.
    Color shadowcol(0.2,0.4,0.15);
    Matrix4 Mshadow =
        Matrix4::Translation(Vector3(ball_.position()[0], -0.1, ball_.position()[2])) *
        Matrix4::Scale(Vector3(ball_.radius(), 0, ball_.radius())) *
        Matrix4::RotationX(90);
    quickShapes_.DrawSphere(modelMatrix_ * Mshadow, viewMatrix_, projMatrix_, shadowcol);
    
    
    // You should add drawing the goals and the boundary of the playing area
    // using quickShapes_.DrawLines()
    Color Boundarycol(1,1,1);
    Matrix4 MBoundary;
    std::vector<Point3> loop;
    loop.push_back(Point3(40,0,50));
    loop.push_back(Point3(40, 0, -50));
    loop.push_back(Point3(-40, 0, -50));
    loop.push_back(Point3(-40, 0, 50));
    loop.push_back(Point3(40, 0, 50));
    loop.push_back(Point3(40, 35, 50));
    loop.push_back(Point3(40, 0, 50));
    loop.push_back(Point3(40, 35, 50));
    loop.push_back(Point3(40, 35, -50));
    loop.push_back(Point3(40, 0, -50));
    loop.push_back(Point3(40, 35, -50));
    loop.push_back(Point3(-40, 35, -50));
    loop.push_back(Point3(-40, 0, -50));
    loop.push_back(Point3(-40, 35, -50));
    loop.push_back(Point3(-40, 35, 50));
    loop.push_back(Point3(-40, 0, 50));
    loop.push_back(Point3(-40, 35, 50));
    loop.push_back(Point3(40, 35, 50));
    quickShapes_.DrawLines(modelMatrix_ *MBoundary, viewMatrix_, projMatrix_,Boundarycol,loop,QuickShapes::LinesType::LINE_LOOP, 0.1);
}
