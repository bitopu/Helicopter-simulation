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

- `TênSubsystem`: viết tắt hoặc tên ngắn gọn, rõ nghĩa.
- `TênTínhNăng`: viết theo kiểu `PascalCase`, ví dụ `CalculateThrust`, `TransformForceOnBodyAxes`, `InflowModel`.

Quy tắc bổ sung:

- Nếu tính năng làm thay đổi parameter hoặc interface, phải cập nhật đồng thời `.sldd`, file interface và [Google Sheets](https://docs.google.com/spreadsheets/d/1OIQVjcaQ8DKk69Lxzy_aSgkTthKjZHlSkRt-WTQtv9E/edit?gid=0#gid=0).
- Chỉ merge branch khi subsystem mới đã được review và có kết quả mô phỏng xác nhận không làm hỏng baseline.

# Quy Trình Pull Push Code Simulink

Do file `.slx` và một số file Simulink là file nhị phân, việc pull và push code cần tuân thủ quy trình rõ ràng để tránh xung đột và mất thay đổi. Trước khi thao tác với Git, cần bảo đảm model đã được lưu đầy đủ và đóng các file Simulink đang chỉnh sửa.

Quy trình pull code:

- Lưu toàn bộ thay đổi trong MATLAB/Simulink.
- Đóng các file `.slx`, `.sldd` và project đang mở trước khi `pull`.
- Kiểm tra trạng thái local bằng `git status`.
- Nếu đang có thay đổi chưa commit, cần `commit` hoặc `stash` trước khi pull.
- Thực hiện pull trên đúng branch đang làm việc.

```powershell
git checkout <ten-branch>
git pull origin <ten-branch>
```

- Sau khi pull xong, mở lại project và kiểm tra model có load đúng, interface có đồng bộ và simulation baseline vẫn chạy được.

Quy trình push code:

- Chỉ push sau khi đã kiểm tra logic, parameter, interface và kết quả mô phỏng.
- Đảm bảo không đưa lên các file tạm hoặc file phát sinh tự động như `*.asv`, `*.autosave`, `slprj/`, `codegen/`, `*.slxc`, `~$*.xlsx`.
- Kiểm tra lại danh sách file thay đổi bằng `git status`.
- Chỉ stage các file liên quan trực tiếp đến thay đổi, ví dụ `.slx`, `.sldd`, file interface, script khởi tạo và tài liệu liên quan.

```powershell
git add <cac-file-can-push>
git commit -m "Mo ta ngan gon noi dung cap nhat"
git push origin <ten-branch>
```

- Sau khi push, tạo pull request hoặc thực hiện review trước khi merge vào branch chính.

Quy tắc bổ sung:

- Không để nhiều người cùng sửa trực tiếp trên một file `.slx` trong cùng thời điểm nếu chưa thống nhất người phụ trách.
- Nếu branch remote đã thay đổi cùng một file `.slx`, không cố merge thủ công như file text; cần trao đổi với người sửa liên quan và chọn cách tích hợp an toàn.
- Khi có xung đột trên file Simulink, ưu tiên giữ một bản baseline rõ ràng rồi cập nhật lại thay đổi bằng cách chỉnh sửa trong Simulink thay vì sửa conflict trực tiếp trong Git.
