import delete_data
import json_handler

core_items_path = 'data/core_items'
core_templates_path = 'data/core_templates'
custom_items_path = 'data/custom_items'
custom_templates_path = 'data/custom_templates'

delete_data.delete_files_in_directory(core_items_path)
json_handler.load()