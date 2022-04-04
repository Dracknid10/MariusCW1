#include "scenebasic_uniform.h"
#include <sstream>

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
}

//constructor for teapot
//SceneBasic_Uniform::SceneBasic_Uniform() : teapot(13, glm::translate(mat4(1.0f), vec3(0.0f, 1.5f, 0.25f))) {}

void SceneBasic_Uniform::initScene()
{
    compile();
	glEnable(GL_DEPTH_TEST);
   
    //initialise the model matrix
    model = mat4(1.0f);
    
    //enable this group for torus rendering, make sure you comment the teapot group
    //model = glm::rotate(model, glm::radians(-35.0f), vec3(1.0f, 0.0f, 0.0f)); //rotate model on x axis
    //model = glm::rotate(model, glm::radians(15.0f), vec3(0.0f, 1.0f, 0.0f));  //rotate model on y axis
    //view = glm::lookAt(vec3(0.0f, 0.0f, 2.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)); //sets the view - read in the documentation about glm::lookAt. if still have questions,come an dtalk to me

    //enable this group for teapot rendering, make sure you comment the torus group
    //model = glm::translate(model, vec3(0.0, -1.0, 0.0));
    //model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
    //view = glm::lookAt(vec3(2.0f, 4.0f, 2.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
  

    //view = glm::lookAt(vec3(0.5f, 0.75f, 0.75f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    view = glm::lookAt(vec3(1.0f, 1.25f, 1.25f), vec3(0.0f, 0.0f, 0.0f),vec3(0.0f, 1.0f, 0.0f));

    projection = mat4(1.0f);

    //float x, z;
    //for (int i = 0; i < 3; i++)
    //{
    // 
    //    std::stringstream name;
    //    name << "Light[" << i << "].Position";
    //    x = 2.0f * cosf((glm::two_pi<float>() / 3) * i);
    //    z = 2.0f * sinf((glm::two_pi<float>() / 3) * i);
    //    prog.setUniform(name.str().c_str(), view * glm::vec4(x, 1.2f, z +
    //        1.0f, 1.0f));
    //}





    projection = mat4(1.0f);

    //make sure you use the correct name, check your vertex shader
    //prog.setUniform("Material.Kd", 0.2f, 0.55f, 0.9f); //seting the Kd uniform    
    
    //prog.setUniform("Light[0].Ld", 1.0f, 1.0f, 1.0f);     //setting the Ld uniform
    //prog.setUniform("Light[1].Ld", 1.0f, 1.0f, 1.0f);     //setting the Ld uniform
    //prog.setUniform("Light[2].Ld", 1.0f, 1.0f, 1.0f);     //setting the Ld uniform
    //prog.setUniform("Light[3].Ld", 1.0f, 1.0f, 1.0f);     //setting the Ld uniform


    prog.setUniform("Light[0].Position", view * glm::vec4(5.0f, 5.0f, 2.0f, 0.0f)); //setting Light Position
    prog.setUniform("Light[1].Position", view * glm::vec4(5.0f, 5.0f, 2.0f, 0.0f)); //setting Light Position
    prog.setUniform("Light[2].Position", view * glm::vec4(5.0f, 5.0f, 2.0f, 0.0f)); //setting Light Position
    //prog.setUniform("Light[3].Position", view * glm::vec4(5.0f, 5.0f, 2.0f, 0.0f)); //setting Light Position


    prog.setUniform("Light[0].La",vec3(0.3f));  //setting ambient vlaue
    prog.setUniform("Light[1].La", vec3(0.4f, 0.3f, 0.3f));  //setting ambient value
    prog.setUniform("Light[2].La", vec3(0.3f, 0.3f, 0.3f));  //setting ambient value
    //prog.setUniform("Light[3].La", vec3(0.1f, 0.1f, 0.1f));  //setting ambient value


    prog.setUniform("Light[0].L", vec3(1));
    prog.setUniform("Light[1].L", vec3(1));
    prog.setUniform("Light[2].L", vec3(0.5));

    //prog.setUniform("Spot.L", vec3(0.9f));
    //prog.setUniform("Spot.La", vec3(0.5f));
    //prog.setUniform("Spot.Exponent", 50.0f);
    //prog.setUniform("Spot.Cutoff", glm::radians(15.0f));

   /* prog.setUniform("Light[3].L", vec3(0.8 , 1 , 0.3));*/




        



}



void SceneBasic_Uniform::compile()
{
	try {
		prog.compileShader("shader/basic_uniform.vert");
		prog.compileShader("shader/basic_uniform.frag");
		prog.link();
		prog.use();
	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::update( float t )
{
    rotation = t;   // add rotations where nessesary by radiuns*rotation 
}

void SceneBasic_Uniform::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, wood);

    //vec4 lightPos = vec4(0.0f, 10.0f, 0.0f, 1.0f);
    //prog.setUniform("Spot.Position", vec3(view * lightPos));
    //mat3 normalMatrix = mat3(vec3(view[0]), vec3(view[1]), vec3(view[2]));
    //prog.setUniform("Spot.Direction", normalMatrix * vec3(-lightPos));

    setMatrices(); //we set matrices 
    //torus.render();     //we render the torus
    //teapot.render();  
    prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Shininess", 1.0f);
    prog.setUniform("Tex1", 0);
    model = mat4(1.0f);
    model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, vec3(10, -3, -7));
    setMatrices();
    mesh->render();


    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, water);

    glBindTexture(GL_TEXTURE_2D, water);
    prog.setUniform("Material.Kd", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Shininess", 0.1f);
    model = mat4(1.0f);
    prog.setUniform("Tex1", 2);
    //model * glm::scale(model, vec3(20));
    model = glm::rotate(model, glm::radians(90.0f * rotation), vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, vec3(0, -6, -7));
    
    
    
    
    setMatrices();
    plane.render();


    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, moss);


    prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Shininess", 1.0f);
    prog.setUniform("Tex1", 1);
    model = mat4(1.0f);
    model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, vec3(8, -8, -3));
    //model = glm::translate(model, vec3(80000, -8, -3));
    setMatrices();
    meshbackground->render();


}

void SceneBasic_Uniform::setMatrices()
{
    mat4 mv = view * model; //we create a model view matrix
    
    prog.setUniform("ModelViewMatrix", mv); //set the uniform for the model view matrix
    
    prog.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2]))); //we set the uniform for normal matrix
    
    prog.setUniform("MVP", projection * mv); //we set the model view matrix by multiplying the mv with the projection matrix
}

void SceneBasic_Uniform::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 100.0f);
}
