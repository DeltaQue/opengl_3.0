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

// ���� ��� �÷��� ��ȯ�ϱ� ���� out vec4(r,g,b,a) ��ũ��
out vec4 FragColor;
in vec3 ourColor;

// vertexShader���� ���޹��� �Է�
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

// uniform�� ��� shader���� ���� ���� like static, �ڵ�� ���� ����
//uniform vec4 ourColor;

void main()
{
	fragColor = ourColor;
}
);