#ifndef MATH_HELPER
#define MATH_HELPER




#include <stdafx.h>





#define LERP(a,b,c)  (((b) - (a)) * (c) + (a))
#define COUNT_OF(x) ((sizeof(x) / sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))





/**
Some useful math functions for matrix transformations
*/
namespace Math
{








/**
    Checks if sphere intersects with frustum
    */
AUInt CylinderInFrustum(std::vector<glm::vec4> planes, glm::vec3 pos, AFloat radius);


/**
    Returns translation matrix from 't_vec'
    */
glm::mat4 Translation(glm::vec3 t_vec);
/**
    Returns translation matrix from 3D vector(x,y,z)
    */
inline glm::mat4 Translation(AFloat x, AFloat y, AFloat z){ return Translation(glm::vec3(x, y, z)); }


/**
    Returns scale matrix from 't_vec'
    */
glm::mat4 Scale(glm::vec3 t_vec);
/**
    Returns scale matrix from 3D vector(x,y,z)
    */
inline glm::mat4 Scale(AFloat x, AFloat y, AFloat z){ return Scale(glm::vec3(x, y, z)); }
/**
    Returns scale matrix from 3D vector(v,v,v)
    */
inline glm::mat4 Scale(AFloat v) { return Scale(v, v, v); }


/**
    Returns rotation matrix from euler angles x,y,z
    */
inline glm::mat4 Rotate(AFloat x, AFloat y, AFloat z){ return glm::mat4_cast(glm::fquat(glm::vec3(x, y, z))); }
/**
    Returns rotation matrix from euler angles v.x,v.y,v.z
    */
inline glm::mat4 Rotate(glm::vec3 v){ return Rotate(v.x, v.y, v.z); }




/**
    Returns a random AFloat number within the boundaries
    */
inline AFloat randomf(AFloat LO, AFloat HI){ return LO + static_cast <AFloat> (rand()) / (static_cast <AFloat> (RAND_MAX / (HI - LO))); }


/**
    Normalize plane
    */
inline glm::vec4 NormalizePlane(glm::vec4 plane){return plane * glm::inversesqrt(plane.x * plane.x + plane.y * plane.y + plane.z * plane.z); }




/**
  Compute frustum out of MVP
*/
std::vector<glm::vec4> GetFrustumPlanes(glm::mat4 MVP);




}




#endif
