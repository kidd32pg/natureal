#ifndef _UTILS_H
#define _UTILS_H

#include "settings.h"
#define BACKSPACE(cnt) for (int i=0; i<cnt; i++){printf("\b \b");}
#define BACK(cnt) for (int i=0; i<cnt; i++){printf("\b");}

#define SAFE_DELETE_PTR(VAR) if(VAR!=NULL){delete VAR; VAR=NULL;}
#define SAFE_DELETE_ARRAY_PTR(VAR) if(VAR!=NULL){delete [] VAR; VAR=NULL;}


static void pauseAndExit()
{
	system("PAUSE");
	exit(1);
}

static v4 glCoordToScreenSpace(const v4 &v){
   // Get the matrices and viewport
   double modelView[16];
   double projection[16];

   glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
   glGetDoublev(GL_PROJECTION_MATRIX, projection);

   // Compose the matrices into a single row-major transformation
   Vector4 T[4];
   int r, c, i;
   for (r = 0; r < 4; ++r)
   {
    for (c = 0; c < 4; ++c)
    {
		T[r].data[c] = 0;
      for (i = 0; i < 4; ++i)
      {
        // OpenGL matrices are column major
         T[r].data[c] += projection[r + i * 4] * modelView[i + c * 4];
      }
    }
   }

   // Transform the vertex
   Vector4 result;
   for (r = 0; r < 4; ++r)
   {
    result.data[r] = T[r].dot(v);
   }

   // Homogeneous divide
   const double rhw = 1 / result.w;

   return Vector4(
   (1 + result.x * rhw)/ 2,
   (1 + result.y * rhw)/ 2,
   (result.z * rhw),
   rhw);
}

static v4 glCoordToScreenCoord(const v4 &v){
   // Get the matrices and viewport
   double modelView[16];
   double projection[16];
   double viewport[4];
   double depthRange[2];

   glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
   glGetDoublev(GL_PROJECTION_MATRIX, projection);
   glGetDoublev(GL_VIEWPORT, viewport);
   glGetDoublev(GL_DEPTH_RANGE, depthRange);

   // Compose the matrices into a single row-major transformation
   Vector4 T[4];
   int r, c, i;
   for (r = 0; r < 4; ++r)
   {
    for (c = 0; c < 4; ++c)
    {
		T[r].data[c] = 0;
      for (i = 0; i < 4; ++i)
      {
        // OpenGL matrices are column major
         T[r].data[c] += projection[r + i * 4] * modelView[i + c * 4];
      }
    }
   }

   // Transform the vertex
   Vector4 result;
   for (r = 0; r < 4; ++r)
   {
    result.data[r] = T[r].dot(v);
   }

   // Homogeneous divide
   const double rhw = 1 / result.w;

   return Vector4(
   (1 + result.x * rhw) * viewport[2] / 2 + viewport[0],
   (1 + result.y * rhw) * viewport[3] / 2 + viewport[1],
   (result.z * rhw) * (depthRange[1] - depthRange[0]) + depthRange[0],
   rhw);
}

static int isExtensionSupported(const char *extension)
{
	const GLubyte *extensions = NULL;
	const GLubyte *start;
	GLubyte *pos, *terminator;
	/* Kontrola parametru � jm�no mus� b�t bez mezer. */
	pos = (GLubyte *) strchr(extension, ' ');// ptr na � �
	if (pos || *extension == '\0') // nebo pr�zdn� jm�no
		return 0;
	extensions = glGetString(GL_EXTENSIONS);
	/* zji�t�n� p��tomnosti extenze */
	start = extensions;
	for (;;) {
		pos = (GLubyte *) strstr((const char *) start, extension);
		if (!pos)
			break;
		/* nen� to jen pod�et�zec del��ho jm�na extenze? */
		terminator = pos + strlen(extension);
		if (pos == start || *(pos - 1) == ' ')
			if (*terminator == ' ' || *terminator == '\0')
				return 1;
		start = terminator;
	}
	return 0;
}

static void show_texture(GLuint texId, GLint x,GLint y, GLsizei width, GLsizei height){
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, g_WinWidth, 0, g_WinHeight, -1,1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texId);
	glColor4f(1.f,1.f,1.f,1.f);

	glBegin(GL_QUADS);
		glTexCoord2f(0.f, 0.f); glVertex2i(x,y);
		glTexCoord2f(1.f, 0.f); glVertex2i(x+width,y);
		glTexCoord2f(1.f, 1.f); glVertex2i(x+width,y+height);
		glTexCoord2f(0.f, 1.f); glVertex2i(x,y+height);
	glEnd();

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

static void glScale(v3 &scaleFactors)
{
	glScalef(scaleFactors.x, scaleFactors.y, scaleFactors.z);
};
static void glTranslate(v3 &movement)
{
	glTranslatef(movement.x, movement.y, movement.z);
};
static void glRotate(v3 &axis, float angle)
{
	glRotatef(angle, axis.x, axis.y, axis.z);
};
static void glColor(v3 &color)
{
	glColor3f(color.x, color.y, color.z);
};

#endif


