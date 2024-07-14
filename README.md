# PF2-Emporium
*This is just a personal project I made for me and my friends, though feel free to mess around with it and give suggestions!*

## Overview
Emporium is a random item generator for Pathfinder 2nd Edition that uses item traits to construct templates for shops you can generate from. 

Run emporium.exe in your terminal to access the command palette, where you can create shops, generate items for shops, as well as lookup and filter through any items in the game. 

## Updating / Modifying Source Files
The database of items and shops can be found in /data. Currently the items are sourced using the JSON files from [PF2 Tools](https://github.com/Pf2eToolsOrg/Pf2eTools.git). Which are not yet updated to the remaster. 

If you have your own JSON files that you'd like to source from, put them into /json_input and run reset.py. This will delete and recreate .txt files in data based on all the JSON files in /json_input. 
