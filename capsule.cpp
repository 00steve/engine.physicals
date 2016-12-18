#include "capsule.h"

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

void Capsule::OnSetWorld(){
    World()->NewCapsule(body,geom,radius,length,density,this);
    Position(position);
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
			gluSphere(quadric,radius,20,20);

            glTranslated(0,0,-length+radius*2);
			glColor3f(0,0,1);
			gluCylinder(quadric,radius,radius,length-radius*2,20,1);

            glColor3f(0,1,0);
			gluSphere(quadric,radius,20,20);

    glPopMatrix();
}

