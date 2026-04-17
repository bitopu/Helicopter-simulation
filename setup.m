%% Script Setup: Chạy toàn bộ cấu hình thông số (*Params.m)
% Mục tiêu: Tự động tìm và thực thi tất cả file thông số trong thư mục setup

fprintf('--- Đang khởi tạo thông số dự án ---\n');

% 1. Xác định đường dẫn đến thư mục setup
% Nếu script này nằm ở thư mục gốc, setupFolder = 'setup'
% Nếu script này nằm trong setup, setupFolder = pwd
setupFolder = 'resources\setup'; 

if ~exist(setupFolder, 'dir')
    error('Không tìm thấy thư mục setup tại: %s', fullfile(pwd, setupFolder));
end

% 2. Tìm tất cả các file có đuôi *Params.m
files = dir(fullfile(setupFolder, '*Params.m'));

if isempty(files)
    fprintf(' [!] Không tìm thấy file *Params.m nào trong thư mục %s\n', setupFolder);
else
    % 3. Vòng lặp chạy từng file
    for i = 1:length(files)
        fileName = files(i).name;
        filePath = fullfile(files(i).folder, fileName);
        
        try
            fprintf('  [RUNNING] %s...', fileName);
            run(filePath); % Thực thi file script
            fprintf(' Done.\n');
        catch ME
            fprintf(' FAILED!\n');
            warning('Lỗi khi chạy file %s: %s', fileName, ME.message);
        end
    end
end

fprintf('--- Hoàn tất thiết lập môi trường ---\n');

% Dọn dẹp biến tạm sau khi setup xong (tùy chọn)
clear setupFolder files i fileName filePath ME;