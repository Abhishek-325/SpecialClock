#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <GL/glut.h>
#define M_TWOPI 360

// define glu objects
GLUquadricObj *Cylinder; //an object that can be defined by a quadratic quation
GLUquadricObj *Disk;

struct tm *newtime;
time_t ltime;
GLfloat rx, ry, rz, angle;
static int hour,minute,sec=0,al=0,ahr,amin,err=0,errm=0,alarmOn=0,alarmOff=1;
char alarm[10];
int j=0;
static float exp1=0.2;
static float expp2=1.0;
static float exp3=1.0;
// lighting
GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightPosition[]= { 5.0f, 25.0f, 15.0f, 1.0f };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };

static int light_state = 1; // light on = 1, light off = 0
static int view_state = 1; // Ortho view = 1, Perspective = 0


void Sprint( float x, float y, char *st)
{
	int l,i;
	//glColor3f(1.,0.0,0.0);
	l=strlen( st );
	glRasterPos3f( x, y, -1);
	for( i=0; i < l; i++)
		{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]);
	}
}

void Cprint( float x, float y, char st)
{
	int l,i;
	//glColor3f(1.,0.0,0.0);
	glRasterPos3f( x, y, -1);
		{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st);
	}
}
static void TimeEvent(int te)
{
	int timent;
	int i;
        if(sec>=59)
        {
         exp1=0.2;
	 expp2=1.0;
         exp3=1.0;
        }
        if(hour==ahr&&minute==amin&&alarmOff==1)
        {
          alarmOn=1;
          al=0; 
          system("./sam Time to wake up.");
        }
        rx = 30 * cos( angle );
	ry = 30 * sin( angle );
	rz = 30 * cos( angle );
	angle += 0.01;
	if (angle > M_TWOPI) angle = 0;
 	 glutPostRedisplay(); 
	glutTimerFunc( 1000, TimeEvent, 1);
}
void init(void)
{

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
   // Lighting is added to scene
   glLightfv(GL_LIGHT1 ,GL_AMBIENT, LightAmbient);
   glLightfv(GL_LIGHT1 ,GL_DIFFUSE, LightDiffuse);
   glLightfv(GL_LIGHT1 ,GL_POSITION, LightPosition);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT1);


   Cylinder = gluNewQuadric();
   gluQuadricDrawStyle( Cylinder, GLU_FILL);
   gluQuadricNormals( Cylinder, GLU_SMOOTH);
   gluQuadricOrientation( Cylinder, GLU_OUTSIDE);
   gluQuadricTexture( Cylinder, GL_TRUE);

   Disk = gluNewQuadric();
   gluQuadricDrawStyle( Disk, GLU_LINE);
   gluQuadricNormals( Disk, GLU_SMOOTH);
   gluQuadricOrientation( Disk, GLU_OUTSIDE);
   gluQuadricTexture( Disk, GL_TRUE);

}

void Draw_gear( void )
{
	int i;
	glPushMatrix();
	gluCylinder(Cylinder, 2.5, 2.5, 1, 16, 16); //quadric_object,base,top,height,slices,stack
	gluDisk(Disk, 0, 2.5, 32, 16);
	glTranslatef(0,0,1);
        gluDisk(Disk, 0, 2.5, 32, 16);
	glPopMatrix();
        for( i = 0; i < 20; i++)
	{
                glPushMatrix();
		glTranslatef( 0.0, 0.0, 0.50);
		glRotatef( (360/20) * i, 0.0, 0.0, 1.0);
		glTranslatef( 3.0, 0.0, 0.0);
		glutSolidCube(1.1 );
		glPopMatrix();
	    }
}
void Sub_gear( void )
{
	int i;
	glPushMatrix();
	gluCylinder(Cylinder, 2.5, 2.5, 1, 16, 16); //quadric_object,base,top,height,slices,stack
	gluDisk(Disk, 0, 2.5, 32, 16);
	glTranslatef(0,0,1);
        gluDisk(Disk, 0, 2.5, 32, 16);
	glPopMatrix();
        for( i = 0; i < 20; i++)
	{
                glPushMatrix();
		glTranslatef( 0.0, 0.0, 0.50);
		glRotatef( (360/20) * i, 0.0, 0.0, 1.0);
		glTranslatef( 1.0, 0.0, 0.0);
		glutSolidCube(0.4 );
		glPopMatrix();
	    }
}
void Draw_clock( GLfloat cx, GLfloat cy, GLfloat cz )
{

  int hour_ticks , sec_ticks;
  char *num[]={'3','4','5','6','7','8','9','01','11','21','1','2'};
 
  glPushMatrix();
  glTranslatef(cx,cy,cz);
  glRotatef( 180, 1.0, 0.0, 0.0);
  glPushMatrix(); // Draw large wire cube
  glColor3f(1.0, 1.0, 0.0);
  glTranslatef( -0.2,-5.7, 6.0);
  glRectf(-1.8,4.0,2.0,2.0);
  glPopMatrix();
  glPushMatrix();// Draw hour hand
  glColor3f(0.8, 0.0, 0.0);
  glTranslatef( 0, 0, 0.0);
//  glRotatef( ((360/12) * newtime->tm_hour)   + ((360/30) * (60 / (newtime->tm_min+1))), 0.0, 0.0, 1.0);
  glRotatef( ((360/12) * newtime->tm_hour), 0.0, 0.0, 1.0);
  glRotatef( 90, 1.0, 0.0, 0.0);
  gluCylinder(Cylinder, 0.75, 0, 4, 16, 16);
  glPopMatrix();

  glPushMatrix();// Draw minute hand
  glColor3f(0.0, 0.0, 1.0);
  glTranslatef( 0, 0, 0.0);
  glRotatef( (360/60) * newtime->tm_min, 0.0, 0.0, 1.0)
  glRotatef( 90, 1.0, 0.0, 0.0);
  gluCylinder(Cylinder, 0.5, 0, 6, 16, 16); //last two parameters are orignially 16
  glPopMatrix();

  glPushMatrix();// Draw second hand
  glColor3f(1.0, 1.0, 1.0);
  glTranslatef( 0, 0, -0.0);
  glRotatef( (360/60) * newtime->tm_sec, 0.0, 0.0, 1.0);
  glPushMatrix();
  glTranslatef(0.0, 0.0, 4.0);
  glScalef(0.25, 0.25, 1.0);
  Draw_gear();
  glPopMatrix();
  glRotatef( 90, 1.0, 0.0, 0.0);
  gluCylinder(Cylinder, 0.25, 0, 6, 16, 16);
  glPopMatrix();
  for(hour_ticks = 0; hour_ticks < 12; hour_ticks++)
	  {
	  glPushMatrix();// Draw next arm axis.
         glColor3f(0.0, 1.0, 0.0); // give it a color
	  glTranslatef(0.0, 0.0, 0.0);
	  glRotatef( (360/12) * hour_ticks, 0.0, 0.0, 1.0);
      glTranslatef(6.0, 0.0, 0.0);
	Sprint(0.0,0.0,&num[hour_ticks]);
      glPopMatrix();
  }
  for(sec_ticks = 0; sec_ticks < 60; sec_ticks++)
	 {
   	glPushMatrix();
        glColor3f(0.0, 0.8, 1.0); // give it a color
	glTranslatef(0.0, 0.1, 0.0);
	glRotatef( (360/60) * sec_ticks, 0.0, 0.0, 1.0);
	glTranslatef(7.0, 0.0, 0.0);
        glutSolidCube(0.2);
	glPopMatrix();
	}

  for(sec_ticks = 0; sec_ticks < 900; sec_ticks++)
	 {
   	glPushMatrix();
        glColor3f(exp1,expp2,exp3); // give it a color
	glTranslatef(0.0, 0.1, 0.0);
	glRotatef( (360/60) * sec_ticks, 0.0, 0.0, 1.0);
	glTranslatef(7.6, 0.0, 0.0);
        glutSolidCube(0.7);
	glPopMatrix();
	}
  //FIRST SMALL CLOCK
glTranslatef(-2.8, 0.0, 0.0);
  for(sec_ticks = 0; sec_ticks < 900; sec_ticks++)
	 {
   	glPushMatrix();
        glColor3f(0.0,1.0,0.0); // give it a color
	glTranslatef(0.0, 0.1,0.0);
	glRotatef( (360/60) * sec_ticks, 0.0, 0.0, 1.0);
	glTranslatef(1.9, 0.0, 0.0);
        glutSolidCube(0.18);
	glPopMatrix();
	}
  glPushMatrix();// Draw minute hand
  glTranslatef( 0, 0, 0.0);
 glColor3f(1.0, 0.0, 0.0);
  glRotatef( (360/60) * ((newtime->tm_min) - 30), 0.0, 0.0, 1.0);
  glPushMatrix();
  glTranslatef(0.0, 0.0, 3.0); 
  glPopMatrix();
  glRotatef( 90, 1.0, 0.0, 0.0);
  gluCylinder(Cylinder, 0.5, 0, 2, 3, 3);
  glPopMatrix();

glPushMatrix();// Draw hour hand
  glTranslatef( 0, 0, 0.0);
  glRotatef( (360/12) * ((newtime->tm_hour) - 7), 0.0, 0.0, 1.0);
  glPushMatrix();
  glTranslatef(0.0, 0.0, 2.0);
  glScalef(0.2, 0.2, 1.0);
  glColor3f(1.0, 1.0, 1.0);
  Draw_gear();
  glPopMatrix();
  glRotatef( 90, 1.0, 0.0, 0.0);
  gluCylinder(Cylinder, 0.5, 0, 1.4, 3, 3);
  glPopMatrix();

  Sprint(-1.5,3.0,"Mid Atlantic");
  //Melbourne
glTranslatef(5.6, 0.0, 0.0);
  for(sec_ticks = 0; sec_ticks < 900; sec_ticks++)
	 {
   	glPushMatrix();
        glColor3f(1.0,0.0,0.5); // give it a color
	glTranslatef(0.0, 0.1,0.0);
	glRotatef( (360/60) * sec_ticks, 0.0, 0.0, 1.0);
	glTranslatef(1.9, 0.0, 0.0);
          glRotatef( 90, 0.0, 0.0, 1.0);
        glutSolidCube(0.18);
	glPopMatrix();
	}

  glPushMatrix();// Draw minute hand
  glColor3f(0.3, 0.3, 0.3);
  glTranslatef( 0, 0, 0.0);
  glRotatef( (360/60) * ((newtime->tm_min) + 30), 0.0, 0.0, 1.0);
  glPushMatrix();
  glTranslatef(0.0, 0.0, 3.0);
  glPopMatrix();
  glRotatef( 90, 1.0, 0.0, 0.0);
  gluCylinder(Cylinder,0.5, 0, 2, 3, 3);
  glPopMatrix();
  glColor3f(1.0,1.0,1.0);

  glPushMatrix();// Draw hour hand
  glColor3f(0.5, 0.0, 1.0);
  glTranslatef( 0, 0, 0.0);
  glRotatef( (360/12) * ((newtime->tm_hour) + 4)+ (360/60) * (60 / (newtime->tm_min+1)), 0.0, 0.0, 1.0);
  glPushMatrix();
  glTranslatef(0.0, 0.0, 2.0);
  glScalef(0.2, 0.2, 1.0);
  Draw_gear();
  glPopMatrix();
  glRotatef( 90, 1.0, 0.0, 0.0);
  gluCylinder(Cylinder,0.5, 0, 1.4, 3, 3);
  glPopMatrix();
  glColor3f(1.0,1.0,1.0);
  Sprint(-1.0,3.0,"Melbourne");
glPopMatrix();
}
void curtime()
{
   FILE *fp;
    char hc1,hc2,mc1,mc2,sc1,sc2,*h,*m;
    int hi1,hi2,mi1,mi2,s1,s2;
    system("date +'%T' >time.txt");
    fp=fopen("time.txt","r");
    if(fp==NULL)
       exit(1) ;
    hc1=fgetc(fp);
    hc2=fgetc(fp);
    fgetc(fp);
    mc1=fgetc(fp);
    mc2=fgetc(fp);
    fgetc(fp);
    sc1=fgetc(fp);
    sc2=fgetc(fp);
    fclose(fp);
    remove("time.txt");
    hi1=hc1;
    hi2=hc2;
    mi1=mc1;
    mi2=mc2;
    s1=sc1;
    s2=sc2; 
    hi1-=48;
    hi2-=48;
    mi1-=48;
    mi2-=48;
    s1-=48;
    s2-=48; 
    hour=hi1*10+hi2;
    minute=mi1*10+mi2;
    sec=s1*10+s2;   
}
void display(void)
{
  int first_dig_hr,sec_dig_hr,first_dig_minute,sec_dig_minute,i;
  char h1,h2,m1,m2,buf[25];
  float xc=0.4;	
  j=0;
  if(hour>9)
  {
    first_dig_hr=hour/10+48;
    sec_dig_hr=hour%10+48;
    h1=first_dig_hr;
    h2=sec_dig_hr;
  }
  else
  {
   first_dig_hr=hour%10+48;
   h1=first_dig_hr;
  }
  if(minute>9)
  {
   first_dig_minute=minute/10+48;
   sec_dig_minute=minute%10+48;
   m1=first_dig_minute;
   m2=sec_dig_minute;
  }
  else
  {
   first_dig_minute=minute%10+48;
   m1=first_dig_minute;
  }
  time(&ltime); // Get time
  newtime = localtime(&ltime); // Convert to local time

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // easy way to put text on the screen.
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-8.0, 8.0, -8.0, 8.0, 1.0, 60.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glDisable(GL_LIGHTING);
  glDisable(GL_COLOR_MATERIAL);
  // Turn Perspective mode on/off
  if (view_state == 0)
     {
     glMatrixMode (GL_PROJECTION);
     glLoadIdentity();
     gluPerspective(60.0, 1, 1.0, 60.0);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     gluLookAt( rx, 0.0, rz, 0.0, 0.0, -14.0, 0, 1, 0);
	 }

	if (light_state == 1)
	  {
	   glEnable(GL_LIGHTING);
	   glEnable(GL_COLOR_MATERIAL);  // Enable for lighing
      }else
	  {
	  glDisable(GL_LIGHTING);
	  glDisable(GL_COLOR_MATERIAL);  // Disable for no lighing
  }
 Draw_clock( 0.0, 0.0, -14.0);	
 if(al==1)
 {
  //memset(alarm,0,sizeof(alarm));
  glColor3f(0.0,0.0,0.0);
  Sprint(-1.6,2.5,"Alarm ready");
  glColor3f(0.0,0.2,1.0);
  Sprint(-1.5,-5.2,"Alarm:");
  for(i=0;i<strlen(alarm);i++)
  {
  Cprint(xc,-5.2,alarm[i]);
  xc=xc+0.3;
  }
  xc=0.4;
 }
 if(al==-1)
 {
  memset(alarm,0,sizeof(alarm));
  glColor3f(0.9,0.0,0.0);
  if(err<=2)
  {
   Sprint(-2.1,-5.2,"Invalid alarm values");
   err++;
  }
  else if(err>2)
  { 
   errm++;
   if(errm<=2)
   {
    Sprint(-2.1,-5.2,"Format:HH:MM");
    
   }
   else
   {
    al=0;
    err=0;
    errm=0;
   }
  }
 }
 if(alarmOff==2&&hour==ahr&&minute==amin)
 {
   glColor3f(0.0,0.0,0.0);	
   Sprint(-1.6,2.5,"Alarm started");
   glColor3f(0.8,0.9,0.0);
   Sprint(-1.5,-5.2,"Alarm disabled");		
 }
 if(alarmOn==1)
 { 
   memset(alarm,0,sizeof(alarm));
   alarmOn++;
   if(alarmOn>=59)
   {
    exp1=0.2;
    alarmOn=0;
    al=0;
    if(alarmOff==2)
     alarmOff=1;
   }
   glColor3f(0.5,0.0,0.0);	
   Sprint(-1.6,2.5,"Alarm Ready");
   glColor3f(1.0,0.0,0.0);
   Sprint(-1.5,-5.2,"Alarm:");
   Sprint(0.4,-5.2," NOW");
 }
  glColor3f(0.0,0.0,0.0);
   if(hour>9)
  {
   Cprint(-1.5,3.0,h1);
   Cprint(-1.2,3.0,h2);
  }
  else
  {
   Cprint(-1.5,3.0,'0');
   Cprint(-1.2,3.0,h1);
  }
   Cprint(-0.8,3.0,':');
 if(minute>9)
  {
   Cprint(-0.6,3.0,m1);
   Cprint(-0.3,3.0,m2);
  }
  else
  {
   Cprint(-0.6,3.0,'0');
   Cprint(-0.3,3.0,m1);
  }
  Sprint(0,3,"hrs");
  strftime(buf,80,"Date: %d/%m/%y",newtime);
  Sprint(-1.8,1.9, buf);
 curtime();
glutSwapBuffers();
}

void display5()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // easy way to put text on the screen.
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glColor3f(1.0, 1.0, 0.0);
Sprint(-0.5,0.3, "Set the alarm in the format: HH:MM");
glutSwapBuffers();
Sprint(-0.6,0.2, " Enter time and press 'D' once you are done.");
glutSwapBuffers();
  glColor3f(0.0, 1.0, 0.0);
Sprint(-0.5,0.1, " Examples:");
glutSwapBuffers();
  glColor3f(0.0, 1.0, 1.0);
Sprint(-0.4,0.0, ">  09:30");
glutSwapBuffers();
Sprint(-0.4,-0.1, ">  12:00");
glutSwapBuffers();
Sprint(-0.4,-0.2, ">  22:58");
glutSwapBuffers();
  glColor3f(1.0, 1.0, 1.0);
Sprint(-0.6,-0.3, " Enter time and press 'D' once you are done.");
glutSwapBuffers();
}
void intro()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // easy way to put text on the screen.
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glColor3f(1.0, 1.0, 0.0);
Sprint(-0.504,0.553, "The Special Clock");
glutSwapBuffers();
  glColor3f(1.0, 1.0, 0.0);
Sprint(-0.506,0.554, "The Special Clock");
glutSwapBuffers();
  glColor3f(1.0, 1.0, 0.0);
Sprint(-0.508,0.555, "The Special Clock");
glutSwapBuffers();
glBegin(GL_LINES);
glVertex2f(-0.51,0.53);
glVertex2f(0.1,0.53);
glEnd();
glutSwapBuffers();

  glColor3f(1.0, 1.0, 0.0);
Sprint(-0.5,0.35, "Project made by:");
glutSwapBuffers();
  glColor3f(0.0, 0.0, 0.8);
Sprint(-0.4,0.2, "Abhijeet Sasidharan (1AY12CS001)");
glutSwapBuffers();
Sprint(-0.4,0.1, "Abhishek Kumar Singh (1AY12CS002)");
glutSwapBuffers();
glColor3f(1.0, 1.0, 0.0);
Sprint(-0.5,-0.1, "Under guidance of: ");
glutSwapBuffers();
glColor3f(0.6,0.5,0.8);
Sprint(-0.4,-0.2, "Mr. Vaishak Sundaresh");
glutSwapBuffers();
Sprint(-0.4,-0.3, "Mrs. Surekha K B");
glutSwapBuffers();
}
void controls()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // easy way to put text on the screen.
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glColor3f(1.0, 1.0, 0.0);
Sprint(-0.504,0.553, "The Special Clock");
glutSwapBuffers();
  glColor3f(1.0, 1.0, 0.0);
Sprint(-0.506,0.554, "The Special Clock");
glutSwapBuffers();
  glColor3f(1.0, 1.0, 0.0);
Sprint(-0.508,0.555, "The Special Clock");
glutSwapBuffers();
glBegin(GL_LINES);
glVertex2f(-0.51,0.53);
glVertex2f(0.1,0.53);
glEnd();
glutSwapBuffers();

  glColor3f(1.0, 1.0, 0.0);
Sprint(-0.5,0.3, "Controls (Keyboard) :");
glutSwapBuffers();
  glColor3f(0.0, 0.0, 0.8);
Sprint(-0.4,0.2, "Key 'D' : Confirm the alarm time");
glutSwapBuffers();
Sprint(-0.4,0.1, "Key 'O' : Switch Off  the alarm");
glutSwapBuffers();
Sprint(-0.4,0.0, "Key 'Q' : Quit the program");
glutSwapBuffers();
glColor3f(1.0, 1.0, 0.0);
Sprint(-0.5,-0.1, "Controls (mouse) :");
glutSwapBuffers();
glColor3f(0.6,0.4,0.4);
Sprint(-0.4,-0.2, "Left click : Hear the clock speak");
glutSwapBuffers();
Sprint(-0.4,-0.3, "Right click : List items appear on the screen");
glutSwapBuffers();

}


void dispText()
{
float xc=-0.15,yc=0.1;
int i;
glClearColor(0.0f,0.0f,0.0f,1.0f);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
glutSwapBuffers();
glColor3f(1.0,1.0,1.0);
for(i=0;i<strlen(alarm);i++)
{
  Cprint(xc,yc,alarm[i]);
  xc=xc+0.05;
}
}
void alarmFunc()
{

 int i,f=0,x=0,cor=0,count=0;
/*for(i=0;i<strlen(alarm);i++)
 printf("%c",alarm[i]);*/

for(i=0;i<strlen(alarm);i++)
{
 if(alarm[i]==':') 
  x=1;
 if(alarm[i]!=':') 
   count++;
 if(count==3&&alarm[i+1]==':')
 {
  al=-1;
  return;
 }
 if(count>3&&x==0)
 {
  al=-1; 
  return;
 }
 else if(count>4)
 {
  al=-1;
  return;
 }
}

for(i=0;i<1;i++)
 if(alarm[i+1]==':'||alarm[i]==':')
 {
  al=-1;
  return;
 }

 for(i=0;i<strlen(alarm);i++)
 {
  if(strlen(alarm)>5)
  {
   al=-1;
   break;
  }
  if(alarm[i+1]==':'&& f==0)//e.g 9:30
   ahr=alarm[i]-48;
  else if(alarm[i+2]==':')//e.g 12:30
   {
     f=1;
     ahr=(alarm[i]-48)*10;
     ahr=ahr+alarm[i+1]-48;
   }
  
   if(alarm[i]==':')
   {
    cor=1;
    if((i+3)==strlen(alarm))
    {
     amin=(alarm[i+1]-48)*10;
     amin=amin+alarm[i+2]-48;
     if(ahr>23||amin>59) 
     {
      al=-1; 
      break;
     }
     else
      al=1;
    }
   } 
 }
 
 if(hour==ahr&&minute==amin)
      al=-1; 
 if(cor==0)
  al=-1;
//printf("h:%d\nm:%d,time:%d:%d",ahr,amin,hour,minute);
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key)
   {
   	  case '0':alarm[j++]='0';
		   glutDisplayFunc(dispText);
                   break;
   	  case '1':alarm[j++]='1';
		   glutDisplayFunc(dispText);
                   break;
   	  case '2':alarm[j++]='2';
		   glutDisplayFunc(dispText);
                   break;
   	  case '3':alarm[j++]='3';
		   glutDisplayFunc(dispText);
                   break;
   	  case '4':alarm[j++]='4';
		   glutDisplayFunc(dispText);
                   break;
          case '5':alarm[j++]='5';
		   glutDisplayFunc(dispText);
                   break;
   	  case '6':alarm[j++]='6';
		   glutDisplayFunc(dispText);
                   break;
   	  case '7':alarm[j++]='7';
		   glutDisplayFunc(dispText);
                   break;
   	  case '8':alarm[j++]='8';
		   glutDisplayFunc(dispText);
                   break;
   	  case '9':alarm[j++]='9';
		   glutDisplayFunc(dispText);
                   break;
	  case ':':alarm[j++]=':';
		   glutDisplayFunc(dispText);
                   break;
          case 'D':alarmFunc();
		   glutDisplayFunc(display);
		    break;//display clock with set alarm
          case 'O':al=0;
	           alarmOff=2;
	           alarmOn=0;
		   memset(alarm,0,sizeof(alarm));
          	   glutDisplayFunc(display);
		    break;//display clock with set alarm
	  case 'I':/*Default time zone */
             		glutDisplayFunc(display);
		        break;
	  case 'L':
	     light_state = abs(light_state - 1);
		 break;
	  
	  case 'V':
	     view_state = abs(view_state - 1);
		 break;
	 
	  case 'Q':
       exit(0); // exit program when [ESC] key presseed
         break;
      default:
         break;
   }
}
char* HourNumMap(int t)
{
 switch(t)
 {
  case 0: return "Twelve";
  case 1: return "One";
  case 2: return "Two";
  case 3: return "Three";
  case 4: return "Four";
  case 5: return "Five";
  case 6: return "Six";
  case 7: return "Seven";
  case 8: return "Eight";
  case 9: return "Nine";
  case 10: return "Ten";
  case 11: return "Eleven";
  case 12: return "Twelve";
  default:exit(0);
 }
}
char* MinuteNumMap(int t)
{
 
switch(t)
{
case 0:return " ";
case 1:return " one";   
case 2:return " two";	
case 3:return " three";	
case 4:return " four";	
case 5:return " five";	
case 6:return " six";	
case 7:return " seven";	
case 8:return " eight";	
case 9:return " nine";	
case 10:return " ten";
case 11:return " eleven";
case 12:return " twelve";	
case 13:return " thirteen";
case 14:return " fourteen";
case 15:return " fifteen";	
case 16:return " sixteen";	
case 17:return " seventeen";	
case 18:return " eighteen";	
case 19:return " nineteen";	
case 20:return " twenty";
case 21:return " twenty one";
case 22:return " twenty two";	
case 23:return " twenty three";	
case 24:return " twenty four";	
case 25:return " twenty five";	
case 26:return " twenty six";	
case 27:return " twenty seven";
case 28:return " twenty eight";	
case 29:return " twenty nine";	
case 30:return " thirty";
case 31:return " thirty one";	
case 32:return " thirty two";	
case 33:return " thirty three";	
case 34:return " thirty four";	
case 35:return " thirty five";	
case 36:return " thirty six";
case 37:return " thirty seven";	
case 38:return " thirty eight";	
case 39:return " thirty nine";	
case 40:return " forty"; 
case 41:return " forty one";	
case 42:return " forty two";	
case 43:return " forty three";	
case 44:return " forty four";	
case 45:return " forty five";	
case 46:return " forty six";	
case 47:return " forty seven";	
case 48:return " forty eight";	
case 49:return " forty nine";	
case 50:return " fifty";
case 51:return " fifty one";	
case 52:return " fifty two";	
case 53:return " fifty three";	
case 54:return " fifty four";	
case 55:return " fifty five";	
case 56:return " fifty six";	
case 57:return " fifty seven";	
case 58: return "fifty eight";	
case 59:return " fifty nine";
case 60:return " sixty";
default:exit(0);
}
}
void spktime()
{
 int i,j,cnt=0,temph;
 char *sent[10];
 char com[100];
 sent[0]="./sam The current time  is ";
 if(hour>12)
 {
  temph=hour-12;
  sent[1]=HourNumMap(temph);
 }
 else
  sent[1]=HourNumMap(hour);
 sent[2]=MinuteNumMap(minute);
 if(hour>=12)
  sent[3]=" p am\0";
 else
  sent[3]=" a am\0";
 for(i=0;i<4;i++)
  for(j=0;j<strlen(sent[i]);j++)
  {
    com[cnt++]=sent[i][j];
  }
  system(com);
}
int count=0;
void mouse(int btn,int state,int x,int y)
{
  int sec_ticks;
  if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
  {
   exp1=exp1+0.2;
   expp2=0.0;
   exp3=0.0;
   if(exp1==1.0)
   {
    system("./sam I am busy right now"); 
    exit(0);
   }
   spktime();
  }
}
void top_menu(int option)
{
	switch(option)
	{
	//case 0: glutDisplayFunc(front_page);
				break;
 
	case 1:glutDisplayFunc(display);
		break;
	case 2:glutDisplayFunc(display5);
		break;
	case 3:glutDisplayFunc(controls);
		break;
	case 4:glutDisplayFunc(intro);
		break;	
	case 5: exit(0);
        
	}
}


int main(int argc, char** argv)
{  
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (650, 750);
   glutInitWindowPosition (10, 10);
   glutCreateWindow ("The Special clock");
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape); // used to trigger reshape call back. Triggered when ever window is reshaped
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouse);
   glutCreateMenu(top_menu);
   glutAddMenuEntry("Home",1); 
   glutAddMenuEntry("Alarm",2); 
   glutAddMenuEntry("Controls",3); 
   glutAddMenuEntry("About",4); 
   glutAddMenuEntry("Exit",5);
   glutAttachMenu(GLUT_RIGHT_BUTTON);
   glutTimerFunc( 10, TimeEvent, 1);
   glutMainLoop();
   return 0;
}

