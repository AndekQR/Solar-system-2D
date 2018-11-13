#include <iostream>
#include <allegro.h>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>

#include <winalleg.h>


#define colorBlack  makecol(0,0,0)
#define colorWhite  makecol(255,255,255)
#define colorRed  makecol(255,0,0)
#define colorGreen  makecol(0,255,0)
#define colorBlue  makecol(0,0,255)
#define colorPink makecol(255, 20, 147)
#define colorYellow makecol(255, 255, 0)
#define colorAqua makecol(0, 255, 255)
#define colorYellowGreen makecol(154, 205, 50)
#define colorGold makecol(255, 215, 0)
#define colorOrange makecol(246, 191, 27)

#define FPS 100

using namespace std;

volatile long speed = 0;

int cuttingArea[4] = {500, 500, 600,600};
BITMAP *planetBMP = NULL;
BITMAP *elipsyBMP = NULL;
BITMAP *bufor = NULL;
BITMAP *gwiazdy = NULL;

int mx;
int my;
int mb;

class Point2D
{

public:
    int x, y;
    vector<int> vectorX;
    vector<int> vectorY;


};

void increment_speed()
{
    speed++;
}

void myszka()
{
    if(mx!=mouse_x || my!=mouse_y || mb!=mouse_b)
    {
        mx=mouse_x;
        my=mouse_y;
        mb=mouse_b;
    }
}

END_OF_FUNCTION( increment_speed );
vector<int> vectorOfPoints; //floodfill
multimap <int, int> elipseOfMerkury;
Point2D elipseOfMerkuryPoint;
multimap <int, int> elipseOfWenus;
Point2D elipseOfWenusPoint;
multimap <int, int> elipseOfZiemia;
Point2D elipseOfZiemiaPoint;
multimap <int, int> elipseOfMars;
Point2D elipseOfMarsPoint;
multimap <int, int> elipseOfJowisz;
Point2D elipseOfJowiszPoint;
multimap <int, int> elipseOfSaturn;
Point2D elipseOfSaturnPoint;
multimap <int, int> elipseOfUran;
Point2D elipseOfUranPoint;
multimap <int, int> elipseOfNeptun;
Point2D elipseOfNeptunPoint;




LOCK_VARIABLE( speed );
LOCK_FUNCTION( increment_speed );



void wstaw(BITMAP *bmp, int x, int y, int d)
{
    if(d == colorRed)
        elipseOfMerkury.insert(pair<int,int>(x,y));
    if(d == colorBlue)
        elipseOfWenus.insert(pair<int,int>(x,y));
    if(d == colorGreen)
        elipseOfZiemia.insert(pair<int,int>(x,y));
    if(d == colorYellow)
        elipseOfMars.insert(pair<int,int>(x,y));
    if(d == colorYellowGreen)
        elipseOfJowisz.insert(pair<int,int>(x,y));
    if(d == colorGold)
        elipseOfSaturn.insert(pair<int,int>(x,y));
    if(d == colorPink)
        elipseOfUran.insert(pair<int,int>(x,y));
    if(d == colorAqua)
        elipseOfNeptun.insert(pair<int,int>(x,y));
}



class Planet
{
    Point2D planetxy;
    int color;
    int radius;

public:
    BITMAP *planeta = NULL;

    Planet(int radius, int color)
    {
        planeta = create_bitmap(4,4);
        this->radius = radius;
        this->color = color;
    }

    void setNewXY(int newX, int newY)
    {
        planetxy.x = newX;
        planetxy.y = newY;
        drawPlanet();
    }

    void drawPlanet()
    {
        //clear_to_color(planetBMP, colorBlue);
        //clear_to_color(screen, colorBlack);
        circlefill(planetBMP, planetxy.x, planetxy.y, radius, color);
        //masked_blit(planetBMP, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
        //draw_sprite(screen, planetBMP, 0,0);
    }
};

class Engine
{

    int newX, newY;

public:
    Engine()
    {
        init(true, 1);
        clear_to_color(screen, colorBlack);
        start();
        cout<<"wyjscie z start()"<<endl;
        destroy_bitmap(planetBMP);
        destroy_bitmap(elipsyBMP);
        destroy_bitmap(bufor);
        allegro_exit();
    }




    void start()
    {

        planetBMP = create_bitmap(800,800);
        elipsyBMP = create_bitmap(800,800);
        bufor = create_bitmap(800,800); //bufor ¿eby nie miga³o
        gwiazdy = create_bitmap(800,800);
        gwiazdy = load_bmp("gwiazdy.bmp", default_palette);
        //draw_sprite

        //circlefill(ekran, 100, 100, 50, colorRed);
        //blit(ekran, screen, 0,0,0,0,SCREEN_W, SCREEN_H);

        //cutting(0,0,700,700);
        //floodFill(545,530, colorBlue);


        wstawPunkty(SCREEN_W/2, SCREEN_H/2, SCREEN_W/10, SCREEN_W/10, colorRed);
        wstawPunkty(SCREEN_W/2, SCREEN_H/2, SCREEN_W/9, SCREEN_W/9, colorBlue);
        wstawPunkty(SCREEN_W/2, SCREEN_H/2, SCREEN_W/8, SCREEN_W/8, colorGreen);
        wstawPunkty(SCREEN_W/2, SCREEN_H/2, SCREEN_W/7, SCREEN_W/7, colorYellow);
        wstawPunkty(SCREEN_W/2, SCREEN_H/2, SCREEN_W/5, SCREEN_W/5, colorYellowGreen);
        wstawPunkty(SCREEN_W/2, SCREEN_H/2, SCREEN_W/4, SCREEN_W/4, colorGold);
        wstawPunkty(SCREEN_W/2, SCREEN_H/2, SCREEN_W/3, SCREEN_W/3, colorPink);
        wstawPunkty(SCREEN_W/2, SCREEN_H/2, SCREEN_W/2.05, SCREEN_W/2.05, colorAqua);

        //drawAnElipse(SCREEN_W/2, SCREEN_H/2, SCREEN_W/10, SCREEN_W/10, &elipseOfMerkury, colorRed);
        //drawAnElipse(SCREEN_W/2, SCREEN_H/2, SCREEN_W/9, SCREEN_W/9, &elipseOfWenus, colorBlue);
        //drawAnElipse(SCREEN_W/2, SCREEN_H/2, SCREEN_W/8, SCREEN_W/8, &elipseOfZiemia, colorGreen);
        //drawAnElipse(SCREEN_W/2, SCREEN_H/2, SCREEN_W/7, SCREEN_W/7, &elipseOfMars, colorYellow);

        //drawAnElipse(SCREEN_W/2, SCREEN_H/2, SCREEN_W/5, SCREEN_W/5, &elipseOfJowisz, colorYellowGreen);
        //drawAnElipse(SCREEN_W/2, SCREEN_H/2, SCREEN_W/4, SCREEN_W/4, &elipseOfSaturn, colorGold);
        //drawAnElipse(SCREEN_W/2, SCREEN_H/2, SCREEN_W/3, SCREEN_W/3, &elipseOfUran, colorPink);
        //drawAnElipse(SCREEN_W/2, SCREEN_H/2, SCREEN_W/2, SCREEN_W/2, &elipseOfNeptun, colorAqua);





        //multimap<int,int>::iterator itMerkury = elipseOfMerkury.begin();
        //vector<int>::iterator itMerkury = elipseOfMerkury.vectorX.begin();
        //multimap<int,int>::iterator itWenus = elipseOfWenus.begin();
        Planet merkury(4, colorRed);
        Planet wenus(4, colorBlue);
        Planet ziemia(4, colorGreen);
        Planet mars(4, colorYellow);
        Planet jowisz(10, colorYellowGreen);
        Planet saturn(8, colorGold);
        Planet uran(6, colorPink);
        Planet neptun(5, colorAqua);

        mapToVector(elipseOfMerkury, elipseOfMerkuryPoint);
        mapToVector(elipseOfWenus, elipseOfWenusPoint);
        mapToVector(elipseOfZiemia, elipseOfZiemiaPoint);
        mapToVector(elipseOfMars, elipseOfMarsPoint);
        mapToVector(elipseOfJowisz, elipseOfJowiszPoint);
        mapToVector(elipseOfSaturn, elipseOfSaturnPoint);
        mapToVector(elipseOfUran, elipseOfUranPoint);
        mapToVector(elipseOfNeptun, elipseOfNeptunPoint);
        int iMerkury=0;
        int iWenus=0;
        int iZiemia=0;
        int iMars=0;
        int iJowisz=0;
        int iSaturn=0;
        int iUran=0;
        int iNeptun=0;

        bool poused = false;


        while(!key[ KEY_ESC ] )
        {
            while(speed>0)
            {
                if(poused == false)
                {
                clear_to_color(planetBMP, makecol(255,0,255));//kolor ró¿owy nie jest kopiowany przez funkcjê masked_blit
                //cout<<"nr. "<<iMerkury<<"  "<<elipseOfMerkuryPoint.vectorX.at(iMerkury)<<":"<<elipseOfMerkuryPoint.vectorY.at(iMerkury)<<endl;

                merkury.setNewXY(elipseOfMerkuryPoint.vectorX.at(iMerkury),elipseOfMerkuryPoint.vectorY.at(iMerkury));
                wenus.setNewXY(elipseOfWenusPoint.vectorX.at(iWenus), elipseOfWenusPoint.vectorY.at(iWenus));
                ziemia.setNewXY(elipseOfZiemiaPoint.vectorX.at(iZiemia), elipseOfZiemiaPoint.vectorY.at(iZiemia));
                mars.setNewXY(elipseOfMarsPoint.vectorX.at(iMars), elipseOfMarsPoint.vectorY.at(iMars));
                jowisz.setNewXY(elipseOfJowiszPoint.vectorX.at(iJowisz), elipseOfJowiszPoint.vectorY.at(iJowisz));
                saturn.setNewXY(elipseOfSaturnPoint.vectorX.at(iSaturn), elipseOfSaturnPoint.vectorY.at(iSaturn));
                uran.setNewXY(elipseOfUranPoint.vectorX.at(iUran), elipseOfUranPoint.vectorY.at(iUran));
                neptun.setNewXY(elipseOfNeptunPoint.vectorX.at(iNeptun), elipseOfNeptunPoint.vectorY.at(iNeptun));

                rysujElipsy();
                blit(gwiazdy, bufor, 0,0,0,0, SCREEN_W, SCREEN_H);
                masked_blit(elipsyBMP, bufor, 0,0,0,0, SCREEN_W, SCREEN_H);
                masked_blit(planetBMP, bufor, 0,0,0,0, SCREEN_W, SCREEN_H);


                myszka();
                showInf(mx, my);

                blit(bufor, screen, 0,0,0,0, SCREEN_W, SCREEN_H);

                if(mouse_b & 1)
                {
                    poused = true;

                }

                iMerkury++;
                iWenus++;
                iZiemia++;
                iMars++;
                iJowisz++;
                iSaturn++;
                iUran++;
                iNeptun++;

                sprawdzCzyZerowac(iMerkury, iWenus, iZiemia, iMars, iJowisz, iSaturn, iUran, iNeptun);

                clear_to_color(bufor, colorBlack);
                }
                else
                {
                rysujElipsy();
                blit(gwiazdy, bufor, 0,0,0,0, SCREEN_W, SCREEN_H);
                masked_blit(elipsyBMP, bufor, 0,0,0,0, SCREEN_W, SCREEN_H);
                masked_blit(planetBMP, bufor, 0,0,0,0, SCREEN_W, SCREEN_H);


                myszka();
                showInf(mx, my);

                blit(bufor, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
                    if(mouse_b & 2)
                        poused = false;
                }
                speed--;
            }

        }


    }

    void showInf(int mx, int my)
    {
        int color = getpixel(screen, mx, my);
        if(color == colorRed)
        {
            textprintf_ex( bufor, font, 5, 5, makecol( 200, 200, 200 ), -1, "Merkury");
            textprintf_ex( bufor, font, 5, 15, makecol( 200, 200, 200 ), -1, "Srednica równikowa: 4 879km");
            textprintf_ex( bufor, font, 5, 25, makecol( 200, 200, 200 ), -1, "Odległość od słońca: 57 909km");
            textprintf_ex( bufor, font, 5, 35, makecol( 200, 200, 200 ), -1, "Czas obiegu: 88 dni");
            textprintf_ex( bufor, font, 5, 45, makecol( 200, 200, 200 ), -1, "Księżyce: 0");
        }
        else if(color == colorBlue)
        {
            textprintf_ex( bufor, font, 5, 5, makecol( 200, 200, 200 ), -1, "Wenus");
            textprintf_ex( bufor, font, 5, 15, makecol( 200, 200, 200 ), -1, "Srednica równikowa: 12 104km");
            textprintf_ex( bufor, font, 5, 25, makecol( 200, 200, 200 ), -1, "Odległość od słońca: 108 208km");
            textprintf_ex( bufor, font, 5, 35, makecol( 200, 200, 200 ), -1, "Czas obiegu: 225 dni");
            textprintf_ex( bufor, font, 5, 45, makecol( 200, 200, 200 ), -1, "Księżyce: 0");
        }
        else if(color == colorGreen)
        {
            textprintf_ex( bufor, font, 5, 5, makecol( 200, 200, 200 ), -1, "Ziemia");
            textprintf_ex( bufor, font, 5, 15, makecol( 200, 200, 200 ), -1, "Srednica równikowa: 12 756km");
            textprintf_ex( bufor, font, 5, 25, makecol( 200, 200, 200 ), -1, "Odległość od słońca: 149 597km");
            textprintf_ex( bufor, font, 5, 35, makecol( 200, 200, 200 ), -1, "Czas obiegu: 365 dni");
            textprintf_ex( bufor, font, 5, 45, makecol( 200, 200, 200 ), -1, "Księżyce: 1");
        }
        else if(color == colorYellow)
        {
            textprintf_ex( bufor, font, 5, 5, makecol( 200, 200, 200 ), -1, "Mars");
            textprintf_ex( bufor, font, 5, 15, makecol( 200, 200, 200 ), -1, "Srednica równikowa: 6 805km");
            textprintf_ex( bufor, font, 5, 25, makecol( 200, 200, 200 ), -1, "Odległość od słońca: 227 936km");
            textprintf_ex( bufor, font, 5, 35, makecol( 200, 200, 200 ), -1, "Czas obiegu: 687 dni");
            textprintf_ex( bufor, font, 5, 45, makecol( 200, 200, 200 ), -1, "Księżyce: 2");
        }
        else if(color == colorYellowGreen)
        {
            textprintf_ex( bufor, font, 5, 5, makecol( 200, 200, 200 ), -1, "Jowisz");
            textprintf_ex( bufor, font, 5, 15, makecol( 200, 200, 200 ), -1, "Srednica równikowa: 142 984km");
            textprintf_ex( bufor, font, 5, 25, makecol( 200, 200, 200 ), -1, "Odległość od słońca: 778 412km");
            textprintf_ex( bufor, font, 5, 35, makecol( 200, 200, 200 ), -1, "Czas obiegu: 4 333 dni");
            textprintf_ex( bufor, font, 5, 45, makecol( 200, 200, 200 ), -1, "Księżyce: 67");
        }
        else if(color == colorGold)
        {
            textprintf_ex( bufor, font, 5, 5, makecol( 200, 200, 200 ), -1, "Saturn");
            textprintf_ex( bufor, font, 5, 15, makecol( 200, 200, 200 ), -1, "Srednica równikowa: 120 536km");
            textprintf_ex( bufor, font, 5, 25, makecol( 200, 200, 200 ), -1, "Odległość od słońca: 1 426 725km");
            textprintf_ex( bufor, font, 5, 35, makecol( 200, 200, 200 ), -1, "Czas obiegu: 10 756 dni");
            textprintf_ex( bufor, font, 5, 45, makecol( 200, 200, 200 ), -1, "Księżyce: 62");
        }
        else if(color == colorPink)
        {
            textprintf_ex( bufor, font, 5, 5, makecol( 200, 200, 200 ), -1, "Uran");
            textprintf_ex( bufor, font, 5, 15, makecol( 200, 200, 200 ), -1, "Srednica równikowa: 51 118km");
            textprintf_ex( bufor, font, 5, 25, makecol( 200, 200, 200 ), -1, "Odległość od słońca: 2 870 972km");
            textprintf_ex( bufor, font, 5, 35, makecol( 200, 200, 200 ), -1, "Czas obiegu: 30 707 dni");
            textprintf_ex( bufor, font, 5, 45, makecol( 200, 200, 200 ), -1, "Księżyce: 0");
        }
        else if(color == colorAqua)
        {
            textprintf_ex( bufor, font, 5, 5, makecol( 200, 200, 200 ), -1, "Neptun");
            textprintf_ex( bufor, font, 5, 15, makecol( 200, 200, 200 ), -1, "Srednica równikowa: 49 528km");
            textprintf_ex( bufor, font, 5, 25, makecol( 200, 200, 200 ), -1, "Odległość od słońca: 4 498 252km");
            textprintf_ex( bufor, font, 5, 35, makecol( 200, 200, 200 ), -1, "Czas obiegu: 60 223 dni");
            textprintf_ex( bufor, font, 5, 45, makecol( 200, 200, 200 ), -1, "Księżyce: 14");
        }
        else if(color == colorOrange)
        {
            textprintf_ex( bufor, font, 5, 5, makecol( 200, 200, 200 ), -1, "Słońce");
            textprintf_ex( bufor, font, 5, 15, makecol( 200, 200, 200 ), -1, "Srednica równikowa: 1 392 000km");

        }
    }

    void sprawdzCzyZerowac(int &iMerkury, int &iWenus, int &iZiemia, int &iMars, int &iJowisz, int &iSaturn, int &iUran, int &iNeptun)
    {
        if(iMerkury>=elipseOfMerkury.size())
            iMerkury=0;
        if(iWenus>=elipseOfWenus.size())
            iWenus=0;
        if(iZiemia>=elipseOfZiemia.size())
            iZiemia=0;
        if(iMars>=elipseOfMars.size())
            iMars=0;
        if(iJowisz>=elipseOfJowisz.size())
            iJowisz=0;
        if(iSaturn>=elipseOfSaturn.size())
            iSaturn=0;
        if(iUran>=elipseOfUran.size())
            iUran=0;
        if(iNeptun>=elipseOfNeptun.size())
            iNeptun=0;
    }

    void mapToVector(multimap<int,int> &mapa, Point2D &point2d) //przepisywanie mapy do vectora w dobrej kolejnosci i sortowanie prawej czesci elipsy
    {
        int greaterX=0;
        int countGreaterX=0;
        int positionFirstGreaterX=0;
        multimap<int,int>::iterator it;
        vector<int>::iterator itVector;

        for(it=mapa.begin(); it!=mapa.end(); it++)
        {
            if(it->first>greaterX)
                greaterX=it->first;
            point2d.vectorX.push_back(it->first);
            point2d.vectorY.push_back(it->second);
            it++;
            if(it==mapa.end())
                break;
        }
        it=mapa.end();
        it--;
        for(it; it!=mapa.begin(); it--)
        {

            point2d.vectorX.push_back(it->first);
            point2d.vectorY.push_back(it->second);
            it--;
            if(it==mapa.begin())
                break;

        }

        for(it=mapa.begin(); it!=mapa.end(); it++) //zliczanie ile jest najwiêkszych X
        {
            if(it->first == greaterX)
                countGreaterX++;
        }
        for(itVector=point2d.vectorX.begin(); itVector!=point2d.vectorX.end(); itVector++)//pozycja pierwszego najwiekszego Xa
        {

            if(*itVector == greaterX)
                break;
            positionFirstGreaterX++;
        }
        sort(point2d.vectorY.begin()+positionFirstGreaterX-90, point2d.vectorY.begin()+positionFirstGreaterX+countGreaterX+90);

    }


    void rysujElipsy()
    {
        clear_to_color(elipsyBMP, makecol(255,0,255));
        circle(elipsyBMP, SCREEN_W/2, SCREEN_H/2, SCREEN_W/10, colorRed);
        circle(elipsyBMP,SCREEN_W/2, SCREEN_H/2, SCREEN_W/9, colorBlue);
        circle(elipsyBMP,SCREEN_W/2, SCREEN_H/2, SCREEN_W/8,colorGreen);
        circle(elipsyBMP,SCREEN_W/2, SCREEN_H/2, SCREEN_W/7,colorYellow);
        circle(elipsyBMP,SCREEN_W/2, SCREEN_H/2, SCREEN_W/5, colorYellowGreen);
        circle(elipsyBMP,SCREEN_W/2, SCREEN_H/2, SCREEN_W/4, colorGold);
        circle(elipsyBMP,SCREEN_W/2, SCREEN_H/2, SCREEN_W/3, colorPink);
        circle(elipsyBMP,SCREEN_W/2, SCREEN_H/2, SCREEN_W/2.05, colorAqua);
        circlefill(elipsyBMP, SCREEN_W/2, SCREEN_H/2, SCREEN_W/15, colorOrange);

    }

    void wstawPunkty(int x, int y, int rx, int ry, int color)
    {
        do_ellipse(screen, x, y, rx, ry, color, wstaw);
    }

    void drawAnElipse(int x, int y, int rx, int ry, multimap<int,int> *mapa, int color) //własna funkcja do rysowania elips
    {
        multimap<int,int>::iterator it;
        do_ellipse(screen, x, y, rx, ry, color, wstaw);
        for(it=mapa->begin(); it!=mapa->end(); it++)
        {
            putpixel(screen, it->first, it->second, color);
            it++;
        }
        it=mapa->end();
        it--;
        for(it; it!=mapa->begin(); it--)
        {
            putpixel(screen, it->first, it->second, color);
            it--;
        }
    }

    void floodFill(int x, int y, int colour)
    {
        vectorOfPoints.push_back(x);
        vectorOfPoints.push_back(y);

        while(!vectorOfPoints.empty())
        {
            newY = vectorOfPoints.back();
            vectorOfPoints.pop_back();
            newX = vectorOfPoints.back();
            vectorOfPoints.pop_back();
            putpixel(screen, newX, newY, colour);

            if(getpixel(screen, newX, newY-1) != colorRed)
                if(getpixel(screen, newX, newY-1) != colour)
                {
                    vectorOfPoints.push_back(newX);
                    vectorOfPoints.push_back(newY-1);
                }
            if(getpixel(screen, newX+1, newY) != colorRed)
                if(getpixel(screen, newX+1, newY) != colour)
                {
                    vectorOfPoints.push_back(newX+1);
                    vectorOfPoints.push_back(newY);
                }
            if(getpixel(screen, newX-1, newY) != colorRed)
                if(getpixel(screen, newX-1, newY) != colour)
                {
                    vectorOfPoints.push_back(newX-1);
                    vectorOfPoints.push_back(newY);
                }
            if(getpixel(screen, newX, newY+1) != colorRed)
                if(getpixel(screen, newX, newY+1) != colour)
                {
                    vectorOfPoints.push_back(newX);
                    vectorOfPoints.push_back(newY+1);
                }



        }

    }

    void cutting(int x, int y, int x1, int y1) //prostokat obcinający
    {
        rect(screen, cuttingArea[0], cuttingArea[1], cuttingArea[2], cuttingArea[3], colorRed);
        int pCode1[4] = {0,0,0,0};
        int pCode2[4] = {0,0,0,0};
        int zeroCode[4] = {0,0,0,0};

        if(x < cuttingArea[0])
            pCode1[3] = 1;
        if(x > cuttingArea[2])
            pCode1[2] = 1;
        if(y > cuttingArea[3])
            pCode1[1] = 1;
        if(y < cuttingArea[1])
            pCode1[0] = 1;

        if(x1 < cuttingArea[0])
            pCode2[3] = 1;
        if(x1 > cuttingArea[2])
            pCode2[2] = 1;
        if(y1 > cuttingArea[3])
            pCode2[1] = 1;
        if(y1 < cuttingArea[1])
            pCode2[0] = 1;

        cout<<"pCode1: "<<pCode1[0]<<", "<<pCode1[1]<<", "<<pCode1[2]<<", "<<pCode1[3]<<endl;
        cout<<"pCode2: "<<pCode2[0]<<", "<<pCode2[1]<<", "<<pCode2[2]<<", "<<pCode2[3]<<endl;

        if((memcmp(pCode1, zeroCode, sizeof(pCode1)) == 0) && (memcmp(pCode2, zeroCode, sizeof(pCode2)) == 0))
        {
            line(screen, x, y, x1, y1, colorGreen);
            return;
        }
        else
        {
            int pCodeAnd[4] = {pCode1[0]&pCode2[0], pCode1[1]&pCode2[1], pCode1[2]&pCode2[2], pCode1[3]&pCode2[3]};
            if(memcmp(pCodeAnd, zeroCode, sizeof(pCodeAnd)) != 0)
            {
                line(screen, x,y,x1,y1, colorRed);
                return;
            }
            else
            {
                if(memcmp(pCode1, zeroCode, sizeof(pCode1))==0)
                {
                    int tmp = x;
                    x = x1;
                    x1 = tmp;
                    tmp = y;
                    y = y1;
                    y1 = tmp;

                    int tmpTab[4];
                    memcpy(tmpTab, pCode1, sizeof(pCode1));
                    memcpy(pCode1, pCode2, sizeof(pCode2));
                    memcpy(pCode2, tmpTab, sizeof(tmp));
                }

                if(pCode1[3] == 1)
                {
                    int tmpy = y;
                    int tmpx = x;
                    y = y+(cuttingArea[0]-x)*(y1-y)/(x1-x);
                    x = cuttingArea[0];
                    line(screen, tmpx, tmpy, cuttingArea[0], y, colorRed);
                    cutting(x, y, x1, y1);
                }
                if(pCode1[2] == 1)
                {
                    int tmpx = x;
                    int tmpy = y;
                    y=y+(cuttingArea[2]-x)*(y1-y)/(x1-x);
                    x = cuttingArea[2];
                    line(screen, cuttingArea[2], y, tmpx, tmpy,colorRed);
                    cutting(x,y,x1,y1);
                }
                if(pCode1[1] == 1)
                {
                    int tmpx = x;
                    int tmpy = y;
                    x=x+(cuttingArea[3]-y)*(x1-x)/(y1-y);
                    y = cuttingArea[3];
                    line(screen, tmpx, tmpy, x, y,colorRed);
                    cutting(x,y,x1,y1);
                }
                if(pCode1[0] == 1)
                {
                    int tmpx = x;
                    int tmpy = y;
                    x=x+(cuttingArea[1]-y)*(x1-x)/(y1-y);
                    y = cuttingArea[1];
                    line(screen, tmpx, tmpy, x, y,colorRed);
                    cutting(x,y,x1,y1);
                }
            }

        }



    }

    void init()
    {
        allegro_init();
        set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
        install_keyboard();
    }

    void init(bool windowed, int resolution)
    {

        allegro_init();
        set_color_depth(32);
        if(windowed)
        {
            switch(resolution)
            {
            case 1:
                set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 800,0,0);
                break;
            case 2:
                set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480,0,0);
                break;
            }

        }
        if(windowed == false)
        {
            set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 1920,1080,0,0);
        }

        install_keyboard();
        install_timer();
        install_mouse();
        show_mouse(screen);
        unscare_mouse();

        install_int_ex( increment_speed, BPS_TO_TIMER( FPS ) );
    }
};

int main()
{

    Engine engine;


    return 0;
}
END_OF_MAIN()
