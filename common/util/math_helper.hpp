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
GLuint CylinderInFrustum(Frustum *frustum, glm::vec3 pos, GLfloat radius);


/**
    Returns translation matrix from 't_vec'
    */
glm::mat4 Translation(glm::vec3 t_vec);
/**
    Returns translation matrix from 3D vector(x,y,z)
    */
inline glm::mat4 Translation(GLfloat x, GLfloat y, GLfloat z){ return Translation(glm::vec3(x, y, z)); }


/**
    Returns scale matrix from 't_vec'
    */
glm::mat4 Scale(glm::vec3 t_vec);
/**
    Returns scale matrix from 3D vector(x,y,z)
    */
inline glm::mat4 Scale(GLfloat x, GLfloat y, GLfloat z){ return Scale(glm::vec3(x, y, z)); }
/**
    Returns scale matrix from 3D vector(v,v,v)
    */
inline glm::mat4 Scale(GLfloat v) { return Scale(v, v, v); }


/**
    Returns rotation matrix from euler angles x,y,z
    */
inline glm::mat4 Rotate(GLfloat x, GLfloat y, GLfloat z){ return glm::mat4_cast(glm::fquat(glm::vec3(x, y, z))); }
/**
    Returns rotation matrix from euler angles v.x,v.y,v.z
    */
inline glm::mat4 Rotate(glm::vec3 v){ return Rotate(v.x, v.y, v.z); }




/**
    Returns a random float number within the boundaries
    */
inline GLfloat randomf(GLfloat LO, GLfloat HI){ return LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO))); }


/**
    Normalize plane
    */
inline glm::vec4 NormalizePlane(glm::vec4 plane){return plane * glm::inversesqrt(plane.x * plane.x + plane.y * plane.y + plane.z * plane.z); }



}




#endif
