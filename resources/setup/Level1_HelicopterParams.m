%% Script khoi tao Helicopter.sldd va link toi Rotor.sldd
% Script nay tao/cap nhat dictionary cha va thiet lap data source toi
% dictionary con Rotor.sldd.

% Dam bao MATLAB dang dung tai thu muc chua script
scriptPath = fileparts(mfilename('fullpath'));
cd(scriptPath);

% 1. Thiet lap duong dan
paramsFolder = fullfile(scriptPath, '..', 'params');
heliSlddName = 'Helicopter.sldd';
heliSlddPath = fullfile(paramsFolder, heliSlddName);
rotorSlddName = 'Rotor.sldd';
rotorSlddPath = fullfile(paramsFolder, rotorSlddName);

% Dam bao thu muc params nam tren MATLAB path de addDataSource resolve duoc file
if isempty(strfind(path, paramsFolder))
    addpath(paramsFolder);
end

% 2. Dong dictionary de tranh loi shadowing.
% Dung '-discard' vi .sldd duoc tai tao tu script, khong phai nguon chinh tay.
Simulink.data.dictionary.closeAll('-discard');

% 3. Mo hoac tao moi Helicopter.sldd
if exist(heliSlddPath, 'file')
    ddObj = Simulink.data.dictionary.open(heliSlddPath);
    fprintf(' Dang cap nhat file: %s\n', heliSlddName);
else
    if ~exist(paramsFolder, 'dir')
        mkdir(paramsFolder);
    end
    ddObj = Simulink.data.dictionary.create(heliSlddPath);
    fprintf(' Da tao moi file: %s\n', heliSlddName);
end

% 3.5. Lien ket Rotor.sldd vao Helicopter.sldd neu chua ton tai
currentSources = ddObj.DataSources;
isRotorLinked = any(strcmp(currentSources, rotorSlddPath));

if ~isRotorLinked
    if exist(rotorSlddPath, 'file')
        addDataSource(ddObj, rotorSlddName);
        fprintf('  [LINKED] Da ket noi %s vao %s\n', rotorSlddName, heliSlddName);
    else
        warning('Khong tim thay file %s de lien ket!', rotorSlddName);
    end
end

% 4. Truy cap Design Data
dSection = getSection(ddObj, 'Design Data');

% 5. Danh sach tham so cap nhat
% Cau truc: {Ten bien, Gia tri, Kieu du lieu, Don vi, Mo ta}
dataMap = {
    'HEL_Mass_P', 7.82, 'double', 'kg', 'Khoi luong helicopter';
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
    paramsFolder heliSlddName heliSlddPath rotorSlddName rotorSlddPath ...
    currentSources isRotorLinked scriptPath;

fprintf('--- Hoan tat cap nhat Helicopter.sldd va lien ket du lieu ---\n');
