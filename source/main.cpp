#include <GL/glut.h>
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "weapon1.h"                                     //insert bullets for multiple shots
#include "weapon2.h"                                    //insert stars
#include "powermeter.h"                                 //header of powermeter
#include<math.h>
#include"startmain.h"                       //header file for inserting texts

#include <windows.h>			// This needs to be included for PlaySound
using namespace std;			// Set our namespace to standard

#pragma comment(lib, "winmm.lib") // Add the Windows library that contains the code for the function PlaySound()
int window=0;
class Point                                             //class Point taking elements as coordinates x & y.
{
public:
    float x,y;
    Point()
    {
        x=0;
        y=0;
    }
    Point(float p,float q)
    {
        x=p;
        y=q;
    }
};
int* angle;                                                                             //variables and pointers
int t=0,angle1=0,angle2=0,count=1,i=0,q=0,o,k,m,p,l=1,acid=0,move1=0,move2=0,missile=0,j,score[2]= {0,0},last=0;
float calibration=0.005,g=-0.98,vx,vy,v,power,vin,x1,x2,x3,x4,tx1=.105,tx2=.885,ty1=.145,ty2=.305;
double a[2][2],z=0,jack=0.0,final,starv=0.7;
Point p1(0.145,0.145),p2(0.845,0.305),star(0,0);
Point pwr,launch,b[20];

void Drawterrain(double x,double y)                         //terrain drawing function
{

    for(int z=0; z<=3; z++)                                 //z variable use for texture formation
    {
        glColor3f(0.0,.45-0.05*z,0.0);
        glBegin(GL_QUAD_STRIP);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(0.0,0.0-0.05*z,0.0);
        glVertex3f(0.25,0.0,0.0);
        glVertex3f(0.25, 0.25-0.05*z, 0.0);

        glEnd();
        glColor3f(0.0, .45-0.05*z,0.0);
        glBegin(GL_QUAD_STRIP);
        glVertex3f( 0.25,0.25-0.05*z,0.0);
        glVertex3f( 0.25,0.0,0.0);
        glVertex3f( a[0][1] ,a[0][0]-0.05*z,0.0);
        glVertex3f(a[0][1],0.0,0.0);

        glEnd();
        glColor3f(0.0, 0.45-0.05*z,0.0);
        glBegin(GL_QUAD_STRIP);
        glVertex3f(a[0][1],a[0][0]-0.05*z ,0.0);
        glVertex3f(a[0][1] ,0.0 ,0.0);
        glVertex3f(a[1][1] ,a[1][0]-0.05*z ,0.0);
        glVertex3f(a[1][1] ,0.0 ,0.0);
        glEnd();
        glColor3f(0.0, 0.45-0.05*z,0.0);
        glBegin(GL_QUAD_STRIP);
        glVertex3f(a[1][1],a[1][0]-0.05*z ,0.0);
        glVertex3f(a[1][1],0.0 ,0.0);
        glVertex3f(0.75,0.4-0.05*z ,0.0);
        glVertex3f(0.75 ,0.0 ,0.0);
        glEnd();
        glColor3f(0.0, 0.45-0.05*z,0.0);
        glBegin(GL_QUAD_STRIP);
        glVertex3f(0.75,0.4-0.05*z ,0.0);
        glVertex3f(0.75 ,0.0 ,0.0);
        glVertex3f(1.00 ,0.15-0.05*z ,0.0);
        glVertex3f(1.00 ,0.0 ,0.0);
        glEnd();
    }
    for(int i=0; i<=count-1; i++)                                           // craters creating code
    {
        {
            if(t==0 || j!=0 || j==0)
            {
                glColor3f(.0,.0,.0);
                glTranslatef(b[i].x ,b[i].y, 0);
                glutSolidSphere(0.025,10,10);
                glTranslatef(-b[i].x,-b[i].y,0.0);
            }
        }
    }
}

void Drawtank()                                                             //animation of tanks, also controlling tanks movements
{
    glColor3f(0.0, 0.8, 0.8);
    glBegin(GL_QUAD_STRIP);
    glVertex3f((11*tx1-3*ty1)/8.0,(11*tx1-3*ty1)/8.0,0.0);                          //tx & ty are used for launcher's position
    glVertex3f(tx1-0.015,ty1-0.015, 0.0);
    glVertex3f((7*ty1+tx1)/8.0, (7*ty1+tx1)/8.0, 0.0);
    glVertex3f(tx1+0.015,ty1+0.015, 0.0);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUAD_STRIP);
    glVertex3f(0.875*(1.15+tx2/7-ty2),1.15-0.875*(1.15+tx2/7-ty2), 0.0);
    glVertex3f(0.375*(ty2+3.6667*tx2-1.15),1.15-0.375*(ty2+3.66667*tx2-1.15), 0.0);
    glVertex3f(tx2-0.015,ty2+0.015, 0.0);
    glVertex3f(tx2+0.015,ty2-0.015, 0.0);
    glEnd();
}
void launcher()                                          //tank's power p.x and p.y launching point
{
    glLineWidth(3.0);
    glColor3f(1.0, 1.0, 1.0);                                                       //tank one
    glBegin(GL_LINE_STRIP);
    glVertex3f(tx1,ty1,0);
    glVertex3f(p1.x,p1.y,0.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.8, 0.8);                                                        //tank two
    glVertex3f(tx2,ty2,0.0);
    glVertex3f(p2.x,p2.y,0.0);
    glEnd();
    glColor3f(0.6, 0.0, 0.3);
    glLineWidth(3.0);
    glBegin(GL_LINE_STRIP);                                                         //draw power bar in the blue power meter
    glVertex3f(power, 0.9, 0.0);
    glVertex3f(power, 1.0, 0.0);
    glEnd();

}

void projectile()                                                                  //main animation part of the program
{
                                                                                  //shoots missiles
    if(missile==3)                  //airstrike
    {
        glColor3f(0.0, 5.0, 2.0);
        if(l==1)
        {
            arrow(launch.x,launch.y);
            b[count-1].x=launch.x;
            b[count-1].y=launch.y;
        }
        glEnd();
        vy+=g*calibration;

        launch.y+=vy*calibration;

        launch.x+=vx*calibration;

        if(vy==vy && q==0)
        {
            x1=launch.x,x2=launch.x,q=1;
            o=1;
            p=1;
            k=1;
            m=1;
        }
        if(o==1 && q==1)
        {
            arrow(x1,launch.y);
            glEnd();
        }
        if(p==1 && q==1)
        {
            arrow(x2,launch.y);
            glEnd();
        }
        if(k==1 && q==1)
        {
            arrow(x3,launch.y);
            glEnd();
        }
        if(m==1 && q==1)
        {
            arrow(x4,launch.y);
            glEnd();
        }
        glFlush();
        x1=launch.x+0.01*calibration*i;
        x2=launch.x-0.01*calibration*i;
        x3=launch.x+0.02*calibration*i;
        x4=launch.x-0.02*calibration*i;
        i=i+2;
        if(launch.x>=1.0)
        {
            l=0;
        }
        if(launch.x<=0.0)
        {
            l=0;
        }
        if(launch.x>=0 && launch.x<.25)
        {
            if((launch.y-0.1)/(launch.x-0.0)<=15.0/25.0)
            {
                l=0;

            }
        }
        if(launch.x>=0.25 && launch.x<a[0][1])
        {
            if((launch.y-0.25)/(launch.x-0.25)<=(a[0][0]-0.25)/(a[0][1]-0.25))
            {
                l=0;

            }
        }
        if(launch.x>=a[0][1] && launch.x<a[1][1])
        {
            if((launch.y-a[0][0])/(launch.x-a[0][1])<=(a[1][0]-a[0][0])/(a[1][1]-a[0][1]))
            {
                l=0;
            }
        }
        if(launch.x>=a[1][1] && launch.x<0.75)
        {
            if((launch.y-0.4)<=(a[1][0]-0.4)/(a[1][1]-0.75)*(launch.x-0.75))
            {
                l=0;
            }
        }
        if(launch.x>=0.75 && launch.x<1)
        {
            if((launch.y-0.4)/(launch.x-0.75)<=-0.2/0.25)
            {
                l=0;
            }
        }


        if(x1>=1.0)
        {
            o=0;
        }
        if(x1<=0.0)
        {
            o=0;
        }
        if(x1>=0 && x1<.25)
        {
            if((launch.y-0.1)/(x1-0.0)<=15.0/25.0)
            {
                o=0;
            }
        }
        if(x1>=0.25 && x1<a[0][1])
        {
            if((launch.y-0.25)/(x1-0.25)<=(a[0][0]-0.25)/(a[0][1]-0.25))
            {
                o=0;
            }
        }
        if(x1>=a[0][1] && x1<a[1][1])
        {
            if((launch.y-a[0][0])/(x1-a[0][1])<=(a[1][0]-a[0][0])/(a[1][1]-a[0][1]))
            {
                o=0;
            }
        }
        if(x1>=a[1][1] && x1<0.75)
        {
            if((launch.y-0.4)<=(a[1][0]-0.4)/(a[1][1]-0.75)*(x1-0.75))
            {
                o=0;
            }
        }
        if(x1>=0.75 && x1<1)
        {
            if((launch.y-0.4)/(x1-0.75)<=-0.2/0.25)
            {
                o=0;
            }
        }
        if(x2>=1.0)
        {
            p=0;
        }
        if(x2<=0.0)
        {
            p=0;
        }
        if(x2>=0 && x2<.25)
        {
            if((launch.y-0.1)/(x2-0.0)<=15.0/25.0)
            {
                p=0;
            }
        }
        if(x2>=0.25 && x2<a[0][1])
        {
            if((launch.y-0.25)/(x2-0.25)<=(a[0][0]-0.25)/(a[0][1]-0.25))
            {
                p=0;
            }
        }
        if(x2>=a[0][1] && x2<a[1][1])
        {
            if((launch.y-a[0][0])/(x2-a[0][1])<=(a[1][0]-a[0][0])/(a[1][1]-a[0][1]))
            {
                p=0;
            }
        }
        if(x2>=a[1][1] && x2<0.75)
        {
            if((launch.y-0.4)<=(a[1][0]-0.4)/(a[1][1]-0.75)*(x2-0.75))
            {
                p=0;
            }
        }
        if(x2>=0.75 && x2<1)
        {
            if((launch.y-0.4)/(x2-0.75)<=-0.2/0.25)
            {
                p=0;
            }
        }
        if(x3>=1.0)
        {
            k=0;
        }
        if(x3<=0.0)
        {
            k=0;
        }
        if(x3>=0 && x3<.25)
        {
            if((launch.y-0.1)/(x3-0.0)<=15.0/25.0)
            {
                k=0;
            }
        }
        if(x3>=0.25 && x3<a[0][1])
        {
            if((launch.y-0.25)/(x3-0.25)<=(a[0][0]-0.25)/(a[0][1]-0.25))
            {
                k=0;
            }
        }
        if(x3>=a[0][1] && x3<a[1][1])
        {
            if((launch.y-a[0][0])/(x3-a[0][1])<=(a[1][0]-a[0][0])/(a[1][1]-a[0][1]))
            {
                k=0;
            }
        }
        if(x3>=a[1][1] && x3<0.75)
        {
            if((launch.y-0.4)<=(a[1][0]-0.4)/(a[1][1]-0.75)*(x3-0.75))
            {
                k=0;
            }
        }
        if(x3>=0.75 && x3<1)
        {
            if((launch.y-0.4)/(x3-0.75)<=-0.2/0.25)
            {
                k=0;
            }
        }
        if(x4>=1.0)
        {
            m=0;
        }
        if(x4<=0.0)
        {
            m=0;
        }
        if(x4>=0 && x4<.25)
        {
            if((launch.y-0.1)/(x4-0.0)<=15.0/25.0)
            {
                m=0;
            }
        }
        if(x4>=0.25 && x4<a[0][1])
        {
            if((launch.y-0.25)/(x4-0.25)<=(a[0][0]-0.25)/(a[0][1]-0.25))
            {
                m=0;
            }
        }
        if(x4>=a[0][1] && x4<a[1][1])
        {
            if((launch.y-a[0][0])/(x4-a[0][1])<=(a[1][0]-a[0][0])/(a[1][1]-a[0][1]))
            {
                m=0;
            }
        }
        if(x4>=a[1][1] && x4<0.75)
        {
            if((launch.y-0.4)<=(a[1][0]-0.4)/(a[1][1]-0.75)*(x4-0.75))
            {
                m=0;
            }
        }
        if(x4>=0.75 && x4<1)
        {
            if((launch.y-0.4)/(x4-0.75)<=-0.2/0.25)
            {
                m=0;
            }
        }

        if(p==0&&l==0&&o==0&&k==0&&m==0)
        {
            j=1;
            t=0;
            missile=0;
            l=1;
            q=0;
            i=0;
            if(count%2==0)
            {
                if(fabs(tx2-launch.x)<=0.02)score[1]+=5;
            }
            if(count%2==0)
            {
                if(fabs(tx2-launch.x)<=0.04)score[1]+=2.5;
            }
            if(count%2==0)
            {
                if(fabs(tx2-x1)<=0.02)score[1]+=5;
            }
            if(count%2==0)
            {
                if(fabs(tx2-x1)<=0.04)score[1]+=2.5;
            }
            {
                if(fabs(tx2-x2)<=0.02)score[1]+=5;
            }
            if(count%2==0)
            {
                if(fabs(tx2-x2)<=0.04)score[1]+=2.5;
            }
            if(count%2==0)
            {
                if(fabs(tx2-x3)<=0.02)score[1]+=5;
            }
            if(count%2==0)
            {
                if(fabs(tx2-x3)<=0.04)score[1]+=2.5;
            }
            if(count%2==0)
            {
                if(fabs(tx2-x4)<=0.02)score[1]+=5;
            }
            if(count%2==0)
            {
                if(fabs(tx2-x4)<=0.04)score[1]+=2.5;
            }
            if(count%2==1)
            {
                if(fabs(tx1-launch.x)<=0.02)score[0]+=5;
            }
            if(count%2==1)
            {
                if(fabs(tx1-launch.x)<=0.04)score[0]+=2.5;
            }
            if(count%2==1)
            {
                if(fabs(tx1-x1)<=0.02)score[0]+=5;
            }
            if(count%2==1)
            {
                if(fabs(tx1-x1)<=0.04)score[0]+=2.5;
            }
            {
                if(fabs(tx1-x2)<=0.02)score[0]+=5;
            }
            if(count%2==1)
            {
                if(fabs(tx1-x2)<=0.04)score[0]+=2.5;
            }
            if(count%2==1)
            {
                if(fabs(tx1-x3)<=0.02)score[0]+=5;
            }
            if(count%2==1)
            {
                if(fabs(tx1-x3)<=0.04)score[0]+=2.5;
            }
            if(count%2==1)
            {
                if(fabs(tx1-x4)<=0.02)score[0]+=5;
            }
            if(count%2==1)
            {
                if(fabs(tx1-x4)<=0.04)score[0]+=2.5;
            }
            cout<<"player1:"<<score[1]<<"   player2:"<<score[0]<<endl;
        }
        glutPostRedisplay();
    }


    if(missile==1)
    {
        glColor3f(.9, .2, .3);                          //sniper
        glBegin(GL_LINES);

        glVertex3f(launch.x,launch.y, 0.0);
        glVertex3f(launch.x+0.02*vx/sqrt(vx*vx+vy*vy),launch.y+0.02*vy/sqrt(vx*vx+vy*vy), 0.0);

        vy+=g*calibration;

        launch.y+=vy*calibration;

        launch.x+=vx*calibration;

        glEnd();
        glFlush();
        glutPostRedisplay();

        if(launch.x>=1.0)
        {
            j=1;
            t=0;
            b[count-1].x=launch.x;
            b[count-1].y=launch.y;
            missile=0;
        }
        if(launch.x<=0.0)
        {
            j=1;
            t=0;
            b[count-1].x=launch.x;
            b[count-1].y=launch.y;
            missile=0;
        }
        if(launch.x>=0 && launch.x<.25)
        {
            if((launch.y-0.1)/(launch.x-0.0)<=15.0/25.0)
            {
                j=1;
                if(count%2==0)
                {
                    {
                        if(fabs(tx2-launch.x)<=0.02)score[1]+=10;
                    }
                    {
                        if(fabs(tx2-launch.x)<=0.04)score[1]+=5;
                    }
                }
                if(count%2==1)
                {
                    {
                        if(fabs(tx1-launch.x)<=0.02)score[0]+=10;
                    }
                    {
                        if(fabs(tx1-launch.x)<=0.04)score[0]+=5;
                    }
                }
                cout<<"player1:"<<score[1]<<"   player2:"<<score[0]<<endl;
                t=0;
                b[count-1].x=launch.x;
                b[count-1].y=launch.y;
                missile=0;
            }
        }
        if(launch.x>=0.25 && launch.x<a[0][1])
        {
            if((launch.y-0.25)/(launch.x-0.25)<=(a[0][0]-0.25)/(a[0][1]-0.25))
            {
                j=1;
                if(count%2==0)
                {
                    {
                        if(fabs(tx2-launch.x)<=0.02)score[1]+=10;
                    }
                    {
                        if(fabs(tx2-launch.x)<=0.04)score[1]+=5;
                    }
                }
                if(count%2==1)
                {
                    {
                        if(fabs(tx1-launch.x)<=0.02)score[0]+=10;
                    }
                    {
                        if(fabs(tx1-launch.x)<=0.04)score[0]+=5;
                    }
                }
                cout<<"player1:"<<score[1]<<"   player2:"<<score[0]<<endl;
                t=0;
                b[count-1].x=launch.x;
                b[count-1].y=launch.y;
                missile=0;
            }
        }
        if(launch.x>=a[0][1] && launch.x<a[1][1])
        {
            if((launch.y-a[0][0])/(launch.x-a[0][1])<=(a[1][0]-a[0][0])/(a[1][1]-a[0][1]))
            {
                j=1;
                if(count%2==0)
                {
                    {
                        if(fabs(tx2-launch.x)<=0.02)score[1]+=10;
                    }
                    {
                        if(fabs(tx2-launch.x)<=0.04)score[1]+=5;
                    }
                }
                if(count%2==1)
                {
                    {
                        if(fabs(tx1-launch.x)<=0.02)score[0]+=10;
                    }
                    {
                        if(fabs(tx1-launch.x)<=0.04)score[0]+=5;
                    }
                }
                cout<<"player1:"<<score[1]<<"   player2:"<<score[0]<<endl;
                t=0;
                b[count-1].x=launch.x;
                b[count-1].y=launch.y;
                missile=0;
            }
        }
        if(launch.x>=a[1][1] && launch.x<0.75)
        {
            if((launch.y-0.4)<=(a[1][0]-0.4)/(a[1][1]-0.75)*(launch.x-0.75))
            {
                j=1;
                if(count%2==0)
                {
                    {
                        if(fabs(tx2-launch.x)<=0.02)score[1]+=10;
                    }
                    {
                        if(fabs(tx2-launch.x)<=0.04)score[1]+=5;
                    }
                }
                if(count%2==1)
                {
                    {
                        if(fabs(tx1-launch.x)<=0.02)score[0]+=10;
                    }
                    {
                        if(fabs(tx1-launch.x)<=0.04)score[0]+=5;
                    }
                }
                cout<<"player1:"<<score[1]<<"   player2:"<<score[0]<<endl;
                t=0;
                cout<<"player1:"<<score[1]<<"   player2:"<<score[0]<<endl;
                b[count-1].x=launch.x;
                b[count-1].y=launch.y;
                missile=0;
            }
        }
        if(launch.x>=0.75 && launch.x<1)
        {
            if((launch.y-0.4)/(launch.x-0.75)<=-0.2/0.25)
            {
                j=1;
                if(count%2==0)
                {
                    {
                        if(fabs(tx2-launch.x)<=0.02)score[1]+=10;
                    }
                    {
                        if(fabs(tx2-launch.x)<=0.04)score[1]+=5;
                    }
                }
                if(count%2==1)
                {
                    {
                        if(fabs(tx1-launch.x)<=0.02)score[0]+=10;
                    }
                    {
                        if(fabs(tx1-launch.x)<=0.04)score[0]+=5;
                    }
                }
                cout<<"player1:"<<score[1]<<"   player2:"<<score[0]<<endl;
                t=0;
                missile=0;
            }
        }
    }

    if(missile==2)
    {
        glColor3f(.9, .2, .3);                           //  threeshots
        if(l==1)
        {
            arrow(launch.x,launch.y);
            b[count-1].x=launch.x;
            b[count-1].y=launch.y;
        }
        glEnd();
        vy+=g*calibration;

        launch.y+=vy*calibration;

        launch.x+=vx*calibration;

        if(vy==vy && q==0)
        {
            x1=launch.x,x2=launch.x,q=1;
            o=1;
            p=1;
        }
        if(o==1 && q==1)
        {
            arrow(x1,launch.y);
            glEnd();
        }
        if(p==1 && q==1)
        {
            arrow(x2,launch.y);
            glEnd();
        }
        glFlush();
        x1=launch.x+0.01*calibration*i;
        x2=launch.x-0.01*calibration*i;
        i=i+2;
        if(launch.x>=1.0)
        {
            l=0;
        }
        if(launch.x<=0.0)
        {
            l=0;
        }
        if(launch.x>=0 && launch.x<.25)
        {
            if((launch.y-0.1)/(launch.x-0.0)<=15.0/25.0)
            {
                l=0;
            }
        }
        if(launch.x>=0.25 && launch.x<a[0][1])
        {
            if((launch.y-0.25)/(launch.x-0.25)<=(a[0][0]-0.25)/(a[0][1]-0.25))
            {
                l=0;
            }
        }
        if(launch.x>=a[0][1] && launch.x<a[1][1])
        {
            if((launch.y-a[0][0])/(launch.x-a[0][1])<=(a[1][0]-a[0][0])/(a[1][1]-a[0][1]))
            {
                l=0;
            }
        }
        if(launch.x>=a[1][1] && launch.x<0.75)
        {
            if((launch.y-0.4)<=(a[1][0]-0.4)/(a[1][1]-0.75)*(launch.x-0.75))
            {
                l=0;
            }
        }
        if(launch.x>=0.75 && launch.x<1)
        {
            if((launch.y-0.4)/(launch.x-0.75)<=-0.2/0.25)
            {
                l=0;

            }
        }


        if(x1>=1.0)
        {
            o=0;
        }
        if(x1<=0.0)
        {
            o=0;
        }
        if(x1>=0 && x1<.25)
        {
            if((launch.y-0.1)/(x1-0.0)<=15.0/25.0)
            {
                o=0;
            }
        }
        if(x1>=0.25 && x1<a[0][1])
        {
            if((launch.y-0.25)/(x1-0.25)<=(a[0][0]-0.25)/(a[0][1]-0.25))
            {
                o=0;
            }
        }
        if(x1>=a[0][1] && x1<a[1][1])
        {
            if((launch.y-a[0][0])/(x1-a[0][1])<=(a[1][0]-a[0][0])/(a[1][1]-a[0][1]))
            {
                o=0;
            }
        }
        if(x1>=a[1][1] && x1<0.75)
        {
            if((launch.y-0.4)<=(a[1][0]-0.4)/(a[1][1]-0.75)*(x1-0.75))
            {
                o=0;
            }
        }
        if(x1>=0.75 && x1<1)
        {
            if((launch.y-0.4)/(x1-0.75)<=-0.2/0.25)
            {
                o=0;
            }
        }
        if(x2>=1.0)
        {
            p=0;
        }
        if(x2<=0.0)
        {
            p=0;
        }
        if(x2>=0 && x2<.25)
        {
            if((launch.y-0.1)/(x2-0.0)<=15.0/25.0)
            {
                p=0;
            }
        }
        if(x2>=0.25 && x2<a[0][1])
        {
            if((launch.y-0.25)/(x2-0.25)<=(a[0][0]-0.25)/(a[0][1]-0.25))
            {
                p=0;
            }
        }
        if(x2>=a[0][1] && x2<a[1][1])
        {
            if((launch.y-a[0][0])/(x2-a[0][1])<=(a[1][0]-a[0][0])/(a[1][1]-a[0][1]))
            {
                p=0;
            }
        }
        if(x2>=a[1][1] && x2<0.75)
        {
            if((launch.y-0.4)<=(a[1][0]-0.4)/(a[1][1]-0.75)*(x2-0.75))
            {
                p=0;
            }
        }
        if(x2>=0.75 && x2<1)
        {
            if((launch.y-0.4)/(x2-0.75)<=-0.2/0.25)
            {
                p=0;
            }
        }
        if(p==0&&l==0&&o==0)
        {
            j=1;
            t=0;
            missile=0;
            l=1;
            q=0;
            i=0;
            if(count%2==0)
            {
                if(fabs(tx2-launch.x)<=0.02)score[1]+=5;
            }
            if(count%2==0)
            {
                if(fabs(tx2-launch.x)<=0.04)score[1]+=2.5;
            }
            if(count%2==0)
            {
                if(fabs(tx2-x1)<=0.02)score[1]+=5;
            }
            if(count%2==0)
            {
                if(fabs(tx2-x1)<=0.04)score[1]+=2.5;
            }
            {
                if(fabs(tx2-x2)<=0.02)score[1]+=5;
            }
            if(count%2==0)
            {
                if(fabs(tx2-x2)<=0.04)score[1]+=2.5;
            }
            if(count%2==1)
            {
                if(fabs(tx1-launch.x)<=0.02)score[0]+=5;
            }
            if(count%2==1)
            {
                if(fabs(tx1-launch.x)<=0.04)score[0]+=2.5;
            }
            if(count%2==1)
            {
                if(fabs(tx1-x1)<=0.02)score[0]+=5;
            }
            if(count%2==1)
            {
                if(fabs(tx1-x1)<=0.04)score[0]+=2.5;
            }
            {
                if(fabs(tx1-x2)<=0.02)score[0]+=5;
            }
            if(count%2==1)
            {
                if(fabs(tx1-x2)<=0.04)score[0]+=2.5;
            }
            cout<<"player1:"<<score[1]<<"   player2:"<<score[0]<<endl;

        }
        glutPostRedisplay();                                         //function use to show continuous animation in opengl
    }                                                                 // it recalls function again and again

    if(missile==4)
    {
        glColor3f(.9, .2, .3);                             // hammer
        vy+=g*3*calibration;

        launch.y+=vy*2.5*calibration;

        launch.x+=vx*2.5*calibration;
        glTranslatef(launch.x,launch.y,0.0);
        glutSolidSphere(0.01,30,5);
        glTranslatef(-launch.x,-launch.y,0.0);
        glEnd();
        glFlush();
        if(launch.x>=1.0)
        {

            j=1;
            t=0;
            b[count-1].x=launch.x;
            b[count-1].y=launch.y;
            missile=0;
        }
        if(launch.x<=0.0)
        {
            j=1;
            t=0;
            b[count-1].x=launch.x;
            b[count-1].y=launch.y;
            missile=0;
        }
        if(launch.x>=0 && launch.x<.25)
        {
            if((launch.y-0.1)/(launch.x-0.0)<=15.0/25.0)
            {
                jack=jack+0.2;
                vx=0;
                vy=1;
            }
        }
        if(launch.x>=0.25 && launch.x<a[0][1])
        {
            if((launch.y-0.25)/(launch.x-0.25)<=(a[0][0]-0.25)/(a[0][1]-0.25))
            {
                jack=jack+0.2;
                vx=0;
                vy=1;
            }
        }
        if(launch.x>=a[0][1] && launch.x<a[1][1])
        {
            if((launch.y-a[0][0])/(launch.x-a[0][1])<=(a[1][0]-a[0][0])/(a[1][1]-a[0][1]))
            {
                jack=jack+0.2;
                vx=0;
                vy=1;
            }
        }
        if(launch.x>=a[1][1] && launch.x<0.75)
        {
            if((launch.y-0.4)<=(a[1][0]-0.4)/(a[1][1]-0.75)*(launch.x-0.75))
            {
                jack=jack+0.2;
                vx=0;
                vy=1;
            }
        }
        if(launch.x>=0.75 && launch.x<1)
        {
            if((launch.y-0.4)/(launch.x-0.75)<=-0.2/0.25)
            {
                jack=jack+0.2;
                vx=0;
                vy=1;
            }
        }

        if(jack==1.0)
        {
            j=1;
            t=0;
            b[count-1].x=launch.x;
            b[count-1].y=launch.y;
            missile=0;
            jack=0;
            if(count%2==0)
            {
                {
                    if(fabs(tx2-launch.x)<=0.02)score[1]+=30;
                }
                {
                    if(fabs(tx2-launch.x)<=0.04)score[1]+=10;
                }
            }
            if(count%2==1)
            {
                {
                    if(fabs(tx1-launch.x)<=0.02)score[0]+=30;
                }
                {
                    if(fabs(tx1-launch.x)<=0.04)score[0]+=10;
                }
            }
            cout<<"player1:"<<score[1]<<"   player2:"<<score[0]<<endl;

        }
    }

    if(missile==5)
    {
        vy+=g*calibration;                                   //miracle bomb
        launch.y+=vy*calibration;
        launch.x+=vx*calibration;
        glColor3f(0.4796, 0.3959,0.1244);
        glTranslatef(launch.x,launch.y,0.0);
        glutSolidSphere(0.015,30,5);
        glTranslatef(-launch.x,-launch.y,0.0);
        glEnd();
        glFlush();
        if(launch.x>=1.0)
        {
            j=1;
            t=0;
            b[count-1].x=launch.x;
            b[count-1].y=launch.y;
            missile=0;
        }
        if(launch.x<=0.0)
        {
            j=1;
            t=0;
            b[count-1].x=launch.x;
            b[count-1].y=launch.y;
            missile=0;
        }
        if(launch.x>=0 && launch.x<.25)
        {
            if((launch.y-0.1)/(launch.x-0.0)<=15.0/25.0)
            {
                acid=acid+1,final=launch.y,g=0,vy=0,vx=0,launch.y=0.75,star.x=launch.x,star.y=0.025+final;
            }
        }
        if(launch.x>=0.25 && launch.x<a[0][1])
        {
            if((launch.y-0.25)/(launch.x-0.25)<=(a[0][0]-0.25)/(a[0][1]-0.25))
            {
                acid=acid+1,final=launch.y,g=0,vy=0,vx=0,launch.y=0.75,star.x=launch.x,star.y=0.025+final;
            }
        }
        if(launch.x>=a[0][1] && launch.x<a[1][1])
        {
            if((launch.y-a[0][0])/(launch.x-a[0][1])<=(a[1][0]-a[0][0])/(a[1][1]-a[0][1]))
            {
                acid=acid+1,final=launch.y,g=0,vy=0,vx=0,launch.y=0.75,star.x=launch.x,star.y=0.025+final;
            }
        }
        if(launch.x>=a[1][1] && launch.x<0.75)
        {
            if((launch.y-0.4)<=(a[1][0]-0.4)/(a[1][1]-0.75)*(launch.x-0.75))
            {
                acid=acid+1,final=launch.y,g=0,vy=0,vx=0,launch.y=0.75,star.x=launch.x,star.y=0.025+final;
            }
        }
        if(launch.x>=0.75 && launch.x<1)
        {
            if((launch.y-0.4)/(launch.x-0.75)<=-0.2/0.25)
            {
                acid=acid+1,final=launch.y,g=0,vy=0,vx=0,launch.y=0.75,star.x=launch.x,star.y=0.025+final;
            }
        }

        if(acid==1||acid==2||acid==3||acid==4||acid==5)
        {
            float g1=-0.98;
            starv+=g1*calibration;
            star.y=starv+g1*calibration;
            DrawStars(star.x,star.y);
            if(star.y<=final)
            {
                acid=acid+1;
                star.y=0.025+final;
                starv=0.7;
                if(acid==2)
                    star.x=star.x-0.007;
                if(acid==3)
                    star.x=star.x+0.015;
                if(acid==4)
                    star.x=star.x-0.01;
                if(acid==5)
                    star.x=star.x+0.009;

            }

        }
        if(acid==6)
        {
            t=0;
            g=-0.98;
            star.x=0;
            star.y=0;
            acid=0;
            missile=0;
            if(count%2==0)
            {
                {
                    if(fabs(tx2-launch.x)<=0.02)score[1]+=30;
                }
                {
                    if(fabs(tx2-launch.x)<=0.04)score[1]+=10;
                }
            }
            if(count%2==1)
            {
                {
                    if(fabs(tx1-launch.x)<=0.02)score[0]+=30;
                }
                {
                    if(fabs(tx1-launch.x)<=0.04)score[0]+=10;
                }
            }
            cout<<"player1:"<<score[1]<<"   player2:"<<score[0]<<endl;

        }
    }
    if(t==0 && count==12)                                       //stops game when count==12....... game stops after 10 chances
    {                                                          //t is used to stop and start projectile function

        if(score[1]>score[0])                                    //game stops when spacebar is pressed on 11th turn
        {
            cout<<"player1 wins";
        }
        if(score[0]>score[1])
        {
            cout<<"player2 wins";
        }
        if(score[1]==score[0])
        {
            cout<<"DRAW";
        }

        exit(0);

    }
}

void keyboard(unsigned char key, int x, int y)                                          //Function for keyboard input.
{
    j=0;

    if(t==0)                                                              //to restrict keyboard inputs while projectile is in motion
    {
        if(count%2==1)
        {
            angle=&angle1;                         //pointer to angle1 and angle2
            power=pwr.x;
            launch=p1;
        }
        if(count%2==0)
        {
            angle=&angle2;
            power=pwr.y;
            launch=p2;
        }

        switch (key)
        {

        case 83:                                                                                    //S
            *angle=*angle-1;
            if(count%2==0)
            {
                p2.x=-0.04*cos(*angle*3.14159265359/180)+tx2;
                p2.y=0.04*sin(*angle*3.14159265359/180)+ty2;
            }
            if(count%2==1)
            {
                p1.x=0.04*cos(*angle*3.14159265359/180)+tx1;
                p1.y=0.04*sin(*angle*3.14159265359/180)+ty1;
            }
            launcher();
            break;

        case 119:                                                                        //w
            *angle=*angle+1;
            if(count%2==0)
            {
                p2.x=-0.04*cos(*angle*3.14159265359/180)+tx2;
                p2.y=0.04*sin(*angle*3.14159265359/180)+ty2;
            }
            if(count%2==1)
            {
                p1.x=0.04*cos(*angle*3.14159265359/180)+tx1;
                p1.y=0.04*sin(*angle*3.14159265359/180)+ty1;
            }
            launcher();
            break;

        case 87:                                                                       //W
            *angle=*angle+1;
            if(count%2==0)
            {
                p2.x=-0.04*cos(*angle*3.14159265359/180)+tx2;
                p2.y=0.04*sin(*angle*3.14159265359/180)+ty2;
            }
            if(count%2==1)
            {
                p1.x=0.04*cos(*angle*3.14159265359/180)+tx1;
                p1.y=0.04*sin(*angle*3.14159265359/180)+ty1;
            }
            launcher();
            break;
        case 115:                                                                       //s
            *angle=*angle-1;
            if(count%2==0)
            {
                p2.x=-0.04*cos(*angle*3.14159265359/180)+tx2;
                p2.y=0.04*sin(*angle*3.14159265359/180)+ty2;
            }
            if(count%2==1)
            {
                p1.x=0.04*cos(*angle*3.14159265359/180)+tx1;
                p1.y=0.04*sin(*angle*3.14159265359/180)+ty1;
            }
            launcher();
            break;
        case 68:                                                                      //D
            if (power>(0.21-0.0042))
            {
                power=0.21;

                break;
            }
            else  power=power+0.0042;
            v=power/0.15;
            if(count%2==1)pwr.x=power;
            if(count%2==0)pwr.y=power;
            launcher();
            break;
        case 100:                                                                        //d
            if (power>(0.21-0.0042))
            {
                power=0.21;
                break;
            }
            else  power=power+0.0042;
            v=power/0.15;
            if(count%2==1)pwr.x=power;
            if(count%2==0)pwr.y=power;
            launcher();
            break;

        case 65:                                                                              //A
            if (power<0.0042)
            {
                power=0;
                break;
            }
            else
                power=power-0.0042;
            v=power/0.15;
            if(count%2==1)pwr.x=power;
            if(count%2==0)pwr.y=power;
            launcher();
            break;

        case 97:                                                                                    //a
            if (power<0.0042)
            {
                power=0;
                break;
            }
            else
                power=power-0.0042;
            if(count%2==1)pwr.x=power;
            if(count%2==0)pwr.y=power;
            launcher();
            break;

        case 32:                                                                                        //fire
            if(missile!=0)
            {
                v=power/0.15;
                count=count+1;
                vx=pow(-1,count)*v*cos(*angle*3.14159265359/180.0);
                vy=v*sin(*angle*3.14159265359/180.0);
                projectile();
                t=1;
            }
            else cout<<"choose missile"<<endl;
            break;

        case 90:                                                                               //Z
            if(count%2==1&&move1<=6)
            {
                tx1-=0.015;
                ty1-=0.015,p1.x-=0.015,p1.y-=0.015;
                Drawtank();
                launcher();
                move1=move1+1;
                break;
            }
            if(count%2==0&&move2<=6)
            {
                tx2-=0.015;
                ty2+=0.015,p2.x-=0.015,p2.y+=0.015;
                Drawtank();
                launcher();
                move2=move2+1;
                break;
            }
        case 122:                                                                               //z
            if(count%2==1&&move1<=6)
            {
                tx1-=0.015;
                ty1-=0.015,p1.x-=0.015,p1.y-=0.015;
                Drawtank();
                launcher();
                move1=move1+1;
                break;
            }
            if(count%2==0&&move2<=6)
            {
                tx2-=0.015;
                ty2+=0.015,p2.x-=0.015,p2.y+=0.015;
                Drawtank();
                launcher();
                move2=move2+1;
                break;
            }
        case 88:                                                                              //S
            if(count%2==1&&move1<=6)
            {
                tx1+=0.015;
                ty1+=0.015,p1.x+=0.015,p1.y+=0.015;
                Drawtank();
                launcher();
                move1=move1+1;
                break;
            }
            if(count%2==0&&move2<=6)
            {
                tx2+=0.015;
                ty2-=0.015,p2.x+=0.015,p2.y-=0.015;
                Drawtank();
                launcher();
                move2=move2+1;
                break;
            }
        case 120:                                                                             //x
            if(count%2==1&&move1<=6)
            {
                tx1+=0.015;
                ty1+=0.015,p1.x+=0.015,p1.y+=0.015;
                Drawtank();
                launcher();
                move1=move1+1;
                break;
            }
            if(count%2==0&&move2<=6)
            {
                tx2+=0.015;
                ty2-=0.015,p2.x+=0.015,p2.y-=0.015;
                Drawtank();
                launcher();
                move2=move2+1;
                break;
            }
        }
    }
}



void weapon()                                                                      //weaponlist
{
    glColor3f(.2, 0.2, 1.0);
    renderBitmapString(0.01,0.395,(void *)font2,"sniper");
    renderBitmapString(0.01,0.445,(void *)font2,"3shots");
    renderBitmapString(0.01,0.495,(void *)font2,"airstrike");
    renderBitmapString(0.013,0.545,(void *)font2,"hammer");
    renderBitmapString(0.01,0.595,(void *)font2,"miracle bomb" );
    glColor3f(.2, 0.2, 1.0);
    glBegin(GL_LINE_LOOP);                                                        //test boxes and texts
    glVertex2f(0.008,0.38);
    glVertex2f(0.008,0.42);
    glVertex2f(0.04,0.42);
    glVertex2f(0.04,0.38);
    glEnd();
    glColor3f(.2, 0.2, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.008,0.43);
    glVertex2f(0.008,0.47);
    glVertex2f(0.04,0.47);
    glVertex2f(0.04,0.43);
    glEnd();
    glColor3f(.2, 0.2, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.008,0.48);
    glVertex2f(0.008,0.52);
    glVertex2f(0.045,0.52);
    glVertex2f(0.045,0.48);
    glEnd();
    glColor3f(.2, 0.2, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.008,0.53);
    glVertex2f(0.008,0.57);
    glVertex2f(0.05,0.57);
    glVertex2f(0.05,0.53);
    glEnd();
    glColor3f(.2, 0.2, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.006,0.58);
    glVertex2f(0.006,0.62);
    glVertex2f(0.07,0.62);
    glVertex2f(0.07,0.58);
    glEnd();
}
Point mouse(int x,int y)                                                              //mouse adjustment according to opengl window
{
    int windowwidth=1300,windowheight=600;
    return Point((float(x)/windowwidth),1.0-float(y)/windowheight);
}
void mouse_click(int button,int state,int x,int y)
{
    Point mouse_point=mouse(x,y);
    if ((button==GLUT_LEFT_BUTTON)&&(state==GLUT_UP))                   //mouse click of left button
    {
        if(mouse_point.x<0.58&mouse_point.x>0.38&&mouse_point.y<0.65&&mouse_point.y>0.55)
        {
            window=1;                                                                         //battlefield
            glutPostRedisplay();
        }
        if(mouse_point.x<0.58&&mouse_point.x>0.38&&mouse_point.y<0.50&&mouse_point.y>0.40)
        {
            window=2;                                                                                //instructions
            glutPostRedisplay();
        }
        if(mouse_point.x<0.90&&mouse_point.x>0.70&&mouse_point.y>0.10&&mouse_point.y<0.20)
        {
            window=0;                                                                           //main screen
            glutPostRedisplay();
        }
        if(mouse_point.x<0.58&&mouse_point.x>0.38&&mouse_point.y>0.25&&mouse_point.y<0.35)
        {
            exit(0);
        }
        if(missile==0)                                                  //missile selection and missiles change restriction
        {
            if(mouse_point.x<=0.04 && mouse_point.x>=0.008 && mouse_point.y<=0.42 && mouse_point.y>=0.38)
            {
                missile=1;
            }
            if(mouse_point.x<=0.04 && mouse_point.x>=0.008 && mouse_point.y<=0.47 && mouse_point.y>=0.43)
            {
                missile=2;
            }
            if(mouse_point.x<=0.045 && mouse_point.x>=0.008 && mouse_point.y<=0.52 && mouse_point.y>=0.48)
            {
                missile=3;
            }
            if(mouse_point.x<=0.05 && mouse_point.x>=0.008 && mouse_point.y<=0.57 && mouse_point.y>=0.53)
            {
                missile=4;
            }
            if(mouse_point.x<=0.07 && mouse_point.x>=0.006 && mouse_point.y<=0.62 && mouse_point.y>=0.58)
            {
                missile=5;
            }
        }
    }
}
void Draw()
{

    glClear(GL_COLOR_BUFFER_BIT);
    if(window==1)
    {
        Drawterrain(b[count-1].x,b[count-1].y);                             //craters creating function on the terrain
        Drawbutton();
        Drawtank();
        launcher();
        weapon();
    }
    if(window==0)
    {
        mainscreen();
    }
    if(window==2)
    {
        InstructionScreen();
    }
    if(t==1)
    {
        projectile();
    }

    glFlush();


    glutPostRedisplay();
}


void Initialize()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int iArgc, char** cppArgv)
{
    srand (time(0));
    int number=rand();
    a[0][1]=0.3+(number%26)/100.0;;
    a[1][1]=((rand()%20)+1)/100.0+0.3+(number%26)/100.0;;
    a[0][0]=0.3+(number%15)/100.0;
    a[1][0]=0.3+(number%15)/100.0+pow(-1,number)*(number%16)/100.0;
    glutInit(&iArgc, cppArgv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1300,600);
    glutInitWindowPosition(50,40);
    glutCreateWindow("POCKET TANKS");
    Initialize();

    PlaySound("voiceplayback.wav", NULL, SND_FILENAME | SND_ASYNC);


    for(int i = 0; i < 50; i++)
    {
        Sleep(50);				// Pause the program for 1/20 of a second (1000 = 1 second)
    }

    glutDisplayFunc(Draw);
    glutKeyboardFunc (keyboard);
    glutMouseFunc(mouse_click);
    glutMainLoop();
    return 0;
}
