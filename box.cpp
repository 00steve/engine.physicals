#include "box.h"

string Box::geometry = "box";


void Box::OnSetSettings(){
    VarMap settings = Settings();
    if(settings.IsSet("lengths")){
        List<double> lens = settings.get<List<double> >("lengths");
        if(lens.GetCount() == 3){
            lengths = double3(lens[0],lens[1],lens[2]);
        } else {
            cout << "the box lengths property requires three values, e.g. 1,2,1.5\n";
            lengths = double3(1,1,1);
        }
    } else {
        lengths = double3(1,1,1);
    }
    PhysicalSingleBody::OnSetSettings();
}


bool Box::HandleMessage(NodeMessage message){
    switch(message.code){
    case MESSAGE_REGISTER_PHYSICS_OFFER: {


            VarMap *physics = new VarMap();
            physics->Add<string>(&geometry,"box.geometry");
            physics->Add<double3>(&lengths,"box.lengths");
            physics->Add<double>(&density,"box.density");
            physics->Add<double3>(&position,"box.position");
            CreateAndSendMessage(message.sender,MESSAGE_REGISTER_PHYSICS_REQUEST,(void*)physics);
            return true;
        }
    case MESSAGE_REGISTER_PHYSICS_FINISHED: {
            PhysicsGroup *pGroup = (PhysicsGroup*) message.data;
            body = pGroup->body["box"];
            geom = pGroup->geom["box"];
            return true;
        }
    }
    return PhysicalSingleBody::HandleMessage(message);
}

void Box::Draw(){
    glPushMatrix();
        glMultMatrixf(gl_matrix);

        double3 d = lengths;
        glBegin(GL_TRIANGLE_FAN);
            glColor3f(d.x,d.y*-1,d.z);
			glVertex3d(d.x*.5,d.y*-.5,d.z*.5);
            glColor3f(d.x*-1,d.y*-1,d.z);
			glVertex3d(d.x*-.5,d.y*-.5,d.z*.5);
            glColor3f(d.x*-1,d.y,d.z);
			glVertex3d(d.x*-.5,d.y*-.5,d.z*-.5);
            glColor3f(d.x*-1,d.y,d.z*-1);
			glVertex3d(d.x*.5,d.y*-.5,d.z*-.5);
            glColor3f(d.x,d.y,d.z*-1);
			glVertex3d(d.x*.5,d.y*.5,d.z*-.5);
            glColor3f(d.x,d.y*-1,d.z*-1);
			glVertex3d(d.x*.5,d.y*.5,d.z*.5);
            glColor3f(d.x,d.y*-1,d.z);
			glVertex3d(d.x*-.5,d.y*.5,d.z*.5);
			glColor3f(d.x,d.y,d.z);
			glVertex3d(d.x*-.5,d.y*-.5,d.z*.5);
		glEnd();
        glColor3f(1,1,0);
		glBegin(GL_TRIANGLE_FAN);
            glColor3f(d.x*-1,d.y,d.z*-1);
			glVertex3d(d.x*-.5,d.y*.5,d.z*-.5);
            glColor3f(d.x*-1,d.y,d.z);
			glVertex3d(d.x*-.5,d.y*.5,d.z*.5);
            glColor3f(d.x*-1,d.y*-1,d.z);
			glVertex3d(d.x*.5,d.y*.5,d.z*.5);
            glColor3f(d.x,d.y*-1,d.z);
			glVertex3d(d.x*.5,d.y*.5,d.z*-.5);
            glColor3f(d.x,d.y*-1,d.z*-1);
			glVertex3d(d.x*.5,d.y*-.5,d.z*-.5);
            glColor3f(d.x,d.y,d.z*-1);
			glVertex3d(d.x*-.5,d.y*-.5,d.z*-.5);
            glColor3f(d.x*-1,d.y,d.z*-1);
			glVertex3d(d.x*-.5,d.y*-.5,d.z*.5);
            glColor3f(d.x*-1,d.y*-1,d.z*-1);
			glVertex3d(d.x*-.5,d.y*.5,d.z*.5);

		glEnd();
    glPopMatrix();
}
