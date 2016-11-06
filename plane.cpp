#include "plane.h"

string Plane::geometry = "plane";

void Plane::OnSetSettings(){
    VarMap settings = Settings();
    if(settings.IsSet("normal")){
        List<double> norm = settings.get<List<double> >("normal");
        if(norm.GetCount() == 3){
            normal = double3(norm[0],norm[1],norm[2]);
        } else {
            cout << " - The plane.normal property should have 3 values to be 3d, e.g. .55,1,0\n";
            normal = double3(0,1,0);
        }
    } else {
        normal = double3(0,1,0);
    }
    if(settings.IsSet("offset")){
        offset = settings.get<double>("offset");
    } else {
        offset = 0;
    }
}


bool Plane::HandleMessage(NodeMessage message){
    switch(message.code){
        case MESSAGE_REGISTER_PHYSICS_OFFER: {
            VarMap *physics = new VarMap();
            physics->Add<string>(&geometry,"plane.geometry");
            physics->Add<double3>(&normal,"plane.normal");
            physics->Add<double>(&offset,"plane.offset");
            CreateAndSendMessage(message.sender,MESSAGE_REGISTER_PHYSICS_REQUEST,(void*)physics);
            return true;
        }

        case MESSAGE_REGISTER_PHYSICS_FINISHED: {
            cout << "successfully created physics object\n";
            PhysicsGroup *pGroup = (PhysicsGroup*) message.data;
            geom = pGroup->geom["plane"];
            return true;
        }
    }
    return PhysicalSingleBody::HandleMessage(message);
}

void Plane::Update(){
    Physical::Update();
}

void Plane::Draw(){


        glPushMatrix();
        glTranslated(0,offset,0);

        double3 d = double3(1,1,1);
        glBegin(GL_TRIANGLE_FAN);


			glColor3f(d.x,d.y,d.z);
			glVertex3d(10,0,10);

            glColor3f(d.x,d.y*-1,d.z);
			glVertex3d(10,0,-10);

            glColor3f(d.x,d.y*-1,d.z*-1);
			glVertex3d(-10,0,-10);

            glColor3f(d.x,d.y*-1,d.z*-1);
			glVertex3d(-10,0,10);
		glEnd();
        glPopMatrix();


}

