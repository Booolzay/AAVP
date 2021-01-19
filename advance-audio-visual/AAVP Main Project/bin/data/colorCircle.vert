#version 150

uniform mat4 modelViewProjectionMatrix;

in vec4 position;

void main(){
	// Simply apply the modelViewProjectionMatrix to all vertex positions.
	gl_Position = modelViewProjectionMatrix * position;
}
