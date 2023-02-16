#	2D Graphics

##	Contents
*	###	[Line Drawing Algorithms](#line-drawing-algorithms-1)
	+	####	[DDA](#digital-differential-analyzer-dda)
	+	####	[Bresenham\'s algorithm](#bresenhams-algorithm-modified-version)
*	####	[Algorithms comparison](#comparison-1)

##	Line Drawing Algorithms
###	Digital Differential Analyzer (`DDA`)
*	####	Find the distance between the ends of the line along the axes
*	####	Determine the minimum number of steps for each loop iteration
	+	####	If it is equal to zero (the coordinates of the ends of the line are equal), then we only need to draw one pixel
*	####	Determine step value for each iteration
*	####	Fill pixels from (x1, y1) to (x2, y2) using x, y steps
```cpp
void DrawLine(Color color, double x1, double y1, double x2, double y2) {
	const double distanceX = x2 - x1;
	const double distanceY = y2 - y1;

	const double absDistanceX = distanceX >= 0 ? distanceX : -distanceX;
	const double absDistanceY = distanceY >= 0 ? distanceY : -distanceY;

	const unsigned long stepsCount = absDistanceX > absDistanceY ? absDistanceX : absDistanceY;

	if (!stepsCount) DrawPixel(color, x1, y1);

	const double stepX = distanceX / (double)stepsCount;
	const double stepY = distanceY / (double)stepsCount;

	double x = x1;
	double y = y1;

	for (unsigned long step = 0; step < stepsCount; step++) {
		DrawPixel(color, x, y);
		x += stepX;
		y += stepY;
	}
}
```

###	Bresenham\'s Algorithm (Modified Version)
*	####	Find the distance between the ends of the line along the axes
*	####	Calculate decision parameter (`2 * distanceY - distanceX`)
```cpp
//	Multiply by 2 has been replaced with a bit shift
//	Conditions have been replaced with two arrays (decisionParameterChanges, yChanges)
void DrawLine(Color color, long x1, long y1, long x2, long y2) {
	const long distanceX = x2 - x1;
	const long distanceY = y2 - y1;

	const long stepX = distanceX > 0 ? 1 : -1;
	const long stepY = distanceY > 0 ? 1 : -1;

	long decisionParameter = (distanceY << 1) - distanceX;	//	2 * distanceY - distanceX

	long x = x1;
	long y = y1;
	
	DrawPixel(color, x2, y2);

	const long decisionParameterChanges[2] = {
		(distanceY << 1),					//	2 * distanceY
		(distanceY - distanceX) << 1		//	2 * distanceY - 2 * distanceX
	};

	const long yChanges[2] = { 0, stepY };
	bool pixelTooFar;

	while (x != x2 || y != y2) {
		DrawPixel(color, x, y);

		pixelTooFar = decisionParameter >= 0;
		decisionParameter += decisionParameterChanges[pixelTooFar];
		x += stepX;
		y += yChanges[pixelTooFar];
	}
}
```

##	Comparison
| Algorithm Group | Name                     | Pros                  | Cons                |
| :-------------- | :----------------------- | :-------------------- | :------------------ |
| Line Drawing    | `DDA`                    | Pretty easy to understand and implement | Slow due to the use of floating point numbers, as well as division operations |
| Line Drawing    | `Bresenham's`            | Not complex, uses integer arithmetic (multiplication, addition, subtraction), is more accurate than `DDA` | The original implementation is slower than `DDA` |