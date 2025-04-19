import os
import random
import string

def generate_random_word(min_length=5, max_length=32):
    length = random.randint(min_length, max_length)
    return ''.join(random.choices(string.ascii_letters, k=length))

def append_words_to_file(file_path, num_words=100):
    os.makedirs(os.path.dirname(file_path), exist_ok=True)
    with open(file_path, 'a') as file:
        for _ in range(num_words):
            word = generate_random_word()
            file.write(word + '\n')

if __name__ == "__main__":
    file_path = "txt/keys.txt"
    num_words = 5000000
    append_words_to_file(file_path, num_words)
    print(f"{num_words} random words have been added to {file_path}.")