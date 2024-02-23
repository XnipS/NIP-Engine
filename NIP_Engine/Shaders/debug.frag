#version 330 core
// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 normal_cameraspace;
in vec3 lightDirection_cameraspace;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

// Normal of the computed fragment, in camera space
 vec3 n = normalize( normal_cameraspace );
 // Direction of the light (from the fragment to the light)
 vec3 l = normalize( lightDirection_cameraspace );

 vec3 DiffuseColour = texture( myTextureSampler, UV ).rgb;

 vec3 AmbientColour = vec3(0.1,0.1,0.1) * DiffuseColour;

float cosTheta;

void main(){
	// Calculate diffusion
	cosTheta = clamp( dot( n,l ), 0.0f,1.0f );
    // Output color = color of the texture at the specified UV
    color = AmbientColour +  cosTheta * DiffuseColour;
    //color = texture( myTextureSampler, UV ).rgb;
}