
#include <random>
#include "Helper/gl_lib.h"
#include "Helper/gl_macros.h"
#include "Helper/glfw_app.h"
#include "Helper/gl_shader.h"
#include "Helper/gl_mouse.h"
#include "Helper/gl_keyboard.h"
#include "Helper/gl_cube.h"
#include "Helper/gl_random.h"
#include "ThirdParty/Noise/FastNoise.h"
#include "Helper/gl_oscillator.h"

struct MyApp : public Helper::App
{
	GLuint viewID{}, projectionID{};

	Helper::Shader *shader{};

	Helper::Mouse *mouseHelper{};

	Helper::Keyboard *keyboardHelper{};

	Helper::Cube *cubeSkyBox{};

	Helper::Cube *cubeGrass{};

	Helper::Cube *cubeStone{};

	Helper::Cube *cubeDirt{};

	Helper::Cube *cubeWater{};

	Helper::Cube *cubeCloud{};

	// to use to for having random values for noise generator
	Helper::Random *random{};

	// to have clouds move ping pong between two values
	Helper::Oscillator *oscillator{};

	// it is used for the random value generation
	float generated_rand_seed{};

	// how much ups and down should be in the terrain, lower values means more details
	float terrain_detail = 0.5;

	// it makes a difference between the highest part and the lowest part of the terrain
	// .. higher values mean, more difference.
	float height_multiplier = 20;

	// the end height of the terrain
	int total_Height = 10;

	FastNoise generated_Noise;

	// different type of noise has been used for the clouds
	// .. so to get more fractal parts
	FastNoise generated_Noise_ForClouds;

	// a vector that will hold some random values, to have on random some dirt layers
	std::vector<int> generated_rand_dirt_layer = {};

	// a vector that will hold some random values,
	// .. it helps us having a less solid clouds, but more jagged
	std::vector<int> generated_rand_cloud_layer = {};

	MyApp()
	{
		init();
	}

	void init()
	{
		// one shader has been used for all the cubes
		shader = new Helper::Shader();

		cubeSkyBox = new Helper::Cube(
			shader->id(),
			R"(Textures\skybox.bmp)");

		cubeGrass = new Helper::Cube(
			shader->id(),
			R"(Textures\grass.bmp)");

		cubeStone = new Helper::Cube(
			shader->id(),
			R"(Textures\stone.bmp)");

		cubeDirt = new Helper::Cube(
			shader->id(),
			R"(Textures\dirt.bmp)");

		cubeWater = new Helper::Cube(
			shader->id(),
			R"(Textures\water.bmp)");

		cubeCloud = new Helper::Cube(
			shader->id(),
			R"(Textures\cloud.bmp)");

		viewID = glGetUniformLocation(shader->id(), "view");

		projectionID = glGetUniformLocation(shader->id(), "projection");

		mouseHelper = new Helper::Mouse((float)window().width(), (float)window().height());

		keyboardHelper = new Helper::Keyboard();

		// for terrain
		generated_Noise.SetNoiseType(FastNoise::SimplexFractal);

		// for clouds
		generated_Noise_ForClouds.SetNoiseType(FastNoise::Cellular);

		// for terrain
		random = new Helper::Random(100000, 999999);

		// for terrain
		generated_rand_seed = random->getGeneratedNumber();

		generated_rand_dirt_layer.reserve(30);

		generated_rand_cloud_layer.reserve(40);

		// filling a vector to have on random some dirt layers
		for (int i = 0; i < 30; ++i)
		{
			random = new Helper::Random(0, 5);
			generated_rand_dirt_layer.push_back(random->getGeneratedNumber());
		}

		// filling a vector with random numbers to have more dis-jointed clouds
		for (int i = 0; i < 40; ++i)
		{
			random = new Helper::Random(0, 30);
			generated_rand_cloud_layer.push_back(random->getGeneratedNumber());
		}

		// it helps us have a moving ping ponged clouds between two values
		oscillator = new Helper::Oscillator(-50, 50);
	}

	void onDraw() override
	{
		keyboardHelper->ListenToKeys(mouseHelper->getCameraFront(), window());

		glm::mat4 view = glm::lookAt(
			keyboardHelper->getCameraPos(),
			keyboardHelper->getCameraPos() + mouseHelper->getCameraFront(),
			glm::vec3(0.0f, 1.0f, 0.0f));

		glm::mat4 projection = glm::perspective(3.14f / 3.0f, window().ratio(), 0.1f, -100.0f);

		glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(projection));

		cubeSkyBox->InsideLoop(view, 1000000, glm::vec3(0, 0, 0), 0.0f, glm::vec3(0, 1, 0));

		for (int x = 0; x < 30; ++x)
		{
			for (int z = 0; z < 30; ++z)
			{
				auto perlin_x = ((float)x / 2.0f + generated_rand_seed) / terrain_detail;
				auto perlin_z = ((float)z / 2.0f + generated_rand_seed) / terrain_detail;
				auto max_y = (int)(generated_Noise.GetNoise(perlin_x, perlin_z) * height_multiplier);

				max_y += total_Height;

				// water layers will happen only relative to the height_multiplier
				if (height_multiplier / 5 > max_y)
				{
					cubeWater->InsideLoop(view, 10, glm::vec3(x * 20, max_y * 20, z * 20), -90.0f, glm::vec3(1, 0, 0));
				}
				else
				{
					cubeGrass->InsideLoop(view, 10, glm::vec3(x * 20, max_y * 20, z * 20), -90.0f, glm::vec3(1, 0, 0));
				}

				for (auto y = 0; y < max_y; y++)
				{
					if (y >= max_y - generated_rand_dirt_layer[y])
					{

						cubeDirt->InsideLoop(view, 10, glm::vec3(x * 20, y * 20, z * 20), -90.0f, glm::vec3(1, 0, 0));
					}
					else
					{
						cubeStone->InsideLoop(view, 10, glm::vec3(x * 20, y * 20, z * 20), -90.0f, glm::vec3(1, 0, 0));
					}
				}
			}	
		}

		// to have moving clouds, we need time
		static float time = 0.0;
		time += .1;

		// it helps us to expand the clouds' cube from each other
		bool checker = false;

		// main loops for the clouds
		for (int x1 = 0; x1 < 40; ++x1)
		{
			for (int z1 = 0; z1 < 40; ++z1)
			{
				auto perlin_x = ((float)x1 / 2.0f + generated_rand_seed) / 0.04;
				auto perlin_z = ((float)z1 / 2.0f + generated_rand_seed) / 0.04;

				auto max_y = (int)(generated_Noise_ForClouds.GetNoise(perlin_x, perlin_z) * 10);

				max_y += 5;

				if (z1 > generated_rand_cloud_layer[x1] && generated_rand_cloud_layer[x1] < z1)
				{
					cubeCloud->InsideLoop(view,
						10,
						glm::vec3(
						(float)x1 * 20 + oscillator->normalize(time) +
							(float)(checker ? -20 : +20),
							max_y * 20 + 500,
							(float)z1 * 20 + (float)(checker ? -20 : +20)),
						-90.0f,
						glm::vec3(1, 0, 0));
					checker = !checker;
				}
			}
		}
	}

	// to get mouse movement
	void onMouseMove(int x, int y)
		override
	{
		mouseHelper->inMouseCallBack(x, y);
	}
};

int main()
{
	MyApp app;
	app.start();

	return 0;
}