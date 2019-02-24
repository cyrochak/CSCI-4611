#ifndef EARTH_HPP
#define EARTH_HPP

#include "engine.hpp"
#include <vector>
using glm::vec2;
using glm::vec3;

class Earth {
public:
    void initialize(Engine *engine, int slices, int stacks, float spherical);
    float isSpherical();
    void setSpherical(float spherical);
    vec3 getPosition(float latitude, float longitude);
    vec3 getNormal(float latitude, float longitude);
    void draw(int textured);
protected:
    int slices, stacks;
    int nVertices, nTriangles;
    float spherical;
    Engine *engine;

    // Define the necessary buffers and texture.
    // Feel free to add helper methods to update the buffers.
    int nVerts, nIndices;

    VertexBuffer vertexBuffer, normalBuffer, texCoordBuffer;
    ElementBuffer indexBuffer;
    Texture texture, heightText;
};

inline void Earth::initialize(Engine *e, int sl, int st, float sp) {
    engine = e;
    slices = sl;
    stacks = st;
    spherical = sp;

    // Initialize nVertices, nTriangles, buffers, texture
    std::vector<vec3> vertices, normals;
    std::vector<vec2> texCoords;

    for (int i = 0; i < slices; i ++)
      for (int j = 0; j <= stacks; j ++) {
        float longitude, latitude;
        longitude = (double)i / slices * 360 - 180;
        latitude = (double)j / stacks * 180 - 90;
        vertices.push_back(getPosition(latitude, longitude));
        normals.push_back(getNormal(latitude, longitude));
        texCoords.push_back(vec2((double)i / slices, 1.0 - (double) j / stacks));

        longitude = (double)(i + 1) / slices * 360 - 180;
        latitude = (double)j / stacks * 180 - 90;
        vertices.push_back(getPosition(latitude, longitude));
        normals.push_back(getNormal(latitude, longitude));
        texCoords.push_back(vec2((double)(i + 1) / slices, 1.0 - (double) j / stacks));
      }
    nVerts = vertices.size();
    vertexBuffer = engine->allocateVertexBuffer(nVerts*sizeof(vec3));
    engine->copyVertexData(vertexBuffer, &vertices[0], nVerts*sizeof(vec3));
    normalBuffer = engine->allocateVertexBuffer(nVerts*sizeof(vec3));
    engine->copyVertexData(normalBuffer, &normals[0], nVerts*sizeof(vec3));
    texCoordBuffer = engine->allocateVertexBuffer(nVerts*sizeof(vec2));
    engine->copyVertexData(texCoordBuffer, &texCoords[0], nVerts*sizeof(vec2));
    std::vector<int> indices;
    for (int i = 0; i < slices; i ++)
      for (int j = 0; j < stacks; j ++) {
        int basis = 2 * i * (stacks + 1) + 2 * j;
        indices.push_back(basis);
        indices.push_back(basis + 2);
        indices.push_back(basis + 1);

        indices.push_back(basis + 1);
        indices.push_back(basis + 2);
        indices.push_back(basis + 3);
      }
    nIndices = indices.size();
    indexBuffer = engine->allocateElementBuffer(nIndices*sizeof(int));
    engine->copyElementData(indexBuffer, &indices[0], nIndices*sizeof(int));
    texture = engine->loadTexture(Config::textureFile);
    heightText = engine->loadTexture(Config::heightFile);
}

inline float Earth::isSpherical() {
    return spherical;
}

inline void Earth::setSpherical(float s) {
    spherical = s;
    std::vector<vec3> vertices, normals;
    for (int i = 0; i < slices; i ++)
      for (int j = 0; j <= stacks; j ++) {
        float longitude, latitude;
        longitude = (double)i / slices * 360 - 180;
        latitude = (double)j / stacks * 180 - 90;
        vertices.push_back(getPosition(latitude, longitude));
        normals.push_back(getNormal(latitude, longitude));

        longitude = (double)(i + 1) / slices * 360 - 180;
        latitude = (double)j / stacks * 180 - 90;
        vertices.push_back(getPosition(latitude, longitude));
        normals.push_back(getNormal(latitude, longitude));
      }
    engine->copyVertexData(vertexBuffer, &vertices[0], nVerts*sizeof(vec3));
    engine->copyVertexData(normalBuffer, &normals[0], nVerts*sizeof(vec3));

}

inline vec3 Earth::getPosition(float latitude, float longitude) {
    vec3 rectangularPosition(0,0,0), sphericalPosition(0,0,0);

    // compute vertex positions on rectangle and sphere
    rectangularPosition = vec3(longitude / 180 * M_PI,
                               latitude / 90 * (M_PI / 2.0),
                               0);
    float lat_r = latitude / 180 * M_PI;
    float lon_r = longitude / 180 * M_PI;
    sphericalPosition = vec3(cos(lat_r) * sin (lon_r),
                             sin(lat_r),
                             cos(lat_r) * cos (lon_r));
    if (spherical == 0)
        return rectangularPosition;
    else if (spherical == 1)
        return sphericalPosition;
    else {
        vec3 d = sphericalPosition - rectangularPosition;
        return rectangularPosition + (spherical * d);
    }
}

inline vec3 Earth::getNormal(float latitude, float longitude) {
    vec3 rectangularNormal(0,0,0), sphericalNormal(0,0,0);

    // compute vertex positions on rectangle and sphere
    rectangularNormal = vec3(0, 0, 1);
    float lat_r = latitude / 180 * M_PI;
    float lon_r = longitude / 180 * M_PI;
    sphericalNormal = vec3(cos(lat_r) * sin (lon_r),
                             sin(lat_r),
                             cos(lat_r) * cos (lon_r));
    if (spherical == 0)
        return rectangularNormal;
    else if (spherical == 1)
        return sphericalNormal;
    else {
        vec3 d = sphericalNormal - rectangularNormal;
        return glm::normalize(rectangularNormal + (spherical * d));
    }
}

inline void Earth::draw(int textured) {

    // Draw the mesh (with or without texture, depending on the input)
    engine->setVertexArray(vertexBuffer);
    engine->setNormalArray(normalBuffer);
    engine->setTexCoordArray(texCoordBuffer);
    if (textured == 1)
      engine->setTexture(texture);
    else if (textured == 2)
      engine->setTexture(heightText);
    else
      engine->unsetTexture();
    engine->drawElements(GL_TRIANGLES, indexBuffer, nIndices);
}

#endif
