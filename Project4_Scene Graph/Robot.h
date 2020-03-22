#ifndef _ROBOT_H_
#define _ROBOT_H_

//#include <stdlib.h>
//#include <iostream>
//#include <GL/glut.h>
//#include "Matrix4.h"
#include "MatrixTransform.h"
#include "Cube.h"
#include "Sphere.h"

//using namespace std;

class Robot:public MatrixTransform
{
public:
	
	double iScale;
	int iTransX;
	int iTransY;
	int iTransZ;
	int rot;
	
	Vector3 v3TorsoScale;
	Vector3 v3HeadScale;
	Robot(int r, int c);
	Matrix4 mRoot;
	void update(double angle);
	//void draw(Matrix4 trans);

	MatrixTransform* robot;
	MatrixTransform* mtRobot;
	MatrixTransform* mtTorso;
	MatrixTransform* mtHead;
	MatrixTransform* mtHeadTrans;
	MatrixTransform* mtHeadScale;
	MatrixTransform* mtLeftArm;
	MatrixTransform* mtLeftArmTrans;
	MatrixTransform* mtLeftArmRot;
	MatrixTransform* mtLeftArmDown;
	MatrixTransform* mtLeftArmScale;
	MatrixTransform* mtRightArm;
	MatrixTransform* mtRightArmTrans;
	MatrixTransform* mtRightArmRot;
	MatrixTransform* mtRightArmDown;
	MatrixTransform* mtRightArmScale;
	MatrixTransform* mtLeftLeg;
	MatrixTransform* mtLeftLegTrans;
	MatrixTransform* mtLeftLegRot;
	MatrixTransform* mtLeftLegDown;
	MatrixTransform* mtLeftLegScale;
	MatrixTransform* mtRightLeg;
	MatrixTransform* mtRightLegTrans;
	MatrixTransform* mtRightLegRot;
	MatrixTransform* mtRightLegDown;
	MatrixTransform* mtRightLegScale;

	Matrix4 mTorso;
	Matrix4 head;
	Matrix4 headTrans;
	Matrix4 headScale;
	Matrix4 rotate;
	Matrix4 leftArm;
	Matrix4 leftArmTrans;
	Matrix4 leftArmDown;
	Matrix4 leftArmScale;
	Matrix4 rightArm;
	Matrix4 rightArmTrans;
	Matrix4 rightArmDown;
	Matrix4 rightArmScale;
	Matrix4 leftLeg;
	Matrix4 leftLegTrans;
	Matrix4 leftLegDown;
	Matrix4 leftLegScale;
	Matrix4 rightLeg;
	Matrix4 rightLegTrans;
	Matrix4 rightLegDown;
	Matrix4 rightLegScale;
};

#endif