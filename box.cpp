#include "box.h"

void Box::OnSetSettings(){
    VarMap settings = Settings();
    if(settings.IsSet("size")){
        List<double> lens = settings.get<List<double> >("size");
        if(lens.GetCount() == 3){
            dimensions = double3(lens[0],lens[1],lens[2]);
        } else {
            cout << "the box size property requires three values, e.g. 1,2,1.5\n";
            dimensions = double3(1,1,1);
        }
    } else {
        dimensions = double3(1,1,1);
    }
    PhysicalSingleBody::OnSetSettings();
}

void Box::OnSetWorld(){
    World()->NewBox(body,geom,dimensions,density,this);
    Position(position);
}

void Box::Draw(){
    glPushMatrix();
        glMultMatrixf(gl_matrix);

        double3 d = dimensions;
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
