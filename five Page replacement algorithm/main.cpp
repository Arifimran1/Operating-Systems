#include <iostream>
#include <bits/stdc++.h>
#include <string.h>
#include <conio.h>

using namespace std;

struct frame_type
{
    int name;
    int mod;
    int ref;
    int level;
};

frame_type * frame = new frame_type[100];
int seq[100];
int num_frame;
int fault;
int num_seq;

void input()
{
    cout << "Enter the number of Frame: " << endl;

    cin >> num_frame;

    cout << "Enter the number of sequence: " << endl;
    cin >> num_seq;

    cout << "Enter the input sequence:" << endl;
         for(int i = 0; i < num_seq; i++)
             cin >> seq[i];
    seq[num_seq] = -1;

    for(int i = 0; i < num_frame; i++)
        frame[i].name = -1;

}

void draw()
{
    cout << "frame:" << endl;
    for(int i = 0; i < num_frame; i++)
    {
        if(frame[i].name == -1)
            cout << "- x " ;
        else
            cout << "- " << frame[i].name << " ";
    }
    cout << "-" << endl;

}
int find(int a)
{
    for(int i = 0; i < num_frame; i++)
    {
        if(a == frame[i].name)
            return i;

    }
    return -1;
}
int high_level()
{
    int m;
    m = 0;

    for(int i = 1; i < num_frame; i++)
    {

        if(frame[m].level < frame[i].level)
        {
            m = i;
        }

    }
    return m;
}

void Optimal()
{
    fault = 0;

    input();

    for(int i = 0; i < num_seq; i++)
    {

        if(find(seq[i]) == -1)
        {
            fault++;
            int index = find(-1);
            if(index == -1)
            {
                cout << "For input level:" << endl;
                for(int j = 0; j < num_frame; j++)
                {
                    cout << "for " << frame[j].name << ": ";
                    cin >> frame[j].level;

                }

                int r = high_level();
                frame[r].name = seq[i];

            }
            else
            {
                frame[index].name = seq[i];
            }


        }

        draw();

    }

    cout << "Page fault is: " << fault << endl;


}

int low_priority()
{
    int m;
    m = -1;

    for(int j = 0; j < 4; j++)
    {
        for(int i = 0; i < num_frame; i++)
        {
            if((frame[i].ref * 2 + frame[i].mod) == j)
            {
                m = i;
                break;
            }

        }
        if(m > -1)
            break;
    }

    return m;
}


void NRU()
{
    fault = 0;

    input();

    for(int i = 0; i < num_seq; i++)
    {

        if(find(seq[i]) == -1)
        {
            fault++;
            int index = find(-1);
            if(index == -1)
            {
                cout << "For input reference and modification:" << endl;
                for(int j = 0; j < num_frame; j++)
                {
                    cout << "for " << frame[j].name << ": ";
                    cin >> frame[j].ref >> frame[j].mod;

                }

                int r = low_priority();
                frame[r].name = seq[i];

            }
            else
            {
                frame[index].name = seq[i];
            }


        }

        draw();

    }

    cout << "Page fault is: " << fault << endl;

}

void FIFO()
{

    fault = 0;

    input();

    for(int i = 0; i < num_seq; i++)
    {

        if(find(seq[i]) == -1)
        {
            fault++;
            int index = find(-1);
            if(index == -1)
            {
                for(int j = 0; j < num_frame-1; j++)
                {
                    frame[j].name = frame[j+1].name;

                }
                frame[num_frame-1].name = seq[i];

            }
            else
            {
                frame[index].name = seq[i];
            }


        }

        draw();

    }

    cout << "Page fault is: " << fault << endl;

}

int refWise()
{
    int m;
    m = -1;

    for(int j = 0; j < 2; j++)
    {
        for(int i = 0; i < num_frame; i++)
        {
            if(frame[i].ref == 1)
            {
                frame[i].ref = 0;
            }
            else
            {
                m = i;
                break;

            }

        }
        if(m > -1)
            break;
    }

    return m;
}

void SecondChance()
{
    fault = 0;

    input();

    for(int i = 0; i < num_seq; i++)
    {

        if(find(seq[i]) == -1)
        {
            fault++;
            int index = find(-1);
            if(index == -1)
            {
                cout << "For input reference:" << endl;
                for(int j = 0; j < num_frame; j++)
                {
                    cout << "for " << frame[j].name << ": ";
                    cin >> frame[j].ref;

                }

                int r = refWise();
                for(int j = r; j < num_frame-1; j++)
                {
                    frame[j].name = frame[j+1].name;

                }
                frame[num_frame-1].name = seq[i];

            }
            else
            {
                frame[index].name = seq[i];
            }

        }

        draw();

    }

    cout << "Page fault is: " << fault << endl;
}

int refWiseClock(int a)
{
    int m;
    m = -1;

    for(int j = 0; j < 2; j++)
    {
        for(int i = a; i < num_frame; i++)
        {
            if(frame[i].ref == 1)
            {
                frame[i].ref = 0;
            }
            else
            {
                m = i;
                break;

            }

        }
        if(m > -1)
            break;
    }

    return m;
}

void ClockPage()
{
    fault = 0;

    input();

    int indicator = 0;

    for(int i = 0; i < num_seq; i++)
    {


        if(find(seq[i]) == -1)
        {
            //cout << "ind: " << indicator << endl;
            fault++;
            int index = find(-1);
            if(index == -1)
            {
                cout << "For input reference:" << endl;
                for(int j = 0; j < num_frame; j++)
                {
                    cout << "for " << frame[j].name << ": ";
                    cin >> frame[j].ref;

                }

                int r = refWiseClock(indicator);

                frame[r].name = seq[i];
                indicator = r;

            }
            else
            {
                frame[index].name = seq[i];
                indicator = index;
            }

        }

        draw();

    }

    cout << "Page fault is: " << fault << endl;
}


int main()
{
    int num1;
    while(1)
    {
        system("cls");
        cout << "1. Optimal Page replacement Algorithm" <<endl;
        cout << "2. Not Recently Used replacement Algorithm" <<endl;
        cout << "3. FIFO replacement Algorithm" <<endl;
        cout << "4. Second Chance page replacement Algorithm" <<endl;
        cout << "5. Clock Page replacement Algorithm" <<endl;
        cout << "Enter the number:" <<endl;
        cin >> num1;

        if(num1 == 1)
            Optimal();
        else if(num1 == 2)
            NRU();
        else if(num1 == 3)
            FIFO();
        else if(num1 == 4)
            SecondChance();
        else if(num1 == 5)
            ClockPage();
        else
            break;
        getch();
    }



    return 0;
}
