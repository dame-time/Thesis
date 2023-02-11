import os
import fnmatch

def test_file_name(filename, filterList):
    for filter in filterList:
        if filter in filename and len(os.listdir("./.objs")) > 0:
            return False
    return True

def get_cpp_files(base_dir):
    discard_keywords = ['imgui', 'ImGuizmo', "ImCurve", "ImGradient", "ImSequencer", "ImNodes", "ImPlot", "GraphEditor", "glm"]
    cpp_files = []
    for root, dirnames, filenames in os.walk(base_dir):
        for filename in fnmatch.filter(filenames, '*.cpp'):
            if '/Includes/libigl' not in root and test_file_name(filename, discard_keywords):
                cpp_files.append(os.path.join(root, filename))
    return cpp_files

cpp_files = get_cpp_files('./')
for file in cpp_files:
    print(file)
