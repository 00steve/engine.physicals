#ifndef PLANE_H
#define PLANE_H

#include <GL/gl.h>
#define dSINGLE
#include <ode/ode.h>

#include <engine/core/varmap.h>
#include <engine/physics/physical_single_body.h>
#include <engine/physics/physics_world.h>


class Plane : public PhysicalSingleBody{

private:

    static string geometry;

    double3 normal;
    double offset;
    double density;

protected:

    virtual void OnSetSettings();
    virtual bool HandleMessage(NodeMessage message);

public:

    Plane();
    ~Plane();

    virtual void Update();
    void Draw();

};




#endif
