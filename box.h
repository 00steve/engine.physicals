#ifndef Box_H
#define Box_H

#include <GL/gl.h>
#include <engine/core/varmap.h>
#include <engine/physics/physical_single_body.h>


class Box : public PhysicalSingleBody{
private:
    double3 dimensions;

protected:
    virtual void OnSetSettings();
    virtual void OnSetWorld();

public:
    void Draw();

};



#endif // Box
