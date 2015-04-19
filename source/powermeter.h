
void Drawbutton()
{
    glColor3f(0.2, 0.0, 1.0);
    glBegin(GL_QUAD_STRIP);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.9, 0.0);
    glVertex3f(0.21, 1.0, 0.0);
    glVertex3f(0.21,0.9,0.0);
    glEnd();
    glColor3f(1.0, 0.2, 0.0);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(0.025, 0.95, 0.0);
    glVertex3f(0.05, 0.925, 0.0);
    glVertex3f(0.05, 0.975, 0.0);
    glEnd();
    glColor3f(0.4, 0.3, 0.1);

    glEnd();
    glColor3f(1.0, 0.2, 0.0);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(0.16, 0.975, 0.0);
    glVertex3f(0.16, 0.925, 0.0);
    glVertex3f(0.185, 0.95, 0.0);
    glEnd();
}
