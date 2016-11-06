#include "trimesh.h"

string Trimesh::geometry = "trimesh";


void Trimesh::OnSetSettings(){
    VarMap settings = Settings();
    /*
    if(settings.IsSet("length")){
        length = settings.get<double>("length");
    } else {
        length = 2;
    }
    */

    PhysicalSingleBody::OnSetSettings();
}


bool Trimesh::HandleMessage(NodeMessage message){
    switch(message.code){
    case MESSAGE_REGISTER_PHYSICS_OFFER: {
            VarMap *physics = new VarMap();
            physics->Add<string>(&geometry,"trimesh.geometry");
            physics->Add<double>(&length,"trimesh.length");
            physics->Add<double>(&radius,"trimesh.radius");
            physics->Add<double>(&density,"trimesh.density");
            physics->Add<double3>(&position,"trimesh.position");
            CreateAndSendMessage(message.sender,MESSAGE_REGISTER_PHYSICS_REQUEST,(void*)physics);
            return true;
        }

    case MESSAGE_REGISTER_PHYSICS_FINISHED: {
            PhysicsGroup *pGroup = (PhysicsGroup*) message.data;
            geom = pGroup->geom["trimesh"];
            return true;
        }
    }
    return PhysicalSingleBody::HandleMessage(message);
}

void Trimesh::Draw(){
    glPushMatrix();
    glPopMatrix();
}

