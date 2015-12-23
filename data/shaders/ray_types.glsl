


struct Ray {
    vec3 o; //origin
    vec3 d; //direction (should always be normalized)
};

struct Sphere {
    vec3 pos;   //center of sphere position
    float rad;  //radius
    vec3 col;   //surface color
};




vec3 FindSphereNormal(Sphere sphere, vec3 point)
{

return normalize((point - sphere.pos) / sphere.rad);

}