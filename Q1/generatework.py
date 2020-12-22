import string 
import random

def generate(Number_of_strings):

    f = open("firstinsert.txt","w+")
    for i in range(Number_of_strings):
        str1 =  ''.join(random.choices(string.ascii_lowercase, k=random.randint(5,14)))
        f.write(str1)
        f.write('\n')
    
    f.close()
    

    f = open("work.txt","w+")
    for i in range(Number_of_strings):
        str1 =  ''.join(random.choices(string.ascii_lowercase, k=random.randint(5,14)))
        f.write(str1)
        f.write('\n')
    
    f.close()
    

generate(99)
