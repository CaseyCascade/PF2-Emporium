import json 
import os 

class Item: 
    name = None
    page = None
    gold = None
    level = None
    bulk = None
    source = None

    price = None
    coin = None
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

    def gold_ready(self):
        if self.price and self.coin:
            return True
        else:
            return False
        
    def set_price(self, price):
        self.price = price 
        if self.gold_ready():
            self.set_gold(self.coin, self.price)

    def set_coin(self, coin):
        self.coin = coin
        if self.gold_ready():
            self.set_gold(self.coin, self.price)

    def set_level (self, level):
        self.level = level 

    def set_bulk (self, bulk): #TODO needs specific entry case similar to set_gold
        self.bulk = bulk 

    def set_source(self, source):
        self.source = source

    def add_entry(self, entry):
        self.entries.append(entry)

    def add_trait(self, trait):
        self.traits.append(trait)

    def set_remaster(self):
        self.remaster = True

    def clear(self):
        self.name = None
        self.page = None
        self.gold = None
        self.level = None
        self.bulk = None
        self.source = None
        self.entries = []
        self.traits = []
        self.remaster = False

    def write_to_file(self, filepath):
        if not self.name:
            return 
        return 
    
def process_data(item: Item, key, value):
    if key == 'name':
        item.set_name(value)
    elif key == 'page':
        item.set_page(value)
    elif key == 'amount':
        item.set_price(value)
    elif key == 'coin':
        item.set_coin(value)
    elif key == 'level':
        item.set_level(value)
    elif key == 'bulk':
        item.set_bulk(value)
    elif key == 'source':
        item.set_source(value)
    elif key == 'entries':
        item.add_entry(value)
    elif key in trait_keys:
        item.add_trait(value)
        

        
    
def walk_item(data, new_item, previous_key):
    if isinstance(data, dict):
        for key, value in data.items():
            walk_item(value, new_item, key)
    elif isinstance(data, list):
        for index, item in enumerate(data):
            walk_item(item, new_item, previous_key)
    else:
        process_data(new_item, previous_key, data)

def process_file(json_file_path):
    instance = Item()
    with open(json_file_path, 'r') as file:
        data = json.load(file)
    if isinstance(data, dict): 
        for key, value in data.items():
            if isinstance(value, list):
                for index, item in enumerate(value):
                    walk_item(item, instance, None)
                    instance.write_to_file(full_data_path)
                    instance.clear()
    else:
        print("ERROR: Unusual JSON Formatting - No Outer List")

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
            process_file(os.path.join(json_dir, file))
    return 

trait_keys = ['category', 'subCategory', 'type', 'damageType', 'group', ]
new_item = Item()

repo_directory = os.path.dirname(os.path.abspath(os.path.dirname(os.path.abspath(__file__)))) 
json_directory = 'json_input'
data_directory = 'data/core_items'

full_json_path = os.path.join(repo_directory, json_directory)
full_data_path = os.path.join(repo_directory, data_directory)

check_for_new_json_files(full_json_path, full_data_path)