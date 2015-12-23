

vec2 map_sphere(vec3 point, float rad, float time)
{


vec2 uv = vec2(0.0);


uv.x = acos(point.z/rad) / 3.14;
uv.y = (acos(point.x/rad * sin (3.14 * uv.x + time) )) / 6.28;
  


return uv;



}



vec3 RotateAroundY(vec3 point, vec3 center, float speed)
{


float radius = length(point - center);
point.xz = center.xz + radius*vec2(cos(speed),sin(speed));


return point;


}




vec3 RotateAroundX(vec3 point, vec3 center, float speed)
{


float radius = length(point - center);
point.yz = center.yz + radius*vec2(cos(speed),sin(speed));


return point;


}

