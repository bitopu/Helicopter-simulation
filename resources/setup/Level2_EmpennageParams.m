%% Script khoi tao Rotor.sldd
% Script nay tao/cap nhat dictionary Rotor.sldd va ghi cac parameter rotor.

% Dam bao MATLAB dang dung tai thu muc chua script
scriptPath = fileparts(mfilename('fullpath'));
cd(scriptPath);

% 1. Thiet lap duong dan
paramsFolder = fullfile(scriptPath, '..', 'params');
rotorSlddName = 'Empennage.sldd';
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
    'EP_AirDensity_P',            1.225, 'double', 'kg/m^3', 'Khối lượng riêng của không khí';

    'EP_RotorRadius_P',           7.82,  'double', 'm',      'Bán kính rotor chính';

    'EP_CoGPos_P',                0.0,   'double', 'm',      'Vị trí dọc của trọng tâm x_cg so với mốc tham chiếu';

    'EP_TailPlanePos_P',          5.0,   'double', 'm',      'Vị trí dọc của cánh đuôi ngang l_tp';
    'EP_TailPlaneArea_P',         1.0,   'double', 'm^2',    'Diện tích cánh đuôi ngang S_tp';
    'EP_TailPlaneSetAng_P',       0.0,   'double', 'rad',    'Góc đặt cánh đuôi ngang alpha_tp0';
    'EP_TailPlaneLiftSlope_P',    3.5,   'double', '-',      'Hệ số độ dốc lực nâng cánh đuôi ngang a0_tp';
    'EP_TailPlaneLiftCoeffLim_P', 2.0,   'double', '-',      'Giới hạn hệ số lực cánh đuôi ngang Cz_tpl';
    'EP_TailPlaneAzimuth_P',      0.0,   'double', 'deg',    'Góc phương vị của cánh đuôi ngang';
    'EP_OutOfWakeAzimuth_P',      30,    'double', 'deg',    'Ngưỡng chênh lệch phương vị để cánh đuôi ra khỏi rotor wake';
    'EP_SkewAngleLwrLim_P',       10,    'double', 'deg',    'Giới hạn dưới của góc skew wake';
    'EP_SkewAngleUpprLim_P',      45,    'double', 'deg',    'Giới hạn trên của góc skew wake';
    'EP_WakeInitialInfluence_P',  0.7,   'double', '-',      'Hệ số ảnh hưởng wake ban đầu k0 lên cánh đuôi ngang';

    'EP_FinPos_P',                5.0,   'double', 'm',      'Vị trí dọc của cánh đuôi đứng l_fn';
    'EP_FinHeight_P',             1.0,   'double', 'm',      'Độ cao cánh đuôi đứng h_fn';
    'EP_FinSetAng_P',             0.0,   'double', 'rad',    'Góc đặt cánh đuôi đứng beta_fn0';
    'EP_FinLiftSlope_P',          3.5,   'double', '-',      'Hệ số độ dốc lực bên của fin b0_fn';
    'EP_FinLiftCoeffLim_P',       2.0,   'double', '-',      'Giới hạn hệ số lực bên của fin Cy_fnl';
    'EP_FinArea_P',               1.0,   'double', 'm^2',    'Diện tích cánh đuôi đứng S_fn';
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
