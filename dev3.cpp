#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

fstream file; // Khai báo file thuộc fstream với chức năng đọc, ghi và tạo file.
int biendem = 0; // Gán biến đếm bằng 0 (số lượng game có trong dữ liệu).

//Khai báo game structR
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
    cout<<" 3. Tìm kiếm game"<<endl;
    cout<<" 4. Xóa game theo ID"<<endl;
    cout<<" 5. Sắp xếp theo năm sản xuất giảm dần"<<endl;
    cout<<" 6. Chỉnh sửa thông tin game"<<endl;
    cout<<" 7. Thoát chương trình"<<endl;
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
    return found;
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
    cout<<"=============================================================================================================\n";

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
        file<<st[i].stt<<" "<<st[i].id<<" "<<st[i].ten_game<<"@ "<<st[i].theloai<<" "
        <<st[i].phienban<<" "<<st[i].dungluong<<" "<<st[i].luottai<<" "<<st[i].namsx<<endl;
        i++;
    }
    file.close();
}

// SẮP XẾP

// Ghi dữ liệu vào file sau khi sắp xếp
void ghifilesx(game st[],int i) {
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

// Hàm sắp xếp game giảm dần theo năm sx
void sapxep_nsx_gd(struct game st[]){
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
    ghifilesx(st,i);
}
void sapxep_nsx_td(struct game st[]){
    int i, j;
    for (i = 0; i < biendem; i++)
        for (j = biendem - 1; j > i; j--)
            if (st[j].namsx < st[j - 1].namsx )//năm sản xuất
                {
                game temp = st[j];
                st[j] = st[j - 1];
                st[j - 1] = temp;
                }

    cout<<"Đã sắp xếp theo năm tăng dần dần!"<<endl;
    ghifilesx(st,i);
}
void sapxep_lt_gd(struct game st[]){
    int i, j;
    for (i = 0; i < biendem; i++)
        for (j = biendem - 1; j > i; j--)
            if (st[j].luottai > st[j - 1].luottai )//năm sản xuất
                {
                game temp = st[j];
                st[j] = st[j - 1];
                st[j - 1] = temp;
                }

    cout<<"Đã sắp xếp theo số lượt tải giảm dần!"<<endl;
    ghifilesx(st,i);
}
void sapxep_lt_td(struct game st[]){
    int i, j;
    for (i = 0; i < biendem; i++)
        for (j = biendem - 1; j > i; j--)
            if (st[j].luottai < st[j - 1].luottai )//năm sản xuất
                {
                game temp = st[j];
                st[j] = st[j - 1];
                st[j - 1] = temp;
                }

    cout<<"Đã sắp xếp theo số lượt tải tăng dần dần!"<<endl;
    ghifilesx(st,i);
}
void sapxep_dl_gd(struct game st[]){
    int i, j;
    for (i = 0; i < biendem; i++)
        for (j = biendem - 1; j > i; j--)
            if (st[j].dungluong > st[j - 1].dungluong )//năm sản xuất
                {
                game temp = st[j];
                st[j] = st[j - 1];
                st[j - 1] = temp;
                }

    cout<<"Đã sắp xếp theo dung lượng giảm dần!"<<endl;
    ghifilesx(st,i);
}
void sapxep_dl_td(struct game st[]){
    int i, j;
    for (i = 0; i < biendem; i++)
        for (j = biendem - 1; j > i; j--)
            if (st[j].dungluong < st[j - 1].dungluong )//năm sản xuất
                {
                game temp = st[j];
                st[j] = st[j - 1];
                st[j - 1] = temp;
                }

    cout<<"Đã sắp xếp theo năm dung lượng dần dần!"<<endl;
            ghifilesx(st,i);
}

void sapxep(game st[]) {
    int a;
    cout<<"1. Sắp xếp theo năm giảm dần"<<endl;
    cout<<"2. Sắp xếp theo năm tăng dần"<<endl;
    cout<<"1. Sắp xếp theo lượt tải giảm dần"<<endl;
    cout<<"2. Sắp xếp theo lượt tải tăng dần"<<endl;
    cout<<"1. Sắp xếp theo dung lượng giảm dần"<<endl;
    cout<<"2. Sắp xếp theo dung lượng tăng dần"<<endl;
    cout<<"Nhập lựa chọn: ";cin>>a;
    switch(a) {
        case 1:
            sapxep_nsx_gd(st);
            break;
        case 2:
            sapxep_nsx_td(st);
            break;
        case 3:
            sapxep_lt_gd(st);
            break;
        case 4:
            sapxep_lt_td(st);
            break;
        case 5:
            sapxep_dl_gd(st);
            break;
        case 6:
            sapxep_dl_td(st);
            break;
    }
}
// TÌM KIẾM

//Danh sách tìm kiếm

void dstimkiem(struct game st[],int index){
    cout<<setw(5)<<left<<"ID";
    cout<<setw(20)<<left<<"TÊN";
    cout<<setw(20)<<left<<"THỂ LOẠI";
    cout<<setw(20)<<left<<"PHIÊN BẢN";
    cout<<setw(20)<<left<<"DUNG LƯỢNG";
    cout<<setw(20)<<left<<"LƯỢT TẢI";
    cout<<setw(20)<<right<<"NĂM SẢN XUẤT"<<endl;
    cout<<"=============================================================================================================\n";
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
//Hàm tìm kiếm game theo ID
void timkiemID(struct game st[]){
    string id;
    cout<<"Nhập ID của game: ";
    cin>>id;
    int index=xacdinh(st,id,biendem);
    if (index != -1)
    { // Hiển thị bản ghi đã tìm thấy
        dstimkiem(st,index);
    }
    else cout<<"Game không tồn tại. Vui lòng kiểm tra lại ID"<<endl;

}

void dllonnhat(game st[]){
    int maxx = st[0].dungluong;
    int index = 0;
    for(int i = 0; i<biendem;i++){
        if(maxx < st[i].dungluong){
            maxx = st[i].dungluong;
            index = st[i].stt - 1;
        }
    }
    cout<<"Dung lượng lớn nhất là : "<<maxx<<endl;
    dstimkiem(st,index);
}

void dlnhonhat(game st[]){
    int minn = st[0].dungluong;
    int index = 0;
    for(int i = 0; i<biendem;i++){
        if(minn > st[i].dungluong){
            minn = st[i].dungluong;
            index = st[i].stt - 1;
        }
    }
    cout<<"Dung lượng nhỏ nhất là : "<<minn<<endl;
    dstimkiem(st,index);

}
void ltlonnhat(game st[]){
    int maxx = st[0].luottai;
    int index = 0;
    for(int i = 0; i<biendem;i++){
        if(maxx < st[i].luottai){
            maxx = st[i].luottai;
            index = st[i].stt - 1;
        }
    }
    cout<<"Lượt tải lớn nhất là : "<<maxx<<endl;
    dstimkiem(st,index);
}

void ltnhonhat(game st[]){
    int minn = st[0].luottai;
    int index = 0;
    for(int i = 0; i<biendem;i++){
        if(minn > st[i].luottai){
            minn = st[i].luottai;
            index = st[i].stt - 1;
        }
    }
    cout<<"Lượt tải nhỏ nhất là : "<<minn<<endl;
    dstimkiem(st,index);

}
void nsxlonnhat(game st[]){
    int maxx = st[0].namsx;
    int index = 0;
    for(int i = 0; i<biendem;i++){
        if(maxx < st[i].namsx){
            maxx = st[i].namsx;
            index = st[i].stt - 1;
        }
    }
    cout<<"Năm sản xuất lớn nhất là : "<<maxx<<endl;
    dstimkiem(st,index);
}

void nsxnhonhat(game st[]){
    int minn = st[0].namsx;
    int index = 0;
    for(int i = 0; i<biendem;i++){
        if(minn > st[i].namsx){
            minn = st[i].namsx;
            index = st[i].stt - 1;
        }
    }
    cout<<"Năm sản xuất nhỏ nhất nhỏ nhất là : "<<minn<<endl;
    dstimkiem(st,index);

}

void minmax(game st[]){
    int b;
    cout<<"1.Dung lượng game"<<endl;
    cout<<"2.Lượt tải game"<<endl;
    cout<<"3.Năm sản xuất"<<endl;
    cout<<"Nhập lựa chọn : ";cin>>b;
    switch(b) {
        case 1:
            dllonnhat(st);
            dlnhonhat(st);
            break;
        case 2:
            ltlonnhat(st);
            ltnhonhat(st);
            break;
        case 3:
            nsxlonnhat(st);
            nsxnhonhat(st);
            break;
    }
}

// BỘ LỌC
void bltheloai(game st[]){
    string tl[100];
    int a;
    int stt = 1;
    for (int i =0; i<biendem; i++){
        if ( i > 0 && st[i].theloai == st[i-1].theloai){
            continue;
        }
        tl[stt] = st[i].theloai;
        cout<< stt <<". " << tl[stt] <<endl;
        stt += 1;
    }
    cout<<"Chọn thể loại: ";cin>> a;
    cout<<setw(5)<<left<<"ID";
    cout<<setw(20)<<left<<"TÊN";
    cout<<setw(20)<<left<<"THỂ LOẠI";
    cout<<setw(20)<<left<<"PHIÊN BẢN";
    cout<<setw(20)<<left<<"DUNG LƯỢNG";
    cout<<setw(20)<<left<<"LƯỢT TẢI";
    cout<<setw(20)<<right<<"NĂM SẢN XUẤT"<<endl;
    cout<<"=============================================================================================================\n";
    for(int i = 0; i<biendem;i++){
        if(st[i].theloai == tl[a]){
            cout<<setw(5)<<left<<st[i].id;
            cout<<setw(20)<<left<<st[i].ten_game;
            cout<<setw(15)<<left<<st[i].theloai;
            cout<<setw(20)<<left<<st[i].phienban;
            cout<<setw(15)<<left<<st[i].dungluong;
            cout<<setw(20)<<left<<st[i].luottai;
            cout<<setw(15)<<left<<st[i].namsx;
            cout<<"\n";
        }
    }
}

void blnamsx(game st[]) {
    int namsx[100];
    int a;
    int stt = 1;
    for (int i =0; i<biendem; i++){
        if ( i > 0 && st[i].namsx == st[i-1].namsx){
            continue;
        }
        namsx[stt] = st[i].namsx;
        cout<< stt <<". Năm " << namsx[stt] <<endl;
        stt += 1;
    }
    cout<<"Chọn năm sản xuất: ";cin>> a;
    cout<<setw(5)<<left<<"ID";
    cout<<setw(20)<<left<<"TÊN";
    cout<<setw(20)<<left<<"THỂ LOẠI";
    cout<<setw(20)<<left<<"PHIÊN BẢN";
    cout<<setw(20)<<left<<"DUNG LƯỢNG";
    cout<<setw(20)<<left<<"LƯỢT TẢI";
    cout<<setw(20)<<right<<"NĂM SẢN XUẤT"<<endl;
    cout<<"=============================================================================================================\n";
    for(int i = 0; i<biendem;i++){
        if(st[i].namsx == namsx[a]){
            cout<<setw(5)<<left<<st[i].id;
            cout<<setw(20)<<left<<st[i].ten_game;
            cout<<setw(15)<<left<<st[i].theloai;
            cout<<setw(20)<<left<<st[i].phienban;
            cout<<setw(15)<<left<<st[i].dungluong;
            cout<<setw(20)<<left<<st[i].luottai;
            cout<<setw(15)<<left<<st[i].namsx;
            cout<<"\n";
        }
    }
}
void boloc(game st[]){
    int b;
    cout<<"1.Thể loại"<<endl;
    cout<<"2.Năm sản xuất"<<endl;
    cout<<"Nhập lựa chọn : ";cin>>b;
    switch(b) {
        case 1: bltheloai(st);break;
        case 2: blnamsx(st);break;
        default:
            cout<<"Lựa chọn không hợp lệ!!";
    }
}

void timkiem(game st[]){
    int a;
    cout<<"1.Tìm kiếm theo ID"<<endl;
    cout<<"2.Tìm kiếm lớn nhất, nhỏ nhất"<<endl;
    cout<<"3.Tìm kiếm theo bộ lọc"<<endl;
    cout<<"Nhập lựa chọn : ";cin>>a;
    switch(a) {
        case 1: timkiemID(st);break;
        case 2: minmax(st);break;
        case 3: boloc(st);break;
    }
}

// CHỈNH SỬA
void sua_game(struct game st[]){
    string id;
    int column_index;
    cout<<"Nhập ID của game cần sửa: ";
    cin>> id;
    cout<<"Bạn muốn cập nhật phần nào (1-6) ?: ";
    cin>>column_index;

    int index = xacdinh(st, id,biendem);

    if (index != -1)
    {
        switch(column_index){
            case 1 :
                cout<<"Nhập tên mới của game: ";
                cin.ignore();
                getline(cin,st[index].ten_game);
                break;
            case 2 :
                cout<<"Nhập thể loại mới: ";
                cin>>st[index].theloai;
                break;
            case 3 :
                cout<<"Nhập phiên bản mới : ";
                cin>>st[index].phienban;
                break;
            case 4 :
                cout<<"Nhập dung lượng mới: ";
                cin>>st[index].dungluong;
                break;
            case 5 :
                cout<<"Nhập lượt tải mới: ";
                cin>>st[index].luottai;
                break;
            case 6 :
                cout<<"Nhập năm sản xuất mới: ";
                cin>>st[index].namsx;
                break;
            default:
                cout<<"Không có mục hợp lệ";
                break;
        }
    }
    else cout<<"Sinh vien không tồn tại. Vui lòng kiểm tra lại MSSV.";
    file.open("QLGAME.DAT",ios::trunc | ios::out);
    int i=0;
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
    game st[100], st_temp;
    int luachon;
    char tieptucct;
    char tieptuctg;
    capnhat_Biendem(st_temp); // Cập nhật biến đếm
    saochep_Dulieu(st);
    do
    {
        lai:
        menu();//Hiện menu
        cout<<"\nLựa chọn của bạn (1-6): ";
        cin>>luachon;

        switch(luachon){
            case 1:
                do {
                    them_game(st);
                    cout<<"Bạn có muốn thêm 1 game mới nữa không (y/n): ";cin>>tieptuctg;
                    if( tieptuctg == 'n' || tieptuctg == 'N') {
                        break;
                    }
                }while ( tieptuctg == 'y' || tieptuctg == 'Y');
                break;
            case 2:danhsach(st);break;
            case 3:timkiem(st);break;
            case 4:xoa_game(st, biendem);break;
            case 5:sapxep(st);break;
            case 6:sua_game(st);break;
            case 7: cout<<"Đang thoát chương trình ...";break;
            default:
                cout<<"Lựa chọn không hợp lệ"<<endl;
                goto lai;
        }
        if(luachon == 7){
            break;
        }else{
            cout<<"Bạn có muốn tiếp tục chương trình (y/n): ";
        }
        cin>>tieptucct;
        if(tieptucct=='n'||tieptucct=='N'){
            cout<<"Đang thoát chương trình ...";
            break;
        }
    }while/*(true);*/(tieptucct=='y'||tieptucct=='Y');
    return 0;
}
