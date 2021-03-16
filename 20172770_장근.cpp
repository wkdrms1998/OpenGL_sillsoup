//���� ĥ�ϱ�//////////////////////////////////////////
// sb6.h ��� ������ ���Խ�Ų��.
#include <sb6.h>
#include <vmath.h>

// sb6::application�� ��ӹ޴´�.
class my_application : public sb6::application
{
public:
	//���̴��� ������
	GLuint compile_shader(void){
		GLuint vertex_shader1;
		GLuint fragment_shader1;
		GLuint program1;

		//���ؽ� ���̴� �ҽ� �ڵ�
		static const GLchar * vertex_shader_source1[] = {
			"#version 430 core													\n"
			"																	\n"
			"void main(void)													\n"
			"{																	\n"
			"	const vec4 vertices[12] = vec4[12](vec4(0.0, 0.0, 0.5, 1.0),	\n"
			"									   vec4(-0.5, 0.5, 0.5, 1.0),	\n"
			"									   vec4(0.0, 0.5, 0.5, 1.0),	\n"
			"									   vec4(0.0, 0.0, 0.5, 1.0),	\n"
			"									   vec4(0.5, 0.5, 0.5, 1.0),	\n"
			"									   vec4(0.5, 0.0, 0.5, 1.0),	\n"
			"									   vec4(0.0, 0.0, 0.5, 1.0),	\n"
			"									   vec4(0.5, -0.5, 0.5, 1.0),	\n"
			"									   vec4(0.0, -0.5, 0.5, 1.0),	\n"
			"									   vec4(0.0, 0.0, 0.5, 1.0),	\n"
			"									   vec4(-0.5, -0.5, 0.5, 1.0),	\n"
			"									   vec4(-0.5, 0.0, 0.5, 1.0));	\n"
			"	gl_Position = vertices[gl_VertexID];							\n"
			"}																	\n"
		};

		//�����׸�Ʈ ���̴� �ҽ� �ڵ�
		static const GLchar * fragment_shader_source1[] = {
			"#version 430 core							\n"
			"											\n"
			"out vec4 color;							\n"
			"											\n"
			"void main(void)							\n"
			"{											\n"
			"	color = vec4(0.0, 0.8, 1.0, 1.0);		\n"
			"}											\n"
		};

		//���ؽ� ���̴��� �����ϰ� ������
		vertex_shader1 = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader1, 1, vertex_shader_source1, NULL);
		glCompileShader(vertex_shader1);
		
		//�����׸�Ʈ ���̴��� �����ϰ� ������
		fragment_shader1 = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader1, 1, fragment_shader_source1, NULL);
		glCompileShader(fragment_shader1);
		
		//���α׷� ���� ���̴� ����ġ ��ũ
		program1 = glCreateProgram();
		glAttachShader(program1, vertex_shader1);
		glAttachShader(program1, fragment_shader1);
		glLinkProgram(program1);


		//���̴� ����
		glDeleteShader(vertex_shader1);
		glDeleteShader(fragment_shader1);

		return program1;
	}

	GLuint compile_shader2(void){
		GLuint vertex_shader2;
		GLuint fragment_shader2;
		GLuint program2;

		static const GLchar * vertex_shader_source2[] = {
			"#version 430 core													\n"
			"																	\n"
			"void main(void)													\n"
			"{																	\n"
			"	const vec4 vertices[5] = vec4[5](vec4(-0.02, 0.0, 0.5, 1.0),	\n"
			"									 vec4(0.02, 0.0, 0.5, 1.0),		\n"
			"									 vec4(0.02, -1.0, 0.5, 1.0),	\n"
			"									 vec4(-0.02, -1.0, 0.5, 1.0),	\n"
			"									 vec4(-0.02, 0.0, 0.5, 1.0));	\n"
			"	gl_Position = vertices[gl_VertexID];							\n"
			"}																	\n"
		};

		static const GLchar * fragment_shader_source2[] = {
			"#version 430 core							\n"
			"											\n"
			"out vec4 color;							\n"
			"											\n"
			"void main(void)							\n"
			"{											\n"
			"	color = vec4(0.62, 0.14, 0.96, 1.0);	\n"
			"}											\n"
		};

		vertex_shader2 = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader2, 1, vertex_shader_source2, NULL);
		glCompileShader(vertex_shader2);

		fragment_shader2 = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader2, 1, fragment_shader_source2, NULL);
		glCompileShader(fragment_shader2);

		program2 = glCreateProgram();
		glAttachShader(program2, vertex_shader2);
		glAttachShader(program2, fragment_shader2);
		glLinkProgram(program2);

		glDeleteShader(vertex_shader2);
		glDeleteShader(fragment_shader2);

		return program2;
	}

	//���ø����̼� �ʱ�ȭ
	virtual void startup() {
		rendering_program1 = compile_shader();
		glGenVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);

		rendering_program2 = compile_shader2();
		glGenVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);
	}

	//���ø����̼� ����� ȣ��
	virtual void shutdown(){
		glDeleteVertexArrays(1, &vertex_array_object);
		glDeleteProgram(rendering_program1);
		glDeleteProgram(rendering_program2);
	}

	// ������ virtual �Լ��� �ۼ��ؼ� �������̵��Ѵ�.
	virtual void render(double currentTime){
		const GLfloat red[] = {
			(float)sin(currentTime) * 0.5f + 0.5f,
			(float)cos(currentTime) * 0.5f + 0.5f,
			0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, red);

		glUseProgram(rendering_program2);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 2, 3);

		//������ ���� ������ ���α׷� ��ü ���
		glUseProgram(rendering_program1);

		//���׸���
		glPointSize(40.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 3, 3);
		glDrawArrays(GL_TRIANGLES, 6, 3);
		glDrawArrays(GL_TRIANGLES, 9, 3);
	}

private:
	GLuint rendering_program1, rendering_program2;
	GLuint vertex_array_object;
};

// DECLARE_MAIN�� �ϳ����� �ν��Ͻ�
DECLARE_MAIN(my_application)
