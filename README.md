Hệ thống Quản lý tài khoản Ví và Điểm thưởng
Giới thiệu dự án
Dự án này xây dựng một hệ thống quản lý tài khoản người dùng cùng với ví điểm thưởng bằng ngôn ngữ C++. Người dùng có thể đăng ký, đăng nhập, thay đổi mật khẩu, và thực hiện các giao dịch chuyển điểm giữa các ví. Hệ thống hỗ trợ xác thực bảo mật bằng OTP và có phân quyền người dùng thông thường và quản lý.
Thành viên tham gia dự án
- K24DTCN507 Vân Giang: Làm phần A.1 và A.2: Tạo mới bộ dữ liệu liên quan đến tài khoản người dùng và Lưu trữ dữ liệu.
- K24DTCN541 Phan Tuyet Trinh: Xác thực và bảo mật Mục A.3.1 – A.3.4, Sinh mật khẩu tự động , hay đổi mật khẩu, OTP – One Time Password, Đăng nhập
- K24DTCN Đình Phong : Làm phần B-Phân chia người dùng và chức năng. Soạn thảo tài liệu README.md.
- K24DTCN512 - Hoàng: Hệ thống ví và giao dịch (Wallet System & Transactions) Mục C, Quản lý hoạt động ví, Nạp điểm, check thông tin ví các ví, chuyển điểm, sinh số OTP trước khi chuyển
Phân tích và đặc tả chức năng
1.**Tạo tài khoản:** 
- Nhập thông tin đăng ký. 
- Cho phép người quản lý tạo hộ tài khoản người dùng. 
- Mỗi tài khoản có một ví điểm riêng biệt, mã hóa mật khẩu bằng hàm băm.
2. **Đăng nhập:**
- Kiểm tra thông tin đăng nhập. 
- Nếu mật khẩu được sinh tự động, yêu cầu thay đổi ngay lần đầu.
3. **OTP:**
- OTP xác thực thay đổi thông tin và giao dịch ví.
 - OTP được tạo ngẫu nhiên và có thời hạn sử dụng.
4. **Phân quyền:**
- Người dùng thường: chỉ được chỉnh sửa thông tin cá nhân.
- Quản lý: tạo tài khoản, chỉnh sửa hộ người dùng, theo dõi toàn bộ hệ thống.
5. **Lưu trữ:**
- Dữ liệu người dùng và ví được lưu vào file.
- Có cơ chế sao lưu dự phòng để phục hồi dữ liệu nếu lỗi.
6. **Quản lý ví và giao dịch:**
- Tạo ví, xem danh sách ví , thông tin chi tiết ví, nạp điểm, chọn ví, mở khóa/ khóa hoạt động của ví 
- Chuyển điểm sang tài khoản khác, OTP xác nhận chuyển điểm. Thông báo lỗi nếu số dư ví không đủ hoặc tài khoản nhận không tồn tại

Hướng dẫn tải và cài đặt
Yêu cầu phần mềm
Windows / macOS / linux
Git
MySQL
Visual Studio
Tải chương trình
Clone repo từ GitHub:
git clone https://github.com/HoangggNguyen/manager-account-application.git
cd manager-account-application
Cài thư viện:
MySQL Connector/C++:
Tải MySQL Connector/C++
Truy cập:
https://dev.mysql.com/downloads/connector/cpp/
Chọn phiên bản Windows. Tải bản .ZIP
Giải nén và cấu hình project để dùng MySQL Connector
Giải nén vào thư mục dễ nhớ. Thêm đường dẫn include (.h). Thêm thư viện .lib để linker nhận diện. Thêm tên thư viện cần link
Copy DLL vào thư mục chạy
Sau khi build, file .exe sẽ cần các DLL từ MySQL để chạy.
Chạy chương trình:
Mở Visual studio -> ctrl O để mở project -> vào project mở file .sln
Start Without Debugging (ctrl + F5) hoặc Local Windows Debugger (F5)

