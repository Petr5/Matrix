import matplotlib.pyplot as plt


def f(x:int):
    return x * x


def test():
    x = my_list(range(1, 1000))
    y = []
    for el in x:
        res = f(el)
        y.append(res)
    plt.plot(x, y)
    plt.show()


if __name__ == '__main__':
    my_list = [1, 2]
    plt.title("Dependency time of sum square matrices from size") #Dependency time of difference matrices with fixed length from height
    plt.xlabel("size of matrix")
    plt.ylabel("time, s")
    name = "-"
    for count_thread in my_list:
        x = []
        y = []
        path = "C:\\Users\\petrm\\CLionProjects\\Lab8\\cmake-build-debug\\" + str(count_thread) + name + "O(n^2)BiggerStepThread_Distribution.txt"
        f = open(path)
        for line in f.readlines():
            two_values = list(map(float, line.strip().split("\t")))
            x.append(two_values[0])
            y.append(two_values[1])
        plt.plot(x, y,  label=str(count_thread) + "Thread")
        f.close()

    plt.legend()
    plt.show()
