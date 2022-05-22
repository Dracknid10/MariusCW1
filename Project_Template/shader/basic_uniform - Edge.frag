#version 460

//in variable that receives the diffuse calculation from the vertex shader
//in vec3 LightIntensity;
//in vec3 Colour;
//out variable, this typical for all fragment shaders
layout (location = 0) out vec4 FragColor;
layout(binding=0) uniform sampler2D Tex1;
const vec3 lum = vec3(0.2126, 0.7152, 0.0722);

layout( binding=0 ) uniform sampler2D RenderTex;

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D SpriteTex;
uniform float EdgeThreshold;
uniform int Pass;


//in vec4 pos;
//in vec3 camCoords;

 //light information struct
uniform struct LightInfo 
{
  vec4 Position; // Light position in eye coords.
  //vec3 Ld;       // Diffuse light intensity
  vec3 La; // Ambient light intensity
  vec3 L; // Diffuse and specular light intensity
} Light[3];



//material information struct
uniform struct MaterialInfo 
{
  vec3 Ka; // Ambient reflectivity
 vec3 Kd; // Diffuse reflectivity
 vec3 Ks; // Specular reflectivity
 float Shininess; // Specular shininess factor
} Material;



//uniforms for matrices required in the shader
uniform mat4 ModelViewMatrix;   //model view matrix
uniform mat3 NormalMatrix;		//normal matrix
uniform mat4 MVP;				//model view projection matrix




vec3 blinnphongModel(int light, vec3 position, vec3 n )
 {

 vec3 texColor = texture(Tex1, TexCoord).rgb;
// vec3 texColor2 = texture(Tex2, TexCoord).rgb;

  //vec3 col = mix(texColor.rgb, texColor2.rgb, texColor2.a);

       
        //calculate ambient 
       
        vec3 ambient = Light[light].La * texColor;

        //calculate diffuse

         vec3 s = normalize(vec3( vec3( Light[light].Position) - position));
         float sDotN = max( dot(s,n), 0.0 );
         vec3 diffuse = sDotN * texColor;

        //calculate specular

         vec3 spec = vec3(0.0);
             if( sDotN > 0.0 )
            {
                 vec3 v = normalize(-position.xyz);
                 //vec3 r = reflect( -s, n );  
                 vec3 h = reflect( -s, n );

                spec = Material.Ks * pow( max( dot(h,n), 0.0 ), Material.Shininess );

             }

        return ambient + Light[light].L * (diffuse + spec);

}

float luminance( vec3 color )
{
 return dot(lum,color);
}


vec4 pass1()
{
        return vec4(blinnphongModel( 0, Position, normalize(Normal) ),1.0);
}



vec4 pass2()
{
 ivec2 pix = ivec2(gl_FragCoord.xy); //we grab a pixel to check if edge
//pick neighboutring pixels for convolution filter
//check lecture slides
 float s00 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(-1,1)).rgb);
 float s10 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(-1,0)).rgb);
 float s20 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(-1,-1)).rgb);
 float s01 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(0,1)).rgb);
 float s21 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(0,-1)).rgb);
 float s02 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(1,1)).rgb);
 float s12 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(1,0)).rgb);
 float s22 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(1,-1)).rgb);
 float sx = s00 + 2 * s10 + s20 - (s02 + 2 * s12 + s22);
 float sy = s00 + 2 * s01 + s02 - (s20 + 2 * s21 + s22);
 float g = sx * sx + sy * sy;
 if( g > EdgeThreshold )
 return vec4(1.0); //edge
 else
 return vec4(0.0,0.0,0.0,1.0); //no edge
}




void main()
{
        if( Pass == 1 ) FragColor = pass1();
         if( Pass == 2 ) FragColor = pass2();



        for(int i = 0; i < 3; i++){

                FragColor = vec4(blinnphongModel(i,Position, normalize(Normal)),1);
      
                }
      
   
   //FragColor = texture(SpriteTex,TexCoord);

}
