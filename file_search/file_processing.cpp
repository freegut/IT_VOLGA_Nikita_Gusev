#include <iostream>
#include <filesystem>
#include <vector>
#include <thread>

namespace fs = std::filesystem;

void process_file(const fs::path& file_path) {
    std::cout << "Processing file: " << file_path << std::endl;
    // Здесь можно добавить логику обработки файла
}

void process_directory(const fs::path& dir_path) {
    for (const auto& entry : fs::recursive_directory_iterator(dir_path)) {
        if (entry.is_regular_file()) {
            process_file(entry.path());
        }
    }
}

void process_drives(const std::vector<char>& drives) {
    std::vector<std::thread> threads;

    for (const auto& drive : drives) {
        if (drive == '\0') break;
        fs::path drive_path(drive);
        threads.emplace_back(process_directory, drive_path);
    }

    for (auto& t : threads) {
        t.join();
    }
}

int main() {
    std::vector<char> drives(GetLogicalDriveStrings(0, NULL));
    if (drives.empty()) {
        std::cerr << "Failed to get drive letters." << std::endl;
        return 1;
    }

    GetLogicalDriveStrings(drives.size(), drives.data());

    process_drives(drives);

    return 0;
}