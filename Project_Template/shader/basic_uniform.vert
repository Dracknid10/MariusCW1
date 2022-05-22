#version 460

//in variables, this are in model coordinates
layout (location = 0) in vec3 VertexPosition; 
layout (location = 1) in vec3 VertexNormal; 
layout (location = 2) in vec2 VertexTexCoord;




//uniforms for matrices required in the shader
uniform mat4 ModelViewMatrix;   //model view matrix
uniform mat3 NormalMatrix;		//normal matrix
uniform mat4 MVP;				//model view projection matrix


uniform float Time;
uniform bool Animated;


out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;

uniform float Freq = 2.5;
uniform float Velocity = 2.5;
uniform float Amp = 0.6;




void main() 
{ 

  //graphics pipeline processes before fragment shader (clipping)

  if(Animated == true){

              vec4 pos = vec4(VertexPosition,1.0);

              float u = Freq * pos.x - Velocity * Time;
              pos.y = Amp * sin( u );

              vec3 n = vec3(0.0);

              n.xy = normalize(vec2(cos( u ),1.0));

              Position = (ModelViewMatrix * pos).xyz;

              Normal = NormalMatrix * n;

              TexCoord = VertexTexCoord;



             gl_Position = MVP * pos;
    }

    else if(Animated==false)
    {

       //transfrom normal from model coordinates to view coordinates
       Normal = normalize( NormalMatrix * VertexNormal);


       //transform vertex position from model coordinates to view coordinates
       Position = (ModelViewMatrix * vec4(VertexPosition,1.0)).xyz;

       
              TexCoord = VertexTexCoord;

         gl_Position = MVP * vec4(VertexPosition,1.0); 

    }

} 

