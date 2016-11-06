#include "capsule.h"

string Capsule::geometry = "capsule";


void Capsule::OnSetSettings(){
    VarMap settings = Settings();
    if(settings.IsSet("length")){
        length = settings.get<double>("length");
    } else {
        length = 2;
    }

    if(settings.IsSet("radius")){
        radius = settings.get<double>("radius");
    } else {
        radius = .5;
    }

    PhysicalSingleBody::OnSetSettings();
}


bool Capsule::HandleMessage(NodeMessage message){
    switch(message.code){
    case MESSAGE_REGISTER_PHYSICS_OFFER: {
            VarMap *physics = new VarMap();
            physics->Add<string>(&geometry,"capsule.geometry");
            physics->Add<double>(&length,"capsule.length");
            physics->Add<double>(&radius,"capsule.radius");
            physics->Add<double>(&density,"capsule.density");
            physics->Add<double3>(&position,"capsule.position");
            CreateAndSendMessage(message.sender,MESSAGE_REGISTER_PHYSICS_REQUEST,(void*)physics);
            return true;
        }

    case MESSAGE_REGISTER_PHYSICS_FINISHED: {
            PhysicsGroup *pGroup = (PhysicsGroup*) message.data;
            body = pGroup->body["capsule"];
            geom = pGroup->geom["capsule"];
            return true;
        }
    }
    return PhysicalSingleBody::HandleMessage(message);
}

void Capsule::Draw(){
    glPushMatrix();


        glMultMatrixf(gl_matrix);
        GLUquadricObj *quadric = gluNewQuadric();
        gluQuadricDrawStyle(quadric, GLU_SMOOTH );

			glColor3f(0,0,0);
			glBegin(GL_LINES);
				glVertex3f(0,0,length*-.5);
				glVertex3f(0,0,length*.5);
			glEnd();


			glTranslated(0,0,length*.5-radius);
			glColor3f(1,0,0);
			gluSphere(quadric,radius,30,30);

            glTranslated(0,0,-length+radius*2);
			glColor3f(0,0,1);
			gluCylinder(quadric,radius,radius,length-radius*2,30,1);

            glColor3f(0,1,0);
			gluSphere(quadric,radius,30,30);

    glPopMatrix();
}

