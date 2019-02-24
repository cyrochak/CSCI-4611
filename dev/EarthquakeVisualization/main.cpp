#include "engine.hpp"
#include "camera.hpp"
#include "config.hpp"
#include "draw.hpp"
#include "earth.hpp"
#include "quake.hpp"
#include "text.hpp"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <iomanip>
#include <algorithm>

using namespace std;
using glm::vec3;
using glm::vec4;

const int slices = 60;
const int stacks = 30;

class QuakeVis: public Engine {
public:

    SDL_Window *window;
    OrbitCamera camera;

    Earth earth;
    int visualizeMesh;
    EarthquakeDatabase qdb;

    float currentTime;
    bool playing;
    float playSpeed;

    float sphericalValue;
    float sphericalSpeed;
    Text text;

    QuakeVis() {
        window = createWindow("Earthquake Visualization", 1280, 720);
        camera = OrbitCamera(5, 0, 0, Perspective(40, 16/9., 0.1, 10));
        sphericalValue = 0;
        sphericalSpeed = -1;
        earth.initialize(this, slices, stacks, sphericalValue);
        visualizeMesh = 1;
        qdb = EarthquakeDatabase(Config::quakeFile);
		if (!qdb.fileFound){
			errorMessage(("Failed to open earthquake file " + Config::quakeFile).c_str());
			exit(EXIT_FAILURE);
		}
        playSpeed = 30*24*3600;
        currentTime = qdb.getByIndex(qdb.getMinIndex()).getDate().asSeconds();
        playing = true;
        text.initialize();
    }

    ~QuakeVis() {
        SDL_DestroyWindow(window);
    }

    void run() {
        float fps = 60, dt = 1/fps;
        while (!shouldQuit()) {
            handleInput();
            advanceState(dt);
            drawGraphics();
            waitForNextFrame(dt);
        }
    }

    void advanceState(float dt) {
        if (playing) {
            currentTime += playSpeed * dt;
            float minTime = qdb.getByIndex(qdb.getMinIndex()).getDate().asSeconds(),
                  maxTime = qdb.getByIndex(qdb.getMaxIndex()).getDate().asSeconds();
            if (currentTime > maxTime)
                currentTime = minTime;
            if (currentTime < minTime)
                currentTime = maxTime;
        }

        sphericalValue += sphericalSpeed * dt;
        sphericalValue = (sphericalValue < 0 ? 0 : sphericalValue);
        sphericalValue = (sphericalValue > 1 ? 1 : sphericalValue);
        earth.setSpherical(sphericalValue);
    }

    void addLight(GLenum light, vec4 position, vec3 color) {
        glEnable(light);
        glLightfv(light, GL_POSITION, &position[0]);
        glLightfv(light, GL_DIFFUSE, &color[0]);
    }

    void drawGraphics() {
        // Black background
        glClearColor(0,0,0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Allow lines to show up on top of filled polygons
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(1,1);
        // Light at camera origin
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glEnable(GL_LIGHTING);
        addLight(GL_LIGHT0, vec4(0,0,0,1), vec3(0.8,0.8,0.8));
        // Apply camera transformation
        camera.apply();
        // Draw earth
        if (visualizeMesh == 0) {
            glColor3f(1,1,1);
            earth.draw(0);
            glColor3f(0.5,0.5,1);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            earth.draw(0);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        } else {
            glColor3f(1,1,1);
            earth.draw(visualizeMesh);
        }
        // Draw quakes
        int start = qdb.getIndexByDate(Date(currentTime - Config::timeWindow));
        int end = qdb.getIndexByDate(Date(currentTime));
        for (int i = start; i <= end; i++) {
            Earthquake e = qdb.getByIndex(i);
            vec3 pos = earth.getPosition(e.getLatitude(), e.getLongitude());
            float ballsize = e.getMagnitude() / 300.0;
            float mul_size = (currentTime - e.getDate().asSeconds()) / Config::timeWindow;
            ballsize *= 1.0 - mul_size;
            if (e.getMagnitude() < 7.0)
              glColor3f(0.8,0.2,0.2);
            else
              glColor3f(0.8,0.2,0.8);
            glPushMatrix();
            glTranslatef(pos.x, pos.y, pos.z);
            glScalef(ballsize, ballsize, ballsize);
            Draw::unitSphere();
            glPopMatrix();

            // TODO: Draw an earthquake

        }
        // Draw current date
        Date d(currentTime);
        stringstream s;
        s << std::right << std::setfill('0')
          << "Current date: " << std::setw(2) << d.getMonth()
          << "/" << std::setw(2) << d.getDay()
          << "/" << d.getYear()
          << "  " << std::setw(2) << d.getHour()
          << ":" << std::setw(2) << d.getMinute();
        glDisable(GL_LIGHTING);
        glColor3f(1,1,1);
        text.draw(s.str(), -0.9,0.9);
        SDL_GL_SwapWindow(window);
    }

    void onMouseMotion(SDL_MouseMotionEvent &e) {
        camera.onMouseMotion(e);
    }

    void onKeyDown(SDL_KeyboardEvent &e) {
        if (e.keysym.scancode == SDL_SCANCODE_LEFT) {
          playSpeed /= 1.4;
          sphericalSpeed /= 1.1;
        }
        if (e.keysym.scancode == SDL_SCANCODE_RIGHT) {
          playSpeed *= 1.4;
          sphericalSpeed *= 1.1;
        }
        if (e.keysym.scancode == SDL_SCANCODE_SPACE)
            playing = !playing;
        if (e.keysym.scancode == SDL_SCANCODE_M)
            visualizeMesh = (visualizeMesh + 1) % 3;
        if (e.keysym.scancode == SDL_SCANCODE_S) {
            sphericalSpeed *= -1.0;
        }

    }
};

int main(int argc, char **argv) {
    QuakeVis app;
    app.run();
    return EXIT_SUCCESS;
}
