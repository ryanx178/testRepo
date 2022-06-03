//class Pawn;
//class ChessPiece;
//class Square;
//class ChessBoard;
//
//#include <iostream>
//#include <string>
//#include <vector>
//using namespace std;
//
//const int SIZE = 64;
//// changed up and down to be 8 instead of 1
//enum {
//	LEFT = -1, RIGHT = 1, UP = -8, DOWN = 8,
//	ROW1 = 0, ROW2 = 8, ROW3 = 16, ROW4 = 24, ROW5 = 32, ROW6 = 40, ROW7 = 48, ROW8 = 56,
//	COL1 = 0, COL2, COL3, COL4, COL5, COL6, COL7, COL8
//};
//
//
//class ChessPiece {
//protected:
//	char color;
//
//	char pieceLetter;
//
//
//	//Square* location;
//public:
//	// Get the type of a piece no matter what type of piece is on there
//
//	char getLetter() {
//		return pieceLetter;
//	}
//	char getColor() {
//		return color;
//	}
//	virtual ~ChessPiece() {};
//
//	virtual void move(Square*, int, int) = 0;
//	virtual void updateMoves(Square*, int) = 0;
//	virtual void printMoves() = 0;
//
//	/*string getLocation() const;
//
//	void setLocation(Square*);*/
//
//
//
//};
//class Square {
//private:
//	ChessPiece* piece;
//
//
//	/*ChessPiece* pieceID;
//	int location;*/
//
//public:
//	Square() {
//		piece = nullptr;
//	}
//	~Square() {
//		// should delete even if piece is nullptr?
//		if (piece != nullptr)
//			delete piece;
//
//		piece = nullptr;
//
//	}
//	bool is_empty() {
//		if (piece == nullptr) {
//			return true;
//		}
//		else {
//			return false;
//		}
//	}
//	// Returns 'N' if square is empty
//	char getPieceLetter() {
//		if (piece == nullptr) {
//			return 'N';
//		}
//		return piece->getLetter();
//	}
//
//	// needs to be set to nullptr if a piece wants to get onto a different square
//	void setPiece(ChessPiece* c) {
//		piece = c;
//	}
//	ChessPiece* getPiece() {
//		return piece;
//	}
//
//
//
//
//	/*Square();
//	Square(ChessPiece*, int);
//	~Square();
//	bool isEmpty();
//	ChessPiece* getPieceID();
//	int getLocation();
//	void printLocation();
//	void clearSquare();
//	void setPiece(ChessPiece*);*/
//
//
//	/*void setLocation(int);*/
//
//
//};
//class Pawn : public ChessPiece {
//private:
//
//	vector<int> tilesMovable;
//
//	int prevPosition = -1;
//	int forwardOne = UP;
//
//	bool hasMoved = false;
//
//
//	bool outOfBounds(int end) {
//		if (end < 0 || end > SIZE - 1) {
//			return true;
//		}
//		return false;
//
//	}
//	bool inVectorTM(int x) {
//		for (int i = 0; i < tilesMovable.size(); ++i) {
//			if (tilesMovable[i] == x) {
//				return true;
//			}
//		}
//		return false;
//	}
//
//	bool is_friendly(Square* b, int here) {
//		if (b[here].getPiece()->getColor() == color) {
//			return true;
//		}
//		return false;
//	}
//	bool is_pawn(Square* b, int here) {
//		if (b[here].getPiece()->getLetter() == 'P') {
//			return true;
//		}
//		return false;
//	}
//
//
//
//public:
//	Pawn(char c, Square* b, int pos) {
//		if (c == 'B') forwardOne = DOWN;
//
//		//updateMoves(b,pos);
//		color = c;
//		pieceLetter = 'P';
//	}
//	~Pawn() {}
//
//	// Assume that Black is top and White is bottom
//	void highlightMoves(Square* b, int positionOfPiece) {}
//
//	void move(Square* b, int initialPositionOfPiece, int finalPositionOfPiece) {
//		if (!inVectorTM(finalPositionOfPiece)) {
//			cout << "Could not move to location" << endl;
//			return;
//		}
//		// Now the move is definetly available
//		prevPosition = initialPositionOfPiece;
//
//
//
//
//
//
//		if (!b[finalPositionOfPiece].is_empty()) {
//			delete b[finalPositionOfPiece].getPiece();
//		}
//
//		b[finalPositionOfPiece].setPiece(b[initialPositionOfPiece].getPiece());
//		b[initialPositionOfPiece].setPiece(nullptr);
//
//
//
//		hasMoved = true;
//		//updateMoves(b, finalPositionOfPiece);
//	}
//
//	// should be private?
//	void updateMoves(Square* b, int pos) {
//		tilesMovable.clear();
//		// needs to check front left/front and right/front
//
//		// in front of pawn is 8
//		// left/front of pawn is 7
//		// right/front of pawn is 9
//
//
//		bool onLeftEdge = pos % 8 == 0;
//		bool onRightEdge = (pos - 7) % 8 == 0;
//
//
//
//
//
//
//
//		// check up one
//		if (!outOfBounds(pos + forwardOne) && b[pos + forwardOne].is_empty()) {
//			tilesMovable.push_back(pos + forwardOne);
//		}
//
//
//
//
//		// check if enPassant left is possible first
//		//if (is_enPassant_Possible_Left(b, pos)) {
//		//	availableMoves.push_back(pos + forwardOne + LEFT);
//		//	passantLeft = true;
//		//	//i_enPassantLeft = pos + forwardOne + LEFT;
//		//}
//
//
//		// check left up // took out else
//		if (!outOfBounds(pos + forwardOne + LEFT) && !b[pos + forwardOne + LEFT].is_empty()) {
//			if (!onLeftEdge && /*!is_friendly(b, pos+forwardOne+LEFT)*/b[pos + forwardOne + LEFT].getPiece()->getColor() != color) {
//				tilesMovable.push_back(pos + forwardOne + LEFT);
//			}
//		}
//
//		// check right up
//		if (!outOfBounds(pos + forwardOne + RIGHT) && !b[pos + forwardOne + RIGHT].is_empty()) {
//			if (!onRightEdge && !is_friendly(b, pos + forwardOne + RIGHT)/*b[pos + forwardOne + RIGHT].getPiece()->getColor() != color*/) {
//				// This piece can go diagonal to the right.
//				tilesMovable.push_back(pos + forwardOne + RIGHT);
//			}
//		}
//		// check up 2
//		if (!outOfBounds(pos + forwardOne + forwardOne)) {
//			// Second, check if tile is empty and this pawn hasnt moved AND there is nothing in between pawn and 2 up
//			if (b[pos + forwardOne + forwardOne].is_empty() && b[pos + forwardOne].is_empty() && !hasMoved) {
//				tilesMovable.push_back(pos + forwardOne + forwardOne);
//			}
//		}
//
//
//
//		// also needs to check this for one turn
//
//
//	}
//
//	void printMoves() {
//		for (int i = 0; i < tilesMovable.size(); ++i) {
//			cout << tilesMovable[i] << endl;
//		}
//	}
//
//
//
//};
//class Chessboard {
//private:
//	// 1d chessboard array
//	Square* Board;
//
//	void updateAll() {
//		for (int i = 0; i < SIZE; ++i) {
//			if (!Board[i].is_empty()) {
//				Board[i].getPiece()->updateMoves(Board, i);
//			}
//		}
//	}
//public:
//
//	//will be used to initialize the chessboard
//	Chessboard() {
//
//		//Assume that Black is top and White it bottom
//		//dynamically allocate each square 
//		//dynamically allocate pieces onto the board
//
//
//		Board = new Square[SIZE];
//
//
//		//initialize all ROW2 with black pawn
//		for (int i = COL1; i <= COL8; ++i) {
//			Board[ROW4 + i].setPiece(new Pawn('B', Board, ROW2 + i));
//		}
//		//initialize all ROW6 with white pawn
//		for (int i = COL1; i <= COL8; ++i) {
//			Board[ROW7 + i].setPiece(new Pawn('W', Board, ROW7 + i));
//		}
//
//
//	}
//	~Chessboard() {
//		delete[] Board;
//	}
//
//
//
//	//could it be a bool function?
//	void move(int initialPositionOfPiece, int finalPositionOfPiece) {
//		updateAll();
//		//8a is 00
//		//1h is 77
//		if (!Board[initialPositionOfPiece].is_empty()) {
//			Board[initialPositionOfPiece].getPiece()->move(Board, initialPositionOfPiece, finalPositionOfPiece);
//		}
//		else {
//			cout << "Square is empty - Chessboard::move" << endl;
//		}
//
//
//	}
//
//	//highlights movable spots
//	void pickSquare(const int positionOfPiece) {
//
//
//		//highlight the moves of that piece
//		//if the player wants to move it then it should call move function of piece - if NOT then it should unhighlight the moves
//	}
//
//
//	void printChessBoard() {
//
//		for (int i = 0; i < SIZE; ++i) {
//			if (i % 8 == 0 && i != 0) {
//				cout << endl;
//			}
//			cout << Board[i].getPieceLetter();
//
//		}
//
//	}
//
//	void printMovesOnSquare(int pos) {
//
//		if (!Board[pos].is_empty()) {
//			Board[pos].getPiece()->updateMoves(Board, pos);
//			Board[pos].getPiece()->printMoves();
//		}
//		else {
//			cout << "Square is empty - Chessboard::printMovesOnSquare" << endl;
//		}
//
//	}
//
//
//};