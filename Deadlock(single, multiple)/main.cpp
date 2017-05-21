#include <iostream>

using namespace std;


void single()
{
    int total;
    int graph[100][100];
    int indicator[100];
    int temp[110];
    int value;
    int dead[100];
    int proc[100];



    cout << "Enter total number of process and resource(s): " << endl;
    cin >> total;
    cout << "input the process(s) or resource(s) requesting and holding value respectively:(-1 to terminate)" << endl;

    for(int i = 0; i < total; i++)
    {
        cout << "for vartex " << i << ": ";
        for(int j = 0; j < total+1; j++)
        {
            cin >> value;
            graph[i][j] = value;
            if(value == -1)
                break;

        }
    }

    for(int j = 0; j < total; j++)
    {
        dead[j] = 0;
        proc[j] = 0;
    }

    cout << "input the name value that are process(s)(-1 to terminate):" << endl;

    while(1)
    {
        cin >> value;
        if(value == -1)
            break;

        proc[value] = 1;

    }

    int ddlck = 0;

    for(int i = 0; i < total; i++) ///find each node
    {
        for(int j = 0; j < total; j++) ///initial point is zero
        {
            indicator[j] = 0;
        }

        int m = 0;
        temp[m] = i; ///store like stack L
        m++;
        int n = 0;

        while(m != 0 && n == 0)
        {
            if(graph[temp[m-1]][indicator[temp[m-1]]] != -1)
            {
                temp[m] = graph[temp[m-1]][indicator[temp[m-1]]];
                indicator[temp[m-1]]++;
                m++;

                int j;

                for(j = 0; j < m-1 ; j++)
                {
                    if((temp[j] == temp[m-1]) && ((m-1) != 0))
                    {

                        for(int jj = j; jj < m; jj++)
                        {
                            dead[temp[jj]] = 1;
                            //cout << i << " " << temp[jj] << " " << temp[m] << endl;

                        }
                        n = 1;
                        ddlck = 1;
                        break;

                    }
                }
            }
            else
            {
                temp[m-1] = -1;
                m--;
            }

            if(n == 1)
                break;

        }



    }

    if(ddlck == 1)
    {
        cout << "deadlock detected!! Nodes are: " << endl;
        for(int i = 0; i < total; i++)
        {
            if(dead[i] == 1)
            {
                cout << i << endl;
            }
        }

        cout << "deadlock detected!! process nodes are: " << endl;
        for(int i = 0; i < total; i++)
        {
            if(dead[i] == 1 && proc[i] == 1)
            {
                cout << i << endl;
            }
        }
    }
    else
        cout << "deadlock undetected!!" << endl;





}

void multiple()
{
    int total_resource[100];
    int available[100];
    int request[100][100];
    int carry[100][100];
    int num_res;
    int num_pro;
    int completed[100];

    cout << "Enter the number of resource(s)and process(s): " << endl;
    cin >> num_res >> num_pro;

    cout << "Enter the total resource instance(s): " << endl;
    for(int i = 0; i < num_res; i++)
    {
        ///cout << "for resource " << i << ": " ;
        cin >> total_resource[i] ;

    }




    cout << "Enter the process(s) holding resource instance(s) respectively: " << endl;
    for(int i = 0; i < num_pro; i++)
    {
        cout << "for process " << i << ": " << endl;

        for(int j = 0; j < num_res; j++)
        {
            ///cout << "for resource " << j << ": " ;
            cin >>  carry[i][j];
        }

    }

    for(int i = 0; i < num_res; i++)
    {
        int sum = 0;
        for(int j = 0; j< num_pro; j++)
        {
            sum += carry[j][i];
        }
        available[i] = total_resource[i] - sum;

    }

    cout << "Enter the process(s) requesting resource instance(s) respectively: " << endl;
    for(int i = 0; i < num_pro; i++)
    {
        cout << "for process " << i << ": " << endl;

        for(int j = 0; j < num_res; j++)
        {
            /// cout << "for resource " << j << ": " ;
            cin >>  request[i][j];
        }
    }

    for(int i = 0; i < num_pro; i++)
    {
        completed[i] = 0;
    }

    int w = 0;
    for(int k = 0; k < num_pro; k++)
    {
        for(int i = 0; i < num_pro; i++)
        {
            w = 0;
            if(completed[i] == 0)
            {
                for(int j = 0; j < num_res; j++)
                {
                    if(request[i][j] <= available[j])
                        w++;
                }

                if(w == num_res)
                {
                    completed[i] = 1;
                    for(int j = 0; j < num_res; j++)
                    {
                        available[j] += carry[i][j];
                        request[i][j] = 0;

                    }
                }
            }
        }
    }

    int m = -1;
    for(int i = 0; i < num_pro; i++)
    {
        if(completed[i] == 0)
        {
            m = i;
            break;
        }

    }

    if(m == -1)
        cout << "Deadlock undetected in process." << endl;
    else
    {
        cout << "Deadlock detected in process:" << endl;
        for(int i = 0; i < num_pro; i++)
        {
            if(completed[i] == 0)
            {
                cout << i << endl;

            }
        }

    }

}


int main()
{

    ///multiple();
    single();



    return 0;
}
