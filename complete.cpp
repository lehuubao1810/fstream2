#include <iostream>
#include <iomanip>
#include <string.h>
#include <fstream>
using namespace std;

fstream file; // added by Joi
int biendem = 0; // added by Joi

//Khai báo game struct
struct game
{
    int stt = 0; // added by Joi
    string id;
    char name_game[20];
    char theloai[20];
    float phienban;
    float dungluong;
    float luottai;
    float namsx;
};

//Hàm để hiện ra menu lựa chọn
void menu(){
    cout<<" "<<endl;
    cout<<"=========================================="<<endl;
    cout<<" MENU "<<"\n";
    cout<<"=========================================="<<endl;
    cout<<" 1. Thêm game mới và lưu dữ liệu vào file QLGAME.DAT"<<endl;
    cout<<" 2. Hiện danh sách game từ dữ liệu trong file QLGAME.DAT "<<endl;
    cout<<" 3. Tìm kiếm game theo ID"<<endl;
    cout<<" 4. Xóa game theo ID"<<endl;
    cout<<" 5. Sắp xếp theo năm sản xuất giảm dần"<<endl;
    cout<<" 6. Thoát chương trình"<<endl;
}

//Khai báo các nguyên mẫu hàm (function prototype)
void updateBiendem(game st_temp); // added by Joi
void fileToArray(game st[]);
int timvitri(struct game st[],string id, int biendem);
void menu();
void them_game(struct game st[]);
void danhsach(struct game st[]);
void clean(struct game st[],int deleteitem);

//*********(code added by Joi)********************************************
void updateBiendem(game st_temp) // cap nhat bien dem tu stt trong file
{
    // cap nhat so thu tu
    fstream file;
    file.open("QLGAME.DAT", ios::in); //it opens a file for a read
    if (!file) // neu chua tao file
    {
        file.close();
    } else // da tao file
    {
        file >> st_temp.stt >> st_temp.id >> st_temp.name_game >> st_temp.theloai >> st_temp.phienban >> st_temp.dungluong >> st_temp.luottai >> st_temp.namsx;
        while(!file.eof())
        {
            file >> st_temp.stt >> st_temp.id >> st_temp.name_game >> st_temp.theloai >> st_temp.phienban >> st_temp.dungluong >> st_temp.luottai >> st_temp.namsx;
        }
    }
    if (st_temp.stt != 0)
    {
        biendem = st_temp.stt;
    }
    file.close();
}

void fileToArray(game st[]) // chep data tu file ra mang st[]
{
    fstream file;
    int i = 0;
    file.open("QLGAME.DAT", ios::in); //it opens a file for a read
    if (!file) // neu chua tao file
    {
        file.close();
    } else // da tao file
    {
        file >> st[i].stt >> st[i].id >> st[i].name_game >> st[i].theloai >> st[i].phienban >> st[i].dungluong >> st[i].luottai >> st[i].namsx;
        while(!file.eof())
        {
            i++;
            file >> st[i].stt >> st[i].id >> st[i].name_game >> st[i].theloai >> st[i].phienban >> st[i].dungluong >> st[i].luottai >> st[i].namsx;
        }
    }
    file.close();
}
//************************************************************************

void ghi_File(game st[]){
    biendem = biendem - 1;
    file.open("QLGAME.DAT",ios::trunc | ios::out);
    st[biendem].stt = biendem + 1;
    file<<st[biendem].stt<<" "<<st[biendem].id<<" "<<st[biendem].name_game<<" "<<st[biendem].theloai<<" "<<st[biendem].phienban<<" "<<st[biendem].dungluong<<" "<<st[biendem].luottai<<" "<<st[biendem].namsx<<endl;
    biendem++;
    file.close();
}

//Hàm để thêm 1 game mới vào danh sách
void them_game(struct game st[]){

    again:
    cout<<"\nnhap ID: ";
    cin>>st[biendem].id;
    if (biendem != 0) // Joi's cmt: Xet them truong hop chua tao file hoac file khong co data
    {
        if (timvitri(st, st[biendem].id, biendem) != -1)
        {
            cout<<"Id da ton tai\n";goto again;
        }
    }

    cout<<"Nhập tên của game: ";
    cin>>st[biendem].name_game;
    cout<<"Nhập thể loại game: ";cin>>st[biendem].theloai;
    cout<<"Nhập phiên bản của game: ";cin>>st[biendem].phienban;
    cout<<"Nhập dung lượng của game (MB): ";cin>>st[biendem].dungluong;
    cout<<"Nhập số lượt tải về của game: ";cin>>st[biendem].luottai;
    cout<<"Nhập năm sản xuất của game: ";cin>>st[biendem].namsx;

    file.open("QLGAME.DAT",ios::app | ios::out);
    st[biendem].stt = biendem + 1;
    file<<st[biendem].stt<<" "<<st[biendem].id<<" "<<st[biendem].name_game<<" "<<st[biendem].theloai<<" "<<st[biendem].phienban<<" "<<st[biendem].dungluong<<" "<<st[biendem].luottai<<" "<<st[biendem].namsx<<endl;
    biendem++;
    file.close();
}

//Hàm hiện danh sách tất cả các game
void danhsach(struct game st[]){
    int i=0;
    cout<<left<<setw(5)<<"ID"<<setw(10)<<"TÊN"<<setw(15)<<"THỂ LOẠI"
        <<setw(15)<<"PHIÊN BẢN"<<setw(15)<<"DUNG LƯỢNG"<<setw(15)<<"LƯỢT TẢI"<<setw(15)<<"NĂM SẢN XUẤT"<<endl;
    cout<<"==============================================\n";
    while(i<biendem){
        if(st[i].id!=""){
            cout<<left<<setw(5)<<st[i].id<<setw(10)<<st[i].name_game<<setw(15)
                <<st[i].theloai;
            cout<<setw(15)<<st[i].phienban<<setw(12)<<st[i].dungluong<<setw(12)<<st[i].luottai
                <<setw(12)<<st[i].namsx;

            cout<<"\n";}
        i=i+1;

    }
}
/*
void doc_File(struct game st[], int biendem)
{
    file.open("QLGAME.DAT",ios::in);
    int i = 0;
    while(i<=biendem){
        file>>st[i].id>>st[i].name_game>>st[i].theloai>>st[i].phienban>>st[i].dungluong>>st[i].luottai>>st[i].namsx;
        i=i+1;
    }
    file.close();
    danhsach(st, biendem);
}
*/
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
    else {
        cout<<"Không có game nào được xóa\n";
    }
    //

    file.open("QLGAME.DAT",ios::trunc | ios::out);
    int i=0;
    biendem -=1; // giảm biến đếm 1 vì đã xóa 1 game
    while(i<= biendem){
        st[i].stt = i+1;
        file<<st[i].stt<<" "<<st[i].id<<" "<<st[i].name_game<<" "<<st[i].theloai<<" "<<st[i].phienban<<" "<<st[i].dungluong<<" "<<st[i].luottai<<" "<<st[i].namsx<<endl;
        i++;
    }
    file.close();
    biendem +=1;
}

void timkiem(struct game st[])
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
int timvitri(struct game st[], string id,int biendem)
{
    int found =-1;
    for (int i = 0; i < biendem && found==-1; i++)
    {

        if (st[i].id == id) found=i;

        //else found=-1 ; (code by HuuBao)
        // Joi's cmt: khong can else nay, bi thua
    }
    return found;
}

//Hàm sắp xếp game giảm dần theo năm sx
void sapxep(struct game st[])
{
    int i, j;
    for (i = 0; i < biendem; i++)
        for (j = biendem - 1; j > i; j--)
            if (st[j].namsx > st[j - 1].namsx )//năm sản xuất
            {
                game temp = st[j];
                st[j] = st[j - 1];
                st[j - 1] = temp;
            }

    file.open("QLGAME.DAT",ios::trunc | ios::out);
    i=0;
    while(i< biendem){
        st[i].stt = i+1;
        file<<st[i].stt<<" "<<st[i].id<<" "<<st[i].name_game<<" "<<st[i].theloai<<" "<<st[i].phienban<<" "<<st[i].dungluong<<" "<<st[i].luottai<<" "<<st[i].namsx<<endl;
        i++;
    }
    file.close();
}

int main()
{
    game st[80], st_temp;
    int luachon;
    char tieptuc;
    updateBiendem(st_temp); // cập nhật biến đếm
    fileToArray(st);
    do
    {
        menu();//Hiện menu
        cout<<"\nLựa chọn của bạn (1-6): ";
        cin>>luachon;

        switch(luachon){
            case 1:them_game(st);break;
            case 2:danhsach(st);break;
            case 3:timkiem(st);break;
            case 4:xoa_game(st, biendem);break;
            case 5:sapxep(st);break;
            case 6: cout<<"Đang thoát chương trình";break;
            default:cout<<"Lựa chọn không hợp lệ";
        }
        if(luachon == 6){
            break;
        }else{
            cout<<"Bạn có muốn tiếp tục chương trình (y/n): ";
        }
        cin>>tieptuc;
        if(tieptuc=='n'||tieptuc=='N'){
            break;
        }
    }while/*(true);*/(tieptuc=='y'||tieptuc=='Y');
    return 0;
}
