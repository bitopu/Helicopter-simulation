%% Script khoi tao Rotor.sldd
% Script nay tao/cap nhat dictionary Rotor.sldd va ghi cac parameter rotor.

% Dam bao MATLAB dang dung tai thu muc chua script
scriptPath = fileparts(mfilename('fullpath'));
cd(scriptPath);

% 1. Thiet lap duong dan
paramsFolder = fullfile(scriptPath, '..', 'params');
engineSlddName = 'Engine.sldd';
engineSlddPath = fullfile(paramsFolder, engineSlddName);

% 2. Dong dictionary de tranh loi shadowing.
% Dung '-discard' vi .sldd duoc tai tao tu script, khong phai nguon chinh tay.
Simulink.data.dictionary.closeAll('-discard');

% 3. Mo hoac tao moi Engine.sldd
if exist(engineSlddPath, 'file')
    ddObj = Simulink.data.dictionary.open(engineSlddPath);
    fprintf(' Dang cap nhat file: %s\n', engineSlddName);
else
    if ~exist(paramsFolder, 'dir')
        mkdir(paramsFolder);
    end
    ddObj = Simulink.data.dictionary.create(engineSlddPath);
    fprintf(' Da tao moi file: %s\n', engineSlddName);
end

% 4. Truy cap Design Data
dSection = getSection(ddObj, 'Design Data');

% 5. Danh sach tham so cap nhat
% Cau truc: {Ten bien, Gia tri, Kieu du lieu, Don vi, Mo ta}
dataMap = {
    'EG_BladesInteria_P',       22000,            'double', 'kg*m^2', 'Momen quán tính của 2 blade';
    'EG_HubInteria_P',          1500,             'double', 'kg*m^2', 'Momen quán tính của hub';
    'EG_TurbinInteria_P',       6500,             'double', 'kg*m^2', 'Momen quán tính của turbin';
    'EG_TailRotorGearRatio_P',  4.6,              'double', 'NA',     'Tỷ số truyền tail rotor';
    'EG_EngineTorqueMax_P',     55000,            'double', 'N*m',    'Momen xoắn tối đa của động cơ';
    'EG_EngineGain_P',          1.33,             'double', 'NA',     'Hệ số gian Ke';
    'EG_TauEngine10Coeff_P',    0.1,              'double', 'NA',     'Hệ số sử dụng trong tính toán tham số tau1';
    'EG_TauEngine11Coeff_P',    -0.03,            'double', 'NA',     'Hệ số sử dụng trong tính toán tham số tau1';
    'EG_TauEngine20Coeff_P',    0.6,              'double', 'NA',     'Hệ số sử dụng trong tính toán tham số tau2';
    'EG_TauEngine21Coeff_P',    -0.5,             'double', 'NA',     'Hệ số sử dụng trong tính toán tham số tau2';
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
    paramsFolder SlddName SlddPath scriptPath;

fprintf('--- Hoan tat cap nhat Engine.sldd ---\n');