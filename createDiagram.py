import matplotlib.pyplot as plt


def read_data(filename):
    x_values = []
    y_values = []
    with open(filename, 'r') as file:
        for line in file:
            
            x, y = map(int, line.strip().split())
            x_values.append(x)
            y_values.append(y)
    return x_values, y_values

def plot_histogram(filename):
    
    x_values, y_values = read_data(filename)
    
    plt.figure(figsize=(15, 6))  
    plt.bar(x_values, y_values, width=1.0, edgecolor='black', color='skyblue')
    
    plt.xlabel('Index (X)')
    plt.ylabel('Height (Y)')
    plt.title('Hash Table Distribution')
    plt.grid(True, axis='y', linestyle='--', alpha=0.7)

    plt.xticks(range(0, max(x_values) + 1, 50))  
    
    plt.tight_layout()
    plt.show()


if __name__ == '__main__':
    filename = 'txt/hashTableInfo.txt'
    plot_histogram(filename)