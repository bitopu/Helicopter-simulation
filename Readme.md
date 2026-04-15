# Quy Ước Tham Số

Trước khi bắt đầu code, cần thiết lập đầy đủ các tham số cần thiết và khai báo chúng trong thư viện `.sldd`, bao gồm các thông tin: tên, ký hiệu, đơn vị, giá trị và người thêm. Mỗi khi một parameter được thêm mới hoặc thay đổi, phải cập nhật ngay vào file theo dõi [Bảng tham số](https://docs.google.com/spreadsheets/d/1OIQVjcaQ8DKk69Lxzy_aSgkTthKjZHlSkRt-WTQtv9E/edit?gid=0#gid=0). Nếu có thêm viết tắt mới trong tên hệ thống, tên tín hiệu hoặc tên tham số, phải cập nhật đồng thời vào [Bảng viết tắt](https://docs.google.com/spreadsheets/d/1_HTWcE8RAuG5lzPQCZ9mHIeLCMMyYjoRWsU7lW2kBN4/edit?gid=0#gid=0).

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

# Cách Sử Dụng `.sldd` Với File Simulink

Trong project này, các Simulink Data Dictionary hiện có nằm tại:

- `resources/params/Helicopter.sldd`
- `resources/params/Rotor.sldd`
- `resources/params/Fuselage.sldd`

Mỗi file `.slx` nên được liên kết với một file `.sldd` phù hợp với phạm vi chức năng của model hoặc subsystem.

Bước đầu tiên trước khi liên kết là xác định có cần tạo file `.sldd` mới hay không. Nếu chưa có dictionary phù hợp với subsystem hoặc chức năng đang phát triển, phải tạo file `.sldd` mới trong thư mục `resources/params/` trước, sau đó mới liên kết file `.slx` tới dictionary đó.

Quy tắc chọn `.sldd`:

- Dùng `Helicopter.sldd` cho parameter dùng chung ở cấp toàn mô hình hoặc nhiều subsystem có thể tạo liên kết từ `Helicopter.sldd` đến các file `.sldd` tiếp theo.
- Dùng `Rotor.sldd` cho parameter chỉ thuộc logic rotor.
- Dùng `Fuselage.sldd` cho parameter chỉ thuộc logic fuselage.
- Với file `.slx` mới, phải xác định rõ dùng lại `.sldd` hiện có hay tạo `.sldd` mới trước khi phát triển.

Cách tạo file `.sldd` mới:

Quy tắc đặt tên:

- Tên file `.sldd` phải ngắn gọn, rõ phạm vi chức năng, ví dụ `Rotor.sldd`, `Fuselage.sldd`, `MainRotor.sldd`.
- File `.sldd` mới phải được lưu trong thư mục `resources/params/`.
- Chỉ tạo `.sldd` mới khi parameter cần tách riêng theo subsystem hoặc theo gói chức năng; không tạo trùng phạm vi với dictionary đã có.

Cách tạo bằng Simulink UI:

Cách 1, dùng `Model Explorer`:

1. Mở một model `.slx` bất kỳ hoặc mở `Model Explorer`.
2. Trong `Model Explorer`, chọn `File > New > Data Dictionary`.
3. Lưu file vào `resources/params/` với tên phù hợp.
4. Mở file `.slx` cần dùng dictionary này.
5. Vào `Model Settings > External Data`.
6. Tại mục `Data Dictionary`, chọn file `.sldd` vừa tạo.
7. Lưu lại model.

Cách 2, tạo trực tiếp từ model:

1. Mở file `.slx` cần cấu hình.
2. Vào `Model Settings > External Data`.
3. Tại mục `Data Dictionary`, chọn `New`.
4. Lưu file `.sldd` mới vào `resources/params/`.
5. Lưu lại model sau khi liên kết xong.

Cách tạo bằng MATLAB command:

```matlab
Simulink.data.dictionary.create('resources/params/MainRotor.sldd');
```
Sau khi tạo `.sldd` mới:

- Phải liên kết file `.sldd` đó với model `.slx` tương ứng.
- Phải kiểm tra model load đúng và đọc được parameter từ dictionary.
- Nếu dictionary mới thay thế cho dictionary cũ, cần rà soát lại toàn bộ parameter reference trong model.

Cách liên kết `.sldd` bằng Simulink UI:

1. Mở file `.slx` cần cấu hình.
2. Vào `Model Settings`.
3. Chọn `External Data`.
4. Tại mục `Data Dictionary`, chọn `Browse`.
5. Liên kết tới file `.sldd` phù hợp trong `resources/params/`.
6. Lưu model sau khi liên kết xong.

Cách liên kết `.sldd` bằng MATLAB command:


# Quy Ước Interface

Trước khi tạo hoặc sửa interface, cần định nghĩa rõ tên tín hiệu, hướng truyền, đơn vị, kiểu dữ liệu, kích thước và subsystem liên quan. Mỗi khi interface được thêm mới hoặc thay đổi, phải cập nhật đồng thời trong file giao diện và file theo dõi [Bảng interface](https://docs.google.com/spreadsheets/d/1OIQVjcaQ8DKk69Lxzy_aSgkTthKjZHlSkRt-WTQtv9E/edit?gid=0#gid=0). Nếu interface sử dụng viết tắt mới hoặc thêm quy ước viết tắt mới, phải cập nhật thêm vào [Bảng viết tắt](https://docs.google.com/spreadsheets/d/1_HTWcE8RAuG5lzPQCZ9mHIeLCMMyYjoRWsU7lW2kBN4/edit?gid=0#gid=0).

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
- Khi tạo một file mới phải thêm file đấy vào project mới có thể commit được.
- Cách lạm chuột phải vào tên file và chọn `Add to project`.
Tham chiếu thêm tại [MATLAB Source Control](https://www.mathworks.com/help/matlab/source-control.html).

# Quy Trình Tạo Branch, Develop, Push Và Merge

Khi phát triển một subsystem hoặc tính năng mới, cần thực hiện theo quy trình cố định để tránh ghi đè file `.slx`, giảm xung đột Git và giữ được baseline ổn định.

## 1. Tạo branch mới

Luôn tạo branch mới từ branch ổn định trước khi bắt đầu làm việc.

Quy tắc đặt tên branch:

- `feature/<ten-tinh-nang>`
- `feature/<ten-subsystem>-<ten-tinh-nang>`
- ví dụ: `feature/rotor-inflow-model`
- ví dụ: `feature/fuselage-aero-update`

Thực hiện bằng `Project UI`:

1. Mở `Project`.
2. Đồng bộ branch ổn định hiện tại bằng thao tác `Fetch` hoặc `Pull`.
3. Vào `Source Control > Branch Manager`.
4. Tạo branch mới từ `master`.
5. Đặt tên branch, ví dụ `feature/rotor-inflow-model`.

Thực hiện bằng `Git command`:

```powershell
git checkout master
git pull origin master
git checkout -b feature/rotor-inflow-model
```

## 2. Develop subsystem mới

Không sửa trực tiếp trên file subsystem `.slx` đang làm baseline. Thay vào đó:

1. Tạo file subsystem hoặc model `.slx` mới.
2. Liên kết file `.slx` mới với `.sldd` phù hợp.
3. Khai báo parameter mới trong `.sldd` nếu cần.
4. Cập nhật interface và Google Sheets nếu có thay đổi tín hiệu hoặc parameter.
5. Chạy kiểm tra mô phỏng để xác nhận subsystem mới hoạt động đúng.


## 3. Commit local

Chỉ commit các file liên quan trực tiếp đến thay đổi.

Thường bao gồm:

- file `.slx` mới hoặc file `.slx` đã tích hợp
- file `.sldd`
- file interface
- tài liệu liên quan như `Readme.md`

Thực hiện bằng `Project UI`:

1. Save toàn bộ model và dictionary.
2. Với file mới, chuột phải vào file và chọn `Add to Project`.
3. Vào `Source Control`.
4. Chọn các file cần commit.
5. Nhập message commit.
6. Chọn `Commit`.

Thực hiện bằng `Git command`:

```powershell
git status
git add <cac-file-lien-quan>
git commit -m "Add rotor inflow subsystem and dictionary updates"
```

## 4. Push branch lên remote

Sau khi commit xong, push branch mới lên remote:

Thực hiện bằng `Project UI`:

1. Vào `Source Control`.
2. Chọn `Push`.
3. Nếu là lần đầu push branch mới, chọn remote branch tương ứng hoặc tạo branch remote mới cùng tên.

Thực hiện bằng `Git command`:

```powershell
git push -u origin feature/rotor-inflow-model
```

Sau lần đầu, các lần push tiếp theo chỉ cần:

```powershell
git push
```


## 5. Review trước khi merge

Trước khi merge vào branch chính, cần review tối thiểu các nội dung sau:

- subsystem mới có đúng logic không
- parameter đã nằm đúng `.sldd` chưa
- interface đã cập nhật chưa
- simulation có chạy ổn không
- kết quả mới có phá baseline không
- branch có kéo kịp thay đổi mới nhất từ `master` chưa

Nếu `master` đã thay đổi trong lúc đang phát triển:

Thực hiện bằng `Project UI`:

1. Chuyển về branch `master`.
2. Chọn `Pull` để cập nhật `master`.
3. Chuyển lại branch feature đang làm.
4. Chọn `Merge` và merge `master` vào branch hiện tại.

Thực hiện bằng `Git command`:

```powershell
git checkout master
git pull origin master
git checkout feature/rotor-inflow-model
git merge master
```

Nếu có xung đột trên file `.slx` hoặc `.sldd`, không nên cố sửa conflict như file text. Cần mở lại trong Simulink, xác nhận bản đúng rồi commit lại kết quả tích hợp.

## 6. Merge branch

Merge chỉ diễn ra khi branch đã được review và xác nhận không làm hỏng baseline.

Cách merge khuyến nghị:

1. Tạo pull request hoặc merge request.
2. Review thay đổi bởi ít nhất một người khác nếu làm việc theo team.
3. Kiểm tra lại simulation lần cuối trên branch chuẩn bị merge.
4. Merge vào `master`.

Thực hiện bằng `Project UI`:

1. Chuyển sang `master`.
2. Chọn `Pull`.
3. Chọn `Merge`.
4. Chọn branch feature cần merge vào `master`.
5. Sau khi merge xong, chọn `Push`.

Thực hiện bằng `Git command`:

```powershell
git checkout master
git pull origin master
git merge --no-ff feature/rotor-inflow-model
git push origin master
```

Sau khi merge xong:

- cập nhật baseline nếu subsystem mới đã thay thế subsystem cũ
- xóa branch đã hoàn tất nếu không còn dùng

Thực hiện bằng `Project UI`:

1. Chọn `Manage Branches`.
2. Xóa branch local đã hoàn tất.
3. Nếu cần, xóa branch remote trên server Git hoặc trên giao diện Git hosting.

Thực hiện bằng `Git command`:

```powershell
git branch -d feature/rotor-inflow-model
git push origin --delete feature/rotor-inflow-model
```

## 7. Tóm tắt workflow chuẩn

1. `pull master`
2. `create branch`
3. `create new subsystem .slx`
4. `link .sldd`
5. `update parameter/interface`
6. `simulate and verify`
7. `commit`
8. `push branch`
9. `review`
10. `merge to master`

Main rotor
