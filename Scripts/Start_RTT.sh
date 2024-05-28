#!/bin/bash

# 设置默认值
reset=false

# 显示帮助信息函数
show_help() {
    echo "用法: $(basename "$0") [--file <文件名>] [--reset] [-h]"
    echo
    echo "参数:"
    echo "  --file <文件名>   指定要处理的文件名"
    echo "  --reset           执行pyocd重置操作"
    echo "  -h, --help        显示帮助信息"
}

# 获取文件名并检查重置标志
while [[ $# -gt 0 ]]; do
    case "$1" in
        --file|-f)
            file="$2"
            shift 2
            ;;
        --reset|-r)
            reset=true
            shift
            ;;
        -h|--help)
            show_help
            exit 0
            ;;
        *)
            echo "未知选项: $1"
            show_help
            exit 1
            ;;
    esac
done

# 检查文件是否存在
if [ ! -f "$file" ]; then
    # 获取当前工作目录
    current_dir=$(dirname "$(readlink -f "$0")")
    file="$current_dir/../bin/Debug/S3_0.1.0.elf"
fi
pack_path="$current_dir/../Utilities/GD32F3x0_DFP.3.0.2.pack"
# 提取地址
echo "提取地址: $file"
address=0x$(nm "$file" | grep "_SEGGER_RTT" | awk '{print $1}')

# 如果需要重置，则执行重置操作
if [ "$reset" = true ]; then
    echo "执行命令: pyocd reset -t GD32F310F8 --pack $pack_path"
    pyocd reset -t GD32F310F8 --pack $pack_path
fi

# 打印并执行 RTT 命令
echo "执行命令: pyocd rtt -a $address -t GD32F310F8 --pack $pack_path"
pyocd rtt -a $address -t GD32F310F8 --pack $pack_path
