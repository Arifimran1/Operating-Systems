#include <iostream>

using namespace std;

int pro_space;
int ram_space;
int page_space;
int num_page;
int num_frame;
int mem_allo[100];
int log_addr;
int phy_addr;

void input()
{
    cout << "enter process space, page space, ram space respectively(KB): " << endl;
    cin >> pro_space >> page_space >> ram_space;

    int num1;
    num_page = pro_space / page_space;
    num_frame = ram_space / page_space;

    for(int i = 0; i < num_page; i++)
    {
        mem_allo[i] = -1;
    }

    cout << "enter mapping respectively in ram frame(0 - " << num_page - 1 << "): " << endl;
    for (int i = 0; i < num_frame; i++)
    {
        cout << "for frame " << i << ": ";
        cin >> num1;
        mem_allo[num1] = i;
    }


}

int page_addr;

void draw()
{
    cout << "ram:" << endl;
    for(int i = 0; i < num_frame; i++)
    {
        cout << " **************" << endl;
        cout << "|            |" << endl;

        if( mem_allo[page_addr] == (num_frame -i-1))
        {
            cout << "|***** "<< num_frame -i-1 << " ****|" << endl;
        }
        else
            cout << "|      "<< num_frame -i-1 << "     |" << endl;
        cout << "|            |" << endl;
    }
        cout << " **************" << endl;

    cout << endl << "process: " << endl;

    for(int i = 0; i < num_page; i++)
    {
        cout << " **************" << endl;
        cout << "|      "<< num_page -i-1 << "      |" << endl;
        if((num_page-i-1) == page_addr)
        {
            cout << "|***** "<< mem_allo[num_page-i-1] <<" *****|" << endl;

        }
        else
            cout << "|            |" << endl;

    }
        cout << " **************" << endl;

}

void calculation()
{
    cout << "enter the logical address: " << endl;
    cin >> log_addr;

    page_addr = log_addr / page_space;
    int byte_off = log_addr % page_space;

    if(mem_allo[page_addr] != -1)
    {
        phy_addr = mem_allo[page_addr] * page_space + byte_off;
        cout << "Physical Address is: " << phy_addr << endl;

    }
    else
        cout << "page fault detected" << endl;

    draw();

}

int main()
{
    input();


    while(1)
    {
        calculation();

    }

    return 0;
}
