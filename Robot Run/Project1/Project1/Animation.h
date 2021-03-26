//Mati Kutt
//https://instituteoftechnol663-my.sharepoint.com/:v:/g/personal/c00250720_itcarlow_ie/ET7MfdaXqgBPsPlBpAkTy1oBANNCEDhLj3D4wRxUZSLTHQ?email=Noel.OHara%40itcarlow.ie&e=8TzVXg
#include <SFML/Graphics.hpp>
#pragma once
#include <iostream>
class Animation {
public:
	int numframes;
	int startOffset;
	int speed;
	bool loop;

};


class AnimationSheet
{
public:

	int frameCounter;
	sf::Vector2i frameSize{  };
	int numRows = 0;
	int numCols = 0;
	Animation curAnimation;
	int curFrameOffset = 0;

	void Init(int _pixelWidth, int _pixelHeight, int _numRows, int _numCols)
	{

		numCols = _numCols;
		numRows = _numRows;
		if (numCols != 0)
		{
			frameSize.x = _pixelWidth / numCols;
		}
		else
		{
			frameSize.x = _pixelWidth;
		}

		if (numRows != 0)
		{
			frameSize.y = _pixelHeight / numRows;
		}
		else
		{
			frameSize.y = _pixelHeight;
		}
		
		curFrameOffset = 0;

	}
	sf::IntRect GetFrame()
	{
		int row = numRows;
		int col;

		if (numCols == 0)
		{
			 col = numCols;
		}
		else
		{
			 col = curFrameOffset % numCols;
		}
		sf::IntRect frameRectangle;
		frameRectangle.left = col * frameSize.x;
		frameRectangle.top = row * frameSize.y;
		frameRectangle.width = frameSize.x;
		frameRectangle.height = frameSize.y;
		return frameRectangle;
	}
	void StartAnimation(Animation curAnimation)
	{
		this->curAnimation = curAnimation;
		frameCounter = 0;
		curFrameOffset = curAnimation.startOffset;

	}
	void nextFrame()
	{
		if (frameCounter > curAnimation.speed)
		{

			frameCounter = 0;
			if (curFrameOffset >= curAnimation.startOffset + curAnimation.numframes - 1)
			{
				if (curAnimation.loop == true)
				{
					curFrameOffset = curAnimation.startOffset;
				}
				else {
					curFrameOffset = curAnimation.startOffset + curAnimation.numframes - 1;
				}

			}
			else {
				std::cout << curFrameOffset << std::endl;
				curFrameOffset++;
			}
		}
		else {
			frameCounter++;
		}
	}
};
