#version 330 core
out vec4 FragColor;

//in vec3 ourColor;
//in vec2 TexCoord;

//uniform sampler2D texture1;
//uniform sampler2D texture2;

void main()
{
    // FragColor = mix(texture(texture1, TexCoord * -1), texture(texture2, TexCoord * -1), 0.2);
    FragColor = vec4(1.0);
}