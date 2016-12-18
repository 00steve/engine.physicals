#include "sphere.h"


void Sphere::OnSetSettings(){
    VarMap settings = Settings();
    if(settings.IsSet("radius")){
        radius = settings.get<double>("radius");
    } else {
        radius = .5;
    }
    PhysicalSingleBody::OnSetSettings();
}


void Sphere::OnSetWorld(){
    World()->NewSphere(body,geom,radius,density,this);
    Position(position);
}


void Sphere::Draw(){
    glPushMatrix();
        glMultMatrixf(gl_matrix);
        GLUquadricObj *quadric = gluNewQuadric();
        glColor3f(1,0,0);
        gluQuadricDrawStyle(quadric, GLU_FILL );
        gluSphere( quadric , radius , 40 , 35 );
        gluDeleteQuadric(quadric);
    glPopMatrix();

}
