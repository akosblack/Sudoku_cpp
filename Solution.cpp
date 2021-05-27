//#include "Solution.h"
//#include <iostream>
//#include <unordered_set>
//
//using namespace std;
//
//bool Solution::isValidSudoku(Class_Sudoku * Game)
//{
//	unordered_set<int> has;
//	for (int i = 0; i < 9; i++) {
//		has.clear();
//		// rows
//		for (int j = 0; j < 9; j++) {
//			if (Game->getBoardElement(i,j) != ' ') {
//				if (has.count(Game->getBoardElement(i, j))) {
//					return false;
//				}
//				has.insert(Game->getBoardElement(i, j));
//			}
//		}
//		has.clear();
//		// columns
//		for (int j = 0; j < 9; j++) {
//			if (Game->getBoardElement(i, j) != ' ') {
//				if (has.count(Game->getBoardElement(i, j))) {
//					return false;
//				}
//				has.insert(Game->getBoardElement(i, j));
//			}
//		}
//	}
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			// sub grids
//			has.clear();
//			for (int x = i * 3; x < i * 3 + 3; x++) {
//				for (int y = j * 3; y < j * 3 + 3; y++) {
//					if (Game->getBoardElement(x, y) != ' ') {
//						if (has.count(Game->getBoardElement(x, y))) {
//							return false;
//						}
//						has.insert(Game->getBoardElement(x, y));
//					}
//				}
//			}
//		}
//	}
//	return true;
//}
