- this project runs on the 16.11.11 version of visual studio and version 21h1 of windows 10 home

- this project uses several exteral files to go through the graphics render pipline ustilising GLSL and opengl. it opens up objects and textures and completes calculations to work out how light should be reacting to the surface of different models. the calculations and filter this projects uses is the BlinPhong filter.
-  it does this by initilising and  calculating ambient, diffuse and specular light and adding them together with effecient calculations to achieve its look.

i used 3 lights in an array, as well as 4 models with different textures on each.
-the scene may look like a mess and while remebering i am not an artist i did put effort into the palcement of the models in the scene and into blender to create the models.For flavour, i like to think the solider is exploreing the cave after finding the chest as he moves in circles


the important files are, 
  -scenebasic_uniform.h   --- where i have declared some additional models
  -scenebasic_uniform.cpp     ---where uniforms are declared and textues are assigned to models (in the render() function)
  -basic_uniform.frag    ---where colours of pixels are done, where the blinn phong filter determines lighting
  -basic_uniform.vert    --- where initial normal and view positions are calculated
 these make up the render pipeline for this project.
 
 

 a more detailed look through the project is listed here https://youtu.be/90bjbk2LE1o please feel free to leave a comment on how i could improve. :D
