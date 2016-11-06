#include "sphere.h"

string Sphere::geometry = "sphere";


void Sphere::OnSetSettings(){
    VarMap settings = Settings();
    if(settings.IsSet("radius")){
        radius = settings.get<double>("radius");
    } else {
        radius = .5;
    }
    PhysicalSingleBody::OnSetSettings();
}


bool Sphere::HandleMessage(NodeMessage message){
    cout << "Box::HandleMessage - " << message.code << endl;
    switch(message.code){
    case MESSAGE_REGISTER_PHYSICS_OFFER: {
        VarMap *physics = new VarMap();
        physics->Add<string>(&geometry,"sphere.geometry");
        physics->Add<double>(&radius,"sphere.radius");
        physics->Add<double>(&density,"sphere.density");
        physics->Add<double3>(&position,"sphere.position");
        physics->Add<double3>(&velocity,"sphere.velocity");
        cout << "position : " << position.x << "," << position.y << "," << position.z << endl;
        CreateAndSendMessage(message.sender,MESSAGE_REGISTER_PHYSICS_REQUEST,(void*)physics);
        return true;
        }

    case MESSAGE_REGISTER_PHYSICS_FINISHED: {
        cout << "successfully created physics::sphere\n";
        PhysicsGroup *pGroup = (PhysicsGroup*) message.data;
        body = pGroup->body["sphere"];
        geom = pGroup->geom["sphere"];
        dBodySetPosition(body,position.x,position.y,position.z);
        dBodySetForce(body,0,0,0);
        return true;
        }
    }
    return PhysicalSingleBody::HandleMessage(message);
}

void Sphere::Update(){
    PhysicalSingleBody::Update();
}

void Sphere::Draw(){
    glPushMatrix();
        glMultMatrixf(gl_matrix);
        GLUquadricObj *quadric = gluNewQuadric();
        glColor3f(1,0,0);
        gluQuadricDrawStyle(quadric, GLU_FILL );
        gluSphere( quadric , radius , 40 , 35 );
        gluDeleteQuadric(quadric);
    glPopMatrix();

}
