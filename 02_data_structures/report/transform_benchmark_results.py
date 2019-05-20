import pandas
import json
import matplotlib.pyplot as plt

fname = "/tmp/result"

pandas.set_option('display.max_rows', 500)
pandas.set_option('display.max_columns', 500)
pandas.set_option('display.width', 1000)

def extractMethodName(name):
    return name.split("_")[2]


def extractType(name):
    type_name = name[name.find("<")+1:name.rfind(">")]

    splitted = name.split("/")
    if len(splitted) == 3:
        type_parameter = splitted[2]
    else:
        type_parameter = ""
    return "{0}({1})".format(type_name, type_parameter)


def extractN(name):
    return int(name.split("/")[1])


def buildDataFrame():
    with open(fname) as fd:
        data = json.load(fd)["benchmarks"]
    src = pandas.DataFrame(data)

    # данные графиков
    df = src[pandas.notnull(src["cpu_time"])][["name", "cpu_time"]]
    df["method"] = df["name"].apply(extractMethodName)
    df["type"] = df["name"].apply(extractType)
    df["n"] = df["name"].apply(extractN)
    df = df.drop(columns="name")
    df = df[["method", "type", "n", "cpu_time"]]

    return df


def buildComplexity():
    with open(fname) as fd:
        data = json.load(fd)["benchmarks"]
    src = pandas.DataFrame(data)

    # вычислительная сложность
    df = src[pandas.notnull(src["big_o"])][["name", "big_o"]]
    print(df)
    df["method"] = df["name"].apply(extractMethodName)
    df["type"] = df["name"].apply(extractType)
    df = df.drop(columns="name")
    df = df[["method", "type", "big_o"]]

    return df


def renderDataFrame(df, method_name):
    print("\n\n")
    print(method_name)
    pivot = df[df["method"] == method_name].pivot(
        index="n", columns="type", values="cpu_time")
    print(pivot)
    axes = pivot.plot(kind="line", title="DynamicArray.{}".format(
        method_name), logx=True, logy=True)
    axes.set_ylabel("nanoseconds")
    lgd = axes.legend(loc='center right', bbox_to_anchor=(1.5, 0.5))
    axes.figure.savefig("/tmp/" + method_name + ".png",
                        bbox_extra_artists=(lgd,), bbox_inches='tight')


def main():
    cf = buildComplexity()
    print(cf)

    df = buildDataFrame()
    df.to_csv("/tmp/benchmark.csv")
    for method_name in df["method"].unique().tolist():
        renderDataFrame(df, method_name)


if __name__ == "__main__":
    main()
