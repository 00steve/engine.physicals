#ifndef __MAIN_H__
#define __MAIN_H__

#include "box.h"
#include "plane.h"
#include "sphere.h"
#include "cylinder.h"
#include "capsule.h"

/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif



#ifdef __cplusplus
extern "C"
{
#endif

    DLL_EXPORT Box* BuildBox();
    DLL_EXPORT Plane* BuildPlane();
    DLL_EXPORT Sphere* BuildSphere();
    DLL_EXPORT Cylinder* BuildCylinder();
    DLL_EXPORT Capsule* BuildCapsule();

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
