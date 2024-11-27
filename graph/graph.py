import pandas as pd
import matplotlib.pyplot as plt

# Function to plot data for a single algorithm
def plot_algorithm(sheet_data, algorithm_name):
    """Plots all input cases for a single algorithm from a combined sheet."""
    # Filter data for the specified algorithm
    data = sheet_data[sheet_data['algorithm'] == algorithm_name]
    
    if data.empty:
        print(f"No data for {algorithm_name}.")
        return
    
    # Plot the data
    plt.figure(figsize=(10, 6))
    input_cases = data['input case'].unique()
    
    for case in input_cases:
        case_data = data[data['input case'] == case]
        plt.plot(
            case_data['input size'],
            case_data['average'],
            marker='o',
            linestyle='-',
            label=case,
            alpha=0.8
        )
    
    plt.title(f"{algorithm_name} Runtime Comparison", fontsize=16)
    plt.xlabel("Input Size", fontsize=14)
    plt.ylabel("Runtime (ms)", fontsize=14)
    plt.legend(title="Input Cases", fontsize=12)
    plt.grid(True, linestyle='--', alpha=0.6)
    plt.tight_layout()
    plt.show()


sheet_data = pd.read_excel("cleaned_data.xlsx", sheet_name="Sheet1")

plot_algorithm(sheet_data, "Insertion")
plot_algorithm(sheet_data, "Bubble")
plot_algorithm(sheet_data, "Selection")
plot_algorithm(sheet_data, "Shell")
plot_algorithm(sheet_data, "Merge")
plot_algorithm(sheet_data, "Quick")
plot_algorithm(sheet_data, "Heap")
plot_algorithm(sheet_data, "Gen Insertion")
plot_algorithm(sheet_data, "Gen Bubble")
plot_algorithm(sheet_data, "Gen Selection")
plot_algorithm(sheet_data, "Gen Shell")
plot_algorithm(sheet_data, "Gen Merge")
plot_algorithm(sheet_data, "Gen Quick")
plot_algorithm(sheet_data, "Gen Heap")