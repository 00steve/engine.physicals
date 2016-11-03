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

    static List<double> lengths;
    static double density;
    static string geometry;

protected:

    virtual bool HandleMessage(NodeMessage message);

public:

    Box();
    ~Box();

    virtual void Update();
    void Draw();

};



#endif // Box
