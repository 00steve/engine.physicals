#include "cylinder.h"

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

void Cylinder::OnSetWorld(){
    World()->NewCylinder(body,geom,radius,length,density,this);
    Position(position);
}


void Cylinder::Draw(){
    glPushMatrix();
        glMultMatrixf(gl_matrix);
        GLUquadricObj *quadric = gluNewQuadric();
        gluQuadricDrawStyle(quadric, GLU_SMOOTH );
        glTranslated(0,0,-length*.5);
        glColor3f(0,0,1);
        gluCylinder( quadric , radius , radius,length, 40 ,1 );
        glColor3f(0,1,0);
        glRotated(180,1,0,0);
        //glTranslated(0,length,0);
        gluDisk(quadric,0,radius,40,1);

        glTranslated(0,0,-length);
        glRotated(180,1,0,0);
        glColor3f(1,0,0);
        gluDisk(quadric,0,radius,40,1);

        gluDeleteQuadric(quadric);
		glEnd();
    glPopMatrix();
}
