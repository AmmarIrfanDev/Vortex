#include <torch/torch.h>

#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

enum Piece { EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };
enum Color { NONE, YOU, ENEMY };

struct Square {
    Piece piece;
    Color color;
};

class Chess {
public:
    Chess() {
        resetBoard();
        whitePoints = 0;
        blackPoints = 0;
        whiteTurn = true;
    }

    int getWhitePoints()
    {
        return whitePoints;
    }

    int getBlackPoints()
    {
        return blackPoints;
    }

    // Reset the board to the starting position
    void resetBoard() {
        board.resize(8, std::vector<Square>(8, { EMPTY, NONE }));

        setupRow(0, YOU);
        setupPawns(1, YOU);

        setupRow(7, ENEMY);
        setupPawns(6, ENEMY);
    }

    // Function for white's turn
    bool whiteMove(int startX, int startY, int endX, int endY) {
        if (!whiteTurn) {
            std::cout << "It's not white's turn!" << std::endl;
            return false;
        }
        if (movePiece(startX - 1, startY - 1, endX - 1, endY - 1, YOU)) {  // Adjusting coordinates
            whiteTurn = false;
            return true;
        }
        return false;
    }

    // Function for black's turn
    bool blackMove(int startX, int startY, int endX, int endY) {
        if (whiteTurn) {
            std::cout << "It's not black's turn!" << std::endl;
            return false;
        }
        if (movePiece(startX - 1, startY - 1, endX - 1, endY - 1, ENEMY)) {  // Adjusting coordinates
            whiteTurn = true; 
            return true;
        }
        return false;
    }

    // Function to print the current board state
    friend void printBoard(Chess* game, bool turn);
    
    std::vector<std::vector<Square>> flipBoard() {
        std::vector<std::vector<Square>> flippedBoard(8, std::vector<Square>(8));

        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                // Flip both axes
                flippedBoard[row][col] = board[7 - row][7 - col];

                // Swap the colors of the pieces
                if (flippedBoard[row][col].piece != EMPTY) {
                    flippedBoard[row][col].color = (flippedBoard[row][col].color == YOU) ? ENEMY : YOU;
                }
            }
        }

        return flippedBoard;
    }

    std::vector<std::vector<Square>> Board()
    {
        return board;
    }


private:
    std::vector<std::vector<Square>> board; // 8x8 chess board
    int whitePoints, blackPoints;
    bool whiteTurn;

    void setupRow(int row, Color color) {
        board[row][0] = { ROOK, color };
        board[row][1] = { KNIGHT, color };
        board[row][2] = { BISHOP, color };
        board[row][3] = { QUEEN, color };
        board[row][4] = { KING, color };
        board[row][5] = { BISHOP, color };
        board[row][6] = { KNIGHT, color };
        board[row][7] = { ROOK, color };
    }

    void setupPawns(int row, Color color) {
        for (int i = 0; i < 8; ++i) {
            board[row][i] = { PAWN, color };
        }
    }

    // Function to move a piece and handle capturing
    bool movePiece(int startX, int startY, int endX, int endY, Color playerColor) {
        if (!isValidMove(startX, startY, endX, endY, playerColor)) {
            std::cout << "Invalid move!" << std::endl;
            return false;
        }

        if (board[endX][endY].piece != EMPTY) {
            addPointsForCapture(board[endX][endY].piece, playerColor);
        }

        board[endX][endY] = board[startX][startY];
        board[startX][startY] = { EMPTY, NONE };
        return true;
    }

    void addPointsForCapture(Piece capturedPiece, Color playerColor) {
        int points = 0;
        switch (capturedPiece) {
        case PAWN:   points = 1; break;
        case KNIGHT: points = 3; break;
        case BISHOP: points = 3; break;
        case ROOK:   points = 5; break;
        case QUEEN:  points = 9; break;
        default: break;
        }

        if (playerColor == YOU) {
            whitePoints += points;
        }
        else {
            blackPoints += points;
        }
    }

    // valid moved:

    bool isValidPawnMove(int startX, int startY, int endX, int endY, Color playerColor) {
        int direction = (playerColor == YOU) ? 1 : -1; // White moves up, Black moves down
        if (startY == endY) { // Moving forward
            if (board[endX][endY].piece == EMPTY) {
                if (endX == startX + direction) return true; // Move forward 1 square
                if ((startX == 1 && playerColor == YOU) || (startX == 6 && playerColor == ENEMY)) {
                    if (endX == startX + 2 * direction && board[startX + direction][startY].piece == EMPTY) {
                        return true; // First move, move forward 2 squares
                    }
                }
            }
        }
        else if (abs(endY - startY) == 1 && endX == startX + direction) { // Diagonal capture
            if (board[endX][endY].piece != EMPTY && board[endX][endY].color != playerColor) {
                return true; // Capture
            }
        }
        return false;
    }

    bool isValidBishopMove(int startX, int startY, int endX, int endY) {
        if (abs(endX - startX) == abs(endY - startY)) { // Diagonal move
            int xDirection = (endX > startX) ? 1 : -1;
            int yDirection = (endY > startY) ? 1 : -1;

            int x = startX + xDirection;
            int y = startY + yDirection;
            while (x != endX && y != endY) {
                if (board[x][y].piece != EMPTY) {
                    return false; // There's a piece in the way
                }
                x += xDirection;
                y += yDirection;
            }
            return true; // Path is clear
        }
        return false;
    }



    bool isValidRookMove(int startX, int startY, int endX, int endY) {
        if (startX == endX) { // Moving vertically
            int direction = (endY > startY) ? 1 : -1; // Moving up or down
            for (int y = startY + direction; y != endY; y += direction) {
                if (board[startX][y].piece != EMPTY) {
                    return false; // There's a piece in the way
                }
            }
        }
        else if (startY == endY) { // Moving horizontally
            int direction = (endX > startX) ? 1 : -1; // Moving right or left
            for (int x = startX + direction; x != endX; x += direction) {
                if (board[x][startY].piece != EMPTY) {
                    return false; // There's a piece in the way
                }
            }
        }
        else {
            return false; 
        }
        return true; 
    }


    bool isValidQueenMove(int startX, int startY, int endX, int endY) {
        return isValidRookMove(startX, startY, endX, endY) || isValidBishopMove(startX, startY, endX, endY);
    }


    bool isValidKingMove(int startX, int startY, int endX, int endY) {
        return (abs(endX - startX) <= 1 && abs(endY - startY) <= 1); // One square in any direction
    }

    bool isValidKnightMove(int startX, int startY, int endX, int endY) {
        int dx = abs(endX - startX);
        int dy = abs(endY - startY);
        return (dx == 2 && dy == 1) || (dx == 1 && dy == 2); // L-shape movement
    }

public:

    bool isValidMove(int startX, int startY, int endX, int endY, Color playerColor) {
        // Check if within bounds
        if (startX < 0 || startX >= 8 || startY < 0 || startY >= 8 ||
            endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
            return false;
        }

        Square startSquare = board[startX][startY];
        Square endSquare = board[endX][endY];

        if (startSquare.color != playerColor || endSquare.color == playerColor) {
            return false; // Can't capture own piece or move an opponent's piece
        }

        if (startSquare.color != playerColor || endSquare.color == playerColor) {
            return false;
        }

        switch (startSquare.piece) {
        case PAWN:
            return isValidPawnMove(startX, startY, endX, endY, playerColor);
        case KNIGHT:
            return isValidKnightMove(startX, startY, endX, endY);
        case BISHOP:
            return isValidBishopMove(startX, startY, endX, endY);
        case ROOK:
            return isValidRookMove(startX, startY, endX, endY);
        case QUEEN:
            return isValidQueenMove(startX, startY, endX, endY);
        case KING:
            return isValidKingMove(startX, startY, endX, endY);
        default:
            return false;
        }
    }

};

void printBoard(Chess* game, bool turn)
{
    if (turn) {
        for (int row = 7; row >= 0; --row) {
            std::cout << row + 1 << " "; 
            for (int col = 0; col < 8; ++col) {
                Square square = game->board[row][col];
                if (square.piece == EMPTY) {
                    std::cout << "-- "; 
                }
                else {
                    std::string pieceStr = (square.color == YOU ? "W" : "B");
                    switch (square.piece) {
                    case PAWN:   pieceStr += "P"; break;
                    case KNIGHT: pieceStr += "N"; break;
                    case BISHOP: pieceStr += "B"; break;
                    case ROOK:   pieceStr += "R"; break;
                    case QUEEN:  pieceStr += "Q"; break;
                    case KING:   pieceStr += "K"; break;
                    default: break;
                    }
                    std::cout << pieceStr << " ";  // Print the piece with its color
                }
            }
            std::cout << std::endl;  // Move to the next row
        }

        std::cout << "  ";
        for (int col = 1; col <= 8; ++col) {
            std::cout << col << "  "; // Print column numbers
        }
    }
    else {
        for (int row = 0; row < 8; ++row) {
            std::cout << 8 - row << " "; 
            for (int col = 7; col >= 0; --col) {
                Square square = game->board[row][col];
                if (square.piece == EMPTY) {
                    std::cout << "-- ";  
                }
                else {
                    std::string pieceStr = (square.color == YOU ? "W" : "B");
                    switch (square.piece) {
                    case PAWN:   pieceStr += "P"; break;
                    case KNIGHT: pieceStr += "N"; break;
                    case BISHOP: pieceStr += "B"; break;
                    case ROOK:   pieceStr += "R"; break;
                    case QUEEN:  pieceStr += "Q"; break;
                    case KING:   pieceStr += "K"; break;
                    default: break;
                    }
                    std::cout << pieceStr << " ";
                }
            }
            std::cout << std::endl;
        }

        std::cout << "  ";
        for (int col = 1; col <= 8; ++col) {
            std::cout << col << "  "; 
        }
    }

    std::cout << std::endl << std::endl;
    std::cout << "WHITE POINTS: " << game->whitePoints << std::endl;
    std::cout << "BLACK POINTS: " << game->blackPoints << std::endl;
    std::cout << std::endl << std::endl;
}



void clear_console() {
    COORD topLeft = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}

void move(Chess* game, bool turn) // true = white; false = black
{
    
    int x1{}, x2{}, y1{}, y2{};

    if (turn)
    {
        std::cout << "WHITE: ";
    }
    else
    {
        std::cout << "BLACK: ";
    }
    std::cout << "Piece you want to move:\n";
    std::cout << "X: ";
    std::cin >> x1;
    std::cout << "Y: ";
    std::cin >> y1;
    std::cout << "Place you want to move piece to:\n";
    std::cout << "X: ";
    std::cin >> x2;
    std::cout << "Y: ";
    std::cin >> y2;
    bool res;
    if (turn)
    {
        res = game->whiteMove(y1, x1, y2, x2);
    }
    else
    {
        res = game->blackMove(9-y1, 9-x1, 9-y2, 9-x2);
    }

    if (!res)
    {
        move(game, turn);
    }
    else
    {
        clear_console();
        printBoard(game, !turn);
    }
    
}

// A simple feedforward neural network for the chess bot
struct ChessBotModel : torch::nn::Module {
    torch::nn::Linear fc1{ nullptr }, fc2{ nullptr }, fc3{ nullptr };

    ChessBotModel() {
        // Initialize the layers
        fc1 = register_module("fc1", torch::nn::Linear(8 * 8 * 12 + 1, 128)); // 12 for each piece type (6 for each color), +1 for points
        fc2 = register_module("fc2", torch::nn::Linear(128, 64));
        fc3 = register_module("fc3", torch::nn::Linear(64, 4));  // Output: x1, y1, x2, y2 (starting and ending positions)
    }

    torch::Tensor forward(torch::Tensor x) {
        // Pass the input through the layers with ReLU activation functions
        x = torch::relu(fc1(x));
        x = torch::relu(fc2(x));
        x = fc3(x);
        return x;
    }
};

torch::Tensor preprocessBoard(const std::vector<std::vector<Square>>& board, int points) {
    // 12 channels for one-hot encoding of pieces (6 white, 6 black)
    torch::Tensor boardTensor = torch::zeros({ 8, 8, 12 });  // Initializes all entries as empty

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Square square = board[row][col];

            if (square.piece != EMPTY) {
                int index = square.color == YOU ? square.piece - 1 : square.piece + 5;  
                boardTensor[row][col][index] = 1.0;
            }
        }
    }

    // Flatten the board to a 1D tensor (8 * 8 * 12 = 768 values)
    auto flatBoard = boardTensor.flatten();

    // Add the points as an additional feature (append points to the end)
    auto inputTensor = torch::cat({ flatBoard, torch::tensor({(float)points}) });

    return inputTensor;
}

void makeMove(ChessBotModel& model, Chess* game, int points)
{
    // Preprocess the board and points
    torch::Tensor input = preprocessBoard(game->Board(), points);

    // Run the model to predict the move
    torch::Tensor moveTensor = model.forward(input);

    // Convert the move tensor back to coordinates
    int startX = static_cast<int>(moveTensor[0].item<float>());
    int startY = static_cast<int>(moveTensor[1].item<float>());
    int endX = static_cast<int>(moveTensor[2].item<float>());
    int endY = static_cast<int>(moveTensor[3].item<float>());

    std::cout << "Model attempts to move piece from (" << startX + 1 << ", " << startY + 1 << ") to (" << endX + 1 << ", " << endY + 1 << ")\n";

    Color playerColor = YOU;

    // Check if the move is valid for the player
    if (game->isValidMove(startX, startY, endX, endY, playerColor)) {
        // If valid, make the move on the board
        game->Board()[endY][endX] = game->Board()[startY][startX];  // Move the piece
        game->Board()[startY][startX] = Square();                   // Set the starting square to empty
        std::cout << "Move made successfully!\n";
    }
    else {
        std::cout << "Invalid move by the model. Trying a new move...\n";

        for (int attempts = 0; attempts < 10000; ++attempts) {
            moveTensor = model.forward(input); // Re-run the model
            startX = static_cast<int>(moveTensor[0].item<float>());
            startY = static_cast<int>(moveTensor[1].item<float>());
            endX = static_cast<int>(moveTensor[2].item<float>());
            endY = static_cast<int>(moveTensor[3].item<float>());

            if (game->isValidMove(startX, startY, endX, endY, playerColor)) {
                // If valid, make the move on the board
                game->Board()[endY][endX] = game->Board()[startY][startX];  // Move the piece
                game->Board()[startY][startX] = Square();
                std::cout << "Move made successfully after reattempt!\n";
                break; // Exit loop if the move was successful
            }
        }
        std::cout << "Failed to make a valid move after several attempts.\n";
    }
}



int main() 
{


    Chess game;
    ChessBotModel model;
    printBoard(&game, true);


    
    while (true)
    {
        makeMove(model, &game, game.getWhitePoints());
        move(&game, true);
        move(&game, false);
    }


    return 0;
}