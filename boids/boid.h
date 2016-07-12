#ifndef BOID_H
#define BOID_H

class Boid{
public:
    Boid ();
    Boid (int, int, bool, int);
    void setx(int);
    void sety(int);
    void setleader(bool);
    void setdirection(int);
    int posx(){return x;};
    int posy(){return y;};
    int heading(){return direction;}
    bool isLeader(){return leader;};
    void decrease();
private:
    int     x;
    int     y;
    bool    leader;
    int     direction;
    int     timer;

};

Boid::Boid ()
{
    x = rand() % SCREEN_WIDTH + 1;
    y = rand() % SCREEN_HEIGHT + 1;
    direction = rand() % 8;
    leader = false;
    timer = rand() % 1000 + 20;
}
Boid::Boid (int tx, int ty, bool tleader = false, int tdirection = 0)
{
    x = tx;
    y = ty;
    leader = tleader;
    direction = tdirection;
    timer = rand() % 1000 + 20;
}

void Boid::decrease()
{
    timer--;
    if (timer < 0)
    {
        timer = rand() % 1000 + 20;
        direction = rand() % 8;
    }
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


#endif