/** CSci-4611 Assignment 2:  Car Soccer
 */

#ifndef BALL_H_
#define BALL_H_

#include <mingfx.h>

/// Small data structure for a ball
class Ball {
public:
    
    /// The constructor sets the radius and calls Reset() to start the ball at
    /// the center of the field
    Ball() : radius_(2.0), speed_(0,1,0) {
        Reset();
    }
    
    /// Nothing special needed in the constructor
    virtual ~Ball() {}

    
    void Reset() {
        position_ = Point3(0, radius_, 0);
        speed_ = Vector3(0,0,1);
    }

    float radius() { return radius_; }
    
    Point3 position() { return position_; }
    void set_position(const Point3 &p) { position_ = p; }
    
    Vector3 speed() { return speed_;}
    void set_speed(const Vector3 sp) { speed_ = sp;}
    
    
private:
    // You will probably need to store some additional data here, e.g., velocity
    
    Point3 position_;
    float radius_;
    Vector3 speed_;
};

#endif
