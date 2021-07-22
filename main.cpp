#include <iostream>
#include <iomanip>
#include <string.h>
#include <fstream>
using namespace std;

fstream file;
//Khai báo game struct
struct game
{

    string id;
    char name_game[20];
    char theloai[20];
    float phienban;
    float dungluong;
    float luottai;
    float namsx;
};
//Khai báo các nguyên mẫu hàm (function prototype)
int timvitri(struct game st[],string id, int biendem);
void clean(struct game st[],int deleteitem);

//Hàm để hiện ra menu lựa chọn
void menu(){
    cout<<" "<<endl;
    cout<<"=========================================="<<endl;
    cout<<" MENU "<<"\n";
    cout<<"=========================================="<<endl;
    cout<<" 1. Thêm game mới vào danh sách"<<endl;
    cout<<"2.ghi file"<<endl;
    cout<<"3. doc file"<<endl;
    cout<<" 4. Hiện danh sách tất cả game"<<endl;
    /*cout<<" 2. Xóa game theo ID "<<endl;
    cout<<" 3. Cập nhật, sửa đổi game trong danh sách "<<endl;//cập nhật sửa đổi

    cout<<" 5. Tìm kiếm game theo ID"<<endl;
    cout<<" 6. Sắp xếp game giảm dần theo năm"<<endl;*/
    cout<<" 7. Thoát chương trình"<<endl;
}
//Hàm để thêm 1 game mới vào danh sách
void them_game(struct game st[],int& biendem){

    again:
    cout<<"\nNhập ID của game: ";
    cin>>st[biendem].id;
    if(timvitri(st,st[biendem].id,biendem)!=-1){
        cout<<"ID này đã tồn tại\n";goto again;
    }

    cout<<"Nhập tên của game: ";
    cin>>st[biendem].name_game;
    cout<<"Nhập thể loại game: ";cin>>st[biendem].theloai;
    cout<<"Nhập phiên bản của game: ";cin>>st[biendem].phienban;
    cout<<"Nhập dung lượng của game (MB): ";cin>>st[biendem].dungluong;
    cout<<"Nhập số lượt tải về của game: ";cin>>st[biendem].luottai;
    cout<<"Nhập năm sản xuất của game: ";cin>>st[biendem].namsx;

    ++biendem;


}

//Hàm hiện danh sách tất cả các game
void danhsach(struct game st[], int biendem){
    int i=0;
    cout<<left<<setw(5)<<"ID"<<setw(10)<<"TÊN"<<setw(15)<<"THỂ LOẠI"
        <<setw(15)<<"PHIÊN BẢN"<<setw(15)<<"DUNG LƯỢNG"<<setw(15)<<"LƯỢT TẢI"<<setw(15)<<"NĂM SẢN XUẤT"<<endl;
    cout<<"==============================================\n";
    while(i<=biendem){
        if(st[i].id!=""){
            cout<<left<<setw(5)<<st[i].id<<setw(10)<<st[i].name_game<<setw(15)
                <<st[i].theloai;
            cout<<setw(15)<<st[i].phienban<<setw(12)<<st[i].dungluong<<setw(12)<<st[i].luottai
                <<setw(12)<<st[i].namsx;

            cout<<"\n";}
        i=i+1;

    }


}

//Hàm xóa game theo ID
void xoa_game(struct game st[], int& biendem){
    string id;
    int index;
    if (biendem > 0)
    {
        cout<<"Nhập ID của game: ";
        cin>>id;
        index = timvitri(st, id,biendem);

        if ((index!=-1) && (biendem != 0))
        {
            if (index == (biendem-1)) //Xóa game cuối cùng
            {

                clean(st, index);
                --biendem;

                cout<<"Game đã được xóa.\n";
            }
            else //Xóa game ở giữa
            {
                for (int i = index; i < biendem-1; i++)
                {
                    st[i] = st[i + 1];
                    clean(st, biendem);
                    --biendem ;
                }

            }

        }
        else cout<<"Game không tổn tại. Vui lòng kiểm tra lại ID.\n";


    }
    else cout<<"Không có game nào được xóa\n";
}

//Hàm xóa game được chọn
void clean(struct game st[],int index)
{
    st[index].id ="";
    strcpy(st[index].name_game,"");
    strcpy(st[index].theloai,"");
    st[index].phienban = 0;
    st[index].dungluong = 0;
    st[index].luottai = 0;
    st[index].namsx = 0;


}
void ghi_File(struct game st[],int biendem){
    file.open("QLGAME.DAT",ios::app);
    int i = 0;
    while(i<=biendem){
        if(st[i].id!=""){
            file<<left<<setw(5)<<st[i].id<<setw(15)<<st[i].name_game<<setw(15)
                <<st[i].theloai;
            file<<setw(15)<<st[i].phienban<<setw(12)<<st[i].dungluong<<setw(12)<<st[i].luottai
                <<setw(12)<<st[i].namsx;

            file<<"\n";}
        i=i+1;
    }
    file.close();
}

void doc_File(struct game st[],int biendem) {
    file.open("QLGAME.DAT",ios::in);
    int i = 0;
    while(i<=biendem){
        file>>st[i].id>>st[i].name_game>>st[i].theloai>>st[i].phienban>>st[i].dungluong>>st[i].luottai>>st[i].namsx;
        i=i+1;
    }
    cout<<left<<setw(5)<<"ID"<<setw(10)<<"TÊN"<<setw(15)<<"THỂ LOẠI"
        <<setw(15)<<"PHIÊN BẢN"<<setw(15)<<"DUNG LƯỢNG"<<setw(15)<<"LƯỢT TẢI"<<setw(15)<<"NĂM SẢN XUẤT"<<endl;
    cout<<"==============================================\n";
    while(!file.eof())
    {
        cout<<left<<setw(5)<<st[i].id<<setw(10)<<st[i].name_game<<setw(15)
            <<st[i].theloai;
        cout<<setw(15)<<st[i].phienban<<setw(12)<<st[i].dungluong<<setw(12)<<st[i].luottai
            <<setw(12)<<st[i].namsx;
        while(i<=biendem){
            file>>st[i].id>>st[i].name_game>>st[i].theloai>>st[i].phienban>>st[i].dungluong>>st[i].luottai>>st[i].namsx;
            i=i+1;
        }
    }
    file.close();
}



//Hàm cập nhật sửa đổi game cso trong danh sách
void sua_game(struct game st[],int biendem){
    string id;
    int column_index;
    cout<<"Nhập ID của game: ";
    cin>>id;
    cout<<"Bạn muốn cập nhật phần nào (1-6) ?: ";
    cin>>column_index;

    int index = timvitri(st, id,biendem);

    if (index != -1)
    {
        if (column_index == 1)
        {
            cout<<"Nhập tên của game: ";

            cin>>st[index].name_game;
        }

        else if (column_index == 2)
        {
            cout<<"Nhập thể loại của game: ";
            cin>>st[index].theloai;
        }
        else if (column_index == 3)
        {
            cout<<"Nhập phiên bản của game: ";
            cin>>st[index].phienban;
        }
        else if (column_index == 4)
        {
            cout<<"Nhập dung lương của game: ";
            cin>>st[index].dungluong;
        }
        else if (column_index == 5)
        {
            cout<<"Nhập số lượt tải của game: ";
            cin>>st[index].luottai;
        }
        else if (column_index == 6)
        {
            cout<<"Nhập năm sản xuất của game: ";
            cin>>st[index].namsx;
        }
        else cout<<"Không có mục hợp lệ";
    }
    else cout<<"Game không tồn tại. Vui lòng kiểm tra lại ID.";


}

//Hàm tìm game theo ID
void timkiem(struct game st[], int biendem)
{
    string id;
    cout<<"Nhập ID của game: ";
    cin>>id;

    int index=timvitri(st,id,biendem);
    if (index != -1)
    { //hien thi ban ghi da tim thay
        cout<<left<<setw(5)<<"ID"<<setw(10)<<"TÊN"<<setw(15)<<"THỂ LOẠI"
            <<setw(15)<<"PHIÊN BẢN"<<setw(15)<<"DUNG LƯỢNG"<<setw(15)<<"LƯỢT TẢI"<<setw(15)<<"NĂM SẢN XUẤT"<<endl;/*<<setw(5)<<"DCK"
        <<setw(5)<<"TONG"<<"\n";*/
        cout<<"==============================================\n";
        cout<<left<<setw(5)<<st[index].id<<setw(10)<<st[index].name_game<<setw(15)<<st[index].theloai;
        cout<<setw(15)<<st[index].phienban<<setw(12)<<st[index].dungluong<<setw(12)
            <<st[index].luottai
            <<setw(12)<<st[index].namsx;
        cout<<"\n";

    }
    else cout<<"Game không tồn tại. Vui lòng kiểm tra lại ID";

}


//Hàm tìm vị trí của game
int timvitri(struct game st[], string id,int biendem){
    int found =-1;
    for (int i = 0; i < biendem && found==-1; i++)
    {

        if (st[i].id == id) found=i;

        else found=-1 ;
    }

    return found;
}

//Hàm sắp xếp game giảm dần theo năm sx
void sapxep(struct game dataset[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = n - 1; j > i; j--)
            if (dataset[j].namsx > dataset[j - 1].namsx )//năm sản xuất
            {
                game temp = dataset[j];
                dataset[j] = dataset[j - 1];
                dataset[j - 1] = temp;
            }

}

int main(int argc, char *argv[])
{


    game st[80];
    int biendem=0;
    int luachon;
    char tieptuc;
    do
    {
        menu();//Hiện menu
        cout<<"\nLựa chọn của bạn (1-7): ";
        cin>>luachon;

        switch(luachon){
            case 1:them_game(st, biendem);break;
            /*case 2:xoa_game(st, biendem);break;
            case 3:sua_game(st, biendem);break;

            case 5:timkiem(st, biendem);break;
            case 6:sapxep(st,biendem);break;*/
            case 2: ghi_File(st,biendem);
            case 3: doc_File(st,biendem);
            case 4:danhsach(st, biendem);break;
            case 7: cout<<"Đang thoát chương trình";break;
            default:cout<<"Lựa chọn không hợp lệ";

        }
        if(luachon == 7){
            break;
        }else{
            cout<<"Nhan y hoac Y de tiep tuc: ";
        }
        cin>>tieptuc;
    }while/*(true);*/(tieptuc=='y'||tieptuc=='Y');

    return 0;
}
