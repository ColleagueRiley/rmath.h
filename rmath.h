/*
*
*	RMath 
*
* 2025 ColleagueRiley
*
* Public domain stb-style math library and glm alternative
* 
* This is free and unencumbered software released into the public domain.
* Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
* software, either in source code form or as a compiled binary, for any purpose,
* commercial or non-commercial, and by any means.
* In jurisdictions that recognize copyright laws, the author or authors of this
* software dedicate any and all copyright interest in the software to the public
* domain. We make this dedication for the benefit of the public at large and to
* the detriment of our heirs and successors. We intend this dedication to be an
* overt act of relinquishment in perpetuity of all present and future rights to
* this software under copyright law.
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
* ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
* WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
*
*/

#ifndef RMATH_HEADER
#define RMATH_HEADER

#if defined(RMATH_EXPORT) ||  defined(RMATH_IMPORT)
	#if defined(_WIN32)
		#if defined(__TINYC__) && (defined(RMATH_EXPORT) ||  defined(RMATH_IMPORT))
			#define __declspec(x) __attribute__((x))
		#endif

		#if defined(RMATH_EXPORT)
			#define RMATHDEF __declspec(dllexport)
		#else
			#define RMATHDEF __declspec(dllimport)
		#endif
	#else
		#if defined(RMATH_EXPORT)
			#define RMATHDEF __attribute__((visibility("default")))
		#endif
	#endif
#endif

#ifndef RMATHDEF
	#define RMATHDEF inline
#endif

#include <stddef.h>
#ifndef RMATH_INT_DEFINED
	#ifdef RMATH_USE_INT /* optional for any system that might not have stdint.h */
		typedef unsigned char 	u8;
		typedef signed char		i8;
		typedef unsigned short  u16;
		typedef signed short 	i16;
		typedef unsigned long int 	u32;
		typedef signed long int		i32;
		typedef unsigned long long	u64;
		typedef signed long long		i64;
	#else /* use stdint standard types instead of c ""standard"" types */
		#include <stdint.h>

		typedef uint8_t     u8;
		typedef int8_t      i8;
		typedef uint16_t   u16;
		typedef int16_t    i16;
		typedef uint32_t   u32;
		typedef int32_t    i32;
		typedef uint64_t   u64;
		typedef int64_t    i64;
	#endif
    #define RMATH_INT_DEFINED
#endif
#endif

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159
#endif

#ifndef DEG2RAD
#define DEG2RAD (M_PI / 180.0f)
#endif

#ifndef rmCos
    #include <math.h>
    #define rmCos cosf
    #define rmSin sinf
#endif

#define rmTan(theta) (rmCos(theta) / rmSin(theta))
#define rmCot(theta) (rmSin(theta) / rmCos(theta))

#ifndef rmMat4
typedef struct rmMat4 { float m[16]; } rmMat4;
#endif

RMATHDEF float rmClamp(float value, float min, float max);
RMATHDEF float rmNormalize(float value, float start, float end);
RMATHDEF float rmLerp(float start, float end, float amount);
RMATHDEF float rmRemap(float value, float inputStart, float inputEnd, float outputStart, float outputEnd);
RMATHDEF float rmWrap(float value, float min, float max);

/* transformations */
RMATHDEF rmMat4 rmLoadIdentity(void);
RMATHDEF rmMat4 rmTranslate(float matrix[16], float x, float y, float z);
RMATHDEF rmMat4 rmRotate(float matrix[16], float angle, float x, float y, float z);
RMATHDEF rmMat4 rmPerspective(float matrix[16], float fovY, float aspect, float zNear, float zFar);
RMATHDEF rmMat4 rmOrtho(float matrix[16], float left, float right, float bottom, float top, float znear, float zfar);
RMATHDEF rmMat4 rmScale(float matrix[16], float x, float y, float z);

RMATHDEF rmMat4 rmMat4Multiply(float left[16], float right[16]);

#ifndef RMATH_VECTORS_DEFINED
typedef struct rmVec2 { float x, y; } rmVec2;
typedef struct rmVec3 { float x, y, z; } rmVec3;
typedef struct rmVec4 { float x, y, z, w; } rmVec4;
#endif

#define RM_VEC2(x, y) (rmVec2){x, y}
#define RM_VEC3(x, y, z) (rmVec3){x, y, z}
#define RM_VEC4(x, y, z, w) (rmVec4){x, y, z, w}

RMATHDEF rmVec2 rmVec2Add(rmVec2 v1, rmVec2 v2);
RMATHDEF rmVec3 rmVec3Add(rmVec3 v1, rmVec3 v2);
RMATHDEF rmVec4 rmVec4Add(rmVec4 v1, rmVec4 v2);

RMATHDEF rmVec2 rmVec2Subtract(rmVec2 v1, rmVec2 v2);
RMATHDEF rmVec3 rmVec3Subtract(rmVec3 v1, rmVec3 v2);
RMATHDEF rmVec4 rmVec4Subtract(rmVec4 v1, rmVec4 v2);

RMATHDEF rmVec2 rmVec2Multiply(rmVec2 v1, rmVec2 v2);
RMATHDEF rmVec3 rmVec3Multiply(rmVec3 v1, rmVec3 v2);
RMATHDEF rmVec4 rmVec4Multiply(rmVec4 v1, rmVec4 v2);

RMATHDEF rmVec2 rmVec2Divide(rmVec2 v1, rmVec2 v2);
RMATHDEF rmVec3 rmVec3Divide(rmVec3 v1, rmVec3 v2);
RMATHDEF rmVec4 rmVec4Divide(rmVec4 v1, rmVec4 v2);

RMATHDEF float rmVec2Dist(rmVec2 v1, rmVec2 v2);
RMATHDEF float rmVec3Dist(rmVec3 v1, rmVec3 v2);
RMATHDEF float rmVec4Dist(rmVec4 v1, rmVec4 v2);

RMATHDEF float rmVec2Dot(rmVec2 v, rmVec2 v1);
RMATHDEF float rmVec3Dot(rmVec3 v, rmVec3 v1);
RMATHDEF float rmVec4Dot(rmVec4 v, rmVec4 v1);

RMATHDEF float rmVec2Cross(rmVec2 v, rmVec2 v1);
RMATHDEF float rmVec3Cross(rmVec3 v, rmVec3 v1);
RMATHDEF float rmVec4Cross(rmVec4 v, rmVec4 v1);

RMATHDEF rmVec2 rmVec2MultiplyMat4(rmVec2 vec, rmMat4 matrix); 
RMATHDEF rmVec3 rmVec3MultiplyMat4(rmVec3 vec, rmMat4 matrix); 
RMATHDEF rmVec4 rmVec4MultiplyMat4(rmVec4 vec, rmMat4 matrix); 

RMATHDEF rmVec3 rmVec4ToVec3(rmVec4 v);

RMATHDEF rmVec2 rmVec2ToWorld(rmVec2 v, float screenWidth, float screenHeight);
RMATHDEF rmVec3 rmVec3ToWorld(rmVec3 v, float screenWidth, float screenHeight);
RMATHDEF rmVec4 rmVec4ToWorld(rmVec4 v, float screenWidth, float screenHeight);

RMATHDEF rmVec2 rmVec2ToScreen(rmVec2 v, float screenWidth, float screenHeight);
RMATHDEF rmVec3 rmVec3ToScreen(rmVec3 v, float screenWidth, float screenHeight);
RMATHDEF rmVec4 rmVec4ToScreen(rmVec4 v, float screenWidth, float screenHeight);

#ifndef RMATH_SHAPES_DEFINED
typedef struct rmCircle { float x, y, d; } rmCircle;
typedef struct rmRect { float x, y, w, h; } rmRect;
typedef struct rmCube { float x, y, z, w, h, l; } rmCube;
#endif

#ifndef RMATH_BOOL_DEFINED
typedef u8 rmBool;
#define RMATH_TRUE 1
#define RMATH_FALSE 0 
#endif

RMATHDEF rmBool rmVec2Cmp(rmVec2 v, rmVec2 v1);
RMATHDEF rmBool rmVec3Cmp(rmVec3 v, rmVec3 v1);
RMATHDEF rmBool rmVec4Cmp(rmVec4 v, rmVec4 v1);

RMATHDEF rmBool rmCircleCollideVec2(rmCircle c, rmVec2 p);
RMATHDEF rmBool rmCircleCollideRect(rmCircle c, rmRect r);
RMATHDEF rmBool rmCircleCollide(rmCircle cir1, rmCircle cir2);
RMATHDEF rmBool rmRectCollideVec2(rmRect r, rmVec2 p);
RMATHDEF rmBool rmRectCollide(rmRect r, rmRect r2);
RMATHDEF rmBool rmVec2Collide(rmVec2 p, rmVec2 p2);
RMATHDEF rmBool rmVec3Collide(rmVec3 p, rmVec3 p2);
RMATHDEF rmBool rmCubeCollideVec3(rmCube p, rmVec3 p2);
RMATHDEF rmBool rmCubeCollide(rmCube cube, rmCube cube2);

#ifndef RMATH_IMPLEMENTATON
float rmClamp(float value, float min, float max) { 
    if (value < min) return min;
    if (value > max) return max;

    return value;
}
float rmNormalize(float value, float start, float end) { 
   return (value - start)/(end - start);
}
float rmLerp(float start, float end, float amount) { 
    return start + amount*(end - start);
}
float rmRemap(float value, float inputStart, float inputEnd, float outputStart, float outputEnd) { 
    return (value - inputStart)/(inputEnd - inputStart)*(outputEnd - outputStart) + outputStart;
}
float rmWrap(float value, float min, float max) { 
    return value - (max - min)*floorf((value - min)/(max - min));
}

rmVec3 rmVec4ToVec3(rmVec4 v) {
   return RM_VEC3(v.x / v.w,  
                  v.y / v.w, 
                  v.z / v.w);
}

rmVec2 rmVec2ToWorld(rmVec2 v, float screenWidth, float screenHeight) {  
    return RM_VEC2((float)(2.0f * (v.x) / screenWidth - 1.0f), (float)(1.0f + -2.0f * (v.y) / screenHeight));
}
rmVec3 rmVec3ToWorld(rmVec3 v, float screenWidth, float screenHeight) {  
    return RM_VEC3((float)(2.0f * (v.x) / screenWidth - 1.0f), (float)(1.0f + -2.0f * (v.y) / screenHeight), v.z);
}
rmVec4 rmVec4ToWorld(rmVec4 v, float screenWidth, float screenHeight) {  
    return RM_VEC4((float)(2.0f * (v.x) / screenWidth - 1.0f), (float)(1.0f + -2.0f * (v.y) / screenHeight), v.z, v.w);
}

rmVec2 rmVec2ToScreen(rmVec2 v, float screenWidth, float screenHeight) { 
    return RM_VEC2((float)((v.x + 1.0f) * 0.5f * screenWidth), (float)((1.0f - v.y) * 0.5f * screenHeight));
}

rmVec3 rmVec3ToScreen(rmVec3 v, float screenWidth, float screenHeight) {  
    return RM_VEC3((float)((v.x + 1.0f) * 0.5f * screenWidth), (float)((1.0f - v.y) * 0.5f * screenHeight), v.z);
}

rmVec4 rmVec4ToScreen(rmVec4 v, float screenWidth, float screenHeight) { 
    return RM_VEC4((float)((v.x + 1.0f) * 0.5f * screenWidth), (float)((1.0f - v.y) * 0.5f * screenHeight), v.z, v.w);
}

rmVec2 rmVec2Add(rmVec2 v1, rmVec2 v2) { return (rmVec2){ v1.x + v2.x, v1.y + v2.y }; }
rmVec3 rmVec3Add(rmVec3 v1, rmVec3 v2) { return (rmVec3){ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z }; }
rmVec4 rmVec4Add(rmVec4 v1, rmVec4 v2) { return (rmVec4){ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w }; }

rmVec2 rmVec2Subtract(rmVec2 v1, rmVec2 v2) {  return (rmVec2){ v1.x - v2.x, v1.y - v2.y}; }
rmVec3 rmVec3Subtract(rmVec3 v1, rmVec3 v2) { return (rmVec3){ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z }; }
rmVec4 rmVec4Subtract(rmVec4 v1, rmVec4 v2) { return (rmVec4){ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w }; }

rmVec2 rmVec2Multiply(rmVec2 v1, rmVec2 v2) { return (rmVec2){ v1.x * v2.x, v1.y * v2.y }; }
rmVec3 rmVec3Multiply(rmVec3 v1, rmVec3 v2) { return (rmVec3){ v1.x * v2.x, v1.y * v2.y, v1.z * v2.z }; }
rmVec4 rmVec4Multiply(rmVec4 v1, rmVec4 v2) { return (rmVec4){ v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w }; }

rmVec2 rmVec2Divide(rmVec2 v1, rmVec2 v2) { return (rmVec2){ v1.x / v2.x, v1.y / v2.y }; }
rmVec3 rmVec3Divide(rmVec3 v1, rmVec3 v2) { return (rmVec3){ v1.x / v2.x, v1.y / v2.y, v1.z / v2.z }; }
rmVec4 rmVec4Divide(rmVec4 v1, rmVec4 v2) { return (rmVec4){ v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w }; }

float rmVec2Dist(rmVec2 v1, rmVec2 v2) { 
    rmVec2 res = rmVec2Subtract(v1, v2);
    return sqrtf((res.x * res.x) + (res.y * res.y));
}
float rmVec3Dist(rmVec3 v1, rmVec3 v2) { 
    rmVec3 res = rmVec3Subtract(v1, v2);
    return sqrtf((res.x * res.x) + (res.y * res.y) + (res.z * res.z));
}
float rmVec4Dist(rmVec4 v1, rmVec4 v2) { 
    rmVec4 res = rmVec4Subtract(v1, v2);
    return sqrtf((res.x * res.x) + (res.y * res.y) + (res.z * res.z) + (res.w * res.w));
}

float rmVec2Dot(rmVec2 v, rmVec2 v1) { return (v.x * v1.x) + (v.y * v1.y); }
float rmVec3Dot(rmVec3 v, rmVec3 v1) { return (v.x * v1.x) + (v.y * v1.y) + (v.z * v1.z); }
float rmVec4Dot(rmVec4 v, rmVec4 v1) { return (v.x * v1.x) + (v.y * v1.y) + (v.z * v1.z) + (v.w * v1.w); }

float rmVec2Cross(rmVec2 v, rmVec2 v1) { return (v.x * v1.x) - (v.y * v1.y); }
float rmVec3Cross(rmVec3 v, rmVec3 v1) { return (v.x * v1.x) - (v.y * v1.y) - (v.z * v1.z); }
float rmVec4Cross(rmVec4 v, rmVec4 v1) { return (v.x * v1.x) - (v.y * v1.y) - (v.z * v1.z) - (v.w * v1.w); }

rmMat4 rmLoadIdentity(void) {
    rmMat4 matrix = (rmMat4) { 
        {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        }
    };

    return matrix;
}
 
rmMat4 rmTranslate(float matrix[16], float x, float y, float z) {
    rmMat4 matTranslation = { 
        {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            x,    y,    z,    1.0f
        }
    };

    return rmMat4Multiply(matTranslation.m, matrix);
}

rmMat4 rmRotate(float matrix[16], float angle, float x, float y, float z) {
    float lengthSquared = x * x + y * y + z * z;
	if ((lengthSquared != 1.0f) && (lengthSquared != 0.0f)) {
		float inverseLength = 1.0f / sqrtf(lengthSquared);
		x *= inverseLength;
		y *= inverseLength;
		z *= inverseLength;
	}

	/* Rotation matrix generation */
	float sinres = sin(angle);
	float cosres = cos(angle);
	float t = 1.0f - cosres;

	float matRotation[16] =  {
					x * x * t + cosres,   	  	y * x * t + z * sinres,   	z * x * t - y * sinres,   	0.0f,
					x * y * t - z * sinres,   	y * y * t + cosres,   		z * y * t + x * sinres,   	0.0f,
					x * z * t + y * sinres,   	y * z * t - x * sinres,  	z * z * t + cosres,   		0.0f,
					0.0f,   					0.0f,   					0.0f,   					1.0f
				};

	return rmMat4Multiply(matRotation, matrix);
}

rmMat4 rmPerspective(float matrix[16], float fovY, float aspect, float zNear, float zFar) {
    rmMat4 perspective = {0};
    fovY =  (fovY * DEG2RAD) / 2.0f;
    const float f = rmCot(fovY);

    perspective.m[0] = f / aspect;
    perspective.m[5] = f;
    perspective.m[10] = (zFar + zNear) / (zNear - zFar);
    perspective.m[11] = -1.0;
    perspective.m[14] = (2.0 * zFar * zNear) / (zNear - zFar);

	return rmMat4Multiply(perspective.m, matrix);
}

rmMat4 rmOrtho(float matrix[16], float left, float right, float bottom, float top, float znear, float zfar) {
    float rl = (float)(right - left);
    float tb = (float)(top - bottom);
    float fn = (float)(zfar - znear);

    float matOrtho[16] = { 
        (2.0f / rl),                          0.0f,                             0.0f,                                 0.0f,
        0.0f,                                (2.0f / tb),                       0.0f,                                0.00,         
        0.0f,                                 0.0f,                             (-2.0f / fn),                         0.0f,        
        (-((float)left + (float)right) / rl), -((float)top + (float)bottom)/tb, (-((float)zfar + (float)znear) / fn), 1.0f
    };

    return rmMat4Multiply(matrix, matOrtho);
}

rmMat4 rmScale(float matrix[16], float x, float y, float z) {
    rmMat4 matScale = { 
        {
            x,    0.0f, 0.0f, 0.0f,
            0.0f, y,    0.0f, 0.0f,
            0.0f, 0.0f, z,    0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        }
    };

    return rmMat4Multiply(matScale.m, matrix);
}

rmVec2 rmVec2MultiplyMat4(rmVec2 vec, rmMat4 matrix) {
    float vecZ = 1;

    const float w = (float)(matrix.m[3] * vec.x + matrix.m[7] * vec.y + matrix.m[11] * vecZ + matrix.m[15]);
    const float z = (float)(matrix.m[2] * vec.x + matrix.m[6] * vec.y + matrix.m[10] * vecZ + matrix.m[14]) / w;


    return (rmVec2) {
        (float)(matrix.m[0] * vec.x + matrix.m[4] * vec.y + matrix.m[8] * vecZ + matrix.m[12]) / w,
        (float)(matrix.m[1] * vec.x + matrix.m[5] * vec.y + matrix.m[9] * vecZ + matrix.m[13]) / w
    };

}

rmVec3 rmVec3MultiplyMat4(rmVec3 vec, rmMat4 matrix) {
    const float w = (float)(matrix.m[3] * vec.x + matrix.m[7] * vec.y + matrix.m[11] * vec.z + matrix.m[15]);

    return (rmVec3) {
        (float)(matrix.m[0] * vec.x + matrix.m[4] * vec.y + matrix.m[8] * vec.z + matrix.m[12]) / w,
        (float)(matrix.m[1] * vec.x + matrix.m[5] * vec.y + matrix.m[9] * vec.z + matrix.m[13]) / w,
        (float)(matrix.m[2] * vec.x + matrix.m[6] * vec.y + matrix.m[10] * vec.z + matrix.m[14]) / w,
    };
} 

rmVec4 rmVec4MultiplyMat4(rmVec4 vec, rmMat4 matrix) {
    return (rmVec4) {
        (float)(matrix.m[0] * vec.x + matrix.m[4] * vec.y + matrix.m[8] * vec.z + matrix.m[12]),
        (float)(matrix.m[1] * vec.x + matrix.m[5] * vec.y + matrix.m[9] * vec.z + matrix.m[13]),
        (float)(matrix.m[2] * vec.x + matrix.m[6] * vec.y + matrix.m[10] * vec.z + matrix.m[14]),
        (float)(matrix.m[3] * vec.x + matrix.m[7] * vec.y + matrix.m[11] * vec.z + matrix.m[15])
    };
} 

rmBool rmVec2Cmp(rmVec2 v, rmVec2 v1) { return (v.x == v1.x && v.y == v1.y); }
rmBool rmVec3Cmp(rmVec3 v, rmVec3 v1) { return (v.x == v1.x && v.y == v1.y && v.z == v1.z); }
rmBool rmVec4Cmp(rmVec4 v, rmVec4 v1) { return (v.x == v1.x && v.y == v1.y && v.z == v1.z && v.w == v1.w); }

rmBool rmCircleCollideVec2(rmCircle c, rmVec2 p) { return rmCircleCollideRect(c, (rmRect){p.x, p.y, 1, 1}); }
rmBool rmCircleCollideRect(rmCircle c, rmRect r) {
    float testX = c.x; 
    float testY = c.y;

    // fill cords based on x/ys of the shapes
    if (c.x < r.x)
      testX = r.x;  

    else if (c.x > r.x+r.w) 
      testX = r.x-r.w;

    if (c.y < r.y)  
      testY = r.y;  

    else if (c.y > r.y+r.h)
      testY = r.y+r.h; 
    
    // check
    return ( sqrt( ( (c.x - testX) * (c.x - testX) ) + ( (c.y - testY) * (c.y - testY) ) )  <= (c.d/2) );
}
rmBool rmCircleCollide(rmCircle cir1, rmCircle cir2) {
    float distanceBetweenCircles = (float) sqrt(
        (cir2.x - cir1.x) * (cir2.x - cir1.x) + 
        (cir2.y - cir1.y) * (cir2.y - cir1.y)
    );

    return !(distanceBetweenCircles > (cir1.d/2) + (cir2.d/2)); // check if there is a collid
}
rmBool rmRectCollideVec2(rmRect r, rmVec2 p) { return (p.x >= r.x &&  p.x <= r.x + r.w && p.y >= r.y && p.y <= r.y + r.h); }
rmBool rmRectCollide(rmRect r, rmRect r2) { return (r.x + r.w >= r2.x && r.x <= r2.x + r2.w && r.y + r.h >= r2.y && r.y <= r2.y + r2.h); }
rmBool rmVec2Collide(rmVec2 p, rmVec2 p2) { return (p.x == p2.x && p.y == p2.y); }
rmBool rmVec3Collide(rmVec3 p, rmVec3 p2) { return (p.x == p2.x && p.y == p2.y && p.z == p2.z); }
rmBool rmCubeCollideVec3(rmCube cube, rmVec3 p) { return rmCubeCollide(cube, (rmCube){p.x, p.y, p.z, 1, 1, 1}); }
rmBool rmCubeCollide(rmCube r, rmCube r2) {
     return (r.x + r.w >= r2.x && r.x <= r2.x + r2.w && r.y + r.h >= r2.y && r.y <= r2.y + r2.h && r.z + r.l >= r2.z && r.z <= r2.z + r2.l);
}

rmMat4 rmMat4Multiply(float left[16], float right[16]) {
    return (rmMat4) {
        {
            left[0] * right[0] + left[1] * right[4] + left[2] * right[8] + left[3] * right[12],
            left[0] * right[1] + left[1] * right[5] + left[2] * right[9] + left[3] * right[13],
            left[0] * right[2] + left[1] * right[6] + left[2] * right[10] + left[3] * right[14],
            left[0] * right[3] + left[1] * right[7] + left[2] * right[11] + left[3] * right[15],
            left[4] * right[0] + left[5] * right[4] + left[6] * right[8] + left[7] * right[12],
            left[4] * right[1] + left[5] * right[5] + left[6] * right[9] + left[7] * right[13],
            left[4] * right[2] + left[5] * right[6] + left[6] * right[10] + left[7] * right[14],
            left[4] * right[3] + left[5] * right[7] + left[6] * right[11] + left[7] * right[15],
            left[8] * right[0] + left[9] * right[4] + left[10] * right[8] + left[11] * right[12],
            left[8] * right[1] + left[9] * right[5] + left[10] * right[9] + left[11] * right[13],
            left[8] * right[2] + left[9] * right[6] + left[10] * right[10] + left[11] * right[14],
            left[8] * right[3] + left[9] * right[7] + left[10] * right[11] + left[11] * right[15],
            left[12] * right[0] + left[13] * right[4] + left[14] * right[8] + left[15] * right[12],
            left[12] * right[1] + left[13] * right[5] + left[14] * right[9] + left[15] * right[13],
            left[12] * right[2] + left[13] * right[6] + left[14] * right[10] + left[15] * right[14],
            left[12] * right[3] + left[13] * right[7] + left[14] * right[11] + left[15] * right[15]
        }
    };
}
 
#endif
