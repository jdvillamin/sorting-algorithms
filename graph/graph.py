import pandas as pd
import matplotlib.pyplot as plt

# load excel file
file_path = 'clean_data.xlsx'  
df = pd.read_excel(file_path)

# split "Gen" and "Non-Gen"
gen_algorithms = df[df['algorithm'].str.contains('Gen', case=False, na=False)]
non_gen_algorithms = df[~df['algorithm'].str.contains('Gen', case=False, na=False)]

# plot all input cases for a single algorithm
def plot_algorithm_comparison(algorithm_name):
    plt.figure(figsize=(10, 6))
    
    # filter data for the algorithm
    algorithm_data = df[df['algorithm'] == algorithm_name]
    
    # plot each input case
    unique_cases = algorithm_data['input case'].unique()
    for case in unique_cases:
        case_data = algorithm_data[algorithm_data['input case'] == case]
        if not case_data.empty:
            plt.plot(case_data['input size'], case_data['average'], marker='o', label=case)
    
    # labels
    plt.title(f'{algorithm_name} Runtime Comparison', fontsize=14)
    plt.xlabel('Number of Inputs', fontsize=12)
    plt.ylabel('Runtime (ms)', fontsize=12)
    plt.legend(title='Input Case')
    plt.grid(True)
    plt.show()

# plot all algorithms for single input case
def plot_input_case_comparison(input_case, category='both'):
    plt.figure(figsize=(10, 6))
    
    # filter data for input case
    if category == 'gen':
        case_data = gen_algorithms[gen_algorithms['input case'] == input_case]
        title_prefix = 'Gen Algorithms'
    elif category == 'non-gen':
        case_data = non_gen_algorithms[non_gen_algorithms['input case'] == input_case]
        title_prefix = 'Non-Gen Algorithms'
    else:
        case_data = df[df['input case'] == input_case]
        title_prefix = 'All Algorithms'
    
    unique_algorithms = case_data['algorithm'].unique()
    for algorithm in unique_algorithms:
        algorithm_data = case_data[case_data['algorithm'] == algorithm]
        if not algorithm_data.empty:
            plt.plot(algorithm_data['input size'], algorithm_data['average'], marker='o', label=algorithm)
    
    # labels
    plt.title(f'{title_prefix} Comparison for {input_case}', fontsize=14)
    plt.xlabel('Number of Inputs', fontsize=12)
    plt.ylabel('Runtime (ms)', fontsize=12)
    plt.legend(title='Algorithm')
    plt.grid(True)
    plt.show()

plot_algorithm_comparison('Insertion')
plot_algorithm_comparison('Bubble')
plot_algorithm_comparison('Selection')
plot_algorithm_comparison('Shell')
plot_algorithm_comparison('Merge')
plot_algorithm_comparison('Heap')
plot_algorithm_comparison('BIQuick')
plot_algorithm_comparison('OwnQuick')
plot_algorithm_comparison('Gen Quick')
plot_algorithm_comparison('Gen Heap')
plot_algorithm_comparison('Gen Merge')
plot_algorithm_comparison('Gen Shell')
plot_algorithm_comparison('Gen Selection')
plot_algorithm_comparison('Gen Bubble')
plot_algorithm_comparison('Gen Insertion')

plot_input_case_comparison('Ascending', category='gen')  
plot_input_case_comparison('Ascending', category='non-gen')  
plot_input_case_comparison('Ascending', category='both')  
