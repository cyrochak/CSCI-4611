#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "graphics.hpp"
#include <iostream>
#include <string>
#include <sstream>

typedef GLuint VertexBuffer;
typedef GLuint ElementBuffer;
typedef GLuint Texture;

class Engine {
public:
    Engine();
    ~Engine();
    SDL_Window* createWindow(std::string title, int width, int height);
    void destroyWindow(SDL_Window*);
    bool shouldQuit();
    void handleInput();
	void errorMessage(std::string message);
    void waitForNextFrame(float secondsPerFrame);
    // input state
    bool isKeyDown(int scancode);
    bool isMouseButtonDown(int button);
    void mousePosition(int *x, int *y);
    int mouseX();
    int mouseY();
    // callback functions; child classes should override
    virtual void onKeyDown(SDL_KeyboardEvent&) {}
    virtual void onKeyUp(SDL_KeyboardEvent&) {}
    virtual void onMouseMotion(SDL_MouseMotionEvent&) {}
    virtual void onMouseButtonDown(SDL_MouseButtonEvent&) {}
    virtual void onMouseButtonUp(SDL_MouseButtonEvent&) {}
    // vertex and element buffers
    VertexBuffer allocateVertexBuffer(int bytes);
    void copyVertexData(VertexBuffer buffer, void *data, int bytes);
    void setVertexArray(VertexBuffer buffer);
    void setColorArray(VertexBuffer buffer);
    void setNormalArray(VertexBuffer buffer);
    void setTexCoordArray(VertexBuffer buffer);
    ElementBuffer allocateElementBuffer(int bytes);
    void copyElementData(ElementBuffer buffer, void *data, int bytes);
    void drawElements(GLenum mode, ElementBuffer buffer, int count);
    // textures
    Texture loadTexture(std::string bmpFile);
    void setTexture(Texture texture);
    void unsetTexture();
protected:
    bool userQuit;
    int lastFrameTime;
    void die_with_sdl_error(std::string message);
    void die_if_opengl_error();
};

// Definitions below

inline void Engine::die_with_sdl_error(std::string message) {
    std::cout << message << ": " << SDL_GetError() << std::endl;
    exit(EXIT_FAILURE);
}

inline void Engine::die_if_opengl_error() {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
		std::stringstream ss;
		ss << "OpenGL error: " << gluErrorString(error);
		errorMessage(ss.str());
        exit(EXIT_FAILURE);
    }
}

inline Engine::Engine() {
    int status = SDL_Init(SDL_INIT_VIDEO);
	if (status < 0){
		errorMessage("Failed to initialize SDL");
		exit(EXIT_FAILURE);
	}
    userQuit = false;
    lastFrameTime = 0;
}

inline Engine::~Engine() {
    SDL_Quit();
}

inline SDL_Window* Engine::createWindow(std::string title, int width, int height) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_Window *window =
        SDL_CreateWindow(title.c_str(),
                         SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                         width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (window == NULL){
		errorMessage("Failed to create window");
		exit(EXIT_FAILURE);
	}
    SDL_GLContext context = SDL_GL_CreateContext(window);
	if (context == NULL){
		die_with_sdl_error("Failed to create OpenGL context");
		exit(EXIT_FAILURE);
	}
    SDL_GL_SetSwapInterval(1);
#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    glewInit();
#endif
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    die_if_opengl_error();
    return window;
}

inline void Engine::destroyWindow(SDL_Window *window) {
    SDL_DestroyWindow(window);
}

inline void Engine::handleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            userQuit = true;
            break;
        case SDL_KEYDOWN:
            onKeyDown(event.key);
            break;
        case SDL_KEYUP:
            onKeyUp(event.key);
            break;
        case SDL_MOUSEMOTION:
            onMouseMotion(event.motion);
            break;
        case SDL_MOUSEBUTTONDOWN:
            onMouseButtonDown(event.button);
            break;
        case SDL_MOUSEBUTTONUP:
            onMouseButtonUp(event.button);
            break;
        }
    }
}

inline void Engine::errorMessage(std::string message){

	SDL_ShowSimpleMessageBox(
		SDL_MESSAGEBOX_ERROR,
		"ERROR",
		message.c_str(),
		NULL
	);

}

inline bool Engine::shouldQuit() {
    return userQuit;
}

inline void Engine::waitForNextFrame(float secondsPerFrame) {
    int millisPerFrame = (int)(1000*secondsPerFrame);
    int now = SDL_GetTicks();
    int nextFrameTime = lastFrameTime + millisPerFrame;
    lastFrameTime = now;
    if (nextFrameTime > now)
        SDL_Delay(nextFrameTime - now);
}

inline bool Engine::isKeyDown(int scancode) {
    return SDL_GetKeyboardState(NULL)[scancode];
}

inline bool Engine::isMouseButtonDown(int button) {
    return SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(button);
}

inline void Engine::mousePosition(int *x, int *y) {
    SDL_GetMouseState(x,y);
}

inline int Engine::mouseX() {
    int x;
    SDL_GetMouseState(&x,NULL);
    return x;
};

inline int Engine::mouseY() {
    int y;
    SDL_GetMouseState(NULL,&y);
    return y;
}

inline VertexBuffer Engine::allocateVertexBuffer(int size) {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);
    die_if_opengl_error();
    return buffer;
}

inline ElementBuffer Engine::allocateElementBuffer(int size) {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);
    die_if_opengl_error();
    return buffer;
}

inline void Engine::copyVertexData(VertexBuffer buffer, void *data, int size) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    die_if_opengl_error();
}

inline void Engine::copyElementData(ElementBuffer buffer, void *data, int size) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
    die_if_opengl_error();
}

inline void Engine::setVertexArray(VertexBuffer buffer) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    die_if_opengl_error();
}

inline void Engine::setColorArray(VertexBuffer buffer) {
    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glColorPointer(3, GL_FLOAT, 0, 0);
    die_if_opengl_error();
}

inline void Engine::setNormalArray(VertexBuffer buffer) {
    glEnableClientState(GL_NORMAL_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glNormalPointer(GL_FLOAT, 0, 0);
    die_if_opengl_error();
}

inline void Engine::setTexCoordArray(VertexBuffer buffer) {
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glTexCoordPointer(2, GL_FLOAT, 0, 0);
    die_if_opengl_error();
}

inline void Engine::drawElements(GLenum mode, ElementBuffer buffer, int count) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glDrawElements(mode, count, GL_UNSIGNED_INT, 0);
    die_if_opengl_error();
}

inline Texture Engine::loadTexture(std::string bmpFile) {
    SDL_Surface *surface = SDL_LoadBMP(bmpFile.c_str());
	if (surface == NULL){
		errorMessage(("Failed to load texture image from file " + bmpFile).c_str());
		exit(EXIT_FAILURE);
	}
    SDL_LockSurface(surface);
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_BGR,
                 GL_UNSIGNED_BYTE, surface->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    SDL_FreeSurface(surface);
    die_if_opengl_error();
    return texture;
}

inline void Engine::setTexture(Texture texture) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    die_if_opengl_error();
}

inline void Engine::unsetTexture() {
    glDisable(GL_TEXTURE_2D);
}

#endif
