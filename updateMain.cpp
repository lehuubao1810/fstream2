#include<iostream>
#include<fstream>

using namespace std;
fstream file;
struct game {
    char name[20];
    int id ;
};

void ghi_File(game x)
{
    file.open("QLGAME.DAT",ios::app);
    file<<x.name<<"\n"<<x.id<<endl;
    file.close();
}


void xuat_File(game x)
{
    file.open("QLGAME.DAT",ios::in);
    file>>x.name>>x.id;
    while(!file.eof())
    {
        cout<<"Name: "<<x.name<<endl;
        cout<<"ID: "<<x.id<<endl;
        file>>x.name>>x.id;
    }
    file.close();
}

int main() {
    game x;
    cout<<"Nhap ten :";cin>> x.name;
    cout<<"Nhap id :";cin>> x.id;
    ghi_File(x);
    xuat_File(x);
    return 0;
}
