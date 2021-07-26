#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

fstream file; // Khai báo file thuộc fstream với chức năng đọc, ghi và tạo file.
int biendem = 0; // Gán biến đếm bằng 0 (số lượng game có trong dữ liệu).

//Khai báo game struct
struct game
{
    int stt = 0;
    string id;
    string ten_game;
    string theloai;
    string phienban;
    int dungluong;
    int luottai;
    int namsx;
};

//Khai báo các nguyên mẫu hàm (function prototype)
void menu();
void capnhat_Biendem(game st_temp);
void saochep_Dulieu(game st[]);
int xacdinh(struct game st[],string id, int biendem);

//Hàm để hiện ra menu lựa chọn
void menu(){
    cout<<" "<<endl;
    cout<<"========================================================="<<endl;
    cout<<" MENU "<<"\n";
    cout<<"========================================================="<<endl;
    cout<<" 1. Thêm game mới và lưu dữ liệu vào file QLGAME.DAT"<<endl;
    cout<<" 2. Hiện danh sách game từ dữ liệu trong file QLGAME.DAT "<<endl;
    cout<<" 3. Tìm kiếm game theo ID"<<endl;
    cout<<" 4. Xóa game theo ID"<<endl;
    cout<<" 5. Sắp xếp theo năm sản xuất giảm dần"<<endl;
    cout<<" 6. Thoát chương trình"<<endl;
}

// Hàm cập nhật biến đếm dựa vào số thứ tự trong dữ liệu của file
void capnhat_Biendem(game st_temp)
{
    // Lấy số thứ tự từ file
    fstream file;
    file.open("QLGAME.DAT", ios::in); // Mở file dưới chế độ đọc
    if (!file) // Nếu file chưa được tạo
    {
        file.close();
    } else // File đã được tạo
    {
        // Đọc hết dữ liệu từ file
        file >> st_temp.stt >> st_temp.id;
        getline(file,st_temp.ten_game,'@') ;
        file>> st_temp.theloai >> st_temp.phienban >> st_temp.dungluong >> st_temp.luottai >> st_temp.namsx;
        while(!file.eof()) // Quét đến dữ liệu cuối file
        {
            file >> st_temp.stt >> st_temp.id;
            getline(file,st_temp.ten_game,'@') ;
            file>> st_temp.theloai >> st_temp.phienban >> st_temp.dungluong >> st_temp.luottai >> st_temp.namsx;
        }
    }
    if (st_temp.stt != 0) // Nếu đã có dữ liệu trong file
    {
        biendem = st_temp.stt; // Gán biến đếm bằng số thứ tự
    }
    file.close();
}

// Sao chép dữ liệu từ file gán vào mảng st[]
void saochep_Dulieu(game st[])
{
    fstream file;
    int i = 0;
    file.open("QLGAME.DAT", ios::in); // Mở file dưới chế độ đọc
    if (!file) // Nếu file chưa được tạo
    {
        file.close();
    } else // File đã được tạo
    {
        // Đọc hết dữ liệu từ file
        file >> st[i].stt >> st[i].id;
        getline(file,st[i].ten_game,'@');
        file>> st[i].theloai >> st[i].phienban >> st[i].dungluong >> st[i].luottai >> st[i].namsx;
        while(!file.eof()) // Đọc từng dữ liệu đến hết file // sao chép từng phần tử vào mảng
        {
            i++;
            file >> st[i].stt >> st[i].id;
            getline(file,st[i].ten_game,'@');
            file>> st[i].theloai >> st[i].phienban >> st[i].dungluong >> st[i].luottai >> st[i].namsx;
        }
    }
    file.close();
}

//Hàm xác định vị trí đó có tồn tại game hay không , nếu có thì trả về vị trí
int xacdinh(struct game st[], string id,int biendem)
{
    int found =-1;
    for (int i = 0; i < biendem && found==-1; i++)
    {
        if (st[i].id == id) found=i; // Nếu tồn tại trả về vị trí
    }
    return found; // Vị trí đã tìm được
}

//Hàm để thêm 1 game mới vào danh sách
void them_game(struct game st[]){
    again:
    cout<<"\nNhập ID của game: ";
    cin>>st[biendem].id;// Nhập ID game
    // Xác định xem có bị trùng ID không dựa hàm xacdinh()
    if (biendem != 0){
        if (xacdinh(st, st[biendem].id, biendem) != -1){
            cout<<"ID đã tồn tại. Vui lòng nhập lại\n";goto again;
        }
    }
    //Nhập các thông tin cần thiết
    cout<<"Nhập tên của game: ";
    cin.ignore();
    getline(cin,st[biendem].ten_game);
    cout<<"Nhập thể loại game: ";cin>>st[biendem].theloai;
    cout<<"Nhập phiên bản của game: ";cin>>st[biendem].phienban;
    cout<<"Nhập dung lượng của game (MB): ";cin>>st[biendem].dungluong;
    cout<<"Nhập số lượt tải về của game: ";cin>>st[biendem].luottai;
    cout<<"Nhập năm sản xuất của game: ";cin>>st[biendem].namsx;
    // Ghi thông tin vào file QLGAME.DAT
    file.open("QLGAME.DAT",ios::app | ios::out); //Mở file ở chế độ ghi và ghi ở cuối file
    st[biendem].stt = biendem + 1;
    file<<st[biendem].stt<<" "<<st[biendem].id<<" "<<st[biendem].ten_game<<"@ "
        <<st[biendem].theloai<<" "<<st[biendem].phienban<<" "<<st[biendem].dungluong
        <<" "<<st[biendem].luottai<<" "<<st[biendem].namsx<<endl;
    biendem++;
    file.close();
}

//Hàm hiện danh sách tất cả các game
void danhsach(struct game st[]){
    /*if (biendem == 0){
        cout<<"Chưa có game nào trong danh sách."<<endl;
    }*/
    int i=0;
    cout<<setw(5)<<left<<"ID";
    cout<<setw(25)<<left<<"TÊN";
    cout<<setw(20)<<left<<"THỂ LOẠI";
    cout<<setw(20)<<left<<"PHIÊN BẢN";
    cout<<setw(20)<<left<<"DUNG LƯỢNG";
    cout<<setw(20)<<left<<"LƯỢT TẢI";
    cout<<setw(20)<<right<<"NĂM SẢN XUẤT"<<endl;
    cout<<"==============================================================================\n";

    // Quét qua từng phần tử của mảng để in ra màn hình
    while(i<biendem){
        if(st[i].id!=""){
            cout<<setw(5)<<left<<st[i].id;
            cout<<setw(25)<<left<<st[i].ten_game;
            cout<<setw(15)<<left<<st[i].theloai;
            cout<<setw(20)<<left<<st[i].phienban;
            cout<<setw(15)<<left<<st[i].dungluong;
            cout<<setw(20)<<left<<st[i].luottai;
            cout<<setw(15)<<left<<st[i].namsx;
            cout<<"\n";}
        i=i+1;

    }
}

// Hàm xóa game theo ID
void xoa_game(struct game st[], int& biendem){
    string id;
    int index;
    if (biendem > 0) // Phải có ít nhất 1 game thì mới có thể xóa được
    {
        cout<<"Nhập ID của game: ";
        cin>>id;
        index = xacdinh(st, id,biendem); // Xác định vị trí game cần xóa dựa vào ID và hàm xacdinh()
        if ((index!=-1) && (biendem != 0)) // Nếu ID tồn tại và biến đếm khác 0 thì tiếp tục hàm
        {
            if (index == (biendem-1)) //Xóa game cuối cùng
            {
                --biendem;
                cout<<"Game đã được xóa.\n";
            }
            else //Xóa game ở giữa
            {
                for (int i = index; i < biendem-1; i++)
                {
                    st[i] = st[i + 1];
                }
                --biendem ;
                cout<<"Game đã được xóa.\n";
            }
        }
        else cout<<"Game không tổn tại. Vui lòng kiểm tra lại ID.\n"; // Nếu không tồn tại ID thì yêu cầu kiểm tra lại.

    }
    else {
        cout<<"Không có game nào được xóa\n"; // Dừng hàm vì không có game nào để xóa.
    }
    //

    file.open("QLGAME.DAT",ios::trunc | ios::out); // Mở file ở chế độ ghi và xóa hết dữ liệu cũ
    int i=0;
    while(i< biendem){
        st[i].stt = i+1; // Điều chỉnh lại stt theo số game còn lại sau khi xóa
        file<<st[i].stt<<" "<<st[i].id<<" "<<st[i].ten_game<<"@ "<<st[i].theloai<<" "<<st[i].phienban<<" "<<st[i].dungluong<<" "<<st[i].luottai<<" "<<st[i].namsx<<endl;
        i++;
    }
    file.close();
}

//Hàm tìm kiếm game theo ID
void timkiem(struct game st[])
{
    string id;
    cout<<"Nhập ID của game: ";
    cin>>id;
    int index=xacdinh(st,id,biendem);
    if (index != -1)
    { // Hiển thị bản ghi đã tìm thấy
        cout<<setw(5)<<left<<"ID";
        cout<<setw(20)<<left<<"TÊN";
        cout<<setw(20)<<left<<"THỂ LOẠI";
        cout<<setw(20)<<left<<"PHIÊN BẢN";
        cout<<setw(20)<<left<<"DUNG LƯỢNG";
        cout<<setw(20)<<left<<"LƯỢT TẢI";
        cout<<setw(20)<<right<<"NĂM SẢN XUẤT"<<endl;
        cout<<"==============================================================================\n";
        //
        cout<<setw(5)<<left<<st[index].id;
        cout<<setw(20)<<left<<st[index].ten_game;
        cout<<setw(15)<<left<<st[index].theloai;
        cout<<setw(20)<<left<<st[index].phienban;
        cout<<setw(15)<<left<<st[index].dungluong;
        cout<<setw(20)<<left<<st[index].luottai;
        cout<<setw(15)<<left<<st[index].namsx;
        cout<<"\n";
    }
    else cout<<"Game không tồn tại. Vui lòng kiểm tra lại ID";

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

    cout<<"Đã sắp xếp theo năm giảm dần!"<<endl;
    file.open("QLGAME.DAT",ios::trunc | ios::out); // Mở file ở chế độ ghi và xóa hết dữ liệu cũ
    i=0;
    while(i< biendem){
        st[i].stt = i+1; // Điều chỉnh lại số thứ tự sau khi sắp xếp
        file<<st[i].stt<<" "<<st[i].id<<" "<<st[i].ten_game<<"@ "
            <<st[i].theloai<<" "<<st[i].phienban<<" "<<st[i].dungluong
            <<" "<<st[i].luottai<<" "<<st[i].namsx<<endl;
        i++;
    }
    file.close();
}

int main()
{
    game st[80], st_temp;
    int luachon;
    char tieptuc;
    capnhat_Biendem(st_temp); // Cập nhật biến đếm
    saochep_Dulieu(st);
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
            case 6: cout<<"Đang thoát chương trình ...";break;
            default:cout<<"Lựa chọn không hợp lệ"<<endl;
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
