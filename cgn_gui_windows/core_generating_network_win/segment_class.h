/*
core class handles natural cores
*/
#include<chrono>
#include<random>
#include<filesystem>
#include<windows.h>
#include"neuron_and_ann_class.h"
#include"core_class.h"
#include "qtextedit.h"
#include<QThread>

using namespace std;
using namespace std::chrono;
namespace fs = std::filesystem;

class genetic_algorithm
{
    /*GENETIC ALGORITHM COMPONENTS START*/
    //gene range
    static const int fp_change_value_min=30,fp_change_value_max=60;
    static const int summation_temp_thershold_min=1500,summation_temp_thershold_max=5000;
    static const int rhs_upper_min=2,rhs_upper_max=20;
    static const int rhs_lower_min=40,rhs_lower_max=150;
    static const int attributes_per_core_min=8,attributes_per_core_max=30;
    float data_div_min=2,data_div_max;
    //algorithm critical data
    unsigned int population_size,ga_iterations,mutation_percentage;
    int no_of_genes_to_mutate;
    vector<chromosome> population;
    //other mics data
    int current_chromosome_id=0;

    //mics functions
    void save_chromosome(chromosome& chromosome);
    void print_population(vector<chromosome>& population);
    int get_random_number(int min,int max);
    bool get_random_bool();
    static bool comparator(chromosome c1,chromosome c2);
    //genetic algorithm critical functions
    void mutation(vector<chromosome>& population);
    void chromosome_data_transfer(int crossover_index,bool before,chromosome& source,chromosome& destination);
    vector<chromosome> crossover(vector<chromosome>& population);
    vector<chromosome> tournament_selection(vector<chromosome> population);
    void generate_initial_population();
    void calc_fitness_threaded(void (*print_message)(string),int no_of_threads,vector<chromosome>& population);

    public:
    datapack_structure_defination ds;
    vector<nn_core_filtered_data>* f_data_vector;

    chromosome start_genetic_algorithm(void (*print_message)(string),int no_of_threads);
    genetic_algorithm(unsigned int &iterations,unsigned int &population_size,unsigned int &mutation_percentage,int &data_div_max);
    /*GENETIC ALGORITHM COMPONENTS END*/
};

class segment_class{
    private:
    void (*print_message)(string) ;
    vector<core_class*> core_vector;
    vector<string> core_save_file_name_vector;
    
    //network information
    datapack_structure_defination ds;
    string network_save_file_name;
    bool id_lock=false;
    int no_of_attributes_per_core_default=25;//25
    int min_no_of_attributes_per_core=4;
    int extra_attributes_in_last_core=0;
    int no_of_attributes_per_core_balanced;//last core may have few extra attributes.

    //segment identification information
    int segment_no=0,segment_aim=0;//this two must be changed using a function so that proper core is loaded
    string segment_name;
    string segment_save_file_name="NULL";//provided if core is loaded from a core/network savefile. Not set using constructor

    //progress bar data
    bool pds=false;
    int predict_progress_bar_numerator=0;//for the predict progress bar
    int predict_progress_bar_denominator=0;//for the predict progress bar

    //genetic algorithm variables
    bool critical_variables_set=false;

    void save_segment();

    void f_data_viewer(string str,vector<nn_core_filtered_data> f_data);

    void filter(nn_core_data_package_class* data_pack);

    vector<nn_core_filtered_data> f_data_vector;
    vector<vector<nn_core_filtered_data>> f_train_data_split;

    vector<int> split_start,split_end;
    void split_attributes_for_each_core();

    void create_cores();

    void checker_df(vector<neuron> &output_neurons);

    void checker_nf(vector<neuron> &output_neurons);

    int index_of_neuron_to_be_fired(int label,vector<float> elements);

    vector<neuron> combine_output_neurons(vector<vector<neuron>> output_neuron_matrix);

    int propagate(vector<float> input);

    void predict_progress_bar();

    void clrscr();

    //test functions
    void display_f_train_data_split()
    {
        for(int a=0;a<f_train_data_split.size();a++)
        {
            print_message("\n\ncore= "+to_string(a));
            for(int b=0;b<f_train_data_split[a].size();b++)
            {
                print_message("\nlabel= "+to_string(f_train_data_split[a][b].label));
                for(int c=0;c<f_train_data_split[a][b].data.size()-(f_train_data_split[a][b].data.size()-5);c++)
                {
                    print_message("\n");
                    for(int d=0;d<f_train_data_split[a][b].data[c].size();d++)
                    {
                        print_message(to_string(f_train_data_split[a][b].data[c][d])+",");
                    }
                }
            }
        }
    }

    void save_data_pack(string name,nn_core_data_package_class data_pack);

    public:
    float data_division=1.5;
    int no_of_threads;
    chromosome* critical_variable;

    bool is_network_compatible_with_data();

    void start_trainer();//there cannot be a case of invalid network and data without labels.
    
    void train();

    float testing_for_each_label(/*,int train_test_predict*/);

    vector<string> line_breaker(string line);
    bool load_segment(string segment_dir);

    void print_prediction(nn_core_data_package_class& data_pack,int train_test_predict);

    int make_prediction_on_user_entered_data(vector<float> data);

    int get_data_length();

    void set_ds(datapack_structure_defination ds1)
    {   ds=ds1;}

    void set_critical_variable(chromosome* critical_cariable);

    void add_f_data(vector<nn_core_filtered_data>& f_data_vec);

    void clear();
    
    string return_name()
    {   return segment_name;}
    datapack_structure_defination return_ds()
    {   return ds;}
    segment_class(int segment_aim1,int segment_no1,string segment_name1,void (*print_message1)(string));
};

void segment_starter(
        string file_name_local,
        int test_train_predict,
        string segment_save_file_name,
        int no_of_threads,
        chromosome critical_variables,
        unsigned int iterations,
        unsigned int population_size,
        unsigned int mutation_percentage,
        void (*print_message)(string));

