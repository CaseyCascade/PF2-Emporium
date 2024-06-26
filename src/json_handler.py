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

    def __init__(self):
        return 
    
    def set_name(self, name):
        if self.name == None:
            self.name = name

    def set_page(self, page):
        if self.page == None:
            self.page = page
        
    def set_gold (self, coin, amount): 
        if self.gold != None:
            return
        
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
        if self.level == None:
            self.level = level 

    def set_bulk (self, data): 
        if isinstance(data, str):
            elements = data.split()
            bulk = elements[0]
        else:
            bulk = data

        if bulk == 'L':
            self.bulk = 0.1
        elif bulk == '\u2014' or bulk == '-' or bulk == '\u2013' or bulk == 'varies':
            self.bulk = 0.0
        else:
            self.bulk = bulk 

    def set_source(self, source):
        if self.source == None:
            self.source = source

    def set_entry(self, entry):
        if self.entry == None:
            self.entry = entry 

    def add_trait(self, input):
        trait = input.lower() 
        parts = trait.split("<") # Weapon traits specifying damage, damage type, and range
        if len(parts) > 1:
            if parts[0] in self.traits:
                return
            else:
                self.traits.append(parts[0])
                return 
        parts = trait.split("|") # Separates source appending from some traits 
        if len(parts) > 1:
            if parts[0] in self.traits:
                return
            else:
                self.traits.append(parts[0])
                return 
        for identifier in reject_trait_identifiers: # Checks for traits to outright reject 
            if identifier in trait: 
                return
        if trait in self.traits:
            return 
        else:
            self.traits.append(trait) # If none apply, accept trait as is 

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
        
    def finalilze(self):
        if self.bulk == None:
            self.set_bulk(0)
        if self.gold == None: 
            self.set_gold('gp', 0)
        if self.level == None:
            self.set_level(0)

        if 'rune' in self.traits:
            self.name += ' Rune'

    def write_to_file(self, filepath):
        self.finalilze()
        if not self.name:
            return 
        if not self.entry:
            self.entry = "NA"
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
    
def process_data(item: Item, key, value): 
    if key == 'name' or key:
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
        item.set_entry(value)
    elif key in trait_keys: 
        item.add_trait(value)

def handle_variants(new_item: Item, data): #TODO Loop through our variants and create new items for each one 
    if isinstance(data, dict):
        for key, value in data.items():
            if key == 'variantType':
                return
            if key == 'level':
                return
            if key == 'price':
                return 
    elif isinstance(data, list):
        for index, item in enumerate(data):
            handle_variants(new_item, item)
            #TODO Might want to finalize and write to file here? 
        return
    return 
    
def walk_item(data, new_item: Item, previous_key):
    if isinstance(data, dict):
        for key, value in data.items():
            if key == 'variants':
                new_item.level = None
                new_item.gold = None
                handle_variants(new_item, value)
            else:
                walk_item(value, new_item, key)
    elif isinstance(data, list):
        for index, item in enumerate(data):
            walk_item(item, new_item, previous_key)
    else:
        process_data(new_item, previous_key, data)

def process_file(json_file_path):
    instance = Item()
    instance.clear()
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

reject_trait_identifiers = ['region', 'Member']
trait_keys = ['category', 'subCategory', 'damage', 'damageType', 'group', 'traits', 'access']
new_item = Item()

repo_directory = os.path.dirname(os.path.abspath(os.path.dirname(os.path.abspath(__file__)))) 
json_directory = 'json_input'
data_directory = 'data/core_items'

full_json_path = os.path.join(repo_directory, json_directory)
full_data_path = os.path.join(repo_directory, data_directory)

check_for_new_json_files(full_json_path, full_data_path)