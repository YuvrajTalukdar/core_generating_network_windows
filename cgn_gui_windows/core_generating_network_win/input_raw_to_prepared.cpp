/*
file modified of compability with shuttle_converted.csv
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<string.h>
#include<algorithm>

//#include"core_class.h"
#include"segment_class.h"

using namespace std;

struct raw_data{
    vector<vector<float>> rawData;
};

bool check_for_missing_data(string line) //to remove the missing data.
{
    bool status=false;
    for(int a=0;a<line.size();a++)
    {
        if(line.at(a)=='?')
        {
            status=true;
        }
    }
    return status;
}

void breaker(raw_data* rw_data,string line)
{
    char num_char[20]={'\0'},ch[2];
    vector<float> one_row_of_data;
    if(check_for_missing_data(line)==false)
    {
        for(int a=0;a<line.size();a++)
        {
            if(line.at(a)==',')
            {
                float val = atof(num_char)*100;//*100
                //cout<<val<<endl;
                one_row_of_data.push_back(val);
                for(int b=0;b<20;b++){
                    num_char[b]='\0';
                }
                continue;
            }
            ch[0]=line.at(a);
            ch[1]='\0';
            strcat(num_char,ch);
        }
        one_row_of_data.push_back(atof(num_char)*100);//*100
        rw_data->rawData.push_back(one_row_of_data);
    }
}

void read_data_from_file(raw_data* rw_data,string file_name)
{
    ifstream  raw_data_stream(file_name,ios::in);
    string line;
    //int count=0;
    while(raw_data_stream)
    {
        raw_data_stream>>line;
        if(raw_data_stream.eof())
        {   break;}
        //to remove the id line. //deleted if(count>0)
        breaker(rw_data,line);
        //count++; //for just counting the no of lines in the file //required if if(count>0) line to remove the id line
    }
}

void display_rw_data(void (*print_message)(string) ,raw_data* rw_data)
{
    for(int a=0;a<rw_data->rawData.size();a++)
    {
        for(int b=0;b<rw_data->rawData[a].size();b++)
        {
            print_message(to_string(rw_data->rawData[a][b])+",");
        }
        print_message("\n");
    }
}

void data_filter(raw_data* filtered_data,string file_name)
{
    raw_data rw_data;
    read_data_from_file(&rw_data,file_name);
    //display_rw_data(&rw_data);
    vector<float> row;
    for(int a=0;a<rw_data.rawData.size();a++)
    {
        row.clear();
        for(int b=0;b<rw_data.rawData[a].size();b++)
        {
            //b>0 option removes the id column //deleted if(b>0)
            row.push_back(rw_data.rawData[a][b]);
        }
        filtered_data->rawData.push_back(row);
    }
}

void prepare_data(nn_core_data_package_class* data_pack,string file_name)
{
    raw_data filtered_data;
    data_filter(&filtered_data,file_name);
    //display_rw_data(&filtered_data);

    vector<float> row;
    //this part pushes the data in the data vector(vector<vector<float>>) and lebel(vector<float>) in the label vector
    for(int a=0;a<filtered_data.rawData.size();a++)
    {
        row.clear();
        for(int b=0;b<filtered_data.rawData[a].size();b++)
        {
            if(b==filtered_data.rawData[a].size()-1)
            {
                data_pack->labels.push_back(filtered_data.rawData[a][b]);
            }
            else
            {
                row.push_back(filtered_data.rawData[a][b]);
            }
        }
        data_pack->data.push_back(row);
    }
}

void display_prepared_data(void (*print_message)(string),nn_core_data_package_class* data_pack,string file_name)
{
    for(int a=0;a<data_pack->data.size();a++)
    {
        //if(data_pack->labels[a]==8){ //for checking each of the labels
        for(int b=0;b<data_pack->data[a].size();b++)
        {
            print_message(to_string(data_pack->data[a][b])+",");
        }
        print_message(" label= "+to_string(data_pack->labels[a])+"\n");
        //}
    }
}

datapack_structure_defination datapack_analyzer(nn_core_data_package_class* data_pack)
{
    datapack_structure_defination ds;    
    ds.no_of_elements_in_each_record=data_pack->data[0].size();
    vector<int> labels;
    bool found=false;
    for(int a=0;a<data_pack->data.size();a++)
    {
        found=false;
        for(int b=0;b<labels.size();b++)
        {
            if(labels[b]==data_pack->labels[a])
            {
                found=true;
                break;
            }
        }
        if(found==false)
        {
            labels.push_back(data_pack->labels[a]);
        }
    }
    ds.no_of_labels=labels.size();
    for(int a=0;a<labels.size();a++)
    {   ds.elements.push_back(labels[a]);}
    data_pack->analyze_status=true;

    return ds;
}

struct shuffling_data{
    vector<float> temp_data;
    int temp_label;
};
void shuffler(nn_core_filtered_data* f_data)
{
    vector<shuffling_data> shuffling_data_temp_vector;
    shuffling_data shuffling_data_temp;
    shuffling_data_temp_vector.clear();
    //pushing the data the the shuffling vector
    for(int a=0;a<f_data->data.size();a++)
    {
        shuffling_data_temp.temp_data=f_data->data[a];
        shuffling_data_temp.temp_label=f_data->label;
        shuffling_data_temp_vector.push_back(shuffling_data_temp);
    }
    //shuffeling the data
    random_shuffle(shuffling_data_temp_vector.begin(),shuffling_data_temp_vector.end());
    //pushing the data in the f_data
    f_data->data.clear();
    for(int a=0;a<shuffling_data_temp_vector.size();a++)
    {
        f_data->data.push_back(shuffling_data_temp_vector[a].temp_data);
        f_data->label=shuffling_data_temp_vector[a].temp_label;
    }
}

int filter(nn_core_data_package_class& data_pack,datapack_structure_defination ds,vector<nn_core_filtered_data>& f_data_vector)
{
    nn_core_filtered_data f_data;
    f_data_vector.clear();
    for(int a=0;a<ds.elements.size();a++)
    {
        f_data.data.clear();
        for(int b=0;b<data_pack.labels.size();b++)
        {
            if(ds.elements[a]==data_pack.labels[b])
            {
                f_data.data.push_back(data_pack.data[b]);
                f_data.label=data_pack.labels[b];
            }
        }
        f_data_vector.push_back(f_data);
    }
    //calling the shuffler
    for(int a=0;a<f_data_vector.size();a++)
    {
        shuffler(&f_data_vector[a]);//has same size as that is of no of element
    }
    int least_data=f_data_vector[0].data.size();
    for(int a=1;a<f_data_vector.size();a++)
    {
        if(least_data>f_data_vector[a].data.size())
        {   least_data=f_data_vector[a].data.size();}
    }
    if(least_data/6<6)
    {   return 2;}
    else
    {   return 6;}
}

void start_segment(
    int no_of_threads,
    int train_test_predict,
    nn_core_data_package_class& data_pack,
    string segment_dir,
    chromosome critical_variables,
    unsigned int iterations,
    unsigned int population_size,
    unsigned int mutation_percentage,
    void (*print_message)(string))
{
    if(train_test_predict==2)//print predictions using already trained network
    {
        segment_class segment1(0,0,"default_segment",print_message);
        if(segment1.load_segment(segment_dir)==true)
        {   
            if(data_pack.data[0].size()==segment1.return_ds().no_of_elements_in_each_record)
            {   segment1.print_prediction(data_pack,train_test_predict);}
            else
            {   print_message("\nERROR!!! Data Pack do not belongs to the loaded network.");}
        }
        else
        {   print_message("\nERROR!!! failed to load network from the network file.");}
    }
    else if(train_test_predict==3)//making prediction on user entered individual data.
    {
        segment_class segment1(0,0,"default_segment",print_message);
        bool network_load_status=segment1.load_segment(segment_dir);
        if(network_load_status==true)
        {   
            print_message("\nNetwork successfully loaded");
            //segment1.make_prediction_on_user_entered_data();
        }
        else
        {   print_message("\nERROR!!! failed to load network from the network file.");}
    }
    else if(train_test_predict==4 || train_test_predict==1)//test an already trained network
    {
        segment_class segment1(0,0,"default_segment",print_message);
        vector<nn_core_filtered_data> f_data_vector;
        datapack_structure_defination ds=datapack_analyzer(&data_pack);
        int data_div_max=filter(data_pack,ds,f_data_vector);
        data_pack.data.clear();
        data_pack.labels.clear();
        segment1.set_ds(ds);
        segment1.add_f_data(f_data_vector);
        if(train_test_predict==1)
        {
            auto start = high_resolution_clock::now();
            if(critical_variables.id==-1)
            {
                genetic_algorithm ga(iterations,population_size,mutation_percentage,data_div_max);
                ga.ds=ds;
                ga.f_data_vector=&f_data_vector;
                critical_variables=ga.start_genetic_algorithm(print_message,no_of_threads);
            }
            segment1.set_critical_variable(&critical_variables);
            print_message("\nflatening_fx_enabled: "+to_string(critical_variables.flatening_fx_enabled));
            print_message("\nzero_weight_remover: "+to_string(critical_variables.zero_weight_remover));
            print_message("\nextreame_weight_remover: "+to_string(critical_variables.extreame_weight_remover));
            print_message("\nfp_change_value: "+to_string(critical_variables.fp_change_value));
            print_message("\nsummation_temp_threshold: "+to_string(critical_variables.summation_temp_thershold));
            print_message("\nrhs_upper: "+ to_string(critical_variables.rhs_upper));
            print_message("\nrhs_lower: "+to_string(critical_variables.rhs_lower));
            print_message("\nattributes_per_core: "+to_string(critical_variables.attributes_per_core));
            print_message("\ndata_division: "+to_string(critical_variables.data_division));
            segment1.no_of_threads=no_of_threads;
            segment1.start_trainer();
            segment1.clear();
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start);
            print_message("\n\nTime Taken= "+to_string(duration.count()/pow(10,6))+"\n\n");
        }
        else if(train_test_predict==4)
        {
            bool network_load_status=segment1.load_segment(segment_dir);
            if(network_load_status)
            {   
                if(segment1.is_network_compatible_with_data())
                {   segment1.data_division=0;segment1.testing_for_each_label();}
                else
                {   print_message("\nERROR!! loaded network is not compatible with loaded dataset.");}
            }
            else
            {   print_message("\nERROR!!! failed to load network from the network file.");}
        }   
    }
}

void segment_starter(string file_name_local,
                     int test_train_predict,
                     string segment_save_file_name,
                     int no_of_threads,
                     chromosome critical_variables,
                     unsigned int iterations,
                     unsigned int population_size,
                     unsigned int mutation_percentage,
                     void (*print_message)(string))
{
    nn_core_data_package_class data_pack;
    if(test_train_predict==1 || test_train_predict==2 || test_train_predict==4)
    {   
        prepare_data(&data_pack,file_name_local);
        print_message("\ndata file reading success!!!\n");
    }
    if(test_train_predict==2)//preprocess the data_pack to move the labels to dataset
    {
        for(int a=0;a<data_pack.data.size();a++)
        {   data_pack.data[a].push_back(data_pack.labels[a]);}
        data_pack.labels.clear();
    }
    print_message("\ndata size= "+to_string(data_pack.data.size())+" s2="+to_string(data_pack.data[0].size()));
    start_segment(no_of_threads,test_train_predict,data_pack,segment_save_file_name,critical_variables,iterations,population_size,mutation_percentage,print_message);
}
