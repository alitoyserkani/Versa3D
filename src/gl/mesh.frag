#version 120

uniform float zoom;

varying vec3 ec_pos;

void main() {
    //current color for when object is simply being viewed, play around with shader combinations
//    vec3 base3 = vec3(0.99, 0.96, 0.89);
//    vec3 base2 = vec3(0.92, 0.91, 0.83);
//    vec3 base00 = vec3(0.40, 0.48, 0.51);

    //current color combo for when object is clicked and is being manipulated
    vec3 base3 = vec3(1.0, 1.0, 1.0);
    vec3 base2 = vec3(1.0, 0.91, 1.0);
    vec3 base00 = vec3(0.9, 0.5, 0.9);

    vec3 ec_normal = normalize(cross(dFdx(ec_pos), dFdy(ec_pos)));
    ec_normal.z *= zoom;
    ec_normal = normalize(ec_normal);

    float a = dot(ec_normal, vec3(0.0, 0.0, 1.0));
    float b = dot(ec_normal, vec3(-0.57, -0.57, 0.57));

    gl_FragColor = vec4((a*base2 + (1-a)*base00)*0.5 +
                        (b*base3 + (1-b)*base00)*0.5, 1.0);
}
