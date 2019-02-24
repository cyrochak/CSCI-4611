#version 330

// CSci-4611 Assignment 5:  Art Render

// TODO: You need to modify this vertex shader to move the edge vertex along
// the normal away from the mesh surface IF you determine that the vertex
// belongs to a silhouette edge.


uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;
uniform mat4 projectionMatrix;
uniform float thickness;

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 leftNormal;
layout(location = 3) in vec3 rightNormal;

void main() {
    vec3 displaced = vertex;
    vec3 L = (normalMatrix * vec4(leftNormal, 0)).xyz;
    vec3 R = (normalMatrix * vec4(rightNormal, 0)).xyz;
    vec3 eye = -(modelViewMatrix *vec4(vertex ,1)).xyz;
    if ((dot(L,eye) * dot(R,eye)) < 0)
         {
             displaced += thickness * normal;
         }
    gl_Position = projectionMatrix * modelViewMatrix * vec4(displaced,1);
}
