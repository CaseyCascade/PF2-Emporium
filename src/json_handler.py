import json 
import os 

class Item: 
    def __init__(self, name):
        return 
    def write_to_file(filepath):
        return 

def write_items_to_file(json_file_path): #TODO
    print("Yup")
    return

def file_exists_in_data(filename, data_dir):
    for file in os.listdir(data_dir):
        name, extension = os.path.splitext(file)
        if filename == name and extension == '.txt':
            return True
    return False 

def check_for_new_json_files(json_dir, data_dir):
    for file in os.listdir(json_dir):
        name, extension = os.path.splitext(file)
        if extension != '.json': 
            continue 
        if not file_exists_in_data(name, data_dir):
            write_items_to_file(os.path.abspath(file))
    return 

script_directory = os.path.dirname(os.path.abspath(__file__))
json_directory = 'json_input'
data_directory = 'data/core_items'

full_json_path = os.path.join(script_directory, json_directory)
full_data_path = os.path.join(script_directory, data_directory)

check_for_new_json_files(full_json_path, full_data_path)