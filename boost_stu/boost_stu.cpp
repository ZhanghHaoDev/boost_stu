#include "boost_stu.h"

#include <iostream>
#include <fstream>

#include <boost/log/trivial.hpp>
#include <boost/version.hpp>
#include <boost/filesystem.hpp>
#include <boost/system/error_code.hpp>

boost_stu::boost_stu() = default;

boost_stu::~boost_stu() = default;

void boost_stu::print_boost_version(){
    BOOST_LOG_TRIVIAL(info) << "Boost 版本: " 
                            << BOOST_VERSION / 100000 << "."  // Major version
                            << BOOST_VERSION / 100 % 1000 << "."  // Minor version
                            << BOOST_VERSION % 100;  // Patch level
}

int boost_stu::boost_filesystem(){
    int err = 0;

    namespace fs = boost::filesystem;

    // 确保基础目录存在
    fs::path base_dir{"build"};
    if (!fs::exists(base_dir)) {
        if (!fs::create_directory(base_dir)) {
            std::cerr << "错误: 无法创建基础目录: " << base_dir << '\n';
            return 1;
        }
    }

    // 1. 路径操作
    fs::path p{base_dir / "example.txt"};
    std::cout << "文件名: " << p.filename() << '\n';
    std::cout << "扩展名: " << p.extension() << '\n';
    std::cout << "父路径: " << p.parent_path() << '\n';

    // 2. 文件和目录操作
    fs::path dir{base_dir / "example_directory"};
    fs::path file{base_dir / "example_file.txt"};
    fs::path copy_file{base_dir / "copy_example_file.txt"};
    fs::path copy_dir{base_dir / "copy_example_directory"};
    fs::path move_file{base_dir / "move_example_file.txt"};
    fs::path symlink{base_dir / "symlink_to_example_file"};

    // 创建目录
    try {
        if (fs::create_directory(dir)) {
            std::cout << "目录已创建: " << dir << '\n';
        } else {
            std::cout << "目录创建失败或目录已存在: " << dir << '\n';
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "错误: " << e.what() << '\n';
    }

    // 创建文件
    try {
        std::ofstream ofs(file.string());
        if (ofs) {
            ofs << "Hello, World!\n";
            std::cout << "文件已创建: " << file << '\n';
        } else {
            std::cout << "文件创建失败: " << file << '\n';
        }
        ofs.close();
    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << '\n';
    }

    // 删除文件
    try {
        if (fs::remove(file)) {
            std::cout << "文件已删除: " << file << '\n';
        } else {
            std::cout << "文件删除失败或文件不存在: " << file << '\n';
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "错误: " << e.what() << '\n';
    }

    // 复制文件
    try {
        std::ofstream ofs(file.string());
        ofs << "Hello, World!\n";
        ofs.close();
        fs::copy_file(file, copy_file);
        std::cout << "文件已复制: 从 " << file << " 到 " << copy_file << '\n';
    } catch (const fs::filesystem_error& e) {
        std::cerr << "错误: " << e.what() << '\n';
    }

    // 复制目录
    try {
        fs::copy(dir, copy_dir);
        std::cout << "目录已复制: 从 " << dir << " 到 " << copy_dir << '\n';
    } catch (const fs::filesystem_error& e) {
        std::cerr << "错误: " << e.what() << '\n';
    }

    // 移动文件
    try {
        fs::rename(copy_file, move_file);
        std::cout << "文件已移动: 从 " << copy_file << " 到 " << move_file << '\n';
    } catch (const fs::filesystem_error& e) {
        std::cerr << "错误: " << e.what() << '\n';
    }

    // 3. 文件状态查询
    // 查询文件或目录是否存在
    if (fs::exists(dir)) {
        std::cout << dir << " 存在.\n";
    } else {
        std::cout << dir << " 不存在.\n";
    }

    // 检测是不是目录
    if (fs::is_directory(dir)) {
        std::cout << dir << " 是一个目录.\n";
    } else {
        std::cout << dir << " 不是一个目录.\n";
    }

    // 检测是不是普通文件
    if (fs::is_regular_file(move_file)) {
        std::cout << move_file << " 是一个普通文件.\n";
    } else {
        std::cout << move_file << " 不是一个普通文件.\n";
    }

    // 获取文件大小
    try {
        std::cout << "文件大小: " << fs::file_size(move_file) << " 字节\n";
    } catch (const fs::filesystem_error& e) {
        std::cerr << "错误: " << e.what() << '\n';
    }

    // 4. 目录遍历
    // 遍历目录中的文件和子目录
    if (fs::exists(dir) && fs::is_directory(dir)) {
        std::cout << dir << " 是一个包含以下内容的目录:\n";
        for (const auto& entry : fs::directory_iterator(dir)) {
            std::cout << entry.path() << '\n';
        }
    } else {
        std::cout << dir << " 不是一个目录或不存在.\n";
    }

    // 递归遍历目录结构
    if (fs::exists(dir) && fs::is_directory(dir)) {
        std::cout << dir << " 是一个包含以下内容的目录:\n";
        for (const auto& entry : fs::recursive_directory_iterator(dir)) {
            std::cout << entry.path() << '\n';
        }
    } else {
        std::cout << dir << " 不是一个目录或不存在.\n";
    }

    // 5. 符号链接
    // 创建符号链接
    try {
        fs::create_symlink(move_file, symlink);
        std::cout << "符号链接已创建: " << symlink << " -> " << move_file << '\n';
    } catch (const fs::filesystem_error& e) {
        std::cerr << "错误: " << e.what() << '\n';
    }

    // 解析符号链接
    try {
        fs::path target = fs::read_symlink(symlink);
        std::cout << "符号链接 " << symlink << " 指向 " << target << '\n';
    } catch (const fs::filesystem_error& e) {
        std::cerr << "错误: " << e.what() << '\n';
    }

    // 判断符号链接的目标
    if (fs::is_symlink(symlink)) {
        std::cout << symlink << " 是一个符号链接.\n";
        fs::path target = fs::read_symlink(symlink);
        std::cout << "它指向 " << target << '\n';
    } else {
        std::cout << symlink << " 不是一个符号链接.\n";
    }

    // 6. 错误处理
    // 使用boost::system::error_code进行错误处理
    boost::system::error_code ec;
    fs::create_directory(base_dir / "error_directory", ec);
    if (ec) {
        std::cerr << "创建目录时出错: " << ec.message() << '\n';
    } else {
        std::cout << "目录已创建: " << base_dir / "error_directory" << '\n';
    }

    return err;
}