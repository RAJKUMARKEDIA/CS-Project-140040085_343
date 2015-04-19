
void arrow(double xpos,double ypos)
{

    glBegin(GL_LINES);

    glVertex3f(xpos,ypos, 0.0);
    glVertex3f(xpos+0.005,ypos+0.004, 0.0);
}
