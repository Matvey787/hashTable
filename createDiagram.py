import matplotlib.pyplot as plt


def read_data(filename):
    x_values = []
    y_values = []
    mean = 0.0
    spread = 0.0
    
    with open(filename, 'r') as file:
        lines = file.readlines()
        
        for line in lines[:750]:
            x, y = map(int, line.strip().split())
            x_values.append(x)
            y_values.append(y)

        mean = float(lines[750].strip())
        
        spread = float(lines[751].strip())
    
    return x_values, y_values, mean, spread


def plot_histogram(filename):
    
    x_values, y_values, mean, spread = read_data(filename)
    
    plt.figure(figsize=(15, 6))  
    plt.bar(x_values, y_values, width=1.0, edgecolor='black', color='skyblue')
    
    plt.axhline(y=mean, color='red', linestyle='-', linewidth=2, label=f'load factor (LF): {mean}')

    plt.axhline(y=mean + spread, color='green', linestyle='--', linewidth=1.5, label=f'LF distribution')
    plt.axhline(y=mean - spread, color='green', linestyle='--', linewidth=1.5)
    
    plt.xlabel('Index of bucket')
    plt.ylabel('Bucket length')
    plt.title('Hash Table Distribution')
    plt.grid(True, axis='y', linestyle='--', alpha=0.7)
    plt.legend()
    
    plt.xticks(range(0, max(x_values) + 1, 50))  
    
    plt.tight_layout()
    plt.show()

if __name__ == '__main__':
    filename = 'txt/hashTableInfo.txt'
    plot_histogram(filename)

