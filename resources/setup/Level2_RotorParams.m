%% Script khoi tao Rotor.sldd
% Script nay tao/cap nhat dictionary Rotor.sldd va ghi cac parameter rotor.

% Dam bao MATLAB dang dung tai thu muc chua script
scriptPath = fileparts(mfilename('fullpath'));
cd(scriptPath);

% 1. Thiet lap duong dan
paramsFolder = fullfile(scriptPath, '..', 'params');
rotorSlddName = 'Rotor.sldd';
rotorSlddPath = fullfile(paramsFolder, rotorSlddName);

% 2. Dong dictionary de tranh loi shadowing.
% Dung '-discard' vi .sldd duoc tai tao tu script, khong phai nguon chinh tay.
Simulink.data.dictionary.closeAll('-discard');

% 3. Mo hoac tao moi Rotor.sldd
if exist(rotorSlddPath, 'file')
    ddObj = Simulink.data.dictionary.open(rotorSlddPath);
    fprintf(' Dang cap nhat file: %s\n', rotorSlddName);
else
    if ~exist(paramsFolder, 'dir')
        mkdir(paramsFolder);
    end
    ddObj = Simulink.data.dictionary.create(rotorSlddPath);
    fprintf(' Da tao moi file: %s\n', rotorSlddName);
end

% 4. Truy cap Design Data
dSection = getSection(ddObj, 'Design Data');

% 5. Danh sach tham so cap nhat
% Cau truc: {Ten bien, Gia tri, Kieu du lieu, Don vi, Mo ta}
dataMap = {
    'RT_RotorRadius_P',      7.82,                'double', 'm',      'Ban kinh dinh muc cua rotor chinh';
    'RT_BladeFlapInertia_P', 1380,                'double', 'kg*m^2', 'Mo-men quan tinh dap cua la bai';
    'RT_HingeFlapPos_P',     0.05,                'double', 'm',      'Khoang cach tu tam rotor den ban le dap';
    'RT_BEDistFromEffSta_A', linspace(0.15,1,20)','double', 'm',      'Khoang cach tu tram hieu dung den goc la bai';
    'RT_BEMassFromHinge_A',  ones(20,1)*5.7,      'double', 'kg',     'Phan bo khoi luong la bai tai cac phan doan';
    'RT_BEDistFromHinge_A',  linspace(0.05,1,20)','double', 'm',      'Khoang cach tu ban le den cac phan doan blade element';
    'RT_BEMassFrHingeLead_A',ones(20,1)*5.7,      'double', 'kg',     'Phân bố khối lượng các phần tử cánh từ bản lề của lead';
    'RT_BEDistFrHingeLead_A',linspace(0.05,1,20)','double', 'kg',     'Khoảng cách từ bản lề lead lag đến phần tử cánh';
    'RT_HingeLeadPos_P',     0.15,                'double', 'NA',     'Vị trí bản lề lead lag theo R';
    'RT_BladeLeadInertia_P', 1380,                'double', 'kg*m^2', 'Mô men quán tính lead lag của cánh';
    'RT_AirDensity_P',       1.225,               'double', 'kg/m^2', 'Khối lượng riêng của không khí';
    'RT_BladeSegment_P',     20,                  'double', '',       'Số lượng phần tử'
    'RT_SigmaAvgUH60_P',     0.0826,                'double', 'NA',     'Solidity trung bình của rotor (tỷ lệ diện tích cánh / đĩa rotor) lấy theo UH60';
    'RT_NumberOfBlades_P',   4,                'double', 'NA', 'Số lượng cánh rotor';
    'RT_TaperedRatio_P',       3/7,               'double', 'NA', 'Tỷ lệ thuôn cánh (tỷ lệ chord gốc / chord đầu cánh)';
    'RT_NondimRadialDisRef_P', 3/4,                'double', 'NA', 'Vị trí bán kính không thứ nguyên tại điểm cách 3/4 gốc cánh';
    'RT_SonicVel_P',       340,               'double', 'm/s', 'Vận tốc âm thanh trong không khí';
    'RT_Weight_P',       128*9.81,               'double', 'N', 'Khối lượng cả cánh quạt';
    };

% 6. Thao tac ghi du lieu vao SLDD
for i = 1:size(dataMap, 1)
    pName = dataMap{i, 1};
    pVal = dataMap{i, 2};
    pType = dataMap{i, 3};
    pUnit = dataMap{i, 4};
    pDesc = dataMap{i, 5};

    entryObj = find(dSection, 'Name', pName);

    newParam = Simulink.Parameter;
    newParam.Value = pVal;
    newParam.DataType = pType;
    newParam.DocUnits = pUnit;
    newParam.Description = pDesc;

    if isempty(entryObj)
        addEntry(dSection, pName, newParam);
        fprintf('  [NEW] %s\n', pName);
    else
        setValue(getEntry(dSection, pName), newParam);
        fprintf('  [UPDATED] %s\n', pName);
    end
end

% 7. Luu va dong
saveChanges(ddObj);
close(ddObj);

% Giai phong bien tam
clear ddObj dSection pName pVal pType pUnit pDesc entryObj newParam dataMap ...
    paramsFolder rotorSlddName rotorSlddPath scriptPath;

fprintf('--- Hoan tat cap nhat Rotor.sldd ---\n');
