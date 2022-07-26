#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <vector>
using namespace std;
vector<int> y_card;
vector<string> y_F;
vector<string> en_F;
vector<int> en_card;
vector<int> card;
string F[4] = {"黑桃", "紅心", "鑽石", "梅花"};
int y_sum, en_sum, A_num, enA_num;
void print()
{
    cout<<"你的點數為: ";
    for (int p = 0; p < y_card.size(); p++)
    {
        cout<<y_F[p];
        if (y_card[p] == 1) cout<<'A'<<" ";
        else cout<<y_card[p]<<" ";
    }
    cout<<endl<<"EN的點數為: ";
    for (int p = 0; p < en_card.size(); p++)
    {
        cout<<en_F[p];
        if (en_card[p] == 1) cout<<'A'<<" ";
        else cout<<en_card[p]<<" ";
    }
    cout<<endl;

}
int count_()
{
    y_sum = 0;
    en_sum = 0;
    for (int p = 0; p < y_card.size(); p++) y_sum += y_card[p];
    for (int p = 0; p < en_card.size(); p++) en_sum += en_card[p];
    for (int p = 0; p < A_num; p++)
    {
        if ((y_sum + 10) <= 21) y_sum += 10;
    }
    for (int p = 0; p < enA_num; p++)
    {
        if ((en_sum + 10) <= 21) en_sum += 10;
    }
}
int en()
{
    int y;
    do
    {
        srand(10*time(NULL));
        y = rand()%52;
    }while(card[y] == 0);

    en_F.push_back(F[y/13]);

    if (card[y] == 1) enA_num++;
    if (card[y] >= 10) en_card.push_back(10);
    else en_card.push_back(card[y]);

    card[y] = 0;

}
int you()
{
    int x;
    do
    {
        srand(time(NULL));
        x = rand()%52;
    }while(card[x] == 0);

    cout<<F[x/13];
    y_F.push_back(F[x/13]);

    if (card[x] == 1)
    {
        cout<<"A"<<endl;
        A_num++;
    }
    else cout<<card[x]<<endl;

    if (card[x] >= 10) y_card.push_back(10);
    else y_card.push_back(card[x]);

    card[x] = 0;
}
char determine_21(int &m, int a)
{
    count_();
    if (y_sum > 21 && en_sum > 21)
    {
        cout<<"平局! 兩方皆爆牌 你的總和: "<<y_sum<<" EN的總和: "<<en_sum<<endl;
        print();
        m += a;
        Sleep(1000);
        return '0';
    }
    if (y_sum > 21)
    {
        cout<<"很可惜 你爆牌了 你的總和: "<<y_sum<<endl;
        print();

        Sleep(1000);
        return '0';
    }
    if (en_sum > 21)
    {
        cout<<"你贏了 EN爆牌了 他的總和: "<<en_sum<<endl;
        print();
        m += (2*a);
        Sleep(1000);
        return '0';
    }
}
void game()
{
    char yn;
    cout<<"=發牌時刻= 選擇跟牌還是停牌?(y or n)"<<endl;
    c : cin>>yn;
    if (yn != 'y' && yn != 'n')
    {
        cout<<"輸入錯誤!請輸入y or n: ";
        goto c;
    }
    if (yn == 'y')
    {
        cout<<"你拿到: ";
        you();
        Sleep(500);
    }
    cout<<"接著換EN進行選擇"<<endl;
    Sleep(1000);
    if (en_sum >= 15 && en_sum < 21)
    {
        srand(5*time(NULL));
        int y_n = rand()%5;
        if (y_n == 0)
        {
            cout<<"等待EN拿牌..."<<endl;
            Sleep(1000);
            en();
        }
        else cout<<"EN決定停牌"<<endl;

    }
    else
    {
        cout<<"等待EN拿牌..."<<endl;
        Sleep(1000);
        en();
    }


}
void re()
{
    y_sum = 0;
    en_sum = 0;
    A_num = 0;
    enA_num = 0;
    y_card.clear();
    en_card.clear();
    y_F.clear();
    en_F.clear();
    card = {1,2,3,4,5,6,7,8,9,10,11,12,13,
            1,2,3,4,5,6,7,8,9,10,11,12,13,
            1,2,3,4,5,6,7,8,9,10,11,12,13,
            1,2,3,4,5,6,7,8,9,10,11,12,13};

}
void compare(int &m, int a)
{
    count_();
    if (y_sum > en_sum)
    {
        cout<<"你贏了! ";
        m += (2*a);
    }
    else if (y_sum == en_sum)
    {
        cout<<"平手! ";
        m += a;
    }
    else cout<<"你輸了! ";
    cout<<"你的總和: "<<y_sum<<" EN的總和: "<<en_sum<<endl;
    print();
}
int main()
{
    int money = 250;
    cout<<"歡迎來到EN's Blackjack~~~"<<endl;
    cout<<"已為您充值250$"<<endl;
    while(true)
    {
        char n;
        cout<<"===EN's Blackjack==="<<endl;
        Sleep(500);
        cout<<"玩一把嗎?(y or n)  剩餘金額: "<<money<<"$"<<endl;
        a : cin>>n;
        if (n != 'y' && n != 'n')
        {
            cout<<"輸入錯誤!請輸入y or n: ";
            goto a;
        }

        if (n == 'n') break;
        int bet;
        cout<<"你要下注多少?"<<endl;
        b : cin>>bet;
        if ((money-bet) < 0 || bet <= 0)
        {
            cout<<"(金額不足或輸入錯誤!) 請重新下注: ";
            goto b;
        }
        money -= bet;

        re();
        cout<<"正在開啟新的一局..."<<endl;
        Sleep(1000); //1s
        int i;
        system("cls");
        for (i = 1; i <= 5; i++)
        {

            cout<<"Round "<<i<<endl;
            game();
            n = determine_21(money, bet);
            if (n == '0') break;
        }
        if (i == 6)
        {
            cout<<"遊戲結束! 結算雙方手牌..."<<endl;
            compare(money, bet);
        }

    }
}
