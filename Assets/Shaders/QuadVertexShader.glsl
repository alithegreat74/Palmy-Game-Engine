#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTextureCoordinates;

out vec2 TextureCoordinates;

uniform mat4 uCameraMatrix;
uniform mat4 uTransform;
void main()
{
	TextureCoordinates = aTextureCoordinates;
	gl_Position = uCameraMatrix * uTransform * vec4(aPos,0.0, 1.0);
}