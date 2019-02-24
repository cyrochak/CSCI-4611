Name: Chun F, Chak
Student ID: 5312343
email: chakx011@umn.edu

In this ArtRender Project, I have implemented phong implementation, and per pixel toon shading, and outliner when artsy mode.

Phong implementation:
    e : the vector from vetex to eye point
    l : the vector from the vertex to the light
    h : the halfway vector for l + e
    color : will be implemented the sum of ambient, diffuse, specular with the equation
    color = ka*Ia + kd*Id*(n dot l) + ks*Is*(h dot n)^s
    We have made some slightly adjustment into specular, so we have added 0.5* to the dot product + 0.5

Per Pixel toon Shading:
Artsy mode:
implemented is almost the same as Phong, but adding the texture in account for diffuse and specular
    use the formula from texture
    texture(smapler2D sampler, vec2 dotproduct)

Outline:
For Artsy mode used:
Added an outliner to draw for the edges of the mesh, which will be rendered in the mode.
Compute the eye vector pointing to the camera, L, R
make a dot product rule: dot(L,eye), dot(R,eye)
if both of them have a negative, we will displace the vertex by thickness * normal

