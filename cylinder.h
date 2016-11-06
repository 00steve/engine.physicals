#ifndef CYLINDER_H
#define CYLINDER_H

#include <GL/gl.h>
#include <GL/glu.h>
#define dSINGLE
#include <ode/ode.h>

#include <engine/core/varmap.h>
#include <engine/physics/physical_single_body.h>
#include <engine/physics/physics_world.h>

class Cylinder : public PhysicalSingleBody{
private:
    double length;
    double radius;
    static string geometry;

protected:
    void OnSetSettings();
    bool HandleMessage(NodeMessage message);

public:
    void Draw();

};


#endif // CYLINDER_H
