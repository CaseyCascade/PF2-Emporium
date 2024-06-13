import json 
import os 

debug = True

class Item: 
    name = None
    page = None
    gold = None
    level = None
    bulk = None
    source = None
    price = None
    coin = None
    entry = None
    traits = []
    remaster = False
    lock_entry = False

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

    def set_entry(self, entry):
        self.entry = entry 
        self.lock_entry = True

    def add_trait(self, trait): #TODO we need to do some string parsing on input traits (Crossbow|PC1 && two-hand <d8>)
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
        self.lock_entry = False

    def print(self):
        print("Name: ", self.name)
        print("Source: ", self.source)
        print("Page: ", self.page)
        print("Gold: ", self.gold)
        print("Level: ", self.level)
        print("Bulk: ", self.bulk)
        print("Entry: ", self.entry)
        print("Traits: ")
        for trait in self.traits:
            print(trait)
        print()
        

    def write_to_file(self, filepath):
        if not self.name:
            return 
        with open(filepath, 'a') as file:
            file.write("NAME\n")
            file.write(self.name)
            file.write("\nSOURCE\n")
            file.write(self.source)
            file.write("\nPAGE\n")
            file.write(str(self.page))
            file.write("\nGOLD\n")
            file.write(str(self.gold))
            file.write("\nLEVEL\n")
            file.write(str(self.level))
            file.write("\nBULK\n")
            file.write(str(self.bulk))
            file.write("\nENTRY\n")
            file.write(self.entry)
            file.write("\nTRAITS\n")
            for trait in self.traits:
                file.write(trait)
                file.write('\n')
            file.write('\n')
        return 
    
def process_data(item: Item, key, value): #TODO Needs testing
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
    elif key == 'entries' and not item.lock_entry:
        item.set_entry(value)
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
                    file_name = os.path.splitext(os.path.basename(json_file_path))[0]
                    file_name = file_name + '.txt'
                    data_file_path = os.path.join(full_data_path, file_name)
                    instance.write_to_file(data_file_path)
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
            if debug:
                print("Processing ", file)
            process_file(os.path.join(json_dir, file))
        else:
            if debug: 
                print(file, "already exists as a .txt. Will not be updated.")
    return 

trait_keys = ['category', 'subCategory', 'damage', 'damageType', 'group', 'traits', 'access']
new_item = Item()

repo_directory = os.path.dirname(os.path.abspath(os.path.dirname(os.path.abspath(__file__)))) 
json_directory = 'json_input'
data_directory = 'data/core_items'

full_json_path = os.path.join(repo_directory, json_directory)
full_data_path = os.path.join(repo_directory, data_directory)

check_for_new_json_files(full_json_path, full_data_path)