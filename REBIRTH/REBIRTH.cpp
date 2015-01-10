#include "REBIRTH.h"


REBIRTH::REBIRTH()
{
}

void __stdcall meErrorCallback(GLenum _source, GLenum _type, GLuint _id, GLenum _severity, GLsizei _length, const char * _message, void* _userParam) {
	printf("%s\n", _message);
}

void REBIRTH::run() {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
	SDL_Window * window = SDL_CreateWindow("REBIRTH",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		1280, 720,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

	SDL_GLContext glcontext = SDL_GL_CreateContext(window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Using GLEW %s\n", glewGetString(GLEW_VERSION));

	const unsigned char* glv = glGetString(GL_VERSION);
	std::string glversion((const char*)glv);
	glversion = glversion.substr(0, glversion.find(" "));
	std::cout << "GL Context Version " << glversion << std::endl;

	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}
	/*
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);
	glDisable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);*/

	CShaderProgram shaderprogram;
	shaderprogram.loadFragment("res/basic_texture_shader.frag");
	shaderprogram.loadVertex("res/basic_texture_shader.vert");
	shaderprogram.compile();
	shaderprogram.bind();

	int attribute_coord2d = shaderprogram.getAttribLocation("coord2d");
	//glDebugMessageCallbackARB(&meErrorCallback, NULL);
	//glEnable(GL_DEBUG_OUTPUT);

	bool keeprunning = true;

	while (keeprunning) {
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) {
				keeprunning = false;
			}
		}
		glClearColor(0.25f, 0.25f, 0.25f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderprogram.bind();
		glEnableVertexAttribArray(attribute_coord2d);
		GLfloat triangle_vertices[] = {
			0.0, 0.8,
			-0.8, -0.8,
			0.8, -0.8,
		};
		/* Describe our vertices array to OpenGL (it can't guess its format automatically) */
		glVertexAttribPointer(
			attribute_coord2d, // attribute
			2,                 // number of elements per vertex, here (x,y)
			GL_FLOAT,          // the type of each element
			GL_FALSE,          // take our values as-is
			0,                 // no extra data between each position
			triangle_vertices  // pointer to the C array
			);

		/* Push each element in buffer_vertices to the vertex shader */
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(attribute_coord2d);


		SDL_GL_SwapWindow(window);
		SDL_Delay(15);
	}

	SDL_GL_DeleteContext(glcontext);
	// Close and destroy the window
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
};

REBIRTH::~REBIRTH()
{
}
