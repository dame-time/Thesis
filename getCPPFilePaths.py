import os
import fnmatch

def get_cpp_files(base_dir):
    cpp_files = []
    for root, dirnames, filenames in os.walk(base_dir):
        for filename in fnmatch.filter(filenames, '*.cpp'):
            if '/Includes/' not in root:
                cpp_files.append(os.path.join(root, filename))
    return cpp_files

cpp_files = get_cpp_files('./')
for file in cpp_files:
    print(file)
