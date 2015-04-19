#include <GL/glut.h>
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<math.h>

void DrawStars(float fX,float fY)
{
    const float kfPi = 3.1415926535897932384626433832795;
    const float kfRadius = 0.0616/4.0;
    const float kfInnerRadius = kfRadius*(1.0/(sin((2.0*kfPi)/5.0)*2.0*cos(kfPi/10.0) + sin((3.0*kfPi)/10.0)));
    glColor3f(0.4796, 0.3959,0.1244);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(fX, fY, 0.0);
    for (int iVertIndex = 0; iVertIndex < 10; ++iVertIndex)
    {
        float fAngleStart	= kfPi/2.0 + (iVertIndex*2.0*kfPi)/10.0;
        float fAngleEnd	= fAngleStart + kfPi/5.0;
        if (iVertIndex % 2 == 0)
        {
            glVertex3f(fX + kfRadius*cos(fAngleStart)/2.9, fY + kfRadius*sin(fAngleStart), 0.0);
            glVertex3f(fX + kfInnerRadius*cos(fAngleEnd)/2.9, fY + kfInnerRadius*sin(fAngleEnd), 0.0);
        }
        else
        {
            glVertex3f(fX + kfInnerRadius*cos(fAngleStart)/2.9, fY + kfInnerRadius*sin(fAngleStart), 0.0);
            glVertex3f(fX + kfRadius*cos(fAngleEnd)/2.9, fY + kfRadius*sin(fAngleEnd), 0.0);
        }
    }
    glEnd();
}
