#ifndef DRAW_HPP
#define DRAW_HPP

#include "graphics.hpp"
using glm::vec3;

namespace Draw {

    void axes();
    void arrow(vec3 base, vec3 vector, float thick);
    void unitCube();
    void unitSphere();
    void unitCircleXY();
    void sphere(vec3 p, float r);

    // Definitions below

    inline void axes() {
        glBegin(GL_TRIANGLES);
        glColor3f(1,0,0);
        glVertex3f(0,-0.2,0);
        glVertex3f(1, 0.0,0);
        glVertex3f(0,+0.2,0);
        glColor3f(0,1,0);
        glVertex3f(0,0,-0.2);
        glVertex3f(0,1, 0.0);
        glVertex3f(0,0,+0.2);
        glColor3f(0,0,1);
        glVertex3f(-0.2,0,0);
        glVertex3f( 0.0,0,1);
        glVertex3f(+0.2,0,0);
        glEnd();
    }

    inline void arrow(vec3 base, vec3 vector, float thick) {
        float vnorm = glm::length(vector);
        if (vnorm == 0)
            return;
        glPushMatrix();
        glTranslatef(base.x,base.y,base.z);
        vec3 vhat = vector/vnorm;
        vec3 w = glm::cross(vec3(0,0,1), vhat);
        float angle = acos(vhat.z);
        if (glm::length(w) > 0)
            glRotatef(angle*180/M_PI, w.x,w.y,w.z);
        GLUquadric* quadric = gluNewQuadric();
        gluCylinder(quadric, thick,thick, vnorm-6*thick, 30,1);
        glTranslatef(0,0,vnorm-6*thick);
        gluCylinder(quadric, 2*thick,0, 6*thick, 30,1);
        gluDeleteQuadric(quadric);
        glPopMatrix();
    }

    inline void unitCube() {
        vec3 verts[8] = {
            vec3(0,0,0),
            vec3(1,0,0),
            vec3(0,1,0),
            vec3(1,1,0),
            vec3(0,0,1),
            vec3(1,0,1),
            vec3(0,1,1),
            vec3(1,1,1)
        };
        int faces[6][4] = {
            {0,2,3,1},
            {0,4,6,2},
            {0,1,5,4},
            {4,5,7,6},
            {1,3,7,5},
            {2,6,7,3}
        };
        glBegin(GL_QUADS);
        for (int f = 0; f < 6; f++) {
            for (int i = 0; i < 4; i++) {
                vec3 v = verts[faces[f][i]];
                glVertex3f(v.x,v.y,v.z);
            }
        }
        glEnd();
    }

    inline void unitSphere() {
        GLUquadric* quadric = gluNewQuadric();
        gluSphere(quadric, 1, 40, 40);
        gluDeleteQuadric(quadric);
    }

    inline void unitCircleXY() {
        int n = 30;
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < n; i++) {
            float t = 2*M_PI*i/n;
            glVertex3f(cos(t),sin(t),0);
        }
        glEnd();
    }

    inline void sphere(vec3 p, float r) {
        glPushMatrix();
        glTranslatef(p.x,p.y,p.z);
        glScalef(r,r,r);
        unitSphere();
        glPopMatrix();
    }

}

#endif
