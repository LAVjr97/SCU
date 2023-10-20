/*
 * Solve the n-Pieces problem of trying to place n identical pieces on
 * an n x n chessboard.
 *
 *      Knights         Bishops         Rooks           Queens          Amazons
 * 2    X               X               X               X               X
 * 3    XX              XX              X               X               X
 * 4    XXX             XXX             XX              X               X
 * 5    XXXX            XXXX            XXX             XX              X
 * 6    XXXXXX          XXXXX           XXX             X               X
 * 7    XXXXXXX         XXXXXXX         XXXX            XX              X
 * 8    XXXXXXXXX       XXXXXXXX        XXXXX           XX              X
 * 9    19206532478     565532992       362880          XXX             X
 * 10   1120204619108   15915225216     3628800         XXX             X
 */

# ifndef QUEENS_H
# define QUEENS_H
# include <cstdlib>


// An abstract chess piece that cannot be instantiated.

class Piece {
    protected:
        int _row, _column;

    public:
        int row() const{
            return _row;
        }
        int column() const{
            return _column;
        }
        void place(int row, int col);
        virtual bool menaces(const Piece *p) const = 0;
};

class Rook : public Piece{
    public:
    bool menaces(const Piece *p) const{
        if(p -> row() == _row)
            return true;
        if(p -> column() == _column)
            return true;

        return false; 
    }
};

class Bishop : public Piece{
    public:
    
};

class Knight : public Piece{
    private: 

    public: 

};

class Queen : public Rook, public Bishop{
    private: 

    public: 

};

class Amazon : public Queen, public Knight{ 
    private:

    public:

};

# endif /* QUEENS_H */
