import matplotlib.pyplot as plt
import sys

jobs = []
weights = []
max_end_time = -1

def read_input(file: str) -> None:
    global max_end_time
    with open(file, "r") as f:
        lines = f.readlines()
        print(lines)
        for l in lines:
            print(l)
            tup = l.split(",")
            max_end_time = max(max_end_time, int(tup[1]))
            jobs.append((int(tup[0]), int(tup[1]) - int(tup[0])))
            weights.append(int(tup[2].strip()))

def plot(save=False) -> None:
    for j in jobs:
        print(j)
    for w in weights:
        print(w)

    fig, ax = plt.subplots()
    ax.grid(True)
    ax.set_ylim(0, len(weights)*10)
    ax.set_xlim(0, max_end_time)
    for i in range(len(jobs)):
        ax.broken_barh([jobs[i]], (i*10, 9), facecolors='tab:blue')
        ax.text(jobs[i][0]+jobs[i][1]/2, i*10+2.5, str(weights[i]), fontsize=12, verticalalignment='center', horizontalalignment='center')

    plt.show()
    if save:
        fig.savefig(f"{file}.png")

if __name__ == "__main__":
    print(sys.argv[1])
    read_input(sys.argv[1])
    if len(sys.argv) > 2 and sys.argv[2] == "save":
        plot(True)
    else:
        plot()