#version 330 core
// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 normal_cameraspace;
in vec3 lightDirection_cameraspace;
in vec3 eyeDirection_cameraspace;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

// Normal of the computed fragment, in camera space
vec3 n = normalize( normal_cameraspace );
// Direction of the light (from the fragment to the light)
vec3 l = normalize( lightDirection_cameraspace );
// Eye vector towards camera
vec3 E = normalize(eyeDirection_cameraspace);
// Direction that triangle reflects light
vec3 R = reflect(-l,n);

vec3 DiffuseColour = texture( myTextureSampler, UV ).rgb;

vec3 AmbientColour = vec3(.1,.1,.1) * DiffuseColour;

vec3 SpecularColour = vec3(1,1,1);

float cosTheta;

float cosAlpha;

void main(){

	// Calculate specular
	cosAlpha = clamp( dot( E,R ), 0.0f,1.0f );
	// Calculate diffusion
	cosTheta = clamp( dot( n,l ), 0.0f,1.0f );
    // Output color = color of the texture at the specified UV
    color = AmbientColour +  (cosTheta * DiffuseColour) + (pow(cosAlpha,5) * SpecularColour) ;

}