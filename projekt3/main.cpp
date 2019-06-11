#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>

class board;

class figure
{

public:
    sf::RectangleShape body;
    board *myboard;
    int isWhite;
    int value;
    int nr;
    bool imPawn = false;
    int x;
    int y;
    virtual void possibleMoves(std::vector<std::pair<int, int>> &possible, std::vector<std::pair<int, int>> &attacked){};
    // figure(sf::Texture* texture, int _x, int _y)
    // {
    //     x=_x;
    //     y=_y;
    //     body.setSize(sf::Vector2f(50.0f,50.0f));
    //     body.setPosition(4+x*64,4+y*64);
    //     body.setTexture(texture);
    // }
    void draw(sf::RenderWindow window)
    {
        window.draw(body);
    }
    // figure()=default;
    // figure(const figure& old)
    // {
    //     body=old.body;
    //     isWhite=old.isWhite;
    //     value=old.value;
    //     imPawn=old.imPawn;
    //     x=old.x;
    //     y=old.y;
    // }
    void move(int _x, int _y)
    {
        x = _x;
        y = _y;

        body.setPosition(4 + x * 64, 4 + y * 64);
        // std::cout << "ruszam  na " << x << " " << y << "\n";
    }
};
bool inRange(int a, int b)
{
    if (a < 8 && a >= 0 && b < 8 && b >= 0)
        return true;
    return false;
}

class field
{
public:
    int x;
    int y;

    figure *occupiedBy = nullptr;
    bool isFree()
    {
        if (occupiedBy == nullptr)
            return true;
        return false;
    };
    void assignFigure(figure *newAssignement)
    {
        occupiedBy = newAssignement;
    };
    void free()
    {
        occupiedBy = nullptr;
    }
};
bool isCheck(board *myboard, bool isWhite);
class board
{
public:
    bool nowMove = 0;
    figure *toMove;
    sf::Texture shape;
    sf::Vector2u size;
    std::vector<figure> figures;
    std::vector<std::vector<field>> fields;
    std::vector<std::pair<int, int>> possbileFields;
    std::vector<std::pair<int, int>> attackedFields;
    std::vector<std::pair<int, int>> endangeredFields;
    std::vector<std::pair<int, int>> helpful;
    board();
    board(const board &old);
    void clear()
    {
        for (std::vector<field> wektor : fields)
        {
            for (field pole : wektor)
            {
                if (!pole.isFree())
                    delete pole.occupiedBy;
            }
            wektor.clear();
        }
        fields.clear();
    }
    int isFieldAttacked(int x, int y, int white);
    void print(sf::RenderWindow *window)
    {
        for (std::vector<field> wektor : fields)
        {
            for (field pole : wektor)
            {
                if (!pole.isFree())
                    window->draw(pole.occupiedBy->body);
            }
        }
        // for(figure fig: figures)
        // window->draw(fig.body);
    }
    void strongMove(int x, int y, int nax, int nay)
    {

        // std::cout << "strong move z: " << x << " " << y << " na pole " << nax << " " << nay << "\n";
        if (!inRange(x, y) || !inRange(nax, nay))
        {
            std::cout << "co do cholery?\n";
            return;
        }

        fields[nax][nay].free();
        // std::cout << " spadam z " << x << " " << y << std::endl;
        fields[nax][nay].assignFigure(fields[x][y].occupiedBy);
        fields[x][y].occupiedBy->move(nax, nay);
        fields[x][y].free();
    }

    void move(int x, int y)
    {
        bool moveIsPossible = false;
        bool capture = false;
        int a = toMove->x;
        int b = toMove->y;
        std::pair<int, int> para(x, y);
        for (std::pair<int, int> elems : possbileFields)
        {
            //std::cout<<"sprawdzam";
            if (elems == para)
            {
                moveIsPossible = true;
            }
        }
        for (std::pair<int, int> elems : attackedFields)
        {

            if (elems == para)
            {
                capture = true;
            }
        }
        if (capture)
        {
            fields[x][y].free();

            std::cout << "bicie:";
        }
        if (moveIsPossible or capture)
        {
            fields[a][b].free();
            toMove->move(x, y);
            fields[x][y].assignFigure(toMove);

            if (isCheck(this, 1))
            {
                toMove = fields[x][y].occupiedBy;
                fields[x][y].free();
                toMove->move(a, b);
                fields[a][b].assignFigure(toMove);
            }
        }
    }
};
bool isCheck(board *myboard, bool isWhite)
{
    for (std::vector<field> pola : myboard->fields)
    {
        for (field pole : pola)
        {
            if (!pole.isFree() && pole.occupiedBy->imPawn && pole.occupiedBy->isWhite == isWhite)
            {
                if (myboard->isFieldAttacked(pole.x, pole.y, isWhite) > 0)
                {
                    std::cout << "\n\nSZACH\n\n";
                    return true;
                }
            }
        }
    }
    return false;
}
class pawn : public figure
{
public:
    pawn(board *tab, int _x, int _y, int iswhite)
    {
        //mPawn=true;
        x = _x;
        y = _y;
        isWhite = iswhite;
        body.setSize(sf::Vector2f(60.0f, 60.0f));
        body.setPosition(4 + x * 64, 4 + y * 64);
        myboard = tab;
        value = 1;
        nr = 1;
        body.setTexture(&tab->shape);
        body.setTextureRect(sf::IntRect(tab->size.x * 5, tab->size.y * iswhite, tab->size.x, tab->size.y));
        // body.setFillColor(sf::Color::Blue);
    }

    void possibleMoves(std::vector<std::pair<int, int>> &possible, std::vector<std::pair<int, int>> &attacked) override
    {
        if (isWhite)
        {
            int a = x;
            int b = y - 1;
            if (inRange(a, b) && myboard->fields[a][b].isFree())
                possible.push_back(std::make_pair(a, b));
            if (inRange(x, y - 2) && y == 6 && myboard->fields[x][y - 2].isFree() && myboard->fields[x][y - 1].isFree())
            {
                possible.push_back(std::make_pair(x, y - 2));
            }
        }
        else
        {
            int a = x;
            int b = y + 1;
            if (inRange(a, b) && myboard->fields[a][b].isFree())
                possible.push_back(std::make_pair(a, b));
            if (y == 1 && myboard->fields[x][y + 2].isFree() && myboard->fields[x][y + 1].isFree() && inRange(x, y + 2))
            {
                possible.push_back(std::make_pair(x, y + 2));
            }
        }
        //     attacking(attacked);
        //    // myboard->possbileFields.clear();

        //     //return toReturn;
        // }
        // void attacking(std::vector<std::pair<int,int>>& attacked)
        // {
        if (isWhite)
        {
            if (inRange(x + 1, y - 1) && !myboard->fields[x + 1][y - 1].isFree() && !(myboard->fields[x + 1][y - 1].occupiedBy->isWhite))
                attacked.push_back(std::make_pair(x + 1, y - 1));

            if (inRange(x - 1, y - 1) && !myboard->fields[x - 1][y - 1].isFree() && !(myboard->fields[x - 1][y - 1].occupiedBy->isWhite))
                attacked.push_back(std::make_pair(x - 1, y - 1));
        }
        else
        {

            if (inRange(x + 1, y + 1) && !myboard->fields[x + 1][y + 1].isFree() && (myboard->fields[x + 1][y + 1].occupiedBy->isWhite))
                attacked.push_back(std::make_pair(x + 1, y + 1));

            if (inRange(x - 1, y + 1) && !myboard->fields[x - 1][y + 1].isFree() && (myboard->fields[x - 1][y + 1].occupiedBy->isWhite))
                attacked.push_back(std::make_pair(x - 1, y + 1));
        }
    }
};

void makeKMove(int isWhite, board *myboard, std::vector<std::pair<int, int>> &possible, std::vector<std::pair<int, int>> &attacked, int x, int y)
{
    if (inRange(x, y))
    {
        if (myboard->fields[x][y].isFree()) //&& myboard->isFieldAttacked(x,y,isWhite)==0)
        {

            // std::cout<<"TO POLE JEST ATTACKED "<<myboard->isFieldAttacked(x,y,isWhite)<<std::endl;
            //if(myboard->isFieldAttacked(x,y,isWhite)==0)
            possible.push_back(std::make_pair(x, y));
        }
        else //if( myboard->fields[x][y].occupiedBy->isWhite==isWhite )//)   &&  myboard->isFieldAttacked(x,y,isWhite)==0)//    &&  myboard->isFieldAttacked(x,y,isWhite)==0)
        {
            // if(myboard->isFieldAttacked(x,y,isWhite)==0)
            attacked.push_back(std::make_pair(x, y));
            // std::cout<<"dodaje pola"<<x<<" i "<< y;
        }
    }
}
void cheatedKingsPossibleMoves(int isWhite, board *myboard, int x, int y, std::vector<std::pair<int, int>> &possible, std::vector<std::pair<int, int>> &attacked)
{
    makeKMove(isWhite, myboard, possible, attacked, x + 1, y + 1);
    makeKMove(isWhite, myboard, possible, attacked, x + 1, y - 1);
    makeKMove(isWhite, myboard, possible, attacked, x - 1, y + 1);
    makeKMove(isWhite, myboard, possible, attacked, x - 1, y - 1);
    makeKMove(isWhite, myboard, possible, attacked, x, y + 1);
    makeKMove(isWhite, myboard, possible, attacked, x, y - 1);
    makeKMove(isWhite, myboard, possible, attacked, x + 1, y);
    makeKMove(isWhite, myboard, possible, attacked, x - 1, y);
}
int board::isFieldAttacked(int x, int y, int white)
{
    int magicznyLicznik = 0;
    int wynik = 0;
    bool magic = false;
    // endangeredFields=possbileFields;
    // helpful=
    //helpful.clear();

    //possbileFields.clear();
    figure *pionek = nullptr;
    std::pair<int, int> para(x, y);
    if (inRange(x, y) && fields[x][y].isFree())
    {
        pionek = new pawn(this, x, y, white);
        fields[x][y].assignFigure(pionek);
    }
    else if (inRange(x, y) && !fields[x][y].isFree() && fields[x][y].occupiedBy->isWhite != white)
    {
        magic = true;
        if (fields[x][y].occupiedBy->isWhite == 1)
            fields[x][y].occupiedBy->isWhite = 0;
        else
            fields[x][y].occupiedBy->isWhite = 1;
    }

    for (std::vector<field> wektor : fields)
    {
        for (field pole : wektor)
        {
            if (!pole.isFree() && pole.occupiedBy->isWhite != white && !pole.occupiedBy->imPawn)
            {
                magicznyLicznik++;
                pole.occupiedBy->possibleMoves(endangeredFields, helpful);
            }
            else if (!pole.isFree() && pole.occupiedBy->isWhite != white && pole.occupiedBy->imPawn)
            {
                magicznyLicznik++;
                cheatedKingsPossibleMoves(pole.occupiedBy->isWhite, this, pole.occupiedBy->x, pole.occupiedBy->y, endangeredFields, helpful);
            }
        }
    }

    for (std::pair<int, int> pary : endangeredFields)
    {
        if (pary == para)
            wynik++;
    }
    for (std::pair<int, int> pary : helpful)
    {
        if (pary == para)
            wynik++;
    }
    endangeredFields.clear();

    helpful.clear();
    // std::cout<<"sprawdzilem "<<magicznyLicznik<<" pol \n";
    if (magic)
    {
        if (fields[x][y].occupiedBy->isWhite == 1)
            fields[x][y].occupiedBy->isWhite = 0;
        else
            fields[x][y].occupiedBy->isWhite = 1;
    }
    if (pionek != nullptr)
    {
        fields[x][y].free();
        delete pionek;
    }
    return wynik;
}
class rook : public figure
{
public:
    rook(board *tab, int _x, int _y, int iswhite)
    {
        x = _x;
        y = _y;
        isWhite = iswhite;
        body.setSize(sf::Vector2f(60.0f, 60.0f));
        body.setPosition(4 + x * 64, 4 + y * 64);
        myboard = tab;
        value = 5;
        nr = 2;
        body.setTexture(&tab->shape);
        body.setTextureRect(sf::IntRect(tab->size.x * 2, tab->size.y * iswhite, tab->size.x, tab->size.y));
        // body.setFillColor(sf::Color::Blue);
    }

    void possibleMoves(std::vector<std::pair<int, int>> &possible, std::vector<std::pair<int, int>> &attacked) override
    {
        for (int i = x + 1; i < 8; i++)
        {
            if (myboard->fields[i][y].isFree())
            {
                possible.push_back(std::make_pair(i, y));
            }
            else if (inRange(i, y) && myboard->fields[i][y].occupiedBy->isWhite != this->isWhite)
            {
                attacked.push_back(std::make_pair(i, y));
                i = 8;
            }
            else
            {
                i = 8;
            }
        }
        for (int i = x - 1; i >= 0; i--)
        {
            if (myboard->fields[i][y].isFree())
            {
                possible.push_back(std::make_pair(i, y));
            }
            else if (inRange(i, y) && myboard->fields[i][y].occupiedBy->isWhite != this->isWhite)
            {
                attacked.push_back(std::make_pair(i, y));
                i = -1;
            }
            else
            {
                i = -1;
            }
        }
        for (int i = y + 1; i < 8; i++)
        {
            if (myboard->fields[x][i].isFree())
            {
                possible.push_back(std::make_pair(x, i));
            }
            else if (inRange(x, i) && myboard->fields[x][i].occupiedBy->isWhite != this->isWhite)
            {
                attacked.push_back(std::make_pair(x, i));
                i = 8;
            }
            else
            {
                i = 8;
            }
        }
        for (int i = y - 1; i >= 0; i--)
        {
            if (myboard->fields[x][i].isFree())
            {
                possible.push_back(std::make_pair(x, i));
            }
            else if (inRange(x, i) && myboard->fields[x][i].occupiedBy->isWhite != this->isWhite)
            {
                attacked.push_back(std::make_pair(x, i));
                i = -1;
            }
            else
            {
                i = -1;
            }
        }
    }
};

class knight : public figure
{
public:
    knight(board *tab, int _x, int _y, int iswhite)
    {
        x = _x;
        y = _y;
        isWhite = iswhite;
        body.setSize(sf::Vector2f(60.0f, 60.0f));
        body.setPosition(4 + x * 64, 4 + y * 64);
        myboard = tab;
        value = 3;
        nr = 3;
        body.setTexture(&tab->shape);
        body.setTextureRect(sf::IntRect(tab->size.x * 4, tab->size.y * iswhite, tab->size.x, tab->size.y));
        // body.setFillColor(sf::Color::Blue);
    }
    void makeMoves(std::vector<std::pair<int, int>> &possible, std::vector<std::pair<int, int>> &attacked, int x, int y)
    {
        //std::cout<<"dodaje ruch\n";
        if (inRange(x, y) && myboard->fields[x][y].isFree())
        {
            possible.push_back(std::make_pair(x, y));
            //std::cout<<"dopchalem ruch konia\n";
        }
        else if (inRange(x, y) && myboard->fields[x][y].occupiedBy->isWhite != this->isWhite)
        {
            attacked.push_back(std::make_pair(x, y));
        }
    }
    void possibleMoves(std::vector<std::pair<int, int>> &possible, std::vector<std::pair<int, int>> &attacked)
    {
        //std::cout<<"BEDE DODAWAL KONIE\n";
        makeMoves(possible, attacked, x + 1, y + 2);
        makeMoves(possible, attacked, x + 2, y + 1);
        makeMoves(possible, attacked, x + 2, y - 1);
        makeMoves(possible, attacked, x + 1, y - 2);
        makeMoves(possible, attacked, x - 1, y - 2);
        makeMoves(possible, attacked, x - 2, y - 1);
        makeMoves(possible, attacked, x - 2, y + 1);
        makeMoves(possible, attacked, x - 1, y + 2);
    }
};

class queen : public figure
{
public:
    queen(board *tab, int _x, int _y, int iswhite)
    {
        x = _x;
        y = _y;
        isWhite = iswhite;
        body.setSize(sf::Vector2f(60.0f, 60.0f));
        body.setPosition(4 + x * 64, 4 + y * 64);
        myboard = tab;
        value = 9;
        nr = 5;
        body.setTexture(&tab->shape);
        body.setTextureRect(sf::IntRect(tab->size.x * 1, tab->size.y * iswhite, tab->size.x, tab->size.y));
        // body.setFillColor(sf::Color::Blue);
    }
    int makeMove(std::vector<std::pair<int, int>> &possible, std::vector<std::pair<int, int>> &attacked, int x, int y)
    {
        if (inRange(x, y) && myboard->fields[x][y].isFree())
        {
            possible.push_back(std::make_pair(x, y));

            return 0;
        }
        else if (inRange(x, y) && myboard->fields[x][y].occupiedBy->isWhite != this->isWhite)
        {
            attacked.push_back(std::make_pair(x, y));
            return 8;
        }
        else
        {
            return 8;
        }
    }
    void possibleMoves(std::vector<std::pair<int, int>> &possible, std::vector<std::pair<int, int>> &attacked) override
    {

        for (int i = 1; i < 8; i++)
        {
            i += makeMove(possible, attacked, x + i, y + i);
        }
        for (int i = 1; i < 8; i++)
        {
            i += makeMove(possible, attacked, x + i, y - i);
        }
        for (int i = 1; i < 8; i++)
        {
            i += makeMove(possible, attacked, x - i, y + i);
        }
        for (int i = 1; i < 8; i++)
        {
            i += makeMove(possible, attacked, x - i, y - i);
        }

        for (int i = 1; i < 8; i++)
        {
            i += makeMove(possible, attacked, x, y + i);
        }
        for (int i = 1; i < 8; i++)
        {
            i += makeMove(possible, attacked, x, y - i);
        }
        for (int i = 1; i < 8; i++)
        {
            i += makeMove(possible, attacked, x - i, y);
        }
        for (int i = 1; i < 8; i++)
        {
            i += makeMove(possible, attacked, x + i, y);
        }
    }
};
class king : public figure
{
public:
    king(board *tab, int _x, int _y, int iswhite)
    {
        value = 1000;
        x = _x;
        y = _y;
        isWhite = iswhite;
        body.setSize(sf::Vector2f(60.0f, 60.0f));
        body.setPosition(4 + x * 64, 4 + y * 64);
        myboard = tab;
        nr = 6;
        imPawn = true;
        body.setTexture(&tab->shape);
        body.setTextureRect(sf::IntRect(tab->size.x * 0, tab->size.y * iswhite, tab->size.x, tab->size.y));
        // body.setFillColor(sf::Color::Blue);
    }
    void makeMove(std::vector<std::pair<int, int>> &possible, std::vector<std::pair<int, int>> &attacked, int x, int y)
    {
        if (inRange(x, y) && myboard->isFieldAttacked(x, y, isWhite) == 0)
        {
            if (myboard->fields[x][y].isFree()) //&& myboard->isFieldAttacked(x,y,isWhite)==0)
            {

                // std::cout<<"TO POLE JEST ATTACKED "<<myboard->isFieldAttacked(x,y,isWhite)<<std::endl;
                //if(myboard->isFieldAttacked(x,y,isWhite)==0)
                possible.push_back(std::make_pair(x, y));
            }
            else if (myboard->fields[x][y].occupiedBy->isWhite != this->isWhite) //)   &&  myboard->isFieldAttacked(x,y,isWhite)==0)//    &&  myboard->isFieldAttacked(x,y,isWhite)==0)
            {
                // if(myboard->isFieldAttacked(x,y,isWhite)==0)
                attacked.push_back(std::make_pair(x, y));
            }
        }
    }
    void possibleMoves(std::vector<std::pair<int, int>> &possible, std::vector<std::pair<int, int>> &attacked) override
    {
        std::vector<std::pair<int, int>> helpful;
        std::vector<std::pair<int, int>> helpful2;

        makeMove(possible, attacked, x + 1, y + 1);
        makeMove(possible, attacked, x + 1, y - 1);
        makeMove(possible, attacked, x - 1, y + 1);
        makeMove(possible, attacked, x - 1, y - 1);
        makeMove(possible, attacked, x, y + 1);
        makeMove(possible, attacked, x, y - 1);
        makeMove(possible, attacked, x + 1, y);
        makeMove(possible, attacked, x - 1, y);

        // helpful=myboard->possbileFields;
        // helpful2=myboard->attackedFields;
        // myboard->possbileFields.clear();
        // myboard->attackedFields.clear();

        //         int licznik=0;
        // for (auto it = helpful.begin(); it != helpful.end(); ) {
        //         if (myboard->isFieldAttacked((*it).first,(*it).second,isWhite)>0)
        //         {
        //             std::cout<<"hujowe pole\n"<<licznik;
        //             licznik++;
        //             it = helpful.erase(it);
        //         } else {
        //             ++it;
        //         }
        //     }
        //         myboard->possbileFields=helpful;
        //         myboard->attackedFields=helpful2;
    }
};

class bishop : public figure
{
public:
    bishop(board *tab, int _x, int _y, int iswhite)
    {
        x = _x;
        y = _y;
        isWhite = iswhite;
        body.setSize(sf::Vector2f(60.0f, 60.0f));
        body.setPosition(4 + x * 64, 4 + y * 64);
        myboard = tab;
        value = 3;
        nr = 4;
        body.setTexture(&tab->shape);
        body.setTextureRect(sf::IntRect(tab->size.x * 3, tab->size.y * iswhite, tab->size.x, tab->size.y));
        // body.setFillColor(sf::Color::Blue);
    }

    int makeMove(std::vector<std::pair<int, int>> &possible, std::vector<std::pair<int, int>> &attacked, int x, int y)
    {
        if (inRange(x, y) && myboard->fields[x][y].isFree())
        {
            possible.push_back(std::make_pair(x, y));
            return 0;
        }
        else if (inRange(x, y) && myboard->fields[x][y].occupiedBy->isWhite != this->isWhite)
        {
            attacked.push_back(std::make_pair(x, y));
            return 8;
        }
        else
        {
            return 8;
        }
    }
    void possibleMoves(std::vector<std::pair<int, int>> &possible, std::vector<std::pair<int, int>> &attacked) override
    {

        for (int i = 1; i < 8; i++)
        {
            i += makeMove(possible, attacked, x + i, y + i);
        }
        for (int i = 1; i < 8; i++)
        {
            i += makeMove(possible, attacked, x + i, y - i);
        }
        for (int i = 1; i < 8; i++)
        {
            i += makeMove(possible, attacked, x - i, y + i);
        }
        for (int i = 1; i < 8; i++)
        {
            i += makeMove(possible, attacked, x - i, y - i);
        }
    }
};

board::board()
{
    shape.loadFromFile("figurki.png");
    size = shape.getSize();
    size.x /= 6;
    size.y /= 2;

    for (int i = 0; i < 8; i++)
    {
        fields.emplace_back();
        for (int j = 0; j < 8; j++)
        {
            fields[i].emplace_back();
            fields[i][j].x = i;
            fields[i][j].y = j;
        }
    }

    for (int i = 0; i < 8; i++)
    {
        pawn *pion = new pawn(this, i, 1, 0);
        fields[i][1].assignFigure(pion);
        // figures.push_back(*pion);
    }
    for (int i = 0; i < 8; i++)
    {
        pawn *pion = new pawn(this, i, 6, 1);
        fields[i][6].assignFigure(pion);
        //figures.push_back(*pion);
    }

    figure *pion;

    pion = new rook(this, 7, 7, 1);
    fields[7][7].assignFigure(pion);
    pion = new rook(this, 0, 7, 1);
    fields[0][7].assignFigure(pion);
    pion = new rook(this, 0, 0, 0);
    fields[0][0].assignFigure(pion);
    pion = new rook(this, 7, 0, 0);
    fields[7][0].assignFigure(pion);

    pion = new knight(this, 6, 7, 1);
    fields[6][7].assignFigure(pion);
    pion = new knight(this, 1, 7, 1);
    fields[1][7].assignFigure(pion);
    pion = new knight(this, 6, 0, 0);
    fields[6][0].assignFigure(pion);
    pion = new knight(this, 1, 0, 0);
    fields[1][0].assignFigure(pion);

    pion = new bishop(this, 5, 7, 1);
    fields[5][7].assignFigure(pion);
    pion = new bishop(this, 2, 7, 1);
    fields[2][7].assignFigure(pion);
    pion = new bishop(this, 5, 0, 0);
    fields[5][0].assignFigure(pion);
    pion = new bishop(this, 2, 0, 0);
    fields[2][0].assignFigure(pion);

    pion = new queen(this, 3, 7, 1);
    fields[3][7].assignFigure(pion);
    pion = new queen(this, 3, 0, 0);
    fields[3][0].assignFigure(pion);

    pion = new king(this, 4, 7, 1);
    fields[4][7].assignFigure(pion);
    pion = new king(this, 4, 0, 0);
    fields[4][0].assignFigure(pion);
}
board::board(const board &old)
{
    nowMove = old.nowMove;
    toMove = nullptr;

    size = old.size;
    //std::vector< figure > figures=old.figures;
    //  std::vector< std::vector < field > > fields=old.fields;
    //std::vector<std::pair<int, int>> possbileFields = old.possbileFields;
    // std::vector< std::pair< int , int > > attackedFields;
    // std::vector< std::pair< int , int > > endangeredFields;
    // std::vector< std::pair< int , int > > helpful;
    //std::cout << "\nROBIE NOWEGO BOARDA\n";
    int i = 0;
    for (std::vector<field> wektor : old.fields)
    {
        // std::cout<<"o co bg?";
        fields.emplace_back();
        for (field pole : wektor)
        {
            // std::cout<<"1sr for";
            fields.back().emplace_back(pole);
            if (!pole.isFree())
            {
                switch (pole.occupiedBy->nr)
                {
                case 1:
                    fields.back().back().assignFigure(new pawn(this, pole.occupiedBy->x, pole.occupiedBy->y, pole.occupiedBy->isWhite));
                    break;

                case 2:
                    fields.back().back().assignFigure(new rook(this, pole.occupiedBy->x, pole.occupiedBy->y, pole.occupiedBy->isWhite));
                    break;

                case 3:
                    fields.back().back().assignFigure(new knight(this, pole.occupiedBy->x, pole.occupiedBy->y, pole.occupiedBy->isWhite));
                    break;

                case 4:
                    fields.back().back().assignFigure(new bishop(this, pole.occupiedBy->x, pole.occupiedBy->y, pole.occupiedBy->isWhite));
                    break;

                case 5:
                    fields.back().back().assignFigure(new queen(this, pole.occupiedBy->x, pole.occupiedBy->y, pole.occupiedBy->isWhite));
                    break;

                case 6:
                    fields.back().back().assignFigure(new king(this, pole.occupiedBy->x, pole.occupiedBy->y, pole.occupiedBy->isWhite));
                    break;
                }
                //fields.back().back().assignFigure(new figure(*(pole.occupiedBy)));
                //std::cout<<"stworzyelm nowa figure o wartosci "<<fields.back().back().occupiedBy->value<<"\n";
                i++;
            }
            fields.back().back().x = pole.x;
            fields.back().back().y = pole.y;
        }
    }
    for (int i = 0; i < 8; i++)
    {

        for (int j = 0; j < 8; j++)
        {

            fields[i][j].x = i;
            fields[i][j].y = j;
        }
    }
    // std::cout << "zrobilem " << i << " figure";
}
class possibilities
{
public:
    board *myboard;
    possibilities *head;
    std::vector<possibilities> nexts;
    int value = 0;
    int depth = 0;
    int x = 2;
    int y = 2;
    int nax = 2;
    int nay = 2;
    possibilities() = default;
    possibilities(const board &oldBoard)
    {
        myboard = new board(oldBoard);
    }
    //     ~possibilities()
    //     {
    //        nexts.clear();
    // head=nullptr;
    // myboard=nullptr;
    //     }

    int calculate(int isWhite)
    {
        int counter = 0;
        int val = value;
        //std::cout << "\n calculate sie zaczyna";
        for (std::vector<field> fields : myboard->fields)
        {
            for (field pole : fields)
            {

                if (!pole.isFree() && pole.occupiedBy->isWhite != isWhite)
                {
                    //std::cout<<pole.x<<pole.y;
                    val -= pole.occupiedBy->value;
                    // value   += myboard->isFieldAttacked(pole.x,pole.y,isWhite);
                    // std::cout<<"\nnie zjebalo sie";
                }
                if (!pole.isFree() && pole.occupiedBy->isWhite == isWhite)
                {
                    // std::cout<<"sorawdzam pole";

                    val += pole.occupiedBy->value; // * myboard->isFieldAttacked(pole.x,pole.y,isWhite);
                                                   // std::cout<<" "<<val<<"\n";
                }
                if (pole.isFree())
                {
                    counter++;
                }
                // else
                // {
                //     std::cout<<"figura o wartosci "<<pole.occupiedBy->value<<"\n";
                // }
            }
            //std::cout<<"\n ale tu juz nie dojde \n";
        }
        // std::cout << "w tym liczeniu jest " << counter << " pustych pol\n";
        // std::cout << "\n calc sie konczy\n\n\n"
        //   << val << "\n";
        value = val;
        return val;
    }
};

void fillvectorwithfiguremoves(std::vector<std::pair<int, int>> *moves, figure &fig)
{
    //std::cout<<"jestem we funkcji \n"<<"bede ruszal wartoscia "<< fig->value;

    fig.possibleMoves(*moves, *moves);
}

bool wontBeCheck()
{
}
class AI
{
public:
    std::vector<possibilities> myoptions;
    // int x=0;
    // int y=0;
    int howDeep = 0;

    void fillNexts(possibilities &tmp, bool iswhite, int depth)
    {
        std::vector<std::pair<int, int>> possibleMoves;
        for (std::vector<field> &pola : tmp.myboard->fields)
        {
            for (field &pole : pola)
            {
                if (!pole.isFree() && pole.occupiedBy->isWhite == iswhite)
                {

                    possibleMoves.clear();
                    fillvectorwithfiguremoves(&possibleMoves, *pole.occupiedBy);
                    //pole.occupiedBy->possibleMoves(possibleMoves,possibleMoves);
                    //std::cout << "rozmiar: " << possibleMoves.size() << "\n";
                    for (std::pair<int, int> coordinates : possibleMoves)
                    {
                        tmp.nexts.emplace_back(*tmp.myboard);
                        tmp.nexts.back().head = &tmp;
                        tmp.nexts.back().depth = depth;
                        tmp.nexts.back().x = pole.x;
                        tmp.nexts.back().y = pole.y;
                        tmp.nexts.back().nax = coordinates.first;
                        tmp.nexts.back().nay = coordinates.second;
                        tmp.nexts.back().myboard->strongMove(tmp.nexts.back().x, tmp.nexts.back().y, tmp.nexts.back().nax, tmp.nexts.back().nay);
                        if (isCheck(tmp.nexts.back().myboard, iswhite))
                            tmp.nexts.pop_back();
                        //tmp.nexts.back().value=tmp.nexts.back().calculate(iswhite);
                        //tmp.nexts.back().myboard->clear();
                    }
                }
            }
        }
        //std::cout << "ten opcja ma ruchow: " << tmp.nexts.size();
    }
    void furtherNexts(possibilities &tmp, bool iswhite, int depth)
    {
        if (depth > 1)
        {
            for (possibilities &elem : tmp.nexts)
            {
                elem.value = elem.calculate(0);
                //std::cout<<"wartosc liscia: "<<elem.value<<"\n";

                std::cout << "doszlem przy tworzeniu drzewa do liscia o wartosci " << elem.value << "\n"
                          << "a jego ruch to z " << elem.x << " " << elem.y << " na " << elem.nax << " " << elem.nay << "\n"
                          << "po uprzednim" << elem.head->x << " " << elem.head->y << " na " << elem.head->nax << " " << elem.head->nay << "\n"
                          << "po wczesniejszym" << elem.head->head->x << " " << elem.head->head->y << " na " << elem.head->head->nax << " " << elem.head->head->nay << "\n";
                std::cout << "po jeszcze wczesniejszym" << elem.head->head->head->x << " " << elem.head->head->head->y << " na " << elem.head->head->head->nax << " " << elem.head->head->head->nay << "\n\n";
                elem.myboard->clear();
            }

            return;
        }

        for (possibilities &elem : tmp.nexts)
        {
            fillNexts(elem, iswhite, depth);
            furtherNexts(elem, !iswhite, depth + 1);
        }
    }
    void minmax(board *myboard, bool iswhite)
    {
        possibilities firstoption(*myboard);
        //firstoption.myboard=myboard;
        possibilities *tmp = &firstoption;

        fillNexts(*tmp, iswhite, 0);
        furtherNexts(*tmp, !iswhite, 0);

        tmp = &firstoption;

        for (auto &temp : firstoption.nexts)
        {
            int a = solve(temp, 0, 0);
            std::cout << a;
            temp.value = a;
            std::cout << "dlatej opcji wyslo " << temp.value << "\n";
        }
        possibilities odp;
        int desired = -10000;
        for (auto &temp : firstoption.nexts)
        {
            if (temp.value > desired)
            {
                desired = temp.value;
                odp = temp;
            }
        }

        std::cout << "wyszlo mi ze trzeba sie ruszyc z " << odp.x << " " << odp.y << " na pole " << odp.nax << "  " << odp.nay << "\n";
        myboard->strongMove(odp.x, odp.y, odp.nax, odp.nay);
        tmp = &firstoption;
    }
    int solve(possibilities &opcja, int depth, bool max)
    {

        if (opcja.nexts.empty())
        {
            std::cout << "doszlem do liscia o wartosci " << opcja.value << " na glebokosci" << opcja.depth << "\n"
                      << "a jego ruch to z " << opcja.x << " " << opcja.y << " na " << opcja.nax << " " << opcja.nay << "\n"
                      << "po uprzednim" << opcja.head->x << " " << opcja.head->y << " na " << opcja.head->nax << " " << opcja.head->nay << "\n";
            std::cout << "po jeszcze wczesniejszym" << opcja.head->head->head->x << " " << opcja.head->head->head->y << " na " << opcja.head->head->head->nax << " " << opcja.head->head->head->nay << "\n\n";

            return opcja.value;
        }

        if (max)
        {
            int val = -10000;
            for (possibilities &tmp : opcja.nexts)
            {
                val = std::max(val, solve(tmp, depth + 1, 0));
                std::cout << "moje maximum " << val << std::endl;
            }

            return val;
        }
        else
        {
            int val = 100000;
            for (possibilities &tmp : opcja.nexts)
            {
                val = std::min(val, solve(tmp, depth + 1, 1));
                std::cout << "moje minimum " << val << std::endl;
            }
            return val;
        }
    }
};

int main()
{

    //  sf::RectangleShape player(sf::Vector2f(50.0f, 50.0f));
    bool whiteTurn = true;
    board plansza;
    AI ai;

    sf::RenderWindow window(sf::VideoMode(516, 516), "szachy", sf::Style::Close | sf::Style::Resize);
    sf::RectangleShape blackfield(sf::Vector2f(60.0f, 60.0f));
    sf::RectangleShape whitefield(sf::Vector2f(60.0f, 60.0f));
    sf::RectangleShape possibleField(sf::Vector2f(60.0f, 60.0f));
    sf::RectangleShape attackedField(sf::Vector2f(60.0f, 60.0f));

    attackedField.setFillColor(sf::Color::Red);
    possibleField.setFillColor(sf::Color::Green);
    blackfield.setFillColor(sf::Color(204, 153, 0));
    whitefield.setFillColor(sf::Color(255, 255, 102));
    // player.setOrigin(50,50);
    //sf::Texture playerTexture;
    //    playerTexture.loadFromFile("mario.jpeg");
    //     player.setTexture(&playerTexture);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(512.0f, 512.0f));
    bool playerMove = true;
    while (window.isOpen())
    {
        sf::Event ent;
        if (playerMove)
        {
            while (window.pollEvent(ent))
            {

                switch (ent.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    std::cout << "New window width: " << ent.size.width << " new window geight: " << ent.size.height << std::endl;
                    break;
                case sf::Event::TextEntered:
                    if (ent.text.unicode < 128)
                    {
                        printf("%c\n", ent.text.unicode);
                    }
                }
                // if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                // {
                //     player.move(-1.0f,0.0f);
                // }
                // if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                // {
                //     player.move(1.0f,0.0f);
                // }
                // if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                // {
                //     player.move(0.0f,-1.0f);
                // }
                // if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                // {
                //     player.move(0.0f,1.0f);
                // }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int x = 8 * mousePos.x / 516;
                    int y = 8 * mousePos.y / 516;
                    std::cout << "\nkliknieto na " << x << " " << y << " i jesli 1 to bedzie ruch " << plansza.nowMove << std::endl;
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && plansza.nowMove)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int zapx, zapy;
                    int x = 8 * mousePos.x / 516;
                    int y = 8 * mousePos.y / 516;
                    std::cout << "HAAAAALO\n";
                    //if((plansza.fields[x][y].isFree()))

                    plansza.nowMove = false;
                    std::cout << x << plansza.toMove->x << y << plansza.toMove->y;
                    if (x != plansza.toMove->x || y != plansza.toMove->y)
                    {
                        zapx = plansza.toMove->x;
                        zapy = plansza.toMove->y;

                        plansza.move(x, y);
                        if (plansza.fields[zapx][zapy].isFree())
                            playerMove = false;
                        whiteTurn = !whiteTurn;
                    }

                    plansza.possbileFields.clear();
                    plansza.attackedFields.clear();
                }

                else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !plansza.nowMove)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    //std::cout<<mousePos.x<<"  "<<mousePos.y<<std::endl;
                    int x = 8 * mousePos.x / 516;
                    int y = 8 * mousePos.y / 516;
                    plansza.possbileFields.clear();
                    plansza.attackedFields.clear();
                    plansza.nowMove = false;
                    std::cout << "\nto pole jest atakowane przez bialych: " << plansza.isFieldAttacked(x, y, 0) << std::endl;
                    std::cout << " i czarnych: " << plansza.isFieldAttacked(x, y, 1) << std::endl;

                    if (inRange(x, y) && !(plansza.fields[x][y].isFree()))
                    {
                        std::cout << "tu nie wchodze";
                        plansza.fields[x][y].occupiedBy->possibleMoves(plansza.possbileFields, plansza.attackedFields);
                        plansza.nowMove = true;
                        plansza.toMove = plansza.fields[x][y].occupiedBy;
                        std::cout << "no dadalo sie i co?\n";
                    }

                    if (plansza.possbileFields.empty() && plansza.attackedFields.empty())
                    {
                        plansza.nowMove = false;
                        std::cout << "tu jest prblem'";
                    }
                    else
                    {
                        std::cout << "wyswietlam mozliwe ruchy\n";
                    }

                    //for()
                    //std::getchar();

                    //blackfield.setPosition((float)mousePos.x, static_cast<float>(mousePos.y));
                }
            }
        }

        else
        {
            //   ai.makeMove(&plansza,0, ai.myoptions);
            ai.minmax(&plansza, 0);
            playerMove = true;
            plansza.nowMove = false;
            std::cout << "zrobilem ruch czlowieku\n";
        }

        window.clear(sf::Color(150, 150, 150));
        // window.setView(view);
        window.draw(blackfield);
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if ((i + j) % 2 == 0)
                {
                    whitefield.setPosition((float)(i * 64 + 4), (float)(j * 64 + 4));
                    window.draw(whitefield);
                }
                else
                {
                    blackfield.setPosition((float)(i * 64 + 4), (float)(j * 64 + 4));
                    window.draw(blackfield);
                }
            }
        }
        for (std::pair<int, int> koordynaty : plansza.possbileFields)
        {
            //std::cout<<"rysowanko\n";
            possibleField.setPosition((float)(4 + 64 * koordynaty.first), (float)(4 + 64 * koordynaty.second));
            window.draw(possibleField);
        }
        for (std::pair<int, int> koordynaty : plansza.attackedFields)
        {
            //std::cout<<"rysowanko\n";
            attackedField.setPosition((float)(4 + 64 * koordynaty.first), (float)(4 + 64 * koordynaty.second));
            window.draw(attackedField);
        }

        // window.draw(player);
        plansza.print(&window);
        window.display();
    }

    return 0;
}