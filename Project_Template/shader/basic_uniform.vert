#version 460

//in variables, this are in model coordinates
layout (location = 0) in vec3 VertexPosition; 
layout (location = 1) in vec3 VertexNormal; 
layout (location = 2) in vec2 VertexTexCoord;




//uniforms for matrices required in the shader
uniform mat4 ModelViewMatrix;   //model view matrix
uniform mat3 NormalMatrix;		//normal matrix
uniform mat4 MVP;				//model view projection matrix
uniform mat4 ProjectionMatrix; 


out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;

void main() 
{ 

        TexCoord = VertexTexCoord;

   //transfrom normal from model coordinates to view coordinates
   Normal = normalize( NormalMatrix * VertexNormal);


   //transform vertex position from model coordinates to view coordinates
   Position = (ModelViewMatrix * vec4(VertexPosition,1.0)).xyz;


  //graphics pipeline processes before fragment shader (clipping)
  gl_Position = MVP * vec4(VertexPosition,1.0); 


} 

