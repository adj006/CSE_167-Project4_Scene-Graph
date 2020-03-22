#include "Robot.h"



Robot::Robot(int r, int c)
{
	//----------------------------------------------------------------------------------------------------------------------------------
	/*Local Variable Declarations*/
	
	//iScale = 0.0;
	//iTransX = 0;
	//iTransY = 0;
	//iTransZ = 0;
	//rot = 0;
	//cout << "Constructor!!!" << endl;
	
	//----------------------------------------------------------------------------------------------------------------------------------

	int row = -(r / 2);
	int col = -(c / 2);
	int nRow = r / 2;
	int nCol = c / 2;

	if (r == 1 && c == 1)
	{
		row = 0;
		col = 0;
		nRow = 1;
		nCol = 1;
	}

	for (int i = row; i < nRow; i++)
	{
		for (int j = col; j < nCol; j++)
		{
			//----------------------------------------------------------------------------------------------------------------------------------
			/*Root*/

			mRoot.identity();
			mtRobot = new MatrixTransform(mRoot);
			
			this->addChild(mtRobot);

			mRoot.makeTranslate(i * 10, 1, j * 10);
			robot = new MatrixTransform(mRoot);
			mtRobot->addChild(robot);

			//----------------------------------------------------------------------------------------------------------------------------------

			//----------------------------------------------------------------------------------------------------------------------------------
			/*Torso*/

			v3TorsoScale.v3[0] = 4;
			v3TorsoScale.v3[1] = 5;
			v3TorsoScale.v3[2] = 4;

			mTorso.identity();
			//mTorso.makeScale(4 + iScale, 5 + iScale, 4 + iScale);
			mTorso.makeScale(v3TorsoScale.v3[0] + iScale, v3TorsoScale.v3[1] + iScale, v3TorsoScale.v3[2] + iScale);

			mtTorso = new MatrixTransform(mTorso);
			robot->addChild(mtTorso);
			mtTorso->addChild(new Cube(1));

			//-----------------------------------------------------------------------------------------------------------------------------------

			//-----------------------------------------------------------------------------------------------------------------------------------
			/*Head*/

			v3HeadScale.v3[0] = 2.5;
			v3HeadScale.v3[1] = 2.0;
			v3HeadScale.v3[2] = 2.5;

			head.identity();

			mtHead = new MatrixTransform(head);
			robot->addChild(mtHead);

			headTrans.identity();
			//headTrans.makeTranslate(0 + iTransX, 4 + iTransY, 0 + iTransZ);
			headTrans.makeTranslate(0 + iTransX, 2 + iTransY, 0 + iTransZ);

			headTrans = headTrans * head;

			headTrans.print("Head Trans Matrix");

			mtHeadTrans = new MatrixTransform(headTrans);
			mtHead->addChild(mtHeadTrans);

			headScale.identity();
			headScale.makeScale(v3HeadScale.v3[0], v3HeadScale.v3[1], v3HeadScale.v3[2]);

			headScale = headTrans * headScale;

			headScale.print("Head Matrix\n");

			mtHeadScale = new MatrixTransform(headScale);
			mtHeadTrans->addChild(mtHeadScale);

			mtHeadScale->addChild(new Sphere(1 + iScale, 20, 20));
			//mtHead->addChild(new Sphere(1.5, 20, 20));
			//mtHeadScale->addChild(new Cube(1));

			//-----------------------------------------------------------------------------------------------------------------------------------

			//-----------------------------------------------------------------------------------------------------------------------------------
			/*Limb Rotations*/

			rotate.identity();
			//rotate.makeRotateX(20);
			//rotate.makeRotateX(rot);

			//-----------------------------------------------------------------------------------------------------------------------------------


			//-----------------------------------------------------------------------------------------------------------------------------------
			/*Left Arm*/

			leftArm.identity();

			mtLeftArm = new MatrixTransform(leftArm);
			robot->addChild(mtLeftArm);

			leftArmTrans.identity();
			//leftArmTrans.makeTranslate(2.75 + iTransX, .8 + iTransY, 0 + iTransZ);
			leftArmTrans.makeTranslate(.9 + iTransX, .8 + iTransY, 0 + iTransZ);

			leftArm = leftArmTrans * leftArm;

			mtLeftArmTrans = new MatrixTransform(leftArm);
			mtLeftArm->addChild(mtLeftArmTrans);

			//leftArm = rotate * leftArm;

			mtLeftArmRot = new MatrixTransform(leftArm);
			mtLeftArmTrans->addChild(mtLeftArmRot);

			leftArmDown.identity();
			//leftArmDown.makeTranslate(0, -((3 + iScale) / 2), 0);
			leftArmDown.makeTranslate(0, -((3 + iScale) / 2), 0);

			leftArm = leftArmDown * leftArm;

			mtLeftArmDown = new MatrixTransform(leftArm);
			mtLeftArmRot->addChild(mtLeftArmDown);

			leftArmScale.identity();
			//leftArmScale.makeScale(1 + iScale, 3 + iScale, 1 + iScale);
			leftArmScale.makeScale(1 + iScale, 3.5 + iScale, 1 + iScale);
			leftArm = leftArm * leftArmScale;
			leftArm.print("Left Arm");

			mtLeftArmScale = new MatrixTransform(leftArm);
			mtLeftArmDown->addChild(mtLeftArmScale);

			mtLeftArmScale->addChild(new Cube(1));

			//-----------------------------------------------------------------------------------------------------------------------------------

			//-----------------------------------------------------------------------------------------------------------------------------------
			/*Right Arm*/

			rightArm.identity();

			mtRightArm = new MatrixTransform(rightArm);
			robot->addChild(mtRightArm);

			rightArmTrans.identity();
			//rightArmTrans.makeTranslate(-2.75 + iTransX, .8 + iTransY, 0 + iTransZ);
			rightArmTrans.makeTranslate(-.9 + iTransX, .8 + iTransY, 0 + iTransZ);

			rightArm = rightArmTrans * rightArm;

			mtRightArmTrans = new MatrixTransform(rightArm);
			mtRightArm->addChild(mtRightArmTrans);

			//rightArm = rotate * rightArm;

			mtRightArmRot = new MatrixTransform(rightArm);
			mtRightArmTrans->addChild(mtRightArmRot);

			rightArmDown.identity();
			rightArmDown.makeTranslate(0, -((3 + iScale) / 2), 0);

			rightArm = rightArmDown * rightArm;

			mtRightArmDown = new MatrixTransform(rightArm);
			mtRightArmRot->addChild(mtRightArmDown);

			rightArmScale.identity();
			//rightArm.makeScale(1 + iScale, 3 + iScale, 1 + iScale);
			rightArmScale.makeScale(1 + iScale, 3.5 + iScale, 1 + iScale);

			rightArm = rightArm * rightArmScale;
			rightArm.print("Right Arm");

			mtRightArmScale = new MatrixTransform(rightArm);
			mtRightArmDown->addChild(mtRightArmScale);

			mtRightArmScale->addChild(new Cube(1));

			//-----------------------------------------------------------------------------------------------------------------------------------

			//-----------------------------------------------------------------------------------------------------------------------------------
			/*Left Leg*/

			leftLeg.identity();

			mtLeftLeg = new MatrixTransform(leftLeg);
			robot->addChild(mtLeftLeg);

			leftLegTrans.identity();
			leftLegTrans.makeTranslate(.4 + iTransX, -.5 + iTransY, 0 + iTransZ);

			leftLeg = leftLegTrans * leftLeg;

			mtLeftLegTrans = new MatrixTransform(leftLeg);
			mtLeftLeg->addChild(mtLeftLegTrans);

			mtLeftLegRot = new MatrixTransform(leftLeg);
			mtLeftLegTrans->addChild(mtLeftLegRot);

			leftLegDown.identity();
			leftLegDown.makeTranslate(0, -((3 + iScale) / 2), 0);

			leftLeg = leftLegDown * leftLeg;

			mtLeftLegDown = new MatrixTransform(leftLeg);
			mtLeftLegRot->addChild(mtLeftLegDown);

			leftLegScale.identity();
			leftLegScale.makeScale(1.2 + iScale, 3.5 + iScale, 1.2 + iScale);

			leftLeg = leftLeg * leftLegScale;
			leftLeg.print("Left Leg");

			mtLeftLegScale = new MatrixTransform(leftLeg);
			mtLeftLegDown->addChild(mtLeftLegScale);

			mtLeftLegScale->addChild(new Cube(1));

			//-----------------------------------------------------------------------------------------------------------------------------------

			//-----------------------------------------------------------------------------------------------------------------------------------
			/*Right Leg*/

			rightLeg.identity();

			mtRightLeg = new MatrixTransform(rightLeg);
			robot->addChild(mtRightLeg);

			rightLegTrans.identity();
			rightLegTrans.makeTranslate(-.4 + iTransX, -.5 + iTransY, 0 + iTransZ);

			rightLeg = rightLegTrans * rightLeg;

			mtRightLegTrans = new MatrixTransform(rightLeg);
			mtRightLeg->addChild(mtRightLegTrans);

			mtRightLegRot = new MatrixTransform(rightLeg);
			mtRightLegTrans->addChild(mtRightLegRot);

			rightLegDown.identity();
			rightLegDown.makeTranslate(0, -((3 + iScale) / 2), 0);

			rightLeg = rightLegDown * rightLeg;

			mtRightLegDown = new MatrixTransform(rightLeg);
			mtRightLegRot->addChild(mtRightLegDown);

			rightLegScale.identity();
			rightLegScale.makeScale(1.2 + iScale, 3.5 + iScale, 1.2 + iScale);

			rightLeg = rightLeg * rightLegScale;
			rightLeg.print("right leg");

			mtRightLegScale = new MatrixTransform(rightLeg);
			mtRightLegDown->addChild(mtRightLegScale);

			mtRightLegScale->addChild(new Cube(1));

			//-----------------------------------------------------------------------------------------------------------------------------------

		}
	}


}

void Robot::update(double angle)
{

	//-----------------------------------------------------------------------------------------------------------------------------------
	/*Left Arm*/

	mtLeftArmRot->m.makeRotateX(angle);

	//-----------------------------------------------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------------------------------------------------
	/*Right Arm*/

	mtRightArmRot->m.makeRotateX(-angle);

	//-----------------------------------------------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------------------------------------------------
	/*Left Leg*/

	mtLeftLegRot->m.makeRotateX(-angle);

	//-----------------------------------------------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------------------------------------------------
	/*Right Leg*/

	mtRightLegRot->m.makeRotateX(angle);


	//-----------------------------------------------------------------------------------------------------------------------------------
}