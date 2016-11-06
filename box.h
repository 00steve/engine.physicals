#ifndef Box_H
#define Box_H

#include <GL/gl.h>
#define dSINGLE
#include <ode/ode.h>

#include <engine/core/varmap.h>
#include <engine/physics/physical_single_body.h>
#include <engine/physics/physics_world.h>



class Box : public PhysicalSingleBody{
private:
    double3 lengths;
    static string geometry;

protected:
    virtual void OnSetSettings();
    bool HandleMessage(NodeMessage message);

public:
    void Draw();

};



#endif // Box
