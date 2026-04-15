# Quy Ước Tham Số

Trước khi bắt đầu code, cần thiết lập đầy đủ các tham số cần thiết và khai báo chúng trong thư viện `.sldd`, bao gồm các thông tin: tên, ký hiệu, đơn vị, giá trị và người thêm. Mỗi khi một parameter được thêm mới hoặc thay đổi, phải cập nhật ngay vào file theo dõi [Google Sheets](https://docs.google.com/spreadsheets/d/1OIQVjcaQ8DKk69Lxzy_aSgkTthKjZHlSkRt-WTQtv9E/edit?gid=0#gid=0).

Quy tắc đặt tên cho tham số:

`[Tên hệ thống]_[Tên tham số]_[Loại thông số]`

- `Tên hệ thống`: viết tắt, dùng chữ in hoa.
- `Tên tham số`: viết theo kiểu `PascalCase`, ví dụ `DensityInflow`.
- `Loại thông số`: sử dụng một trong các hậu tố sau.

- `_P`: một giá trị đơn.
- `_A`: một mảng giá trị.
- `_X`: mảng breakpoint đầu vào theo trục `X` của bảng tra.
- `_Y`: mảng breakpoint đầu vào theo trục `Y` của bảng tra 2 chiều.
- `_M`: ma trận hoặc mảng giá trị đầu ra của bảng tra.

# Quy Ước Interface

Trước khi tạo hoặc sửa interface, cần định nghĩa rõ tên tín hiệu, hướng truyền, đơn vị, kiểu dữ liệu, kích thước và subsystem liên quan. Mỗi khi interface được thêm mới hoặc thay đổi, phải cập nhật đồng thời trong file giao diện và file theo dõi [Google Sheets](https://docs.google.com/spreadsheets/d/1OIQVjcaQ8DKk69Lxzy_aSgkTthKjZHlSkRt-WTQtv9E/edit?gid=0#gid=0).

Quy tắc đặt tên cho interface:

`[Tên hệ thống]_[Tên tín hiệu]_[Hướng]`

- `Tên hệ thống`: viết tắt, dùng chữ in hoa.
- `Tên tín hiệu`: viết theo kiểu `PascalCase`, mô tả đúng ý nghĩa vật lý hoặc chức năng của tín hiệu, ví dụ `CollectiveCmd`, `BodyAxisForceZ`, `RotorSpeed`.
- `Hướng`: sử dụng một trong các hậu tố sau.

- `_I`: tín hiệu đi vào subsystem.
- `_O`: tín hiệu đi ra từ subsystem.
- `_B`: tên bus interface, dùng khi gom nhiều tín hiệu cùng một nhóm chức năng.

Quy tắc bổ sung:

- Không đưa đơn vị, kiểu dữ liệu hoặc kích thước vào tên tín hiệu.
- Tên phải thể hiện đúng bản chất tín hiệu: `Cmd` cho lệnh điều khiển, `Fb` cho phản hồi, `State` cho trạng thái, `Flag` cho tín hiệu logic nếu cần.
- Với tín hiệu trong bus, tên phần tử bus vẫn tuân theo kiểu `PascalCase` và không cần lặp lại tên hệ thống nếu bus đã thể hiện rõ phạm vi.

# Quy Ước Cập Nhật Tính Năng

Khi phát triển tính năng mới, không sửa trực tiếp trên branch chính và không cập nhật trực tiếp trên cùng file subsystem `.slx` đang dùng ổn định. Mỗi tính năng mới phải được thực hiện theo một nhánh phát triển riêng và một file subsystem riêng để dễ kiểm soát thay đổi, so sánh hành vi và rollback khi cần.

Quy trình thực hiện:

- Tạo một branch mới từ branch ổn định trước khi bắt đầu phát triển tính năng.
- Đặt tên branch theo chức năng, ví dụ `feature/main-rotor-inflow` hoặc `feature/main-rotor-inflow-v1`.
- Tạo subsystem hoặc model `.slx` mới cho tính năng thay vì sửa trực tiếp trên file `.slx` hiện tại.
- Giữ file `.slx` cũ làm baseline để đối chiếu kết quả mô phỏng và kiểm tra hồi quy.
- Chỉ thay thế hoặc tích hợp subsystem mới vào mô hình chính sau khi đã kiểm tra logic, interface, parameter và kết quả mô phỏng.

Quy tắc đặt tên file subsystem mới:

`[TênSubsystem]_[TênTínhNăng].slx`
- 

Ví dụ:
- `Tên Subsystem`: viết tắt, dùng chữ in hoa.
- `Tên tín hiệu`: viết theo kiểu `PascalCase`, mô tả đúng ý nghĩa vật lý hoặc chức năng của tín năng, ví dụ `CalculateThrust`, `TransformForceOnBodyAxes`.
