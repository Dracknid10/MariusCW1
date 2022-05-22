#include "scenebasic_uniform.h"
#include <sstream>
#include <time.h>
#include <iostream>
using std::cerr;
using std::endl;

#include <glm/gtc/matrix_transform.hpp>

using glm::vec3;
using glm::mat4;

//constructor for torus
SceneBasic_Uniform::SceneBasic_Uniform() : rotation(0.0f), plane(10.0f, 10.0f, 100, 100)
{
    mesh = ObjMesh::load("../Project_Template/media/texturedchesttest.obj",
        true);

    meshbackground = ObjMesh::load("../Project_Template/media/CAVEWALLStetured.obj",
        true);

    Solider = ObjMesh::load("../Project_Template/media/soilder.obj",
        true);

}

//constructor for teapot
//SceneBasic_Uniform::SceneBasic_Uniform() : teapot(13, glm::translate(mat4(1.0f), vec3(0.0f, 1.5f, 0.25f))) {}

void SceneBasic_Uniform::initScene()
{
    compile();

    glClearColor(0.5f, 0.05f, 0.5f, 1.0f);
    glEnable(GL_DEPTH_TEST);

	glEnable(GL_DEPTH_TEST);

   numSprites = 50;

    locations = new float[numSprites * 3];
    srand((unsigned int)time(0));


    for (size_t i = 0; i < numSprites; i++)
    {
        vec3 p(((float)rand() / RAND_MAX * 2.0f) - 1.0f,
            ((float)rand() / RAND_MAX * 2.0f) - 1.0f,
            ((float)rand() / RAND_MAX * 2.0f) - 1.0f);

        locations[i * 3] = p.x;
        locations[i * 3 + 1] = p.y;
        locations[i * 3 + 2] = p.z;
    }

    GLuint handle;
    glGenBuffers(1, &handle);

    glBindBuffer(GL_ARRAY_BUFFER, handle);
    glBufferData(GL_ARRAY_BUFFER, numSprites * 3 * sizeof(float), locations, GL_STATIC_DRAW);

    delete[] locations;

    glGenVertexArrays(1, &sprites);
    glBindVertexArray(sprites);

    glBindBuffer(GL_ARRAY_BUFFER, handle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 ,((GLubyte*)NULL + (0)));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    const char* texname = "../Project_Template/media/texture/hardwood2_diffuse.jpg";
    Texture::loadTexture(texname);

    prog2.setUniform("SpriteTex", 0);
    prog2.setUniform("Size2", 0.15f);


   
    //initialise the model matrix
    model = mat4(1.0f);

    view = glm::lookAt(vec3(1.0f, 1.25f, 1.25f), vec3(0.0f, 0.0f, 0.0f),vec3(0.0f, 1.0f, 0.0f));

    projection = mat4(1.0f);


    projection = mat4(1.0f);


    
    prog.setUniform("Light[0].Position", view * glm::vec4(5.0f, 5.0f, 2.0f, 0.0f)); //setting Light Position
    prog.setUniform("Light[1].Position", view * glm::vec4(5.0f, 5.0f, 2.0f, 0.0f)); //setting Light Position
    prog.setUniform("Light[2].Position", view * glm::vec4(5.0f, 5.0f, 2.0f, 0.0f)); //setting Light Position
   
    //prog.setUniform("Light[3].Position", view * glm::vec4(5.0f, 5.0f, 2.0f, 0.0f)); //setting Light Position


    prog.setUniform("Light[0].La",vec3(0.3f));  //setting ambient vlaue
    prog.setUniform("Light[1].La", vec3(0.4f, 0.3f, 0.3f));  //setting ambient value
    prog.setUniform("Light[2].La", vec3(0.3f, 0.3f, 0.3f));  //setting ambient value

    //prog.setUniform("Light[3].La", vec3(0.1f, 0.1f, 0.1f));  //setting ambient value


    prog.setUniform("Light[0].L", vec3(0.5f, 0.5f, 0.5f));
    prog.setUniform("Light[1].L", vec3(0.5f, 0.5f, 0.5f));
    prog.setUniform("Light[2].L", vec3(0.5f, 0.5f, 0.5f));

    angle = glm::half_pi<float>();
    


}



void SceneBasic_Uniform::compile()
{
	try {

		//prog.compileShader("shader/basic_uniform.vert");  
		//prog.compileShader("shader/basic_uniform.frag");
  //      prog.link();
  //      prog.use();


        prog2.compileShader("shader/basic_uniform - Copy.vert");
        prog2.compileShader("shader/basic_uniform - Copy.frag");
        prog2.compileShader("shader/basic_uniform.geom");
		prog2.link();
        prog2.use();




	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::update( float t )
{
    rotation = t;   // add rotations where nessesary by radiuns*rotation 

    flow = t;
}

void SceneBasic_Uniform::render()
{


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, wood);

    prog.setUniform("Time", flow);
 
    setMatrices(prog); //we set matrices 
 
    prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Animated", false);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Shininess", 0.8f);
    prog.setUniform("Tex1", 0);
    model = mat4(1.0f);
    model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, vec3(10, -3, -7));
    setMatrices(prog);
    mesh->render();


    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, water);

    glBindTexture(GL_TEXTURE_2D, water);
    prog.setUniform("Material.Kd", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Animated", true);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Shininess", 1.0f);
    model = mat4(1.0f);
    prog.setUniform("Tex1", 2);
    model = glm::scale(model, vec3(1.8f, 1.8f, 1.8f));
    //model = glm::rotate(model, glm::radians(90.0f * rotation), vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, vec3(0, -4, -2));
    setMatrices(prog);
    plane.render();


    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, moss);


    prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Animated", false);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Shininess", 1.0f);
    prog.setUniform("Tex1", 1);
    model = mat4(1.0f);
    model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, vec3(8, -8, -3));
    //model = glm::translate(model, vec3(80000, -8, -3));
    setMatrices(prog);
    meshbackground->render();



    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, moss);

    //vec4 lightPos = vec4(0.0f, 10.0f, 0.0f, 1.0f);
    //prog.setUniform("Spot.Position", vec3(view * lightPos));
    //mat3 normalMatrix = mat3(vec3(view[0]), vec3(view[1]), vec3(view[2]));
    //prog.setUniform("Spot.Direction", normalMatrix * vec3(-lightPos));

    setMatrices(prog); //we set matrices 
 
    prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Animated", false);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Shininess", 1.0f);
    prog.setUniform("Tex1", 0);
    model = mat4(1.0f);
    model = glm::scale(model, vec3(1.0f, 1.0f, 1.0f));
    model = glm::rotate(model, glm::radians(90.0f * rotation), vec3(0.0f, 1.0f, 0.0f));
 
    model = glm::translate(model, vec3(-1, 0, 0));
    setMatrices(prog);
    Solider->render();



    setMatrices(prog2);

    glBindVertexArray(sprites);
    glDrawArrays(GL_POINTS, 0, numSprites);


    glFinish();

}

void SceneBasic_Uniform::setMatrices(GLSLProgram& p)
{
    mat4 mv = view * model; //we create a model view matrix
    
    p.setUniform("ModelViewMatrix", mv); //set the uniform for the model view matrix

    p.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2]))); //we set the uniform for normal matrix
    
    p.setUniform("MVP", projection * mv); //we set the model view matrix by multiplying the mv with the projection matrix

    p.setUniform("ProjectionMatrix", projection);

}

void SceneBasic_Uniform::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(60.0f), (float)w / h, 0.3f, 100.0f);
}
