#version 330

in vec4 color;
out vec4 final_color;

void main() {
    final_color = color;
    
    // light_intensity = K_a*I_a + k_d*I_d(N.dot(l)) + k_s*I_s (h dot n) ^ s
}
