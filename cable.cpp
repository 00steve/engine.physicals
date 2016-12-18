#include "cable.h"




dBodyID Cable::Body(unsigned int index){
    return bodies[index];
}
unsigned int Cable::BodyCount(){
    return (unsigned int)bodies.GetCount();
}

Cable::Cable() :
    geometry("capsule"),
    jointType("ball-and-socket"),
    segmentCount(10),
    bodies(List<dBodyID>(segmentCount)),
    geoms(List<dGeomID>(segmentCount)),
    gl_matrix(List<float*>(segmentCount)),
    active(List<bool>(segmentCount)),
    length(10),
    radius(.1),
    density(1){

}


Cable::~Cable(){
    //while(bodies.GetCount()){
    //}
    while(joints.GetCount()){
        cout << " kill joint \n";
        dJointDestroy(joints.Pop());
    }
}

void Cable::Draw(){
    if((unsigned int)bodies.GetCount() != segmentCount) return;
    int i = segmentCount;
    double l = length / segmentCount;
    while(i --> 0){
        glPushMatrix();
            glColor3f(0,.5,0);
            glMultMatrixf(gl_matrix[i]);


            GLUquadricObj *quadric = gluNewQuadric();
            gluQuadricDrawStyle(quadric, GLU_SMOOTH );

            glColor3f(0,0,0);
            glBegin(GL_LINES);
                glVertex3f(0,0,l*-.5);
                glVertex3f(0,0,l*.5);
            glEnd();


            glTranslated(0,0,l*.5-radius);
            glColor3f(1,0,0);
            gluSphere(quadric,radius,6,6);

            glTranslated(0,0,-l+radius*2);
            glColor3f(0,0,1);
            gluCylinder(quadric,radius,radius,l-radius*2,6,1);

            glColor3f(0,1,0);
            gluSphere(quadric,radius,6,6);

        glPopMatrix();


    }

    //draw joints
    glPointSize(10);
    glColor3f(0,0,0);
    glBegin(GL_POINTS);
    i = joints.GetCount();
    while(i --> 0){
        glVertex3d(anchorPosition[i].x,anchorPosition[i].y,anchorPosition[i].z);
    }
    glEnd();

}

bool Cable::HandleMessage(NodeMessage message){
    switch(message.code){
    case MESSAGE_REGISTER_PHYSICS_OFFER: {
            VarMap *physics = new VarMap();
            int overlap = 1;
            int i = segmentCount;
            string name;
            while(i --> 0){
                //cout <<  "add capsule num " << i << endl;
                name = numberToString(i);
                physics->Add(&geometry,name + ".geometry");
                physics->Add(new double(length/(double)segmentCount),name + ".length");
                physics->Add(new double(radius),name + ".radius");
                physics->Add(new double3(1,(length/(double)segmentCount)*i*overlap+10,3),name + ".position");
            }


            i = segmentCount-1;
            string jointName;
            string name1;
            string name2;
            while(i --> 0){
                //cout <<  "add joint " << i << endl;
                name1 = numberToString(i);
                name2 = numberToString(i+1);
                jointName = name1 + "_" + name2;
                physics->Add(&jointType,"joints." + jointName + ".type");
                physics->Add(new double3(1,(length/(double)segmentCount)*(i+1)*overlap+10-(length/(double)segmentCount*overlap*.5),3),"joints." + jointName + ".anchor");
                physics->Add(new string(name1),"joints." + jointName + ".body1");
                physics->Add(new string(name2),"joints." + jointName + ".body2");
            }


            CreateAndSendMessage(message.sender,MESSAGE_REGISTER_PHYSICS_REQUEST,(void*)physics);
            return true;
        }
    case MESSAGE_REGISTER_PHYSICS_FINISHED: {

            PhysicsGroup *pGroup = (PhysicsGroup*) message.data;

            int i = segmentCount;
            string name;
            while(i --> 0){
                //cout <<  "add capsule num " << i << endl;
                name = numberToString(i);
                bodies.Push(pGroup->body[name]);
                geoms.Push(pGroup->geom[name]);
                gl_matrix.Push(new float[16]());
                active.Push(false);
                if(bodies.GetCount() > 1){

                }
            }
            List<string> jointGroups = pGroup->joint.AllKeys();
            i = jointGroups.GetCount();
            while(i --> 0){
                joints.Push(pGroup->joint[jointGroups[i]]);
                anchorPosition.Push(double3());
            }
            return true;
        }
    }
    return Physical::HandleMessage(message);
}


void Cable::OnSetSettings(){
    Physical::OnSetSettings();
    VarMap settings = Settings();

    if(settings.IsSet("length")){
        length = settings.get<double>("length");
    }
    if(settings.IsSet("thickness")){
        radius = settings.get<double>("thickness")*.5;
    }
    if(settings.IsSet("segments")){
        segmentCount = (int)settings.get<double>("segments");
    }
}


void Cable::Update(){
    if((unsigned int)bodies.GetCount() == segmentCount){
        int i = segmentCount;
        while(i --> 0){
            if(bodies[i] && (active[i] = dBodyIsEnabled(bodies[i]))){
                PhysicsWorld::GlMatrix(bodies[i],gl_matrix[i]);
            }
        }
        i = joints.GetCount();
        while( i--> 0){
            dVector3 dVec;
            //dJointGetUniversalAnchor2(joints[i],dVec);
            dJointGetBallAnchor(joints[i],dVec);
            anchorPosition[i] = double3(dVec[0],dVec[1],dVec[2]);
        }
    }

    Physical::Update();
}
