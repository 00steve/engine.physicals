#include "plane.h"

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

void Plane::OnSetWorld(){
    World()->NewPlane(geom,normal,offset,this);
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

