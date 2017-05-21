#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int cpu_time = 0;
int gantt_chart[1000];
int quantum_time = 0;

struct process
{
    string name;
    int brust_time;
    int arrival_time;
    int wait;
    int turn;
    int rem_exe;
    bool online;
    int previous;
    int priority;
};


void inc_gantt(int a)
{
    gantt_chart[cpu_time] = a;
    cpu_time++;
    gantt_chart[cpu_time] = -2;

}

void inc_gantt()
{
    gantt_chart[cpu_time] = -1;
    cpu_time++;
    gantt_chart[cpu_time] = -2;
}


process * p = new process[100];
int num_pro = 0;


void input()
{
    cout << "enter the number of process(s):" << endl;
    cin >> num_pro;

    cout << "enter process name, brust time, arrival time, priority respectively" << endl;
    for(int i = 0; i < num_pro; i++)
    {
        cin >> p[i].name >> p[i].brust_time >> p[i].arrival_time >> p[i].priority ;
        p[i].online = false;
        p[i].rem_exe = p[i].brust_time;
        p[i].previous = 0;
    }
    cout << "enter quantum time:" << endl;
    cin >> quantum_time;

}



void FCFS1()
{
    for(int i = 1; i < num_pro; i++)
    {
        p[i].arrival_time -= p[0].arrival_time;
    }
    p[0].arrival_time = 0;
    p[0].online = true;
    int i, k, m;

    for(i = 0; ; i++)///cpu_time
    {
        k = 0; m = 0;
        for(int j = 0; j < num_pro; j++) ///processes
        {
            if(p[j].online == true )
            {
                if( p[j].rem_exe == 0 )
                {
                    p[j].online = false;
                }
                else
                {
                    inc_gantt(j);
                    p[j].rem_exe--;
                }
            }
            else if(p[j].online == false)
            {
                if(p[j].rem_exe > 0)
                {

                    if(p[j].arrival_time <= i)
                    {
                        p[j].online = true;
                        p[j].rem_exe--;
                        inc_gantt(j);
                    } /// code for empty
                    else
                    {
                        m++;
                    }


                }
                else
                    k++;
            }

        }


        if(k == num_pro - 1)
        {
            inc_gantt();
            break;

        }
    }

}

void print_gantt()
{
    cout << endl << "gantt Chart:" << endl;
    cout << "- ";
    for(int i = 0; gantt_chart[i] != -2; i++)
    {
        if (gantt_chart[i] == -1 )
            cout << "x - ";
        else
            cout << p[gantt_chart[i]].name << " - ";
    }
    cout << endl;
}

float avg_wait = 0;
void waiting_time()
{
    p[0].wait = 0;

    int tot_wait = 0;

    for(int i = 0; gantt_chart[i] != -2; i++)
    {
        if( !p[gantt_chart[i]].previous )
        {
            p[gantt_chart[i]].wait = i - p[gantt_chart[i]].arrival_time;
            p[gantt_chart[i]].previous = i;
        }
        else
        {
            p[gantt_chart[i]].wait += i - p[gantt_chart[i]].previous - 1;
            p[gantt_chart[i]].previous = i;
        }
    }

    if(gantt_chart[0] == gantt_chart[1])
        p[gantt_chart[0]].wait--;

    for(int i = 0; i < num_pro; i++)
    {
        tot_wait += p[i].wait;
    }

    avg_wait = (float)tot_wait / num_pro;

    cout << endl << "Waiting time: " << endl;
    for(int i = 0; i < num_pro; i++)
        cout << p[i].name <<": " << p[i].wait << endl;
    cout << "avarage waiting time: " << avg_wait << endl;

}

float avg_turn = 0;
void turn_around_time()
{
    int turn = 0;
    for(int i = 0; i < num_pro; i++)
    {
        p[i].turn = p[i].brust_time + p[i].wait;
    }

    cout << endl << "Turn arround time: " << endl;
    for(int i = 0; i < num_pro; i++)
    {
        cout << p[i].name <<": " << p[i].turn << endl;
        turn += p[i].turn;
    }
    avg_turn = (float)turn / num_pro;
    cout << "avarage turn arround time: " << avg_turn << endl;
}

float throug = 0;
void throughput()
{
    for(int i = 0; i < num_pro; i++)
        throug += p[i].brust_time;
    cout << endl << "throughput is: " << num_pro/throug << endl;
}

void showAll()
{
    print_gantt();

    waiting_time();

    turn_around_time();

    throughput();

}

void refill()
{
    cpu_time = 0;

    for(int i = 0; i < num_pro; i++)
    {
        p[i].rem_exe = p[i].brust_time;
        p[i].previous = 0;
        p[i].online = false;
    }

    avg_wait = 0;
    avg_turn = 0;
    throug = 0;
}


bool wayToSortFCFS(const process la, const process ra)
{
    return la.arrival_time < ra.arrival_time;
}

void FCFS()
{
    refill();
    cout << endl << "FCFS Started Here:" << endl;

    sort(p, p + num_pro, wayToSortFCFS);

    for(int i = 1; i < num_pro; i++)
    {
        p[i].arrival_time -= p[0].arrival_time;
    }
    p[0].arrival_time = 0;
    p[0].online = true;



    for(int j = 0; j < num_pro; j++)
    {
        while( p[j].rem_exe )
        {
            inc_gantt(j);
            p[j].rem_exe--;
        }
    }

    showAll();

    cout << "FCFS Completed." << endl;
}

bool wayToSortSJFS(const process la, const process ra)
{
    return la.brust_time < ra.brust_time;
}

void SJFS()
{
    refill();
    cout << endl <<  "SJFS Started Here:" << endl;

    sort(p, p + num_pro, wayToSortSJFS);

    for(int i = 1; i < num_pro; i++)
    {
        p[i].arrival_time -= p[0].arrival_time;
    }
    p[0].arrival_time = 0;
    p[0].online = true;



    for(int j = 0; j < num_pro; j++)
    {
        while( p[j].rem_exe )
        {
            inc_gantt(j);
            p[j].rem_exe--;
        }
    }

    showAll();
''
    cout << "SJFS Completed." << endl;
}

bool wayToSortPS(const process la, const process ra)
{
    if(la.arrival_time == ra.arrival_time)
        return la.priority < ra.priority;
    else
        return false;
}

void PriorityS()
{
    refill();
    cout << endl << "Priority Schedule Algorithm Started Here:" << endl;

    sort(p, p + num_pro, wayToSortFCFS);
    sort(p, p + num_pro, wayToSortPS);

    int waited = 0;



    for(int i = 0; i < num_pro; i++)
    {
        waited += p[i].brust_time;

        for(int j = 1; j < num_pro; j++)
        {
            for(int k = j + 1; k < num_pro; k++)
            {
                if(waited > p[j].arrival_time && waited > p[k].arrival_time)
                {
                    if( p[j].priority > p[k].priority)
                        swap(p[j], p[k]);

                }
            }
            waited += p[j].brust_time;

        }
    }


    for(int i = 1; i < num_pro; i++)
    {
        p[i].arrival_time -= p[0].arrival_time;
    }
    p[0].arrival_time = 0;
    p[0].online = true;



    for(int j = 0; j < num_pro; j++)
    {
        while( p[j].rem_exe )
        {
            inc_gantt(j);
            p[j].rem_exe--;
        }
    }

    showAll();

    cout << "Priority Schedule Algorithm Completed." << endl;
}

void RoundRobin()
{
    refill();
    cout << endl << "Round Robin Algorithm Started Here:" << endl;

    sort(p, p + num_pro, wayToSortFCFS);

    int i = 0;

    while(1)
    {
        for(int j = 0; j < num_pro ;j++)
        {
            if(i >= p[j].arrival_time && p[j].rem_exe > 0)
            {
                if( p[j].rem_exe < quantum_time)
                {
                    for(int k = 0; k < p[j].rem_exe; k++)
                        {
                            inc_gantt(j);
                            i++;
                            p[j].rem_exe--;
                        }

                }
                else
                {
                    for(int k = 0; k < quantum_time; k++)
                        {
                            inc_gantt(j);
                            i++;
                            p[j].rem_exe--;
                        }
                }
            }


        }
        int mm = 0;
        for(int ll = 0; ll < num_pro; ll++)
        {
            if( p[ll].rem_exe > 0)
            {
                mm = 1;
                break;
            }
        }
        if(mm == 0)
            break;
    }

    showAll();

    cout << "Round Robin Algorithm Completed." << endl;
}

int main()
{
    input();

    FCFS();
    SJFS();
    PriorityS();
    RoundRobin();


    return 0;
}
