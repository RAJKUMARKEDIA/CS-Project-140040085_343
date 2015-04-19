const int font=(int)GLUT_BITMAP_9_BY_15;
const int font1=(int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2=(int)GLUT_BITMAP_HELVETICA_12;
void renderBitmapString(float x, float y, void *font,const char *string)
{
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}


void mainscreen(void)
{
    glColor3f(0.0,1.0,0.0);
    renderBitmapString(0.4,0.8,(void *)font1,"ARTILLERY DUEL");
    glColor3d(0.0, 1.0, 1.0);
    renderBitmapString(0.44,0.6,(void *)font,"NEW GAME");
    renderBitmapString(0.42,0.45,(void *)font,"INSTRUCTIONS");
    renderBitmapString(0.46,0.30,(void *)font,"EXIT");
    glColor3f(0.5,0.3,0.3);
    glLineWidth(5.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.38,0.55);
    glVertex2f(0.38,0.65);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.38,0.65);
    glVertex2f(0.58,0.65);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.58,0.65);
    glVertex2f(0.58,0.55);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.38,0.55);
    glVertex2f(0.58,0.55);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.38,0.40);
    glVertex2f(0.38,0.50);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.58,0.50);
    glVertex2f(0.38,0.50);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.58,0.40);
    glVertex2f(0.58,0.50);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.38,0.40);
    glVertex2f(0.58,0.40);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.58,0.40);
    glVertex2f(0.58,0.50);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.38,0.35);
    glVertex2f(0.38,0.25);
    glVertex2f(0.58,0.25);
    glVertex2f(0.58,0.35);

    glEnd();
}
void InstructionScreen(void)
{
    glColor3f(0.0,1.0,0.0);
    renderBitmapString(0.4,0.8,(void *)font1,"CONTROLS");
    glColor3d(0.0, 1.0, 1.0);
    renderBitmapString(0.3,0.7,(void *)font,"Increase Power-D          Decrease Power-A");
    renderBitmapString(0.3,0.3,(void *)font,"NOTE: only six moves would be allowed per player.");
    renderBitmapString(0.3,0.6,(void *)font,"Increase Angle-W          Decrease Angle-S");
    renderBitmapString(0.3,0.5,(void *)font,"Move left-Z            Move right-X");
    renderBitmapString(0.3,0.4,(void *)font," FIRE-SPACEBAR");
    glColor3f(0.3,0.5,0.8);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.70,0.10);
    glVertex2f(0.70,0.20);
    glVertex2f(0.90,0.20);
    glVertex2f(0.90,0.10);
    glEnd();
    glLineWidth(5.0);
    glColor3f(0.9,0.3,0.3);
    renderBitmapString(0.73,0.15,(void *)font,"BACK TO MAIN MENU");
}
