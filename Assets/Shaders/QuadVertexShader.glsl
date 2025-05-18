#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec2 aTextureCoordinates;
layout (location = 2) in vec4 aColor;
layout (location = 3) in int aTextureNumber;

out vec2 TextureCoordinates;
out vec4 Color;
flat out int TextureNumber;

uniform mat4 uCameraMatrix;
void main()
{
	TextureCoordinates = aTextureCoordinates;
	Color = aColor;
	TextureNumber = aTextureNumber;
	gl_Position = uCameraMatrix * aPos;
}