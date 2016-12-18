
#ifndef CAPSULE_H
#define CAPSULE_H

#include <GL/gl.h>
#include <GL/glu.h>
#define dSINGLE
#include <ode/ode.h>

#include <engine/core/varmap.h>
#include <engine/physics/physical_single_body.h>

class Capsule : public PhysicalSingleBody{
private:
    double length;
    double radius;

protected:
    virtual void OnSetSettings();
    virtual void OnSetWorld();

public:
    void Draw();

};


#endif // CYLINDER_H
