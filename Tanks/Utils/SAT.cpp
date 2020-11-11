#include "SAT.h"

//Perform the dot product between two 2D vectors
float DotProduct(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

//Get the Magnitude of the given vector
float GetMagnitude(const sf::Vector2f& vector)
{
	return std::sqrtf(vector.x * vector.x + vector.y * vector.y);
}

//Retrieve the normals of the Rectangle
void GetNormals(const sf::RectangleShape& box, sf::Vector2f normals[])
{
	for (int i = 0; i < box.getPointCount(); i++)
	{
		int j = i + 1;
		j %= box.getPointCount();

		sf::Vector2f temp = sf::Vector2f(
			box.getTransform().transformPoint(box.getPoint(j)).y - box.getTransform().transformPoint(box.getPoint(i)).y,
			box.getTransform().transformPoint(box.getPoint(j)).x - box.getTransform().transformPoint(box.getPoint(i)).x
		);

		if (temp.y != 0)
			temp.y *= -1;

		Normalize(temp);
		normals[i] = temp;
	}
}

//Turns the given vector into a Unit Vector 
void Normalize(sf::Vector2f& vec)
{
	float magnitude = GetMagnitude(vec);
	if (magnitude > 0)
		magnitude = 1 / magnitude;

	vec.x *= magnitude;
	vec.y *= magnitude;
}

bool CheckSATDetection(const sf::RectangleShape& boxA, const sf::RectangleShape& boxB)
{
	//Step 1: Get the normals of both boxes
	sf::Vector2f boxANormals[4];
	GetNormals(boxA, boxANormals);

	sf::Vector2f boxBNormals[4];
	GetNormals(boxB, boxBNormals);

	//Normals to project our vertices in;
	//Pick 2 normals from each boxes
	sf::Vector2f normalsToTest[4];
	normalsToTest[0] = boxANormals[0];
	normalsToTest[1] = boxANormals[1];
	normalsToTest[2] = boxBNormals[2];
	normalsToTest[3] = boxBNormals[3];

	//Step 2: Get the points to project onto the axes!
	sf::Vector2f boxAPoints[4];
	boxAPoints[0] = boxA.getTransform().transformPoint(sf::Vector2f(0.0f, 0.0f));
	boxAPoints[1] = boxA.getTransform().transformPoint(sf::Vector2f(boxA.getSize().x, 0.0f));
	boxAPoints[2] = boxA.getTransform().transformPoint(sf::Vector2f(boxA.getSize().x, boxA.getSize().y));
	boxAPoints[3] = boxA.getTransform().transformPoint(sf::Vector2f(0.0f, boxA.getSize().y));

	sf::Vector2f boxBPoints[4];
	boxBPoints[0] = boxB.getTransform().transformPoint(sf::Vector2f(0.0f, 0.0f));
	boxBPoints[1] = boxB.getTransform().transformPoint(sf::Vector2f(boxB.getSize().x, 0.0f));
	boxBPoints[2] = boxB.getTransform().transformPoint(sf::Vector2f(boxB.getSize().x, boxB.getSize().y));
	boxBPoints[3] = boxB.getTransform().transformPoint(sf::Vector2f(0.0f, boxB.getSize().y));

	//Step 3: Identify the max & min projection points - The Bounds of a line (axis)
	Axis a = ProjectOntoAxis(boxAPoints, normalsToTest[0]);
	Axis b = ProjectOntoAxis(boxAPoints, normalsToTest[1]);
	Axis c = ProjectOntoAxis(boxAPoints, normalsToTest[2]);
	Axis d = ProjectOntoAxis(boxAPoints, normalsToTest[3]);

	Axis e = ProjectOntoAxis(boxBPoints, normalsToTest[0]);
	Axis f = ProjectOntoAxis(boxBPoints, normalsToTest[1]);
	Axis g = ProjectOntoAxis(boxBPoints, normalsToTest[2]);
	Axis h = ProjectOntoAxis(boxBPoints, normalsToTest[3]);

	//Step 4: Check for any overlaps 
	if (a.maxProjection < e.minProjection || e.maxProjection < a.minProjection ||
		b.maxProjection < f.minProjection || f.maxProjection < b.minProjection ||
		c.maxProjection < g.minProjection || g.maxProjection < c.minProjection ||
		d.maxProjection < h.minProjection || h.maxProjection < d.minProjection)
	{
		return false;
	}
	else
	{
		return true;
	}
}

Axis ProjectOntoAxis(const sf::Vector2f boxPoints[], const sf::Vector2f normal)
{
	float minProjection = DotProduct(boxPoints[0], normal);
	float maxProjection = minProjection;

	for (int i = 0; i < 4; i++)
	{
		float currentProjection = DotProduct(boxPoints[i], normal);
		//Is it a max or min projection on the axis?
		if (minProjection > currentProjection)	//For min
			minProjection = currentProjection;
		if (currentProjection > maxProjection)  //For max
			maxProjection = currentProjection;
	}
	Axis temp;
	temp.maxProjection = maxProjection;
	temp.minProjection = minProjection;
	return temp;
}