#pragma once

#define STRINGIFY(A) #A

const char* default_vertex_shader = STRINGIFY
(
#version 330 core\n

// Vertex Attribute
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 ourColor;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	ourColor = aColor;
}
);

const char* default_fragment_shader = STRINGIFY
(
#version 330 core\n

// 최종 출력 컬러를 반환하기 위한 out vec4(r,g,b,a) 매크로
out vec4 FragColor;
in vec3 ourColor;

// vertexShader에서 전달받은 입력
//in vec4 vertexColor;

void main()
{
	FragColor = ourColor;
}
);

const char* movable_fragment_shader = STRINGIFY
(
#version 330 core\n

out vec4 fragColor;

// uniform은 모든 shader에서 접근 가능 like static, 코드로 접근 가능
//uniform vec4 ourColor;

void main()
{
	fragColor = ourColor;
}
);