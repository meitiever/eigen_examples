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

void basic_operations()
{
	Eigen::MatrixXd mat(2, 2);
	mat << 0, 1, 2, 3;
	mat.resize(3, 3);
	cout << mat << endl;
	mat << 0, 1, 2, 3;
	mat.conservativeResize(3, 3);
	cout << mat << endl;
}

void advanced_initialization()
{
	Eigen::MatrixXd mat(2, 2);
	mat(0, 0) = 3;
	mat(0, 1) = 2.5;
	mat(1, 0) = -1;
	mat(1, 1) = mat(0,0) + mat(0,1);

	Eigen::MatrixXd mat1(2, 2);
	mat1 << 1, 2, 3, 4;

	Eigen::VectorXd vec(5);
	vec << 1, 2, 3, 4, 5;

	Eigen::MatrixXd mat2 = Eigen::MatrixXd::Zero(1, 1);
	Eigen::MatrixXd mat3 = Eigen::MatrixXd::Random(3, 3);
	Eigen::MatrixXd mat4 = Eigen::MatrixXd::Zero(3, 3);
	mat4 = (mat4 + Eigen::MatrixXd::Constant(3, 3, 1.2)) * 50;
	Eigen::MatrixXd mat5 = Eigen::MatrixXd::Random(2, 3);
	mat5 = (MatrixXd(2, 2) << 0, 1, 2, 3).finished() * mat5;
	cout << mat5 << endl;
}

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

	Eigen::Transform <float, 3, Affine> t = Eigen::Transform <float, 3, Affine>::Identity();
	t.scale(0.8f);
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
	advanced_initialization();
}