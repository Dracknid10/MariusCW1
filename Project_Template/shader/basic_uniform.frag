#version 460

//in variable that receives the diffuse calculation from the vertex shader
//in vec3 LightIntensity;
//in vec3 Colour;
//out variable, this typical for all fragment shaders
layout (location = 0) out vec4 FragColor;
layout(binding=0) uniform sampler2D Tex1;


in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;


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

//uniform struct SpotLightInfo 
//{
//
//vec3 Position; // Position in cam coords
//vec3 L; // Diffuse/spec intensity
//vec3 La; // Amb intensity
//vec3 Direction; // Direction of the spotlight in cam coords.
//float Exponent; // Angular attenuation exponent
//float Cutoff; // Cutoff angle (between 0 and pi/2)
//
//
//} Spot;
//

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
uniform mat4 ProjectionMatrix; 



vec3 blinnphongModel(int light, vec3 position, vec3 n )
 {

 vec3 texColor = texture(Tex1, TexCoord).rgb;
//  vec3 texColor2 = texture(Tex2, TexCoord).rgb;

  //vec3 col = mix(texColor.rgb, texColor2.rgb, texColor2.a);

       
        //calculate ambient 
       
        vec3 ambient = Light[light].La * texColor * Material.Ka;

        //calculate diffuse

         vec3 s = normalize(vec3( vec3( Light[light].Position) - position));
         float sDotN = max( dot(s,n), 0.0 );
         vec3 diffuse = Material.Kd * sDotN * texColor;

        //calculate specular

         vec3 spec = vec3(0.0);
             if( sDotN > 0.0 )
            {
                 vec3 v = normalize(-position.xyz);
                 //vec3 r = reflect( -s, n );  
                 vec3 h = reflect( -s, n );

                spec = Material.Ks * pow( max( dot(h,n), 0.0 ),
                Material.Shininess );

             }

        return ambient + Light[light].L * (diffuse + spec);

}
//vec3 blinnPhongSpot( vec3 position, vec3 n )
//{
//         vec3 ambient = Spot.La * Material.Ka;
//         vec3 s = normalize(vec3( vec3( Spot.Position) - position));
//         float sDotN = max( dot(s,n), 0.0 );
//       
//
//        float cosAng = dot(-s, normalize(Spot.Direction)); //cosine of the angle
//        float angle = acos( cosAng ); //gives you the actual angle
//        float spotScale = 0.0;
//        if(angle < Spot.Cutoff )
//        {
//        spotScale = pow( cosAng, Spot.Exponent );
//
//
//        vec3 spec = vec3(0.0);
//         if( sDotN > 0.0 )
//            {
//                 vec3 v = normalize(-position.xyz);
//                 //vec3 r = reflect( -s, n );  
//                 vec3 h = reflect( -s, n );
//
//                spec = Material.Ks * pow( max( dot(h,n), 0.0 ),
//                Material.Shininess );
//
//             }
//         vec3 diffuse = Material.Kd * sDotN;
//
//          return ambient + spotScale * Spot.L * (diffuse + spec);
//        }
//       
//} 

void main()
{


        for(int i = 0; i < 3; i++){

                FragColor = vec4(blinnphongModel(i,Position, normalize(Normal)),1);
      
      }
      
   


}
