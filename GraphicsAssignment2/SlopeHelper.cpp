/*		Slope Helper
 *	AUTHOR: STEWART TAYLOR
 *------------------------------------
 * This class is used to provide functions that will determine the slope of a surface
 *
 *
 * Last Updated: 05/11/2012
*/

#include "SlopeHelper.h"
#include <math.h>

SlopeHelper::SlopeHelper(void)
{
}

SlopeHelper::~SlopeHelper(void)
{
}


float  SlopeHelper::getSlopeValue(int x , int y , GLfloat landsc[65][65])
{
	size = 65;

	float topLeft = getTopLeftSlope(x, y ,  landsc);
	float topMid = getTopMiddleSlope(x, y, landsc);
	float topRight = getTopRightSlope(x, y,  landsc);

	float midLeft = getMiddleLeftSlope(x, y,  landsc);
	float midRight = getMiddleRightSlope(x, y,  landsc);

	float botLeft = getBottomLeftSlope(x, y,  landsc);
	float botMid = getBottomMiddleSlope(x, y,  landsc);
	float botRight = getBottomRightSlope(x, y,  landsc);


	float high = 0;

	if (topLeft >= high) { high = topLeft; }
	if (topMid >= high) { high = topMid; }
	if (topRight >= high) { high = topRight; }
	if (midLeft >= high) { high = midLeft; }
	if (midRight >= high) { high = midRight; }
	if (botLeft >= high) { high = botLeft; }
	if (botMid >= high) { high = botMid; }
	if (botRight >= high) { high = botRight; }

	float total = topLeft + topRight + topMid + midLeft + midRight + botLeft + botMid + botRight;

    // float value = total / 8;
	float value = high;

	return value;
}


GLfloat SlopeHelper::getGradientValue(GLfloat x, GLfloat y)
{
	GLfloat gradient = 0;

	if ((x > 0) && (y > 0))
	{
		gradient = x - y;
		gradient = abs(gradient);
	}

	return gradient;
}



GLfloat SlopeHelper::getTopLeftSlope(int x, int y , GLfloat landsc[65][65])
{
	GLfloat gradient = 0;

    if ((x > 0) && (y > 0))
    {
		gradient = getGradientValue(landsc[x - 1][ y - 1], landsc[x][ y]);
	}

	return gradient;
}

GLfloat SlopeHelper::getTopMiddleSlope(int x, int y , GLfloat landsc[65][65])
{
	GLfloat gradient = 0;

	if (y > 0)
	{
		gradient = getGradientValue(landsc[x][ y - 1], landsc[x][ y]);
	}

	return gradient;
}

GLfloat SlopeHelper::getTopRightSlope(int x, int y , GLfloat landsc[65][65])
{
	GLfloat gradient = 0;

	if ((x < size - 1) && (y > 0))
	{
                gradient = getGradientValue(landsc[x + 1][ y - 1], landsc[x][ y]);
	}

	return gradient;
}

GLfloat SlopeHelper::getMiddleLeftSlope(int x, int y , GLfloat landsc[65][65])
{
	GLfloat gradient = 0;

	if (x > 0)
	{
		gradient = getGradientValue(landsc[x - 1][ y], landsc[x][ y]);
	}

	return gradient;
}

GLfloat SlopeHelper::getMiddleRightSlope(int x, int y , GLfloat landsc[65][65])
{
	GLfloat gradient = 0;

    if (x < size - 1)
    {
		gradient = getGradientValue(landsc[x + 1][ y], landsc[x][ y]);
	}

	return gradient;
}

GLfloat SlopeHelper::getBottomLeftSlope(int x, int y , GLfloat landsc[65][65])
{
	GLfloat gradient = 0;

	if ((x > 0) && (y < size - 1))
	{
		gradient = getGradientValue(landsc[x - 1][ y + 1], landsc[x][ y]);
	}

	return gradient;
}

GLfloat SlopeHelper::getBottomMiddleSlope(int x, int y , GLfloat landsc[65][65])
{
	GLfloat gradient = 0;

	if (y < size - 1)
	{
		gradient = getGradientValue(landsc[x][ y + 1], landsc[x][ y]);
	}

	return gradient;
}

GLfloat SlopeHelper::getBottomRightSlope(int x, int y , GLfloat landsc[65][65])
{
	GLfloat gradient = 0;

	if ((x < size - 1) && (y < size - 1))
	{
		gradient = getGradientValue(landsc[x + 1][ y + 1], landsc[x][ y]);
	}

	return gradient;
}