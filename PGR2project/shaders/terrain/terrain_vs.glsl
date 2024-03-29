#
//==============================================================================
//  Terrain VERTEX shader   
//
//==============================================================================
	
varying vec3	eye;
varying vec3	normal;
varying float	height;
varying float	fogFactor;

// shadow mapping
uniform mat4	LightMVPCameraVInverseMatrix;
uniform mat4	LightMViewCameraViewInverseMatrix;

varying	vec4	lightSpacePosition;
varying	vec4	lightProjSpacePosition;

void main()
{
	vec4 position = gl_ModelViewMatrix * gl_Vertex;
	eye = position.xyz;
	lightProjSpacePosition	= LightMVPCameraVInverseMatrix*(position);
	lightSpacePosition		= LightMViewCameraViewInverseMatrix*(position);


	normal = gl_NormalMatrix * gl_Normal;
	height = gl_Vertex.y;

	const float LOG2 = 1.442695;
	gl_FogFragCoord = length(eye);
	fogFactor = exp2( -gl_Fog.density * 
					   gl_Fog.density * 
					   gl_FogFragCoord * 
					   gl_FogFragCoord * 
					   LOG2 );
	fogFactor = clamp(fogFactor, 0.0, 1.0);
	gl_TexCoord[0] = gl_MultiTexCoord0;


	gl_FrontColor = gl_Color;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}