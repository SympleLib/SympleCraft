#include <pch.h>
#include "SympleCraft/Util/Noise.h"

/* ----- Perlin Noise By JavidX9 ----- */

float GetNoise(int width, int height, float* seed, int octives, float bias, float* out)
{
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
		{
			float noise = 0;
			float scaleAcc = 0;
			float scale = 1;

			for (int o = 0; o < octives; o++)
			{
				int pitch = width >> o;
				int sampleX1 = (x / pitch) * pitch;
				int sampleY1 = (y / pitch) * pitch;

				int sampleX2 = (sampleX1 + pitch) % width;
				int sampleY2 = (sampleY1 + pitch) % height;

				float blendX = (float)(x - sampleX1) / (float)pitch;
				float blendY = (float)(y - sampleY1) / (float)pitch;

				float sampleT = (1.0f - blendX) * seed[sampleY1 * width + sampleX1] + blendX * seed[sampleY1 * width + sampleX2];
				float sampleB = (1.0f - blendX) * seed[sampleY2 * height + sampleX1] + blendX * seed[sampleY2 * height + sampleX2];

				scaleAcc += scale;
				noise = (blendY * (sampleB - sampleT) + sampleT) * scale;
				scale /= bias;
			}

			out[x + y * width] = noise / scaleAcc;
		}
}