#include<iostream>
#include<fstream>
abcd 
using namespace std;

struct game {
    char name[20];
    int id ;
};

void ghi_File(std::fstream file,game &x)
{
    file.open("QLGAME.DAT",ios::app);
    file<<x.name<<"\n"<<x.id<<endl;
    file.close();
}

void doc_File(fstream file,game x)
{
    file.open("QLGAME.DAT",ios::in);
    file>>x.name>>x.id;
}
void xuat_File(fstream file,game x)
{
    while(!file.eof()) {
        cout<<"Name: "<<x.name<<endl;
        cout<<"ID: "<<x.id<<endl;
        file.close();
    }
}

int main() {
    fstream file;
    game x;
    cout<<"Nhap ten :";cin>> x.name;
    cout<<"Nhap id :";cin>> x.id;
    ghi_File(file,x);
    return 0;
}
