#ifndef PHYSICAL_CABLE_H
#define PHYSICAL_CABLE_H


#include <string>
#include <GL/glu.h>

#include <engine/physics/physical.h>
#include <engine/physics/physicsgroup.h>
#include <engine/physics/physics_world.h>

using namespace std;

class Cable : public Physical{
private:

    string geometry;
    string jointType;
    unsigned int segmentCount;
    List<dBodyID> bodies;
    List<dGeomID> geoms;
    List<float*> gl_matrix;
    List<bool> active;
    List<dJointID> joints;
    List<double3> anchorPosition;
    double length;
    double radius;
    double density;

protected:
    virtual bool HandleMessage(NodeMessage message);
	virtual void OnSetSettings();

public:

    Cable();
    ~Cable();

    virtual dBodyID Body(unsigned int index);
	virtual unsigned int BodyCount();

	virtual void Draw();
	virtual void Update();
};


#endif // PHYSICAL_CABLE_H
