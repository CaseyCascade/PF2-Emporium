import json 
import os 

debug = True



class Item: 
    base_name = None
    name = None
    page = None
    gold = None
    level = None
    bulk = None
    source = None
    price = None
    coin = None
    variant = False
    entry = None
    traits = []

    def __init__(self):
        return 
    
    def set_name(self, name):
        if self.base_name == None:
            self.name = name
            self.base_name = name
        elif self.name == None:
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
        elif isinstance(bulk, str):
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

    def string_diff(self, str1, str2):
        set1 = str1.split()
        set2 = str2.split()
        final_set = []
        for word in set2:
            if word not in set1:
                final_set.append(word)
        final_set = {element for element in final_set if '{' not in element and '}' not in element}
        joined_string = ' '.join(final_set)
        return joined_string


    def set_variant_name (self, variant_name: str): 
        if '(' in variant_name or ')' in variant_name:
            variant_name = variant_name.replace("(", "")
            variant_name = variant_name.replace(")", "")
        if self.base_name == None:
            print("ERROR: Base Name is Empty in set_variant_name()")
            return 
        if self.string_diff(self.base_name.lower(), variant_name.lower()) == '':
            new_name = str(self.base_name)
        else:
            new_name = self.base_name + ' (' + self.string_diff(self.base_name.lower(), variant_name.lower()) + ')'
        if self.name != None and self.name != new_name:
            #print("ERROR: name variable was not erased before set_variant_name()")
            print("Old:", self.name, "New:", new_name)
        elif self.name != None:
            return 
        self.name = new_name

    def clear(self):
        self.base_name = None 
        self.name = None
        self.page = None
        self.gold = None
        self.level = None
        self.bulk = None
        self.source = None
        self.variant = False
        self.entries = []
        self.traits = []

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

    def get_substring_after_character(self, s, target_char):
        index = s.find(target_char)
        if index == -1:
            return ""  # Return empty string if target_char is not found
        
        # Move index past the target_char
        index += len(target_char)
        
        # Find the next space or end of string
        start_index = index
        end_index = len(s)
        while start_index < len(s) and s[start_index] != ' ':
            start_index += 1
            
        return s[index:start_index]

    def get_substring_between(self, s, start_substr, end_substr):
        start_index = s.find(start_substr)
        if start_index == -1:
            return ""  # Return empty string if start_substr is not found
        
        start_index += len(start_substr)
        end_index = s.find(end_substr, start_index)
        if end_index == -1:
            return ""  # Return empty string if end_substr is not found after start_substr
    
        return s[start_index:end_index]

    def parse_traits(self):
        for index, trait in enumerate(self.traits):
            if '@' in trait:
                start_target = self.get_substring_after_character(trait, '@')
                new_trait = self.get_substring_between(trait, start_target, '}')
                new_trait = new_trait.strip()
                
                if new_trait != "craft": # Weird edgecase for a single long string
                    self.traits[index] = new_trait
                else:
                    self.traits.pop(index)

    def finalize(self):
        if self.name == None:
            print("No Name in Finalize:", self.base_name)
            return
        if self.bulk == None:
            self.set_bulk(0)
        if self.gold == None: 
            self.set_gold('gp', 0)
        if self.level == None:
            self.set_level(0)
        self.parse_traits()

        # Edge Case for Runes
        if 'rune' in self.traits:
            if '(' in self.name:
                self.name = self.name.replace("(", "Rune (")
            else:
                self.name += ' Rune'
        # Edge Case for Organizations
        for index, trait in enumerate(self.traits):
            if "member" in trait:
                trait = trait.replace("member of the ", "")
                trait = trait.replace("member of a ", "")
                self.traits[index] = trait

    def write_to_file(self, filepath):
        self.finalize()
        if not self.name:
            return 
        if not self.entry:
            self.entry = "NA"
        if not self.source:
            print(self.name)
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
    if key == 'name' and not item.variant:
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
    elif key == 'variantType' or key == 'name':
        if item.variant == True and item.name == None:
            #print(f"Setting name: {value}")
            item.set_variant_name(value)
    
def walk_item(data, new_item: Item, previous_key, filepath):
    if isinstance(data, dict):
        for key, value in data.items():
            if new_item.variant == True:
                variant_keys = ['name', 'variantType', 'amount', 'coin', 'price', 'level']
                if key in variant_keys:
                    walk_item(value, new_item, key, filepath)
            else:
                walk_item(value, new_item, key, filepath)
    elif isinstance(data, list):
        for index, item in enumerate(data):
            if previous_key == 'variants': # TODO Need to Write Variant Items to File and Clear() somehow. Hasn't been tested yet 
                    new_item.variant = True 
                    new_item.name = None 
                    new_item.gold = None
                    new_item.level = None
                    walk_item(item, new_item, None, filepath)

                    if (index + 1) != len(data):
                        new_item.write_to_file(filepath)
                        new_item.variant = False
            else:
                walk_item(item, new_item, previous_key, filepath)
    else:
        process_data(new_item, previous_key, data)

def process_file(json_file_path):
    instance = Item()
    instance.clear()
    with open(json_file_path, 'r') as file:
        data = json.load(file)
    # This is hard-coded in a way that expects each file to be a list containing all items under a key 
    # (Which is how the PF2 Easy JSON files are formatted)
    if isinstance(data, dict): 
        for key, value in data.items():
            if isinstance(value, list):
                for index, item in enumerate(value):
                    file_name = os.path.splitext(os.path.basename(json_file_path))[0]
                    file_name = file_name + '.txt'
                    data_file_path = os.path.join(full_data_path, file_name)
                    walk_item(item, instance, None, data_file_path)
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

def load():
    check_for_new_json_files(full_json_path, full_data_path)