////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Author: Shashi Dongur
// Data: 11/15/2015
// Purpose: Class, BlocksLevel will be used to create the structre of each level
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
// Procedure:
// 1) BlocksLevel will be used to produce procedural levels for this game.
// 2) Each level is divided into 16 Blocks. 4X4
// 3) Each Block will have one of 6 different Block Types characterised by what direction the
//	  block is open and closed.
//		-> Block Type X - Open[top,right,down,left] 1 for open. 0 for closed.
//		-> Block Type A - Open[1,0,1,0]
//		-> Block Type B - Open[1,0,0,1]
//		-> Block Type C - Open[0,0,1,1]
//		-> Block Type D - Open[1,1,0,1]
//		-> Block Type E - Open[1,1,1,0]
//		-> Block Type F - Open[0,1,1,1]
// 4) The starting block for the game is always at bottom left [block 0]
// 5) The final block is randomly selected from other blocks with atleast distance of 2 blocks from the starting block.
// 6) Block 0 is randomly given a block type.
// 7) Depending on what block type 'Block 0' is assigned, next block on the solution path is created by randomly selecting.
//	  from the pool of possible (current block opens to) next block on the path.
// 8) Process is repeated for each block till the final block is reached.
// 9) Once the final block is reached, the reast of the blocks not touched by the solution path are randomly assigned a block type.
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
class ProceduralProgramming
{

public:
	
	ProceduralProgramming();
	void SolutionPath();
	void AssignBoxInPath(blockBox &prevBox, blockBox &currentBox);
	void AssignNextBox(blockBox &current, blockBox &next);
	~ProceduralProgramming();

	int** levelDesign = new int*[122];


};

