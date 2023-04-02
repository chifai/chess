#include "pch.h"
#include "ChessGame.h"
#include "ChessGameTest.h"

CChessGameTest::CChessGameTest()
{

}

CChessGameTest::~CChessGameTest()
{

}

TEST_F(CChessGameTest, Test1)
{
	printf("ChessGameTest\n");
	CChessGame Game;
	EXPECT_TRUE(Game.moveOnePiece({ 4, 1 }, { 4, 3 }));
	EXPECT_TRUE(Game.moveOnePiece({ 4, 6 }, { 4, 5 }));
}