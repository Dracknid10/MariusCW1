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
    
    //Torus torus;
    //Teapot teapot;

    void setMatrices();

    void compile();

    Plane plane; //plane surface
    std::unique_ptr<ObjMesh> mesh; //chest mesh
    std::unique_ptr<ObjMesh> meshbackground; //background mesh


    GLuint wood = Texture::loadTexture("../Project_Template/media/texture/hardwood2_diffuse.jpg");
    GLuint moss = Texture::loadTexture("../Project_Template/media/texture/moss.png");
    GLuint water = Texture::loadTexture("../Project_Template/media/texture/bluewater.png");

    float rotation;


public:
    SceneBasic_Uniform();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);


};

#endif // SCENEBASIC_UNIFORM_H
