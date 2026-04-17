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

## Nguyên tắc quan trọng: SLDD không được commit vào Git

File `.sldd` là file nhị phân do MATLAB tự động tạo và quản lý, **không được đưa vào Git**. Thay vào đó, mỗi `.sldd` phải có một file script `.m` khởi tạo tương ứng nằm trong `resources/params/`. Script này chịu trách nhiệm tạo file `.sldd`, khai báo toàn bộ parameter và thiết lập liên kết giữa các dictionary.

Sau mỗi lần `git pull`, bắt buộc phải chạy lại các script khởi tạo để tái tạo các file `.sldd` cục bộ.

## Cấu trúc script khởi tạo

Các script khởi tạo hiện có trong `resources/params/`:

| Script | Dictionary được tạo | Mô tả |
|---|---|---|
| `HelicopterParams.m` | `Helicopter.sldd` | Parameter dùng chung toàn mô hình, liên kết tới các `.sldd` con |
| `RotorParams.m` | `Rotor.sldd` | Parameter thuộc logic rotor |
| `MainRotorParams.m` | `MainRotor.sldd` | Parameter riêng của main rotor |
| `FuselageParams.m` | `Fuselage.sldd` | Parameter thuộc logic fuselage |

## Quy trình sau khi pull

Sau khi pull code về, chạy lần lượt các script theo thứ tự từ dictionary con lên dictionary cha:

```matlab
cd('resources/params')
run('RotorParams.m')
run('MainRotorParams.m')
run('FuselageParams.m')
run('HelicopterParams.m')   % chạy sau cùng vì có liên kết tới các .sldd con
```

## Cấu trúc một file script khởi tạo

Mỗi script `.m` phải tuân theo cấu trúc sau:

```matlab
% RotorParams.m - Khởi tạo Rotor.sldd
% Chạy script này sau khi pull để tái tạo file dictionary

ddPath = fullfile(fileparts(mfilename('fullpath')), 'Rotor.sldd');

% Tạo mới hoặc mở lại dictionary
if exist(ddPath, 'file')
    dd = Simulink.data.dictionary.open(ddPath);
    dd.discardChanges();
else
    dd = Simulink.data.dictionary.create(ddPath);
end

dSec = getSection(dd, 'Design Data');

% --- Khai báo parameter ---
% addOrUpdate(dSec, 'TênParam', Simulink.Parameter(giá_trị));
addOrUpdate(dSec, 'ROT_Radius_P',     Simulink.Parameter(5.18));
addOrUpdate(dSec, 'ROT_NBlades_P',    Simulink.Parameter(4));
% ... thêm parameter mới vào đây

saveChanges(dd);
disp('Rotor.sldd đã được tạo/cập nhật.');

% --- Hàm nội bộ ---
function addOrUpdate(section, name, value)
    try
        entry = getEntry(section, name);
        entry.Value = value;
    catch
        addEntry(section, name, value);
    end
end
```

Script khởi tạo của dictionary cha (`Helicopter.sldd`) phải thiết lập thêm liên kết tới các dictionary con:

```matlab
% HelicopterParams.m - Khởi tạo Helicopter.sldd và liên kết các .sldd con

ddPath = fullfile(fileparts(mfilename('fullpath')), 'Helicopter.sldd');

if exist(ddPath, 'file')
    dd = Simulink.data.dictionary.open(ddPath);
    dd.discardChanges();
else
    dd = Simulink.data.dictionary.create(ddPath);
end

% Liên kết các dictionary con
dd.addDataSource(fullfile(fileparts(mfilename('fullpath')), 'Rotor.sldd'));
dd.addDataSource(fullfile(fileparts(mfilename('fullpath')), 'MainRotor.sldd'));
dd.addDataSource(fullfile(fileparts(mfilename('fullpath')), 'Fuselage.sldd'));

dSec = getSection(dd, 'Design Data');

% --- Khai báo parameter dùng chung ---
addOrUpdate(dSec, 'HELI_GravAccel_P', Simulink.Parameter(9.81));
% ... thêm parameter mới vào đây

saveChanges(dd);
disp('Helicopter.sldd đã được tạo/cập nhật.');
```

## Quy tắc chọn `.sldd`

- Dùng `Helicopter.sldd` cho parameter dùng chung ở cấp toàn mô hình; dictionary này liên kết tới các `.sldd` con.
- Dùng `Rotor.sldd` cho parameter thuộc logic rotor chung.
- Dùng `MainRotor.sldd` cho parameter riêng của main rotor.
- Dùng `Fuselage.sldd` cho parameter chỉ thuộc logic fuselage.
- Với file `.slx` mới, xác định rõ dùng lại `.sldd` hiện có hay cần thêm dictionary mới trước khi phát triển.

## Thêm parameter mới

Khi cần thêm parameter mới, **không mở MATLAB Data Dictionary Editor** để thêm trực tiếp. Thay vào đó:

1. Mở file script `.m` tương ứng với dictionary chứa parameter đó.
2. Thêm dòng `addOrUpdate(dSec, 'TênParam', Simulink.Parameter(giá_trị));` vào phần khai báo parameter.
3. Chạy lại script để cập nhật dictionary.
4. Commit file `.m` vào Git (không commit file `.sldd`).

## Tạo dictionary mới

Khi cần thêm `.sldd` mới cho một subsystem:

Quy tắc đặt tên:

- Tên file `.sldd` và script `.m` phải ngắn gọn, rõ phạm vi, ví dụ `TailRotor.sldd` / `TailRotorParams.m`.
- Lưu script `.m` trong `resources/params/`.
- Chỉ tạo dictionary mới khi parameter cần tách riêng theo subsystem; không tạo trùng phạm vi với dictionary đã có.

Quy trình:

1. Tạo file script `<TênSubsystem>Params.m` theo cấu trúc mẫu ở trên.
2. Nếu dictionary mới cần được tham chiếu từ `Helicopter.sldd`, thêm lệnh `addDataSource` vào `HelicopterParams.m`.
3. Chạy script để kiểm tra dictionary được tạo đúng.
4. Liên kết model `.slx` tương ứng tới dictionary mới bằng MATLAB command:

```matlab
set_param('TênModel', 'DataDictionary', 'resources/params/TailRotor.sldd');
save_system('TênModel');
```

5. Commit file `.m` mới và file `.slx` đã cập nhật vào Git.

## Liên kết `.sldd` với model `.slx`

Liên kết bằng MATLAB command (khuyến nghị, để đảm bảo nhất quán):

```matlab
set_param('TênModel', 'DataDictionary', 'resources/params/Rotor.sldd');
save_system('TênModel');
```

Liên kết bằng Simulink UI:

1. Mở file `.slx` cần cấu hình.
2. Vào `Model Settings`.
3. Chọn `External Data`.
4. Tại mục `Data Dictionary`, chọn `Browse`.
5. Liên kết tới file `.sldd` phù hợp trong `resources/params/`.
6. Lưu model sau khi liên kết xong.


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

- Nếu tính năng làm thay đổi parameter, phải cập nhật trong script `*Params.m` tương ứng (không sửa trực tiếp trong SLDD Editor), cập nhật đồng thời file interface và [Google Sheets](https://docs.google.com/spreadsheets/d/1OIQVjcaQ8DKk69Lxzy_aSgkTthKjZHlSkRt-WTQtv9E/edit?gid=0#gid=0).
- Chỉ commit file `.m` và `.slx`; không commit file `.sldd`.
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
2. Liên kết file `.slx` mới với `.sldd` phù hợp bằng MATLAB command.
3. Nếu cần thêm parameter mới, mở file script `.m` tương ứng trong `resources/params/` và thêm vào đó, sau đó chạy lại script để cập nhật dictionary.
4. Nếu cần tạo dictionary mới, tạo script `<TênSubsystem>Params.m` mới, cập nhật liên kết trong `HelicopterParams.m` nếu cần.
5. Cập nhật interface và Google Sheets nếu có thay đổi tín hiệu hoặc parameter.
6. Chạy kiểm tra mô phỏng để xác nhận subsystem mới hoạt động đúng.


## 3. Commit local

Chỉ commit các file liên quan trực tiếp đến thay đổi.

Thường bao gồm:

- file `.slx` mới hoặc file `.slx` đã tích hợp
- file script `.m` trong `resources/params/` nếu có thay đổi parameter hoặc thêm dictionary mới
- file interface
- tài liệu liên quan như `Readme.md`

Không commit file `.sldd` — các file này được sinh ra từ script và nằm trong `.gitignore`.

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
2. **`run init scripts`** — chạy lại các script `*Params.m` để tái tạo `.sldd`
3. `create branch`
4. `create new subsystem .slx`
5. `link .sldd` — liên kết model tới dictionary bằng MATLAB command
6. `update parameter in *Params.m script` — không sửa trực tiếp trong SLDD Editor
7. `update interface`
8. `simulate and verify`
9. `commit` — chỉ commit `.slx`, `.m`, interface, docs; **không commit `.sldd`**
10. `push branch`
11. `review`
12. `merge to master`

Main rotor

# Phân chia nhiệm vụ
- Vui lòng xem qua nội dung phân chia nhiệm vụ tại [Hệ thống](https://docs.google.com/spreadsheets/d/1E3evOJmuEFXV8uu241oN48Fo-u8azcXVNiiyphNGNEE/edit?gid=0#gid=0)