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
    'RT_BladeFlapInertia_P', 2500,                'double', 'kg*m^2', 'Mo-men quan tinh dap cua la bai';
    'RT_HingeFlapPos_P',     0.05,                'double', 'm',      'Khoang cach tu tam rotor den ban le dap';
    'RT_BEDistFromEffSta_A', linspace(0.05,1,20)','double', 'm',      'Khoang cach tu tram hieu dung den goc la bai';
    'RT_BEMassFromHinge_A',  ones(20,1)*5.7,      'double', 'kg',     'Phan bo khoi luong la bai tai cac phan doan';
    'RT_BEDistFromHinge_A',  linspace(0.05,1,20)','double', 'm',      'Khoang cach tu ban le den cac phan doan blade element';
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
