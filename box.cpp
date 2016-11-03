
#include "box.h"

List<double> Box::lengths = List<double>(3,new double[3]{1,1,1});
double Box::density = 1;
string Box::geometry = "box";

Box::Box(){
}

Box::~Box(){
}

bool Box::HandleMessage(NodeMessage message){
    cout << "Box::HandleMessage - " << message.code << endl;
    switch(message.code){
    case MESSAGE_REGISTER_PHYSICS_OFFER: {
            VarMap *physics = new VarMap();
            physics->Add<string>(&geometry,"box.geometry");
            physics->Add<List<double> >(&lengths,"box.lengths");
            physics->Add<double>(&density,"box.density");
            physics->Add<double3>(&position,"box.position");
            cout << "position : " << position.x << "," << position.y << "," << position.z << endl;
            CreateAndSendMessage(message.sender,MESSAGE_REGISTER_PHYSICS_REQUEST,(void*)physics);
            return true;
        }

    case MESSAGE_REGISTER_PHYSICS_FINISHED: {
            cout << "successfully created physics object\n";
            PhysicsGroup *pGroup = (PhysicsGroup*) message.data;
            body = pGroup->body["box"];
            geom = pGroup->geom["box"];
            return true;
        }
    }
    return PhysicalSingleBody::HandleMessage(message);
}

void Box::Update(){
    PhysicalSingleBody::Update();
}

void Box::Draw(){

        //cout << " draw box\n";
        glPushMatrix();
        //glTranslated(boxPosition.x,boxPosition.y,boxPosition.z);
        glMultMatrixf(gl_matrix);

        double3 d = double3(1,1,1);
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
