import os 
import shutil

core_items_path = 'data/core_items'
core_templates_path = 'data/core_templates'
custom_items_path = 'data/custom_items'
custom_templates_path = 'data/custom_templates'

def delete_files_in_directory(local_directory):
    directory = os.path.abspath(local_directory)
    for filename in os.listdir(directory):
        file_path = os.path.join(directory, filename)
        try:
            if os.path.isfile(file_path) or os.path.islink(file_path):
                os.unlink(file_path)
            elif os.path.isdir(file_path):
                shutil.rmtree(file_path)
        except Exception as e:
            print(f'Failed to delete {file_path}. Reason: {e}')

    gitkeep = '.gitkeep' # Add a .gitkeep file after deleting
    new_file = os.path.join(directory, gitkeep) 
    with open(new_file, 'w') as file:
        pass  # Do nothing

delete_files_in_directory(core_items_path)