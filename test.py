import numpy as np
from collections import defaultdict
#import networkx as nx
import time
import subprocess
from subprocess import Popen, PIPE, STDOUT, run
import  matplotlib.pyplot as plt

exe_file_name = "AI_game.exe"
exe_cmd = "./" + exe_file_name
player1 = "40\n./d.exe\n"
player2 = "1\n./Sample1.exe\n"
std_in = bytes(player1 + player2 + "\n", encoding='utf-8')


def run1():
    p = run([exe_cmd], stdout=PIPE, input= std_in ) #, encoding='utf-8'
    print(p.stdout)
    print(p.stderr)
    #ans, t= map(int,p.stdout.split())
    #return ans, t
    return p.stdout, p.stderr