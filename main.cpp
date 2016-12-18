#include "main.h"

// a sample exported function

extern "C" {

    DLL_EXPORT Box* BuildBox() {
        return new Box();
    }
    DLL_EXPORT Plane* BuildPlane() {
        return new Plane();
    }
    DLL_EXPORT Sphere* BuildSphere() {
        return new Sphere();
    }
    DLL_EXPORT Cylinder* BuildCylinder() {
        return new Cylinder();
    }
    DLL_EXPORT Capsule* BuildCapsule() {
        return new Capsule();
    }
    DLL_EXPORT Cable* BuildCable(){
        return new Cable();
    }
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // successful
}
