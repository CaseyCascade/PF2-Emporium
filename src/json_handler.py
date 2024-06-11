import json 
import os 

trait_keys = ['category', 'subCategory', 'type', 'damageType', 'group', ]
class Item: 
    name = None
    page = None
    gold = None
    level = None
    bulk = None
    sources = []
    entries = []
    traits = []
    remaster = False

    def __init__(self):
        return 
    
    def set_name(self, name):
        self.name = name

    def set_page(self, page):
        self.page = page
        
    def set_gold (self, coin, amount): # TODO change to allow the key value to be passed through instead
        if coin == 'pp':
            self.gold = amount * 10
        elif coin == 'gp':
            self.gold = amount
        elif coin == 'sp':
            self.gold = amount/10
        elif coin == 'cp': 
            self.gold = amount/100
        else:
            print("Coin Value Not Recognized: ", coin)

    def set_level (self, level):
        self.level = level 

    def set_bulk (self, bulk): #TODO needs specific entry case similar to set_gold
        self.bulk = bulk 

    def add_source(self, source):
        self.sources.append(source)

    def add_entry(self, entry):
        self.entries.append(entry)

    def add_trait(self, trait):
        self.traits.append(trait)

    def set_remaster(self):
        self.remaster = True

    def write_to_file(filepath):
        return 
    
def walk(data):
    if isinstance(data, dict):
        for key, value in data.items():
            print(f'Key: {key}')
            # print(f'Key: {key}, Value: {value}')
            walk(value)
    elif isinstance(data, list):
        for index, item in enumerate(data):
            #print(f'Index: {index}, Item: {item}')
            walk(item)
    #else:
        #print(f'Value: {data}')

def write_items_to_file(json_file_path): #TODO
    print(json_file_path)
    with open(json_file_path, 'r') as file:
        data = json.load(file)
        walk(data)

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
            write_items_to_file(os.path.join(json_dir, file))
    return 

repo_directory = os.path.dirname(os.path.abspath(os.path.dirname(os.path.abspath(__file__)))) 
json_directory = 'json_input'
data_directory = 'data/core_items'

full_json_path = os.path.join(repo_directory, json_directory)
full_data_path = os.path.join(repo_directory, data_directory)

check_for_new_json_files(full_json_path, full_data_path)