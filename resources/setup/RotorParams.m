%% Script khởi tạo Rotor.sldd với Đơn vị (Units)
% Vị trí lưu: resources/params/Rotor.sldd

% 1. Thiết lập đường dẫn tương đối
%% Script khởi tạo Rotor.sldd (Bản sửa lỗi Shadowing)
% Đảm bảo MATLAB đứng đúng vị trí thư mục chứa script
scriptPath = fileparts(mfilename('fullpath'));
cd(scriptPath);

% 1. Thiết lập đường dẫn (Relative Path chuẩn hơn)
% Giả sử script đang ở thư mục 'setup', targetFolder sẽ là:
targetFolder = fullfile(scriptPath, '..', 'resources', 'params');
slddName = 'Rotor.sldd';
slddPath = fullfile(targetFolder, slddName);

% 3. Mở hoặc Tạo mới
if exist(slddPath, 'file')
    ddObj = Simulink.data.dictionary.open(slddPath);
else
    if ~exist(targetFolder, 'dir'), mkdir(targetFolder); end
    ddObj = Simulink.data.dictionary.create(slddPath);
end

% 4. Truy cập Design Data
dSection = getSection(ddObj, 'Design Data');


% 4. Danh sách tham số cập nhật (Thêm cột đơn vị)
% Cấu trúc: {Tên biến, Giá trị, Kiểu dữ liệu, Đơn vị}
dataMap = {
    'RT_RotorRadius_P',          7.82,                'double',  'm';
    'RT_BladeFlapInertia_P',     2500,                'double',  'kg*m^2';
    'RT_HingeFlapPos_P',         0.05,                'double',  'm';
    'RT_BEDistFromEffSta_A',     linspace(0.05,1,20)','double',  'm';
    'RT_BEMassFromHinge_A',      ones(20,1)*5.7,      'double',  'kg';
    'RT_BEDistFromHinge_A',      linspace(0.05,1,20)','double',  'm';
};
% 6. Thao tác an toàn
for i = 1:size(dataMap, 1)
    pName = dataMap{i,1}; pVal = dataMap{i,2}; pType = dataMap{i,3}; pUnit = dataMap{i,4};
    
    entryObj = find(dSection, 'Name', pName);
    
    % Khởi tạo đối tượng Parameter
    newParam = Simulink.Parameter;
    newParam.Value = pVal;
    newParam.DataType = pType;
    newParam.DocUnits = pUnit;
    
    if isempty(entryObj)
        addEntry(dSection, pName, newParam);
    else
        setValue(getEntry(dSection, pName), newParam);
    end
end

% 7. Quan trọng: Lưu và Đóng ngay lập tức trong file này
saveChanges(ddObj);
close(ddObj); 

% Giải phóng biến để tránh script khác dùng nhầm ddObj đã đóng
clear ddObj dSection pName pVal pType pUnit entryObj newParam dataMap;