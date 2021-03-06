#ifndef SCENEBASIC_UNIFORM_H
#define SCENEBASIC_UNIFORM_H

#include "helper/scene.h"

#include <glad/glad.h>
#include "helper/glslprogram.h"


#include "helper/texture.h"
#include "helper/teapot.h"
#include <glm/glm.hpp>

#include "helper/plane.h"
#include "helper/objmesh.h"




class SceneBasic_Uniform : public Scene
{
private:
    GLSLProgram prog;
    GLSLProgram prog2;
    GLSLProgram prog3;
    
    //Torus torus;
    //Teapot teapot;

    void setMatrices(GLSLProgram& p);


    float angle, flow;
   
    GLuint fsQuad, fboHandle, renderTex;
    void setupFBO();
    void pass1();
    void pass2();

    void compile();

    Plane plane; //plane surface
    std::unique_ptr<ObjMesh> mesh; //chest mesh
    std::unique_ptr<ObjMesh> meshbackground; //background mesh
    std::unique_ptr<ObjMesh> Solider; //background mesh


    GLuint wood = Texture::loadTexture("../Project_Template/media/texture/hardwood2_diffuse.jpg");
    GLuint moss = Texture::loadTexture("../Project_Template/media/texture/moss.png");
    GLuint water = Texture::loadTexture("../Project_Template/media/texture/bluewater.png");


    GLuint sprites;
    int numSprites;
    float* locations;

    float rotation;

   


public:
    SceneBasic_Uniform();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);


};

#endif // SCENEBASIC_UNIFORM_H
