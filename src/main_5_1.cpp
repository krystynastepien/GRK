#include "glew.h"
#include "freeglut.h"
#include "glm.hpp"
#include "ext.hpp"
#include <iostream>
#include <cmath>

#include "Shader_Loader.h"
#include "Render_Utils.h"
#include "Camera.h"
#include "Texture.h"

GLuint programColor;
GLuint programTexture;


//tekstury
GLuint earthTexture;
GLuint moonTexture;
GLuint moon2Texture;
GLuint moon3Texture;
GLuint moon4Texture;
GLuint moon5Texture;
GLuint shipTexture;
GLuint sunTexture;
GLuint jowiszTexture;
GLuint marsTexture;
GLuint wenusTexture;
GLuint saturnTexture;
GLuint merkuryTexture;
GLuint neptunTexture;


GLuint tloTexture;




Core::Shader_Loader shaderLoader;

obj::Model shipModel;
obj::Model sphereModel;
float cameraAngle = 0;
glm::vec3 cameraPos = glm::vec3(-10, 0, 0);
glm::vec3 cameraDir;
glm::vec3 cameraYo;

glm::mat4 cameraMatrix, perspectiveMatrix, perspectiveMatrix2; ////

//kierunek œwiat³a
glm::vec3 lightDir =glm::vec3(0.9f, -0.3f, 0.2f);

//klawisze ruchu
void keyboard(unsigned char key, int x, int y)
{
	float angleSpeed = 0.1f;
	float moveSpeed = 0.1f;
	switch(key)
	{
	case 'z': cameraAngle -= angleSpeed*2; break;
	case 'x': cameraAngle += angleSpeed*2; break;
	case 'w': cameraPos += cameraDir * moveSpeed*2; break;
	case 's': cameraPos -= cameraDir * moveSpeed*2; break;
	case 'd': cameraPos += glm::cross(cameraDir, glm::vec3(0,1,0)) * moveSpeed*2; break;
	case 'a': cameraPos -= glm::cross(cameraDir, glm::vec3(0,1,0)) * moveSpeed*2; break;
	case 'f': cameraPos += glm::cross(cameraDir, glm::vec3(0, 0, 1)) * moveSpeed*2; break;
	case 'r': cameraPos -= glm::cross(cameraDir, glm::vec3(0, 0, 1)) * moveSpeed*2; break;
	}
}


glm::mat4 createCameraMatrix()
{
	// Obliczanie kierunku patrzenia kamery (w plaszczyznie x-z) przy uzyciu zmiennej cameraAngle kontrolowanej przez klawisze.
	cameraDir = glm::vec3(cosf(cameraAngle), 0.0f, sinf(cameraAngle));
	glm::vec3 up = glm::vec3(0,1,0);
	return Core::createViewMatrix(cameraPos, cameraDir, up);
}


void drawObjectColor(obj::Model * model, glm::mat4 modelMatrix, glm::vec3 color)
{
	GLuint program = programColor;
	glUseProgram(program);
	glUniform3f(glGetUniformLocation(program, "objectColor"), color.x, color.y, color.z);
	glUniform3f(glGetUniformLocation(program, "lightDir"), lightDir.x, lightDir.y, lightDir.z);

	glm::mat4 transformation = perspectiveMatrix * cameraMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)&transformation);
	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);

	Core::DrawModel(model);
	glUseProgram(0);
}

void drawObjectTexture(obj::Model * model, glm::mat4 modelMatrix, GLuint textureID) /////////////////////////////////////////////
{
	GLuint program = programTexture;
	glUseProgram(program);

	//glUniform3f(glGetUniformLocation(program, "objectColor"), color.x, color.y, color.z);
	glUniform3f(glGetUniformLocation(program, "lightDir"), lightDir.x, lightDir.y, lightDir.z);

	glm::mat4 transformation = perspectiveMatrix* cameraMatrix * modelMatrix;

	glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)&transformation);
	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);
	
	Core::SetActiveTexture(textureID, "objectTex", program, 0); 
	Core::DrawModel(model);

	glUseProgram(0);
}



void renderScene()
{
	// Aktualizacja macierzy widoku i rzutowania. Macierze sa przechowywane w zmiennych globalnych, bo uzywa ich funkcja drawObject.
	// (Bardziej elegancko byloby przekazac je jako argumenty do funkcji, ale robimy tak dla uproszczenia kodu.
	//  Jest to mozliwe dzieki temu, ze macierze widoku i rzutowania sa takie same dla wszystkich obiektow!)	
	cameraMatrix = createCameraMatrix();
	perspectiveMatrix = Core::createPerspectiveMatrix();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.1f, 0.0f);

	// Macierz statku "przyczepia" go do kamery. Warto przeanalizowac te linijke i zrozumiec jak to dziala.
	glm::mat4 shipModelMatrix = glm::translate(cameraPos + cameraDir * 0.5f + glm::vec3(0,-0.25f,0)) * glm::rotate(-cameraAngle + glm::radians(90.0f), glm::vec3(0,1,0)) * glm::scale(glm::vec3(0.25f));
	drawObjectTexture(&shipModel, shipModelMatrix, shipTexture);

	glm::mat4 sphereModelMatrix = glm::scale(glm::vec3(0.6f)) * glm::translate(glm::vec3(14, -1, 3))  ;         
	float time = glutGet(GLUT_ELAPSED_TIME) / 500.0f; //---------
	
	
    //////////////////////////////////////////////////// poziomo ////////////////
	/////////////////////////////////////////////////////////////
	  
	/*
	glm::mat4 Tlo = glm::scale(glm::vec3(20));//predkosc na orbicie
	Tlo = Tlo *glm::translate(glm::vec3(0, 0, 0))*glm::rotate(glm::radians(time * 1), glm::vec3(0, 1, 0)); //predkosc wokol osi
	drawObjectTexture(&sphereModel, Tlo, tloTexture);  /////
	*/

	  glm::mat4 Slonce = glm::scale(glm::vec3(4))*glm::rotate(glm::radians(time * 5), glm::vec3(0, 1, 0)); //predkosc na orbicie
	  Slonce = Slonce *glm::translate(glm::vec3(0, 0, 1.6))*glm::rotate(glm::radians(time*30), glm::vec3(0, 1, 0)); //predkosc wokol osi
	  drawObjectTexture(&sphereModel, Slonce, sunTexture);  /////


	  glm::mat4 Merkury = glm::scale(glm::vec3(0.2f))*glm::rotate(glm::radians(time*5.7f), glm::vec3(0, 1, 0)); //predkosc na orbicie
	  Merkury = Merkury *glm::translate(glm::vec3(0, 0, 6.5))*glm::rotate(glm::radians(time*22), glm::vec3(0, 1, 0));  //predkosc wokol osi
	  Merkury = Slonce * Merkury;
	  drawObjectTexture(&sphereModel, Merkury, merkuryTexture);  /////


	  glm::mat4 Wenus = glm::scale(glm::vec3(0.3f)) *glm::rotate(glm::radians(time * 5.6f), glm::vec3(0, 1, 0)); //predkosc na orbicie
	  Wenus = Wenus *glm::translate(glm::vec3(0, 0, 7.1))*glm::rotate(glm::radians(time*20), glm::vec3(0, 1, 0)); //predkosc wokol osi
	  Wenus = Slonce * Wenus;
	  drawObjectTexture(&sphereModel, Wenus, wenusTexture);  /////

	  glm::mat4 Ziemia =  glm::rotate(glm::radians(2.6f), glm::vec3(0, 1, 0));
	  Ziemia = glm::scale(glm::vec3(0.35f))*glm::rotate(glm::radians(time * 5.5f), glm::vec3(0, 1, 0)); //predkosc na orbicie
	  Ziemia = Ziemia *glm::translate(glm::vec3(0, 0, 9))*glm::rotate(glm::radians(time * 12), glm::vec3(0, 1, 0));  //predkosc wokol osi
	  Ziemia = Slonce * Ziemia;
	  drawObjectTexture(&sphereModel, Ziemia, earthTexture);  /////


	  glm::mat4 Ksiezyc = glm::scale(glm::vec3(0.3))*glm::rotate(glm::radians(time * 19), glm::vec3(0, 1, 0)); //predkosc na orbicie
	  Ksiezyc = Ksiezyc *glm::translate(glm::vec3(0, 0, 5))*glm::rotate(glm::radians(time*60), glm::vec3(0, 1, 0)); //predkosc wokol osi
	  Ksiezyc = Ziemia * Ksiezyc;
	  drawObjectTexture(&sphereModel, Ksiezyc, moonTexture);  /////


	  glm::mat4 Ksiezyc5 = glm::scale(glm::vec3(0.3))*glm::rotate(glm::radians(time * 19), glm::vec3(1, 1, 1)); //predkosc na orbicie
	  Ksiezyc5 = Ksiezyc5 *glm::translate(glm::vec3(0, 0, 6))*glm::rotate(glm::radians(time * 60), glm::vec3(0, 1, 0)); //predkosc wokol osi
	  Ksiezyc5 = Ziemia * Ksiezyc5;
	  drawObjectTexture(&sphereModel, Ksiezyc5, moonTexture);

	  glm::mat4 Mars = glm::scale(glm::vec3(0.22f))*glm::rotate(glm::radians(time * 5.4f), glm::vec3(0, 1, 0)); //predkosc na orbicie
	  Mars = Mars *glm::translate(glm::vec3(0, 0, 23))*glm::rotate(glm::radians(time*100), glm::vec3(0, 1, 0));  //predkosc wokol osi
	  Mars = Slonce * Mars;
	  drawObjectTexture(&sphereModel, Mars, marsTexture);  /////

	  glm::mat4 Ksiezyc2 = glm::scale(glm::vec3(0.55f))*glm::rotate(glm::radians(time * 7), glm::vec3(0, 1, 0));  //predkosc na orbicie
	  Ksiezyc2 = Ksiezyc2 *glm::translate(glm::vec3(0, 0, 3))*glm::rotate(glm::radians(time * 4), glm::vec3(0, 1, 0)); //predkosc wokol osi
	  Ksiezyc2 = Mars * Ksiezyc2;
	  drawObjectTexture(&sphereModel, Ksiezyc2, moon2Texture);  /////


	  glm::mat4 Ksiezyc3 = glm::scale(glm::vec3(0.5f))*glm::rotate(glm::radians(time * 5.2f), glm::vec3(0, 1, 0));  //predkosc na orbicie
	  Ksiezyc3 = Ksiezyc3 *glm::translate(glm::vec3(0, 6, 3))*glm::rotate(glm::radians(time*490), glm::vec3(0, 1, 0)); //predkosc wokol osi
	  Ksiezyc3 = Mars * Ksiezyc3;
	  drawObjectTexture(&sphereModel, Ksiezyc3, moon3Texture);  /////


	  glm::mat4 Jowisz = glm::scale(glm::vec3(0.9))*glm::rotate(glm::radians(time * 5.3f), glm::vec3(0, 1, 0)); //predkosc na orbicie
	  Jowisz = Jowisz *glm::translate(glm::vec3(0, 0, 8))*glm::rotate(glm::radians(time*99), glm::vec3(0, 1, 0));  //predkosc wokol osi
	  Jowisz = Slonce * Jowisz;
	  drawObjectTexture(&sphereModel, Jowisz, jowiszTexture);


	  glm::mat4 Saturn = glm::scale(glm::vec3(0.7))*glm::rotate(glm::radians(time * 5.2f), glm::vec3(0, 1, 0)); //predkosc na orbicie
	  Saturn = Saturn  *glm::translate(glm::vec3(0, 0, 13))*glm::rotate(glm::radians(time*220), glm::vec3(0, 1, 0)); //predkosc wokol osi
	  Saturn = Slonce * Saturn;
	  drawObjectTexture(&sphereModel, Saturn, saturnTexture);

	  glm::mat4 Neptun = glm::scale(glm::vec3(0.35f))*glm::rotate(glm::radians(time * 5.1f), glm::vec3(0, 1, 0)); //predkosc orbity
	  Neptun = Neptun *glm::translate(glm::vec3(0, 0, 35))*glm::rotate(glm::radians(time * 12), glm::vec3(0, 1, 0));  //predkosc wokol osi
	  Neptun = Slonce * Neptun;
	  drawObjectTexture(&sphereModel, Neptun, neptunTexture);  /////
	  //////////////////////////////////////////////////////////////////////////////////

	  
	/////////////////////////////////////////////////////pionowo////////////////////
	/*
	glm::mat4 Slonce = glm::scale(glm::vec3(4))*glm::rotate(glm::radians(time * 5), glm::vec3(1, 0, 0)); //predkosc na orbicie
	Slonce = Slonce *glm::translate(glm::vec3(0, 0, 1.1))*glm::rotate(glm::radians(time*20), glm::vec3(1, 0, 0)); //predkosc wokol osi
	drawObjectTexture(&sphereModel, Slonce, sunTexture);  /////


	glm::mat4 Merkury = glm::scale(glm::vec3(0.2f))*glm::rotate(glm::radians(time*5.7f), glm::vec3(1, 0, 0)); //predkosc na orbicie
	Merkury = Merkury *glm::translate(glm::vec3(0, 0, 6.5))*glm::rotate(glm::radians(time*22), glm::vec3(1, 0, 0));  //predkosc wokol osi
	Merkury = Slonce * Merkury;
	drawObjectTexture(&sphereModel, Merkury, merkuryTexture);  /////

	
	glm::mat4 Wenus = glm::scale(glm::vec3(0.3f)) *glm::rotate(glm::radians(time * 5.6f), glm::vec3(1, 0, 0)); //predkosc na orbicie
	Wenus = Wenus *glm::translate(glm::vec3(0, 0, 7.1))*glm::rotate(glm::radians(time*20), glm::vec3(1, 0, 0)); //predkosc wokol osi
	Wenus = Slonce * Wenus;
	drawObjectTexture(&sphereModel, Wenus, wenusTexture);  /////

	glm::mat4 Ziemia =  glm::rotate(glm::radians(2.6f), glm::vec3(0, 1, 0));
		Ziemia = glm::scale(glm::vec3(0.35f))*glm::rotate(glm::radians(time * 5.5f), glm::vec3(1, 0, 0)); //predkosc na orbicie
	Ziemia = Ziemia *glm::translate(glm::vec3(0, 0, 9))*glm::rotate(glm::radians(time * 12), glm::vec3(1, 0, 0));  //predkosc wokol osi
	Ziemia = Slonce * Ziemia;
	drawObjectTexture(&sphereModel, Ziemia, earthTexture);  /////


	glm::mat4 Ksiezyc = glm::scale(glm::vec3(0.3))*glm::rotate(glm::radians(time * 19), glm::vec3(1, 0, 0)); //predkosc na orbicie
	Ksiezyc = Ksiezyc *glm::translate(glm::vec3(0, 0, 5))*glm::rotate(glm::radians(time*60), glm::vec3(1, 0, 0)); //predkosc wokol osi
	Ksiezyc = Ziemia * Ksiezyc;
	drawObjectTexture(&sphereModel, Ksiezyc, moonTexture);  /////


	glm::mat4 Mars = glm::scale(glm::vec3(0.22f))*glm::rotate(glm::radians(time * 5.4f), glm::vec3(1, 0, 0)); //predkosc na orbicie
	Mars = Mars *glm::translate(glm::vec3(0, 0, 23))*glm::rotate(glm::radians(time*100), glm::vec3(1, 0, 0));  //predkosc wokol osi
	Mars = Slonce * Mars;
	drawObjectTexture(&sphereModel, Mars, marsTexture);  /////

	glm::mat4 Ksiezyc2 = glm::scale(glm::vec3(0.55f))*glm::rotate(glm::radians(time * 7), glm::vec3(1, 0, 0));  //predkosc na orbicie
	Ksiezyc2 = Ksiezyc2 *glm::translate(glm::vec3(0, 0, 3))*glm::rotate(glm::radians(time * 4), glm::vec3(1, 0, 0)); //predkosc wokol osi
	Ksiezyc2 = Mars * Ksiezyc2;
	drawObjectTexture(&sphereModel, Ksiezyc2, moon2Texture);  /////


	glm::mat4 Ksiezyc3 = glm::scale(glm::vec3(0.5f))*glm::rotate(glm::radians(time * 5.2f), glm::vec3(1, 0, 0));  //predkosc na orbicie
	Ksiezyc3 = Ksiezyc3 *glm::translate(glm::vec3(0, 6, 3))*glm::rotate(glm::radians(time*490), glm::vec3(1, 0, 0)); //predkosc wokol osi
	Ksiezyc3 = Mars * Ksiezyc3;
	drawObjectTexture(&sphereModel, Ksiezyc3, moon3Texture);  /////


	glm::mat4 Jowisz = glm::scale(glm::vec3(0.9))*glm::rotate(glm::radians(time * 5.3f), glm::vec3(1, 0, 0)); //predkosc na orbicie
	Jowisz = Jowisz *glm::translate(glm::vec3(0, 0, 8))*glm::rotate(glm::radians(time*99), glm::vec3(1, 0, 0));  //predkosc wokol osi
	Jowisz = Slonce * Jowisz;
	drawObjectTexture(&sphereModel, Jowisz, jowiszTexture);


	glm::mat4 Saturn = glm::scale(glm::vec3(0.7))*glm::rotate(glm::radians(time * 5.2f), glm::vec3(1, 0, 0)); //predkosc na orbicie
	Saturn = Saturn  *glm::translate(glm::vec3(0, 0, 13))*glm::rotate(glm::radians(time*220), glm::vec3(1, 0, 0)); //predkosc wokol osi
	Saturn = Slonce * Saturn;
	drawObjectTexture(&sphereModel, Saturn, saturnTexture);

	glm::mat4 Neptun = glm::scale(glm::vec3(0.35f))*glm::rotate(glm::radians(time * 5.1f), glm::vec3(1, 0, 0)); //predkosc orbity
	Neptun = Neptun *glm::translate(glm::vec3(0, 0, 35))*glm::rotate(glm::radians(time * 12), glm::vec3(1, 0, 0));  //predkosc wokol osi
	Neptun = Slonce * Neptun;
	drawObjectTexture(&sphereModel, Neptun, neptunTexture);  /////
	  */
	  //////////////////////////////////////////////////////////////////////////////////



	glutSwapBuffers();
}

void init()
{
	glEnable(GL_DEPTH_TEST);
	programColor = shaderLoader.CreateProgram("shaders/shader_color.vert", "shaders/shader_color.frag");
	programTexture = shaderLoader.CreateProgram("shaders/shader_tex.vert", "shaders/shader_tex.frag");

	sphereModel = obj::loadModelFromFile("models/sphere.obj");
	shipModel = obj::loadModelFromFile("models/spaceship.obj");


	moonTexture = Core::LoadTexture("textures/moon.png");
	moon2Texture = Core::LoadTexture("textures/pl1.png");
	moon3Texture = Core::LoadTexture("textures/pl2.png");
	moon4Texture = Core::LoadTexture("textures/rusted2.png");
	moon5Texture = Core::LoadTexture("textures/pl2.png");
	earthTexture = Core::LoadTexture("textures/earth.png");
	shipTexture = Core::LoadTexture("textures/ship2.png");
	sunTexture = Core::LoadTexture("textures/sun.png");
	jowiszTexture = Core::LoadTexture("textures/pl9.png");
	saturnTexture = Core::LoadTexture("textures/pl6.png");
	marsTexture = Core::LoadTexture("textures/pl3.png");
	wenusTexture = Core::LoadTexture("textures/jupiter.png");
	merkuryTexture = Core::LoadTexture("textures/merkury.png");
	neptunTexture = Core::LoadTexture("textures/neptun.png");

	tloTexture = Core::LoadTexture("textures/tlo2.png");
}

void shutdown()
{
	shaderLoader.DeleteProgram(programColor);
	shaderLoader.DeleteProgram(programTexture);
}

void idle()
{
	glutPostRedisplay();
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(90, 90);
	glutInitWindowSize(530, 530);
	glutCreateWindow("Space");
	glewInit();

	init();
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);

	glutMainLoop();
	shutdown();

	return 0;
}
