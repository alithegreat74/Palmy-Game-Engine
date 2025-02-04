#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTextureCoordinates;

out vec2 TextureCoordinates;
uniform vec2 uPos;
void main()
{
	TextureCoordinates = aTextureCoordinates;
	gl_Position = vec4(aPos + uPos,0.0, 1.0);
}