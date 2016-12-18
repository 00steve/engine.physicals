#ifndef PLANE_H
#define PLANE_H

#include <GL/gl.h>
#define dSINGLE
#include <ode/ode.h>

#include <engine/core/varmap.h>
#include <engine/physics/physical_single_body.h>


class Plane : public PhysicalSingleBody{
private:
    double3 normal;
    double offset;

protected:
    virtual void OnSetSettings();
    virtual void OnSetWorld();

public:
    void Draw();

};




#endif
