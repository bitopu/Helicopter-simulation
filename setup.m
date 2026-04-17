%% Script Setup: Chạy cấu hình thông số theo thứ tự ưu tiên (Level)
% Mục tiêu: Tự động chạy Level1 trước, sau đó đến các Level cao hơn.

fprintf('--- Đang khởi tạo thông số dự án theo thứ tự ưu tiên ---\n');

% 1. Xác định đường dẫn
setupFolder = fullfile('resources', 'setup'); 
if ~exist(setupFolder, 'dir')
    error('Không tìm thấy thư mục setup tại: %s', fullfile(pwd, setupFolder));
end

% 2. Lấy danh sách tất cả các file *Params.m
files = dir(fullfile(setupFolder, '*Params.m'));

if isempty(files)
    fprintf(' [!] Không tìm thấy file *Params.m nào trong thư mục %s\n', setupFolder);
else
    % 3. Sắp xếp danh sách file theo bảng chữ cái
    % Vì bạn đặt tên là "Level1...", "Level2...", việc sắp xếp này 
    % sẽ đảm bảo Level 1 luôn đứng trước Level 2.
    [~, idx] = sort({files.name});
    files = files(idx);

    % 4. Vòng lặp chạy từng file
    for i = length(files):-1:1
        fileName = files(i).name;
        filePath = fullfile(files(i).folder, fileName);
        
        try
            % Hiển thị thông tin Level đang chạy
            fprintf('  [EXECUTING] %s...', fileName);
            
            % Thực thi script
            run(filePath); 
            
            fprintf(' Done.\n');
        catch ME
            fprintf(' FAILED!\n');
            warning('Lỗi tại %s: %s', fileName, ME.message);
        end
    end
end

fprintf('--- Hoàn tất thiết lập môi trường ---\n');

% Dọn dẹp biến tạm
clear setupFolder files i fileName filePath ME idx;