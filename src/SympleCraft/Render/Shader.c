#include <pch.h>
#include "SympleCraft/Render/Shader.h"

#include <gl/glew.h>

Shader CreateShader(const char* vertFile, const char* fragFile)
{
	char* vertexSource;
	char* fragmentSource;

	{
		FILE* fs;
		errno_t err = fopen_s(&fs, vertFile, "rb");
		if (!err && fs)
		{
			fseek(fs, 0, SEEK_END);
			size_t size = ftell(fs);
			rewind(fs);

			vertexSource = malloc(size + 1);
			if (!vertexSource)
				return 0;

			fread_s(vertexSource, size, 1, size, fs);
			fclose(fs);
			vertexSource[size] = 0;
		}
		else
		{
			char errMsg[64];
			if (!strerror_s(errMsg, sizeof(errMsg), err))
				fprintf(stderr, "[!]: Error reading Vertex File '%s': %s", vertFile, errMsg);
			return 0;
		}
	}

	{
		FILE* fs;
		errno_t err = fopen_s(&fs, fragFile, "rb");
		if (!err && fs)
		{
			fseek(fs, 0, SEEK_END);
			size_t size = ftell(fs);
			rewind(fs);

			fragmentSource = malloc(size + 1);
			if (!fragmentSource)
				return 0;

			fread_s(fragmentSource, size, 1, size, fs);
			fclose(fs);
			fragmentSource[size] = 0;
		}
		else
		{
			char errMsg[64];
			if (!strerror_s(errMsg, sizeof(errMsg), err))
				fprintf(stderr, "[!]: Error reading Fragment File '%s': %s", fragFile, errMsg);
			return -1;
		}
	}

	Shader shader = malloc(sizeof(struct Shader));
	if (!shader)
		return NULL;

	shader->Program = glCreateProgram();
	{
		shader->Vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(shader->Vertex, 1, &vertexSource, NULL);
		glCompileShader(shader->Vertex);
		{
			GLint status;
			glGetShaderiv(shader->Vertex, GL_COMPILE_STATUS, &status);
			if (!status)
			{
				GLsizei length;
				glGetShaderiv(shader->Vertex, GL_INFO_LOG_LENGTH, &length);

				GLchar* msg = malloc(length);
				glGetShaderInfoLog(shader->Vertex, length, &length, msg);
				glDeleteShader(shader->Vertex);

				fprintf(stderr, "[!]: Failed to compile Vertex Shader: %s\n", msg);
				free(msg);
			}
		}

		shader->Fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(shader->Fragment, 1, &fragmentSource, NULL);
		glCompileShader(shader->Fragment);
		{
			GLint status;
			glGetShaderiv(shader->Fragment, GL_COMPILE_STATUS, &status);
			if (!status)
			{
				GLsizei length;
				glGetShaderiv(shader->Fragment, GL_INFO_LOG_LENGTH, &length);

				GLchar* msg = malloc(length);
				glGetShaderInfoLog(shader->Fragment, length, &length, msg);
				glDeleteShader(shader->Fragment);

				fprintf(stderr, "[!]: Failed to compile Fragment Shader: %s\n", msg);
				free(msg);
			}
		}

		glAttachShader(shader->Program, shader->Vertex);
		glAttachShader(shader->Program, shader->Fragment);

		glLinkProgram(shader->Program);
		glValidateProgram(shader->Program);

		free(vertexSource);
		free(fragmentSource);
	}

	return shader;
}

void BindShader(Shader shader)
{
	glUseProgram(shader->Program);
}

void DeleteShader(Shader shader)
{
	glDetachShader(shader->Program, shader->Vertex);
	glDeleteShader(shader->Vertex);
	glDetachShader(shader->Program, shader->Fragment);
	glDeleteShader(shader->Fragment);

	glDeleteProgram(shader->Program);
}

int GetUniformLocation(Shader shader, const char* name)
{
	return glGetUniformLocation(shader->Program, name);
}

void SetShaderUniformi(Shader shader, const char* name, int value)
{
	glUniform1i(GetUniformLocation(shader, name), value);
}
void SetShaderUniformf(Shader shader, const char* name, float value)
{
	glUniform1f(GetUniformLocation(shader, name), value);
}
void SetShaderUniformVec(Shader shader, const char* name, Vector vector)
{
	glUniform4f(GetUniformLocation(shader, name), vector->x, vector->y, vector->z, vector->w);
}
void SetShaderUniformMat(Shader shader, const char* name, Matrix matrix)
{
	glUniformMatrix4fv(GetUniformLocation(shader, name), 1, GL_TRUE, matrix);
}