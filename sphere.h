#ifndef SPHERE_H
#define SPHERE_H


#include <GL/gl.h>
#include <GL/glu.h>

#define dSINGLE
#include <ode/ode.h>

#include <engine/core/varmap.h>
#include <engine/physics/physical_single_body.h>
#include <engine/physics/physics_world.h>



class Sphere : public PhysicalSingleBody{
private:

    static string geometry;
    double radius;

protected:

    virtual void OnSetSettings();
    virtual bool HandleMessage(NodeMessage message);

public:

    virtual void Update();
    void Draw();

};



#endif // Sphere

