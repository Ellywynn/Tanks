#ifndef SAT_H
#define SAT_H

#include <SFML/Graphics.hpp>

struct Axis
{
	float minProjection;
	float maxProjection;
};

bool CheckSATDetection(const sf::RectangleShape& boxA, const sf::RectangleShape& boxB);
Axis ProjectOntoAxis(const sf::Vector2f boxPoints[], const sf::Vector2f normal);

float DotProduct(const sf::Vector2f& vec1, const sf::Vector2f& vec2);
float GetMagnitude(const sf::Vector2f& vector);
void GetNormals(const sf::RectangleShape& box, sf::Vector2f normals[]);
void Normalize(sf::Vector2f& vec);
sf::Vector2f GetDirection(const sf::Vector2f& from, const sf::Vector2f& to);

#endif