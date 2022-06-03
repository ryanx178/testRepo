// Ryan Lopez 

// problem: I have to update moves every time something on the board moves



#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int SIZE = 64;
// changed up and down to be 8 instead of 1
enum {	LEFT = -1, RIGHT = 1, UP = -8, DOWN = 8, 
		ROW1 = 0, ROW2 = 8, ROW3 = 16, ROW4 = 24, ROW5 = 32, ROW6 = 40, ROW7 = 48, ROW8 = 56,
		COL1 = 0, COL2,		COL3,	   COL4,	  COL5,		 COL6,		COL7,	   COL8};



class Pawn;
class ChessPiece;
class Square;
class ChessBoard;
class King;
class Rook;


class ChessPiece {
protected:
	char color;
	char pieceLetter;

	Square* location;
public:
	// Get the type of a piece no matter what type of piece is on there
	
	char getLetter() { 
		return pieceLetter;
	}
	char getColor() {
		return color;
	}
	//virtual ~ChessPiece() {};

	virtual void move(Square*,int,int) = 0;
	virtual void updateMoves(Square*, int) = 0;
	virtual void printMoves() = 0;

	
	//virtual ~ChessPiece() = 0;
	virtual void move(Square*) = 0;
	virtual vector<Square*> tilesMovable() = 0;
	char getType() {
		return pieceLetter;
	}
	bool getColor() const;
	/*string getLocation() const;*/
	Square* getLocation() const;

	void setLocation(Square*);

	
};


bool ChessPiece::getColor() const {
	return this->color;
}

//string ChessPiece::getLocation() const {
//	return this->location->printLocation();
//}
Square* ChessPiece::getLocation() const {
	return this->location;
}

void ChessPiece::setLocation(Square* s) {
	this->location = s;
}




class Square {
private:
	ChessPiece* piece;


	//ChessPiece* pieceID;
	int location;

public:
	//Square() {
	//	piece = nullptr;
	//}
	//~Square() {
	//	// should delete even if piece is nullptr?
	//	if (piece != nullptr) 
	//		delete piece;
	//		
	//	piece = nullptr;

	//}
	bool is_empty() {
		if (piece == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	// Returns 'N' if square is empty
	char getPieceLetter() {
		if (piece == nullptr) {
			return 'N';
		}
		return piece->getLetter();
	}

	// needs to be set to nullptr if a piece wants to get onto a different square
	/*void setPiece(ChessPiece* c) {
		piece = c;
	}*/
	ChessPiece* getPiece() {
		return piece;
	}






	Square();
	Square(ChessPiece*, int);
	~Square();
	bool isEmpty();
	ChessPiece* getPieceID();
	int getLocation();
	void printLocation();
	void clearSquare();
	void setPiece(ChessPiece*);

	void setLocation(int);


};

void Square::setLocation(int l) {
	location = l;
}

Square::Square() {
	piece = nullptr;

	//pieceID = nullptr;
	location = -1;
}

Square::Square(ChessPiece* piece, int point) {
	piece = piece;
	location = point;
}

Square::~Square() {
	if (piece != nullptr) {
		delete piece;
	}
	
	
	//delete this->pieceID;
}

bool Square::isEmpty() {
	return (piece == nullptr);
}

ChessPiece* Square::getPieceID() {
	return this->piece;
}

int Square::getLocation() {
	return this->location;
}

void Square::printLocation() {
	cout << this->location;
}

void Square::clearSquare() {
	this->piece->setLocation(nullptr);
	piece = nullptr;
}

void Square::setPiece(ChessPiece* c) {
	piece = c;
}


class Pawn : public ChessPiece {
private:

	vector<int> tilesM;
	vector<Square*> tilesMove;

	int prevPosition = -1;
	int forwardOne = UP;
	
	bool hasMoved = false;


	bool outOfBounds(int end) {
		if (end < 0 || end > SIZE - 1) {
			return true;
		}
		return false;
		
	}
	bool inVectorTM(int x) {
		for (int i = 0; i < tilesM.size(); ++i) {
			if (tilesM[i] == x) {
				return true;
			}
		}
		return false;
	}

	bool is_friendly(Square* b, int here) {
		if (b[here].getPiece()->getColor() == color) {
			return true;
		}
		return false;
	}
	bool is_pawn(Square* b, int here) {
		if (b[here].getPiece()->getLetter() == 'P') {
			return true;
		}
		return false;
	}

	

public:
	Pawn(char c, Square* b, int pos) {
		if (c == 'B') forwardOne = DOWN;
		
		//updateMoves(b,pos);
		color = c;
		pieceLetter = 'P';
	}
	~Pawn() {}

	// Assume that Black is top and White is bottom
	//void highlightMoves(Square* b, int positionOfPiece) {}

	void move(Square* b, int initialPositionOfPiece, int finalPositionOfPiece) {
		if (!inVectorTM(finalPositionOfPiece)) {
			cout << "Could not move to location" << endl;
			return;
		}
		// Now the move is definetly available
		prevPosition = initialPositionOfPiece;
		



		
		
		if (!b[finalPositionOfPiece].is_empty()) {
			delete b[finalPositionOfPiece].getPiece();
		}
		
		b[finalPositionOfPiece].setPiece(b[initialPositionOfPiece].getPiece());
		b[initialPositionOfPiece].setPiece(nullptr);
		
	
		
		hasMoved = true;
		//updateMoves(b, finalPositionOfPiece);
	}

	// should be private?
	void updateMoves(Square* b, int pos) {
		tilesM.clear();
		tilesMove.clear();
		// needs to check front left/front and right/front

		// in front of pawn is 8
		// left/front of pawn is 7
		// right/front of pawn is 9


		bool onLeftEdge = pos % 8 == 0;
		bool onRightEdge = (pos - 7) % 8 == 0;
		
		
	


		

		// check up one
		if (!outOfBounds(pos + forwardOne) && b[pos + forwardOne].is_empty()) {
			tilesM.push_back(pos + forwardOne);

			tilesMove.push_back(&b[pos+forwardOne]);
		}




		// check if enPassant left is possible first
		//if (is_enPassant_Possible_Left(b, pos)) {
		//	availableMoves.push_back(pos + forwardOne + LEFT);
		//	passantLeft = true;
		//	//i_enPassantLeft = pos + forwardOne + LEFT;
		//}
		

		// check left up // took out else
		if (!outOfBounds(pos + forwardOne + LEFT) && !b[pos + forwardOne + LEFT].is_empty()) {
			if (!onLeftEdge && /*!is_friendly(b, pos+forwardOne+LEFT)*/b[pos + forwardOne + LEFT].getPiece()->getColor() != color) {
				tilesM.push_back(pos + forwardOne + LEFT);
				tilesMove.push_back(&b[pos + forwardOne + LEFT]);
			}
		}

		// check right up
		if (!outOfBounds(pos + forwardOne + RIGHT) && !b[pos + forwardOne + RIGHT].is_empty()) {
			if (!onRightEdge && !is_friendly(b, pos + forwardOne + RIGHT)/*b[pos + forwardOne + RIGHT].getPiece()->getColor() != color*/) {
				// This piece can go diagonal to the right.
				tilesM.push_back(pos + forwardOne + RIGHT);
				tilesMove.push_back(&b[pos + forwardOne + RIGHT]);
			}
		}
		// check up 2
		if (!outOfBounds(pos + forwardOne + forwardOne)) {
			// Second, check if tile is empty and this pawn hasnt moved AND there is nothing in between pawn and 2 up
			if (b[pos + forwardOne + forwardOne].is_empty() && b[pos+forwardOne].is_empty() && !hasMoved) {
				tilesM.push_back(pos + forwardOne + forwardOne);
				tilesMove.push_back(&b[pos + forwardOne + forwardOne]);
			}
		}

		
		
		// also needs to check this for one turn
		
		
	}

	void printMoves() {
		for (int i = 0; i < tilesM.size(); ++i) {
			cout << tilesM[i] << endl;
		}
	}

	// override
	void move(Square*) {};
	vector<Square*> tilesMovable() {
		return tilesMove;
	};
	

	
};



class Rook : public ChessPiece {
private:
	bool castPossible;
public:
	Rook();
	Rook(char, Square*);
	~Rook();
	void move(Square*);
	vector<Square*> tilesMovable();
	bool castlingPossible();
	void disableCastling();
	void castling();

	Square* getLocationSquareRook() {
		return location;
	}


	virtual void move(Square*, int, int) {};
	virtual void updateMoves(Square*, int) {};
	virtual void printMoves() {};
};

Rook::Rook() {
	this->color = 0;
	this->location = NULL;
	this->pieceLetter = 'R';
	this->castPossible = 1;
}

Rook::Rook(char side, Square* loc) {
	this->color = side;
	this->location = loc;
	this->pieceLetter = 'R';
	this->castPossible = 1;
}

vector<Square*> Rook::tilesMovable() {
	vector<Square*> tiles;
	string availTiles = "";
	int columnRelative;
	int rowRelative;
	int pieceLocation = this->location->getLocation();
	rowRelative = pieceLocation % 8;
	columnRelative = pieceLocation / 8;
	Square* tempLoc = this->location - 1;
	for (int i = rowRelative; i > 0; i--) {
		if (tempLoc->isEmpty() == true) {
			tiles.push_back(tempLoc);
		}
		else if (tempLoc->getPieceID()->getColor() != this->getColor()) {
			tiles.push_back(tempLoc);
			break;
		}
		else if (tempLoc->getPieceID()->getColor() == this->getColor()) {
			break;
		}
		tempLoc--;
	}
	tempLoc = this->location + 1;
	for (int j = 7; j > rowRelative; j--) {
		if (tempLoc->isEmpty() == true) {
			tiles.push_back(tempLoc);
		}
		else if (tempLoc->getPieceID()->getColor() != this->getColor()) {
			tiles.push_back(tempLoc);
			break;
		}
		else if (tempLoc->getPieceID()->getColor() == this->getColor()) {
			break;
		}
		tempLoc++;
	}
	tempLoc = this->location - 8;
	for (int k = columnRelative; k > 0; k--) {
		if (tempLoc->isEmpty() == true) {
			tiles.push_back(tempLoc);
		}
		else if (tempLoc->getPieceID()->getColor() != this->getColor()) {
			tiles.push_back(tempLoc);
			break;
		}
		else if (tempLoc->getPieceID()->getColor() == this->getColor()) {
			break;
		}
		tempLoc -= 8;
	}
	tempLoc = this->location + 8;
	for (int h = 7; h > columnRelative; h--) {
		if (tempLoc->isEmpty() == true) {
			tiles.push_back(tempLoc);
		}
		else if (tempLoc->getPieceID()->getColor() != this->getColor()) {
			tiles.push_back(tempLoc);
			break;
		}
		else if (tempLoc->getPieceID()->getColor() == this->getColor()) {
			break;
		}
		tempLoc += 8;
	}
	cout << "Available tiles:";
	for (int n = 0; n < tiles.size(); n++) {
		/*cout << " " << tiles.at(n)->printLocation();*/
		cout << " ";
		tiles.at(n)->printLocation();
	}
	cout << '\n';
	return tiles;
}

void Rook::move(Square* targetTile) {
	vector<Square*> availTiles = this->tilesMovable();
	for (int i = 0; i < availTiles.size(); i++) {
		if (targetTile == availTiles.at(i)) {
			targetTile->clearSquare();
			location->clearSquare();
			location = targetTile;
			location->setPiece(this);
			this->castPossible = false;
			return;
		}
	}
	cout << "Can't move to this square." << endl;
}

bool Rook::castlingPossible() {
	if (!castPossible) {
		return false;
	}
	if (this->location->getLocation() % 8 == 0) {
		if ((location + 1)->isEmpty() && (location + 2)->isEmpty() && (location + 3)->isEmpty()) {
			return true;
		}
	}
	if (this->location->getLocation() % 8 == 7) {
		if ((location - 1)->isEmpty() && (location - 2)->isEmpty()) {
			return true;
		}
	}
	return false;
}

void Rook::disableCastling() {
	castPossible = false;
}

void Rook::castling() {
	if (this->castlingPossible()) {
		if (this->location->getLocation() % 8 == 0) {
			this->move(this->location + 3);
		}
		if (this->location->getLocation() % 8 == 7) {
			this->move(this->location - 2);
		}
	}
	cout << "Castling is not possible" << endl;
}





class King : public ChessPiece {
private:
	bool castPossible;
public:
	King();
	King(char, Square*);
	~King();
	void move(Square*);
	vector<Square*> tilesMovable();
	bool castlingPossible(Rook*);
	void disableCastling();
	void castling(Rook*);


	virtual void move(Square*, int, int) {};
	virtual void updateMoves(Square*, int) {};
	virtual void printMoves() {};
};

King::King() {
	this->color = 0;
	this->location = NULL;
	this->pieceLetter = 'K';
	this->castPossible = 1;
}

King::King(char side, Square* loc) {
	this->color = side;
	this->location = loc;
	this->pieceLetter = 'K';
	this->castPossible = 1;
}

vector<Square*> King::tilesMovable() {
	vector<Square*> availTiles;
	bool edgeRight = 0;
	bool edgeLeft = 0;
	bool edgeTop = 0;
	bool edgeBottom = 0;
	if (this->location->getLocation() % 8 == 1) {
		edgeRight = 1;
	}
	if (this->location->getLocation() % 8 == 0) {
		edgeLeft = 1;
	}
	if (this->location->getLocation() <= 7) {
		edgeTop = 1;
	}
	if (this->location->getLocation() >= 56) {
		edgeBottom = 1;
	}
	Square* tileChecked = this->location;
	if (edgeTop == 0) {
		tileChecked = this->location - 9;
		for (int i = 0; i < 3; i++) {
			if (tileChecked->isEmpty() == true || tileChecked->getPieceID()->getColor() != this->getColor()) {
				availTiles.push_back(tileChecked);
			}
			else {
				continue;
			}
			tileChecked++;
		}
	}
	if (edgeLeft == 0) {
		tileChecked = this->location - 1;
		if (tileChecked->isEmpty() == true || tileChecked->getPieceID()->getColor() != this->getColor()) {
			availTiles.push_back(tileChecked);
		}
	}
	if (edgeRight == 0) {
		tileChecked = this->location + 1;
		if (tileChecked->isEmpty() == true || tileChecked->getPieceID()->getColor() != this->getColor()) {
			availTiles.push_back(tileChecked);
		}
	}
	if (edgeBottom == 0) {
		tileChecked = this->location + 7;
		for (int j = 0; j < 3; j++) {
			if (tileChecked->isEmpty() == true || tileChecked->getPieceID()->getColor() != this->getColor()) {
				availTiles.push_back(tileChecked);
			}
			else {
				continue;
			}
			tileChecked++;
		}
	}
	cout << "Available tiles:";
	for (int k = 0; k < availTiles.size(); k++) {
		//cout << " " << availTiles.at(k)->printLocation();
		cout << " ";
		availTiles.at(k)->printLocation();
	}
	cout << '\n';
	return availTiles;
}

void King::move(Square* targetTile) {
	vector<Square*> availTiles = this->tilesMovable();
	for (int i = 0; i < availTiles.size(); i++) {
		if (targetTile == availTiles.at(i)) {
			targetTile->clearSquare();
				location->clearSquare();
				location = targetTile;
				location->setPiece(this);
				this->castPossible = false;
				return;
		}
	}
	cout << "Can't move to this square." << endl;
}

bool King::castlingPossible(Rook* castle) {
	if (this->castPossible) {
		return castle->castlingPossible();
	}
	return false;
}

void King::disableCastling() {
	this->castPossible = false;
}

void King::castling(Rook* castle) {
	if (castle->castlingPossible()) {
		if (castle->getLocationSquareRook()->getLocation() % 8 == 0) {
			Square* defense = this->location - 2;
			this->location->clearSquare();
			location = defense;
			location->setPiece(this);
			this->castPossible = false;
		}
		if (castle->getLocationSquareRook()->getLocation() % 8 == 7) {
			Square* defense = this->location + 2;
			this->location->clearSquare();
			location = defense;
			location->setPiece(this);
			this->castPossible = false;
		}
	}
	cout << "Castling not possible" << endl;
}




class Chessboard {
private:
	// 1d chessboard array
	Square* Board;

	void updateAll() {
		for (int i = 0; i < SIZE; ++i) {
			if (!Board[i].is_empty()) {
				Board[i].getPiece()->updateMoves(Board,i);
			}
		}
	}
public:
	
	//will be used to initialize the chessboard
	Chessboard() {
		
		//Assume that Black is top and White it bottom
		//dynamically allocate each square 
		//dynamically allocate pieces onto the board


		Board = new Square[SIZE];


		//initialize all ROW2 with black pawn
		for (int i = COL1; i <= COL8; ++i) {
			Board[ROW4 + i].setPiece(new Pawn('B',Board,ROW4+i));
		}
		//initialize all ROW6 with white pawn
		for (int i = COL1; i <= COL8; ++i) {
			Board[ROW7 + i].setPiece(new Pawn('W', Board, ROW7 + i));
		}


		
		Board[ROW2 + 3].setPiece(new King('B', &Board[ROW2 + 3]));
		Board[ROW1 + 3].setPiece(new Rook('B', &Board[ROW1 + 3]));
		


	}
	~Chessboard() {
		delete[] Board;
	}

	

	//could it be a bool function?
	void move(int initialPositionOfPiece, int finalPositionOfPiece) {
		updateAll();
		//8a is 00
		//1h is 77
		if (!Board[initialPositionOfPiece].is_empty()) {
			Board[initialPositionOfPiece].getPiece()->move(Board, initialPositionOfPiece, finalPositionOfPiece);
		}
		else {
			cout << "Square is empty - Chessboard::move" << endl;
		}
		
		
	}

	//highlights movable spots
	void pickSquare(const int positionOfPiece) {
		

		//highlight the moves of that piece
		//if the player wants to move it then it should call move function of piece - if NOT then it should unhighlight the moves
	}


	void printChessBoard() {

		for (int i = 0; i < SIZE; ++i) {
			if (i % 8 == 0 && i != 0) {
				cout << endl;
			}
			cout << Board[i].getPieceLetter();
			
		}

	}
	
	void printMovesOnSquare(int pos) {
		
		if (!Board[pos].is_empty()) {
			Board[pos].getPiece()->updateMoves(Board, pos);
			Board[pos].getPiece()->printMoves();
		}
		else {
			cout << "Square is empty - Chessboard::printMovesOnSquare" << endl;
		}
		
	}
	

};














int main() {

	Chessboard b1;
	

	int initialPos;
	int finalPos;
	while (true) {
		b1.printChessBoard();
		cout << endl;
		cin >> initialPos;
		b1.printMovesOnSquare(initialPos);
		cin >> finalPos;
		b1.move(initialPos, finalPos);


	}
	

}