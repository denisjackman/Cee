
class Boid{
public:
    Boid (int, int, bool, int);
    void setx(int);
    void sety(int);
    void setleader(bool);
    void setdirection(int);
    int posx(){return x;};
    int posy(){return y;};
    int heading(){return direction;}
    bool isLeader(){return leader;};
private:
    int     x;
    int     y;
    bool    leader;
    int     direction;
};


Boid::Boid (int tx, int ty, bool tleader = false, int tdirection = 0)
{
    x = tx;
    y = ty;
    leader = tleader;
    direction = tdirection;
}

void Boid::sety(int ty)
{
    y = ty;
}

void Boid::setx(int tx)
{
    x = tx;
}

void Boid::setleader(bool tleader)
{
    leader = tleader;
}

void Boid::setdirection(int tdirection)
{
    direction = tdirection;
}