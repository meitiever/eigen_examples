// EigenExample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
#include <eigen3/Eigen/Geometry>
#include <eigen3/Eigen/Core>

using namespace Eigen;
using namespace std;

void ex3()
{
	Eigen::Quaternionf q(2., 0., 1., -3.);
	q.normalize();
	Eigen::Quaternionf p;
	Eigen::Vector3f robot_position(1., 2., -1.);
	p.setFromTwoVectors(Vector3f(0., 1., 0.), robot_position);

	Eigen::Quaternionf rotatedP = q * p * q.inverse();
	Eigen::Vector3f rotatedV = rotatedP.vec();
	std::cout << "We can now use it to rotate a vector " << std::endl
		<< robot_position << " to " << std::endl << rotatedV << std::endl;
}

void ex2()
{
	Eigen::Vector3f robot_position(0, 0, 0);
	Eigen::Vector3f robot_position1(1.5f, 10.2f, -5.1f);
	std::cout << "after t, the robot position is: " << robot_position + robot_position1;
	Eigen::Quaterniond q(2, 0, 1, -3);
	std::cout << "the robot position is: " << q.w() << " and vec is: " << q.vec() << endl;
	q.normalize();
	std::cout << "the normalized robot position is: " << q.w() << " and vec is: " << q.vec() << endl;
}

void ex1()
{
	float arrVertices[] = { -1.0 , -1.0 , -1.0 ,
						1.0 , -1.0 , -1.0 ,
						1.0 , 1.0 , -1.0 ,
						-1.0 , 1.0 , -1.0 ,
						-1.0 , -1.0 , 1.0 ,
						1.0 , -1.0 , 1.0 ,
						1.0 , 1.0 , 1.0 ,
						-1.0 , 1.0 , 1.0 };
	MatrixXf mVertices = Map < Matrix <float, 3, 8 > >(arrVertices);
	Eigen::Transform <float, 3, Affine> t = Eigen::Transform <float, 3, Affine>::Identity();	t.scale(0.8f);
	t.rotate(Eigen::AngleAxisf(0.25f * M_PI, Eigen::Vector3f::UnitX()));
	t.translate(Eigen::Vector3f(1.5, 10.2, -5.1));

	std::cout << t * mVertices.colwise().homogeneous() << std::endl;
}

int main()
{
	Eigen::initParallel();
	Eigen::setNbThreads(4);

	ex1();
	ex2();
	ex3();
}