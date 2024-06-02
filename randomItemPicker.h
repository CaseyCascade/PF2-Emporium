#include "tableGenerator.h"
#include <random> 

class RandomItemPicker {

    vector <pair <Item, int> > scoredTable;

    public: 
        RandomItemPicker(vector <pair <Item, int> > t)
        {
            scoredTable = t;  
        }

        bool search_vector (vector <int> range, int n)
        {
            for (auto& i : range)
            {
                if (i == n) return true; 
            }
            return false; 
        }

        void print_vector (vector <int> range)
        {
            cout << "[";
            for (auto& i : range) 
            {
                cout << i << ", ";
            }
            cout << "]" << endl; 
        }

        vector <int> get_score_range ()
        {
            vector <int> range; 
            for (int i = 0; i < scoredTable.size(); i++)
            {
                if (!search_vector(range, scoredTable.at(i).second)) range.push_back(scoredTable.at(i).second);
            } 
            return range; 
        }

        int get_average (vector <int> pickedNumbers) //TODO This is not working right 
        {
            int sum; 
            for (auto& i : pickedNumbers)
            {
                sum += i; 
            }
            return sum / pickedNumbers.size(); 
        }

        void rubberband_recursion (vector <int> &pickedNumbers, int tableSize, int target, int N)
        {
            random_device rd;
            mt19937 gen(rd());
            int random_number = -1;

            // Calculate our Average, and pick a number in a range so that we attempt to increase or decrease our average towards the target
            int average = get_average(pickedNumbers);  
            while (true)
            {
                if (average <= target)
                {
                    uniform_int_distribution<> distrib(target, tableSize);
                    random_number = distrib(gen);
                }
                else 
                {
                    uniform_int_distribution<> distrib(0, target);
                    random_number = distrib(gen);
                }
                if (!search_vector(pickedNumbers, random_number)) break; 
            }    

            pickedNumbers.push_back(random_number); 
            N--; 

            if (N == 0) return; 
            rubberband_recursion(pickedNumbers, tableSize, target, N); 
        }

        vector <Item> rubberband_generator(int N, float percentile)
        {

            // Seed with a real random value, if available
            vector <Item> result; 
            random_device rd;
            int tableSize = scoredTable.size(); 
            int target = tableSize * percentile; 
            vector <int> pickedNumbers; 
            
            // Base Case
            mt19937 gen(rd());
            uniform_int_distribution<> distrib(0, tableSize);
            int random_number = distrib(gen);
            pickedNumbers.push_back(random_number); 

            //Recursive Case
            rubberband_recursion(pickedNumbers, tableSize, target, N - 1);   

            cout << "Average: " << get_average(pickedNumbers) << endl;  // TODO THIS IS WRONG 
            print_vector(pickedNumbers); 
            return result;          
        }

};