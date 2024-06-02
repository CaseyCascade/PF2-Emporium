#include "tableGenerator.h"
#include <random> 

class RandomItemPicker {
    protected: 
        vector <pair <Item, int> > scoredTable;
        float percentile; 
        int target; 

        vector <int> pickedItemIndexes; 
        bool debug = true; 

    public: 
        RandomItemPicker(vector <pair <Item, int> > t, float p)
        {
            scoredTable = t;  
            percentile = p; 

            target = scoredTable.size() * percentile;
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
            int sum = 0;
            for (auto& i : pickedNumbers)
            {
                sum += i; 
            }
            return sum / pickedNumbers.size(); 
        }

        void print_results()
        {
            cout << "Target: " << target << endl; 
            cout << "Average: " << get_average(pickedItemIndexes) << endl; 
            print_vector(pickedItemIndexes);

            cout << endl << "Picked Items: " << endl; 
            for (auto& i : pickedItemIndexes)
            {
                cout << scoredTable.at(i).first.get_name() << endl;  
            }
        }

        void rubberband_recursion (vector <int> &pickedNumbers, int N)
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
                    uniform_int_distribution<> distrib(target, scoredTable.size());
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
            rubberband_recursion(pickedNumbers, N); 
        }

        void rubberband_generator(int N)
        {
            // Seed with a real random value, if available
            random_device rd;
            
            // Base Case
            mt19937 gen(rd());
            uniform_int_distribution<> distrib(0, scoredTable.size());
            int random_number = distrib(gen);
            pickedItemIndexes.push_back(random_number); 

            //Recursive Case
            rubberband_recursion(pickedItemIndexes, N - 1);   

            if (debug) print_results();          
        }

};