#include "cylinder.h"

string Cylinder::geometry = "cylinder";


void Cylinder::OnSetSettings(){
    VarMap settings = Settings();
    if(settings.IsSet("length")){
        length = settings.get<double>("length");
    } else {
        length = 1;
    }

    if(settings.IsSet("radius")){
        radius = settings.get<double>("radius");
    } else {
        radius = .5;
    }

    PhysicalSingleBody::OnSetSettings();
}


bool Cylinder::HandleMessage(NodeMessage message){
    switch(message.code){
    case MESSAGE_REGISTER_PHYSICS_OFFER: {
            VarMap *physics = new VarMap();
            physics->Add<string>(&geometry,"cylinder.geometry");
            physics->Add<double>(&length,"cylinder.length");
            physics->Add<double>(&radius,"cylinder.radius");
            physics->Add<double>(&density,"cylinder.density");
            physics->Add<double3>(&position,"cylinder.position");
            cout << "position : " << position.x << "," << position.y << "," << position.z << endl;
            CreateAndSendMessage(message.sender,MESSAGE_REGISTER_PHYSICS_REQUEST,(void*)physics);
            return true;
        }

    case MESSAGE_REGISTER_PHYSICS_FINISHED: {
            PhysicsGroup *pGroup = (PhysicsGroup*) message.data;
            body = pGroup->body["cylinder"];
            geom = pGroup->geom["cylinder"];
            return true;
        }
    }
    return PhysicalSingleBody::HandleMessage(message);
}

void Cylinder::Draw(){
    glPushMatrix();
        glMultMatrixf(gl_matrix);
        GLUquadricObj *quadric = gluNewQuadric();
        glColor3f(0,1,0);
        gluQuadricDrawStyle(quadric, GLU_LINE );
        gluCylinder( quadric , radius , radius,length, 40 ,1 );
        gluDeleteQuadric(quadric);
		glEnd();
    glPopMatrix();
}
